#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#endif // CONTROLADOR_H

#include <QThread>
#include <QMutex>
#include "CargaBotellas.h"
#include "Inspector.h"
#include "Maquina.h"
#include "Estructuras.h"
#include <QDebug>

class Controlador: public QThread{

private:
    int estado;
    void run();

public:    
    Controlador(int velociadaPersona1, int velocidadPersona2, int velocidadLimpiadora, int velocidadLlenadora1, int velocidadLlenadora2,
                int velociadaTapadora, int cantidaMaximaCola1, int cantidaMaximaCola2, int cantidaMaximaCola3, int cantidaMaximaCola4, int cantidaMaximaCola5);
    QMutex mutex;
    void cambiarEstado(int);
    void modificarParametros(int velociadaPersona1, int velocidadPersona2, int velocidadLimpiadora, int velocidadLlenadora1, int velocidadLlenadora2,
                             int velociadaTapadora, int cantidaMaximaCola1, int cantidaMaximaCola2, int cantidaMaximaCola3, int cantidaMaximaCola4, int cantidaMaximaCola5);
    CargaBotellas *cargaBotellas;
    Inspector *inspector;

    Maquina *limpiadora;
    Maquina *llenadora1;
    Maquina *llenadora2;
    Maquina *tapadora;

    ColaBandaTransportadora *cola1;
    ColaBandaTransportadora *cola2;
    ColaBandaTransportadora *cola3;
    ColaBandaTransportadora *cola4;
    ColaBandaTransportadora *cola5;
};
