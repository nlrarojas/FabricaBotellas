#include "limpiabotellas.h"
#include <QDebug>

LimpiaBotellas::LimpiaBotellas(int cantidadMaxima, ColaBandaTransportadora * cola1, ColaBandaTransportadora * cola2, ColaBandaTransportadora * colaEspecial)
    :Maquina::Maquina(cantidadMaxima, cola1, cola2)
{
    this->colaEspecial = colaEspecial;
}

void LimpiaBotellas::run(){
    while(true){
        while(this->estado){
            mutex.lock();
            Botella * temporal;
            if(colaEntrada->cantidadActual > 0 && (colaSalida->cantidadActual + 1 <= colaSalida->cantiadadMaxima || colaEspecial->cantidadActual + 1 <= colaEspecial->cantiadadMaxima)){
                try{
                    temporal = colaEntrada->desEncolar();
                    tiposDeBotellas->aumentarCantidad(new TipoBotella(temporal->tipoBotella, temporal->medida, 0,0));
                }catch(exception e){
                    qDebug() << e.what();
                }

                if(this->obtenerAleatorio() == 1 && colaSalida->cantidadActual + 1 <= colaSalida->cantiadadMaxima){
                    colaSalida->encolar(temporal);
                }else{
                    if(colaEspecial->cantidadActual + 1 <= colaEspecial->cantiadadMaxima){
                        colaEspecial->encolar(temporal);
                    }
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
