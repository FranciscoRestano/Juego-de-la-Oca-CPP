#ifndef CASILLA_NORMAL_H
#define CASILLA_NORMAL_H

#include "Casilla.h"

class CasillaNormal : public Casilla {
public:
    CasillaNormal(int n);
    void ejecutarAccion(Jugador* jugador) override;
    string tipo() const override;
};

#endif
