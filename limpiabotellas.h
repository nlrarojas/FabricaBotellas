#ifndef LIMPIABOTELLAS_H
#define LIMPIABOTELLAS_H

#include "Maquina.h"
#include <random>

class LimpiaBotellas : public Maquina
{
public:
    LimpiaBotellas(int, ColaBandaTransportadora *, ColaBandaTransportadora *, ColaBandaTransportadora *);
    void run();
    ColaBandaTransportadora * colaEspecial;    
};

#endif // LIMPIABOTELLAS_H
