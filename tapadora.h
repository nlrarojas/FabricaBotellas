#ifndef TAPADORA_H
#define TAPADORA_H

#include "Maquina.h"

class Tapadora : public Maquina
{
public:
    Tapadora(int, ColaBandaTransportadora *, ColaBandaTransportadora *);
    void run(void);
};

#endif // TAPADORA_H
