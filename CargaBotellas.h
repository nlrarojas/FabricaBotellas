#ifndef PERSONA_H
#define PERSONA_H

#endif // PERSONA_H

#include "Estructuras.h"
#pragma once
#include <QThread>
#include <QMutex>
#include <random>

//Hereda de QThread
class CargaBotellas : public QThread{

    /*
     *Variables globales
     *La clase tiene una lista de probabilidades : probabilidades de tipo Estructuras/ListaProbabilidades
     *Una lista de tipos de botellas: tiposBotellas de tipo Estructuras/ListaTiposBotellas
     *Una cola de botellas, la cual va a ser modificada : cola de tipo Estructuras/ColaBandaTransportadora
     *Una velociadad que especifica el tiempo en que el hilo actua velociad de tipoint
     *Una variable de tipo QMutex para el ThreadSafe
     *Una variable que especifica el estado del hilo de ejecucion : estado de tipo bool
    */
private:
    ListaProbabilidades * probabilidades;
    ListaTiposBotellas * tiposBotellas;
    int velocidad;

    QMutex mutex;
    ColaBandaTransportadora * cola;
public:
    bool estado;
    CargaBotellas(int, ColaBandaTransportadora *);
    void modificarVelocidad(int);
    void modificarEstado(bool);
    void agregarListaProbabilidades(ListaProbabilidades *);
    ListaProbabilidades * obtenerListaProbabilidades(void);
    void agregarListaBotellas(ListaTiposBotellas *);
    ListaTiposBotellas * obtenerListaBotellas(void);
    void run(void);
    QString tipoBotellaSeleccionada(void);
};
