#include "CargaBotellas.h"
#include <QDebug>

CargaBotellas::CargaBotellas(int velocidad, ColaBandaTransportadora * cola){
    this->velocidad = velocidad;
    this->estado = false;
    this->cola = cola;
}

void CargaBotellas::modificarVelocidad(int velocidad){
    this->velocidad = velocidad;
}

void CargaBotellas::modificarEstado(bool pEstado){
     this->estado = pEstado;
}

void CargaBotellas::agregarListaProbabilidades(ListaProbabilidades * listaProbabilidades){
    this->probabilidades = listaProbabilidades;
}

ListaProbabilidades * CargaBotellas::obtenerListaProbabilidades(){
    return this->probabilidades;
}

void CargaBotellas::agregarListaBotellas(ListaTiposBotellas * lista){
    this->tiposBotellas = lista;
}

ListaTiposBotellas * CargaBotellas::obtenerListaBotellas(){
    return this->tiposBotellas;
}

void CargaBotellas::run(){
    while(true){
        while(this->estado){
            mutex.lock();
            if(cola->cantidadActual + 1 <= cola->cantiadadMaxima){
                try{
                    TipoBotella * temporal = tiposBotellas->obtenerPorTipo(tipoBotellaSeleccionada());
                    cola->encolar(new Botella(cola->cantidadActual + 1, temporal->tipoBotellas, temporal->medida));
                    tiposBotellas->aumentarCantidad(new TipoBotella(temporal->tipoBotellas, temporal->medida, 0, 0));
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


QString CargaBotellas::tipoBotellaSeleccionada(){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 100);

    int total = 0;
    int cantiadadDeProbabilidades[probabilidades->size()];
    int i = 0;
    int random = dis(gen);

    Probabilidad * temporal = probabilidades->primerNodo;

    while(temporal != NULL){
        total += temporal->probabilidadBotella;
        cantiadadDeProbabilidades[i++] = total;
        temporal = temporal->siguiente;
    }

    for (int i = 0; i < probabilidades->size(); i++) {
        if(random < cantiadadDeProbabilidades[i]){
            return probabilidades->obtenerPorIndex(i)->tipo;
        }
    }
    return NULL;
}
