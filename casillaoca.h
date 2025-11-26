#ifndef CASILLA_OCA_H
#define CASILLA_OCA_H

#include "Casilla.h"

class CasillaOca : public Casilla {
public:
    CasillaOca(int n);
    void ejecutarAccion(Jugador* jugador) override;
    string tipo() const override;
};

#endif
