#ifndef MAQUINA_H
#define MAQUINA_H

#endif // MAQUINA_H

#include "Estructuras.h"
#pragma once
#include <QThread>
#include <QMutex>

class Maquina : public QThread{

protected:
    int velocidad;
    bool estado;
    ListaTiposBotellas * tiposDeBotellas;
    ColaBandaTransportadora * colaEntrada;
    ColaBandaTransportadora * colaSalida;
    QMutex mutex;

public:
    Maquina(int, ColaBandaTransportadora *, ColaBandaTransportadora *);
    int  modificarVelocidad(int);
    bool modificarEstado   (bool);
    void agregarListaTiposBotellas(ListaTiposBotellas *);
    ListaTiposBotellas * obtenerListaTiposBotellas(void);
    int aumentarTipoBotella(TipoBotella *);
    void run(void);
    int obtenerAleatorio(void);
};
