#include "Controlador.h"
#include "limpiabotellas.h"
#include "tapadora.h"

Controlador::Controlador(int velociadaPersona1, int velocidadPersona2, int velocidadLimpiadora, int velocidadLlenadora1, int velocidadLlenadora2,
                         int velociadaTapadora, int cantidaMaximaCola1, int cantidaMaximaCola2, int cantidaMaximaCola3, int cantidaMaximaCola4, int cantidaMaximaCola5){
    this->estado = 4;

    cola1 = new ColaBandaTransportadora(cantidaMaximaCola1);
    cola2 = new ColaBandaTransportadora(cantidaMaximaCola2);
    cola3 = new ColaBandaTransportadora(cantidaMaximaCola3);
    cola4 = new ColaBandaTransportadora(cantidaMaximaCola4);
    cola5 = new ColaBandaTransportadora(cantidaMaximaCola5);

    cargaBotellas = new CargaBotellas(velociadaPersona1, cola1);
    inspector = new Inspector(velocidadPersona2, cola5);

    limpiadora = new LimpiaBotellas(velocidadLimpiadora, cola1, cola2, cola3);
    llenadora1 = new Maquina(velocidadLlenadora1, cola2, cola4);
    llenadora2 = new Maquina(velocidadLlenadora2, cola3, cola4);
    tapadora = new Maquina(velociadaTapadora, cola4, cola5);
}

void Controlador::run(){
    while(true){
        mutex.lock();
        if(this->estado == 1){ //PLAY
            cargaBotellas->start();
            inspector->start();
            limpiadora->start();
            llenadora1->start();
            llenadora2->start();
            tapadora->start();
            this->estado = 3;
        }else if(this->estado == 2){//PAUSA
            cargaBotellas->modificarEstado(false);
            inspector->modificarEstado(false);
            limpiadora->modificarEstado(false);
            tapadora->modificarEstado(false);
            llenadora1->modificarEstado(false);
            llenadora2->modificarEstado(false);
            this->estado = 3;
        }else{

        }
        this->sleep(1);

        mutex.unlock();
    }
}

void Controlador::cambiarEstado(int estadoNuevo){
    this->estado = estadoNuevo;
}

void Controlador::modificarParametros(int velociadaPersona1, int velocidadPersona2, int velocidadLimpiadora, int velocidadLlenadora1, int velocidadLlenadora2,
                                      int velociadaTapadora, int cantidaMaximaCola1, int cantidaMaximaCola2, int cantidaMaximaCola3, int cantidaMaximaCola4,
                                      int cantidaMaximaCola5){
    cola1->modificarCantidadMaxima(cantidaMaximaCola1);
    cola2->modificarCantidadMaxima(cantidaMaximaCola2);
    cola3->modificarCantidadMaxima(cantidaMaximaCola3);
    cola4->modificarCantidadMaxima(cantidaMaximaCola4);
    cola4->modificarCantidadMaxima(cantidaMaximaCola5);

    cargaBotellas->modificarVelocidad(velociadaPersona1);
    inspector->modificarVelocidad(velocidadPersona2);

    limpiadora->modificarVelocidad(velocidadLimpiadora);
    llenadora1->modificarVelocidad(velocidadLlenadora1);
    llenadora2->modificarVelocidad(velocidadLlenadora2);
    tapadora->modificarVelocidad(velociadaTapadora);
}
