#ifndef CASILLA_POZO_H
#define CASILLA_POZO_H

#include "Casilla.h"

class CasillaPozo : public Casilla {
public:
    CasillaPozo(int n);
    void ejecutarAccion(Jugador* jugador) override;
    string tipo() const override;
};

#endif
