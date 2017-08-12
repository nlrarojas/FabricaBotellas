#include "Estructuras.h"

//Lista de tipos de botellas

bool ListaTiposBotellas::insertar(QString tipoBotella, QString medida, int aceptadas, int rechazadas){
    if(ListaTiposBotellas::obtenerPorTipo(tipoBotella) == NULL){
        if(primerNodo == NULL){
            primerNodo = new TipoBotella(tipoBotella, medida, aceptadas, rechazadas);
            primerNodo->siguiente = primerNodo;
            primerNodo->anterior = primerNodo;
        }else{
            TipoBotella * nuevo = new TipoBotella(tipoBotella, medida, aceptadas, rechazadas);
            nuevo->siguiente = primerNodo->siguiente;
            nuevo->anterior = primerNodo;
            primerNodo->siguiente = nuevo;
            nuevo->siguiente->anterior = nuevo;
        }
        return true;
    }
    return false;
}

TipoBotella * ListaTiposBotellas::borrar(QString tipoBotella, QString medida){
    if(primerNodo != NULL){
        TipoBotella * buscado = ListaTiposBotellas::buscar(tipoBotella, medida);
        buscado->anterior->siguiente = buscado->siguiente;
        buscado->siguiente->anterior = buscado->anterior;
        buscado->anterior = buscado->siguiente = NULL;
        return buscado;
    }
    return NULL;
}

TipoBotella * ListaTiposBotellas::buscar(QString tipoBotella, QString medida){
    if(primerNodo != NULL){
        TipoBotella * temporal = primerNodo;
        do{
            if(temporal->tipoBotellas == tipoBotella && temporal->medida == medida){
                return temporal;
            }
            temporal = temporal->siguiente;
        }while(temporal != primerNodo);
    }
    return NULL;
}

int ListaTiposBotellas::aumentarCantidad(TipoBotella * tipoBotella){
    TipoBotella * temporal = buscar(tipoBotella->tipoBotellas, tipoBotella->medida);
    if(temporal != NULL){
        return temporal->cantidadAceptadas++;
    }else{
        return -1;
    }
}

int ListaTiposBotellas::aumentarCantidadRechazadas(TipoBotella * tipoBotella){
    TipoBotella * temporal = buscar(tipoBotella->tipoBotellas, tipoBotella->medida);
    if(temporal != NULL){
        return temporal->cantidadRechazadas++;
    }else{
        return -1;
    }
}

int ListaTiposBotellas::size(){
    int contador = 0;
    if(primerNodo == NULL){
        return contador;
    }else{
        TipoBotella * temporal = primerNodo->siguiente;
        do{
            contador++;
            temporal = temporal->siguiente;
        }while(temporal != primerNodo);
        return contador;
    }
}

bool ListaTiposBotellas::isEmpty(void){
    return primerNodo == NULL;
}

TipoBotella * ListaTiposBotellas::obtenerPorTipo(QString tipo){
    if(ListaTiposBotellas::isEmpty()){
        return NULL;
    }else{
        TipoBotella * temporal = primerNodo;
        do{
            if(QString::compare(temporal->tipoBotellas, tipo) == 0){
                return temporal;
            }
            temporal = temporal->siguiente;
        }while(temporal != primerNodo);
        return NULL;
    }
}

//Fin lista de tipos de botellas

//Cola de las bandas transportadoras (almacenan botellas)

bool ColaBandaTransportadora::isEmpty(){
    return this->frente == NULL;
}

void ColaBandaTransportadora::encolar(Botella * nuevaBotella){
    if(isEmpty()){
        frente = fondo = nuevaBotella;
        cantidadActual++;
    }else{
        fondo->siguiente = nuevaBotella;
        nuevaBotella->siguiente = NULL;
        fondo = fondo->siguiente;
        cantidadActual++;
    }
}

Botella * ColaBandaTransportadora::desEncolar(){
    if(isEmpty()){
        return NULL;
    }else if(frente->siguiente == NULL){
        Botella * borrado = fondo;
        frente = fondo = NULL;
        cantidadActual--;
        return borrado;
    }else{
        Botella * temporal = frente;
        while(temporal->siguiente != fondo){
            temporal = temporal->siguiente;
        }
        Botella * borrado = fondo;
        fondo = temporal;
        fondo->siguiente = NULL;
        cantidadActual--;
        return borrado;
    }
}

void ColaBandaTransportadora::modificarCantidadMaxima(int cantiadad){
    this->cantiadadMaxima = cantiadad;
}

int ColaBandaTransportadora::obtenerCantidadMaxima(){
    return this->cantiadadMaxima;
}

int ColaBandaTransportadora::obtenerCantidadActual(){
    return this->cantidadActual;
}

//Fin cola de botellas de las bandas transportadoras

//Lista de probabilidades

void ListaProbabilidades::insertarAlInicio(QString tipo, int probabilidad){
    if(primerNodo == NULL){
        primerNodo = ultimoNodo = new Probabilidad(tipo, probabilidad);
    }else{
        Probabilidad * temporal = new Probabilidad(tipo, probabilidad);
        temporal->siguiente = primerNodo;
        primerNodo->anterior = temporal;
        primerNodo = temporal;
    }
}

void ListaProbabilidades::insertarAlFinal(QString tipo, int probabilidad){
    if(primerNodo == NULL){
        primerNodo = ultimoNodo = new Probabilidad(tipo, probabilidad);
    }else{
        ultimoNodo->siguiente = new Probabilidad(tipo, probabilidad);
        ultimoNodo->siguiente->anterior = ultimoNodo;
        ultimoNodo = ultimoNodo->siguiente;
    }
}

Probabilidad * ListaProbabilidades::borrarAlInicio(){
    if(primerNodo == NULL){
        return NULL;
    }else{
        Probabilidad * borrado = primerNodo;
        primerNodo = primerNodo->siguiente;

        if(primerNodo != NULL){
            primerNodo->anterior = NULL;
        }else{
            ultimoNodo = NULL;
        }

        borrado->siguiente = NULL;
        return borrado;
    }
}

Probabilidad * ListaProbabilidades::borrarAlFinal(){
    Probabilidad * temporal = ultimoNodo;
    if(ultimoNodo != NULL){
        ultimoNodo = ultimoNodo->anterior;
        temporal->anterior = NULL;
        temporal->siguiente = NULL;

        if(ultimoNodo != NULL){
            ultimoNodo->siguiente = NULL;
        }else{
            primerNodo = NULL;
        }
    }
    return temporal;
}

int ListaProbabilidades::size(){
    int cantidad = 0;
    if(primerNodo == NULL){
        return cantidad;
    }else{
        Probabilidad * temporal = primerNodo;

        while (temporal != NULL){
            cantidad++;
            temporal = temporal->siguiente;
        }
        return cantidad;
    }
}

Probabilidad * ListaProbabilidades::obtenerPorIndex(int index){
    if(primerNodo == NULL){
        return NULL;
    }else{
        Probabilidad * temporal = primerNodo;
        int contador = 0;
        while(temporal != NULL){
            if(contador == index){
                return temporal;
            }
            contador++;
            temporal = temporal->siguiente;
        }
        return NULL;
    }
}

Probabilidad * ListaProbabilidades::obtenerPorTipo(QString tipo){
    if(primerNodo == NULL){
        return NULL;
    }else{
        Probabilidad * temporal = primerNodo;
        while(temporal != NULL){
            if(temporal->tipo == tipo){
                return temporal;
            }
            temporal = temporal->siguiente;
        }
        return NULL;
    }
}
