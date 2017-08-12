#include "Inspector.h"
#include <QDebug>

Inspector::Inspector(int velocidad, ColaBandaTransportadora * cola){
    this->velocidad = velocidad;
    this->estado = false;
    this->cola = cola;
}

void Inspector::modificarVelocidad(int velocidad){
    this->velocidad = velocidad;
}

void Inspector::modificarEstado(bool estado){
     this->estado = estado;
}

void Inspector::agregarListaProbabilidades(ListaProbabilidades * listaProbabilidades){
    this->probabilidades = listaProbabilidades;
}

ListaProbabilidades * Inspector::obtenerListaProbabilidades(){
    return this->probabilidades;
}

void Inspector::agregarListaBotellas(ListaTiposBotellas * lista){
    this->tiposBotellas = lista;
}

ListaTiposBotellas * Inspector::obtenerListaBotellas(){
    return this->tiposBotellas;
}

void Inspector::run(){
    while(true){
        while(this->estado){
            mutex.lock();

            if(cola->cantidadActual - 1 > 0){
                Botella * temporal = cola->desEncolar();
                if(Inspector::tipoBotellaASerRechazada(temporal)){
                    tiposBotellas->aumentarCantidad(new TipoBotella(temporal->tipoBotella, temporal->medida, 0, 0));
                }else{
                    tiposBotellas->aumentarCantidadRechazadas(new TipoBotella(temporal->tipoBotella, temporal->medida, 0, 0));
                }
            }

            this->sleep(this->velocidad);
            mutex.unlock();
        }
    }

}

bool Inspector::tipoBotellaASerRechazada(Botella * botella){
    Probabilidad * temporal = this->probabilidades->obtenerPorTipo(botella->tipoBotella);

    qDebug() << temporal->probabilidadBotella;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 100);
    int random = dis(gen);

    if(random < temporal->probabilidadBotella){
        return false;
    }else{
        return true;
    }
}
