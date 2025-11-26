#ifndef CASILLA_POSADA_H
#define CASILLA_POSADA_H

#include "Casilla.h"

class CasillaPosada : public Casilla {
public:
    CasillaPosada(int n);
    void ejecutarAccion(Jugador* jugador) override;
    string tipo() const override;
};

#endif
