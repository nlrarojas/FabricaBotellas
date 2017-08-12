#ifndef INSPECTOR_H
#define INSPECTOR_H

#endif // INSPECTOR_H
#include "Estructuras.h"
#pragma once
#include <QThread>
#include <QMutex>
#include <random>

class Inspector : public QThread{

private:
    ListaProbabilidades * probabilidades;
    ListaTiposBotellas * tiposBotellas;
    int velocidad;   
    QMutex mutex;
    ColaBandaTransportadora * cola;

public:
    bool estado;
    Inspector(int, ColaBandaTransportadora *);
    void modificarVelocidad(int);
    void modificarEstado(bool);
    void agregarListaProbabilidades(ListaProbabilidades *);
    ListaProbabilidades * obtenerListaProbabilidades(void);
    void agregarListaBotellas(ListaTiposBotellas *);
    ListaTiposBotellas * obtenerListaBotellas(void);
    void run(void);
    bool tipoBotellaASerRechazada(Botella *);
};
