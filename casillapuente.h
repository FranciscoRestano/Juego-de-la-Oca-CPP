#ifndef CASILLA_PUENTE_H
#define CASILLA_PUENTE_H

#include "Casilla.h"

class CasillaPuente : public Casilla {
public:
    CasillaPuente(int n);
    void ejecutarAccion(Jugador* jugador) override;
    string tipo() const override;
};

#endif
