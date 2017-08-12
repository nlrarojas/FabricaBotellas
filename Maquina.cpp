#include "Maquina.h"
#include <QDebug>

Maquina::Maquina(int velocidad, ColaBandaTransportadora * cola1, ColaBandaTransportadora * cola2){
    this->velocidad = velocidad;
    this->estado = false;
    this->colaEntrada = cola1;
    this->colaSalida = cola2;
}

int Maquina::modificarVelocidad(int velocidad){
    this->velocidad = velocidad;
    return this->velocidad;
}

bool Maquina::modificarEstado(bool estado){
    this->estado = estado;
    return this->estado;
}

void Maquina::agregarListaTiposBotellas(ListaTiposBotellas * listaTipos){
    this->tiposDeBotellas = listaTipos;
}

ListaTiposBotellas * Maquina::obtenerListaTiposBotellas(void){
    return this->tiposDeBotellas;
}

int Maquina::aumentarTipoBotella(TipoBotella * tipoBotella){
    return this->tiposDeBotellas->aumentarCantidad(tipoBotella);
}

void Maquina::run(){
    while(true){
        while(this->estado){
            mutex.lock();
            Botella * temporal;
            if(colaEntrada->cantidadActual > 0 && (colaSalida->cantidadActual + 1 <= colaSalida->cantiadadMaxima)){
                try{
                    temporal = colaEntrada->desEncolar();
                    tiposDeBotellas->aumentarCantidad(new TipoBotella(temporal->tipoBotella, temporal->medida, 0,0));
                    colaSalida->encolar(temporal);
                }catch(exception e){
                    qDebug() << e.what();
                }
            }
            if(!this->estado){
                break;
            }
            this->sleep(this->velocidad);
            mutex.unlock();
        }
    }
}

int Maquina::obtenerAleatorio(){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 2);
    return dis(gen);
}

