#include "salarios.h"
#include "ui_salarios.h"


Salarios::Salarios(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Salarios)
{
    ui->setupUi(this);
    m_contolador = new Controlador();
    m_porGuardar = false;
}

Salarios::~Salarios()
{
    delete ui;
}


void Salarios::on_btnCalcular_clicked()
{
    calcular();
}


void Salarios::on_actionNuevo_triggered()
{

    limpiar();

    ui->outCalculos->clear();

    ui->statusbar->showMessage("Nuevos cálculos de salario.", 3000);
}

void Salarios::limpiar()
{
    // Limpiar widgets
    ui->inNombre->setText("");
    ui->inHoras->setValue(0);
    ui->inMatutina->setChecked(true);
    ui->inNombre->setFocus();
}

void Salarios::calcular()
{

    QString nombre = ui->inNombre->text();
    int horas = ui->inHoras->value();
    TipoJornada jornada;
    if(ui->inMatutina->isChecked()){
        jornada = TipoJornada::Matituna;
    }else if (ui->inVespertina->isChecked()){
        jornada = TipoJornada::Vespertina;
    }else{
        jornada = TipoJornada::Nocturna;
    }

    if(nombre == "" || horas == 0){
        QMessageBox::warning(this,"Advertencia","El nombre y/o el número de horas es incorrecto");
        return;
    }


    m_contolador->setDatos(nombre, horas, jornada);

    if (m_contolador->calcular()) {

        ui->outCalculos->appendPlainText(m_contolador->getDatos());
        m_porGuardar = true;
    } else {
        QMessageBox::critical(
                    this,
                    "Error",
                    "No se puede calcular el salario.");
    }

    limpiar();

    ui->statusbar->showMessage("Salario de " + nombre + " calculado.",5000);




}

void Salarios::salir()
{
  if (m_porGuardar){
              int respuesta = QMessageBox::warning(
              this,"Salir",
              "Desea Guardar el Archivo", "Aceptar", "Cancelar");
              if(respuesta == QMessageBox::AcceptRole) {
          on_actionGuardar_triggered();
     }
  }
  this->close();
}


void Salarios::on_actionCalcular_triggered()
{
    calcular();
}


void Salarios::on_actionSalir_triggered()
{
    salir();
}


void Salarios::on_actionGuardar_triggered()
{

    QString nombreArchivo = QFileDialog::getSaveFileName(this,
                                                   "Guardar calculos de salarios",
                                                   QDir::home().absolutePath() + "/salarios.txt",
                                                   "Archivos de texto (*.txt)");
    // Crear un objeto File
    QFile archivo(nombreArchivo);
    // Tartar de abrir para escritura
    if(archivo.open(QFile::WriteOnly | QFile::Truncate)){

        QTextStream salida(&archivo);
        // Enviar los datos del resultado a la salida
        salida << ui->outCalculos->toPlainText();
        // Mostrar mensaje en la barra de estados
        ui->statusbar->showMessage("Datos guardados en: " + nombreArchivo, 5000);
        // Cerrar el archivo
        archivo.close();
        m_porGuardar = false;
    }else {
        // Mensaje de error
        QMessageBox::warning(this,
                             "Guardar archivo",
                             "No se puede acceder al archivo para guardar los datos.");
    }


}


void Salarios::on_actionAcerca_de_triggered()
{
    // Crear un objeto del cuadro de diálogo
    Acerca *dialog = new Acerca(this);
    // Enviar datos a la otra ventana
    dialog->setVersion(VERSION);
    // Mostrar la venta en modo MODAL
    dialog->exec();
    // Luego de cerrar la ventana se acceden a los datos de la misma
    qDebug() << dialog->valor();

}

