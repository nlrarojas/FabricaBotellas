#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <iostream>
#include <QDialog>

using namespace std;

struct TipoBotella;             //Nodo lista doblemente enlazada circular(ListaTiposBotellas)
struct ListaTiposBotellas;      //Lista Doblemente enlazada circular
struct Botella;                 //Nodo de la cola de las bandas transportadoras
struct ColaBandaTransportadora; //Cola de las bandas transportadoras almacena botellas
struct Probabilidad;            //Probabilidad de que sea seleccionada una botella
struct ListaProbabilidades;     //Lista de probabilidades que contendrá el inspector de calidad.

struct TipoBotella{
    QString tipoBotellas;
    QString medida;
    int cantidadAceptadas;
    int cantidadRechazadas;

    TipoBotella * siguiente, * anterior;

    TipoBotella(QString pTipoBotella, QString pMedida, int aceptadas, int rechazadas){
        this->tipoBotellas = pTipoBotella;
        this->medida = pMedida;
        this->cantidadAceptadas = aceptadas;
        this->cantidadRechazadas = rechazadas;
        this->siguiente = this->anterior = NULL;
    }
};

struct ListaTiposBotellas{
    TipoBotella * primerNodo;

    ListaTiposBotellas(){
        primerNodo = NULL;
    }

    bool insertar(QString tipoBotella, QString medida, int aceptadas, int rechazadas);
    void imprimir(void);
    TipoBotella * borrar(QString tipoBotella, QString medida);
    TipoBotella * buscar(QString tipoBotella, QString medida);
    int aumentarCantidad(TipoBotella *);
    int aumentarCantidadRechazadas(TipoBotella *);
    int size(void);
    bool isEmpty(void);
    TipoBotella * obtenerPorTipo(QString);
};

struct Botella{
    int idBotella;
    QString tipoBotella;
    QString medida;

    Botella * siguiente;

    Botella (int id, QString tipoBotella, QString medida){
        this->idBotella = id;
        this->tipoBotella = tipoBotella;
        this->medida = medida;
        this->siguiente = NULL;
    }
};

struct ColaBandaTransportadora{
    int cantiadadMaxima;
    int cantidadActual;

    Botella * frente, * fondo;

    ColaBandaTransportadora(int cantidadMaxima){
        this->cantiadadMaxima = cantidadMaxima;
        this->cantidadActual = 0;
        this->frente = this->fondo = NULL;
    }

    bool isEmpty(void);
    void encolar(Botella *);
    Botella * desEncolar(void);
    void modificarCantidadMaxima(int);
    int obtenerCantidadMaxima(void);
    int obtenerCantidadActual(void);
};

struct Probabilidad{
    QString tipo;
    int probabilidadBotella;

    Probabilidad * siguiente, * anterior;

    Probabilidad(QString tipo, int probabilidadBotella){
        this->tipo = tipo;
        this->probabilidadBotella = probabilidadBotella;
        this->anterior = this->siguiente = NULL;
    }
};

struct ListaProbabilidades{
    Probabilidad * primerNodo, * ultimoNodo;

    ListaProbabilidades(){
        primerNodo = ultimoNodo = NULL;
    }

    void insertarAlInicio(QString, int);
    void insertarAlFinal (QString, int);
    Probabilidad * borrarAlInicio(void);
    Probabilidad * borrarAlFinal (void);
    int size(void);
    Probabilidad * obtenerPorIndex(int);
    Probabilidad * obtenerPorTipo(QString);
};

#endif // ESTRUCTURAS_H
