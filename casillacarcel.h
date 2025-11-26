#ifndef CASILLA_CARCEL_H
#define CASILLA_CARCEL_H

#include "Casilla.h"

class CasillaCarcel : public Casilla {
public:
    CasillaCarcel(int n);
    void ejecutarAccion(Jugador* jugador) override;
    string tipo() const override;
};

#endif
