#include "controlador.h"

Controlador::Controlador(QObject *parent)
    : QObject{parent}
{
    this->m_modelo = nullptr;
}

void Controlador::setDatos(QString nombre, int horas, TipoJornada jornada)
{
    this->m_modelo = new Obrero(nombre, horas, jornada);
}

bool Controlador::calcular()
{

    if (m_modelo == nullptr)
        return false;


    double valorHora = 0;
    switch (m_modelo->jornada()) {
    case TipoJornada::Matituna:
        valorHora = MATUTINO;
        break;
    case TipoJornada::Vespertina:
        valorHora = VESPERTINO;
        break;
    case TipoJornada::Nocturna:
        valorHora = NOCTURNO;
        break;
    }


    int horas = m_modelo->horas();
    int horasExtra = 0;
    if (m_modelo->horas() > 40){
        horasExtra = m_modelo->horas() - 40;
        horas = 40;
    }


    double salarioBruto = horas * valorHora + (horasExtra * HORA_EXTRA);
    double descuento = salarioBruto * IESS / 100.0;
    double salarioNeto = salarioBruto - descuento;


    m_modelo->setSalarioBruto(salarioBruto);
    m_modelo->setDescuento(descuento);
    m_modelo->setSalarioNeto(salarioNeto);

    // Si todo va bien, retornamos true
    return true;
}

QString Controlador::getDatos()
{
    return m_modelo->toString();
}
