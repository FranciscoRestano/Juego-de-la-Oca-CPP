#ifndef CASILLA_CALAVERA_H
#define CASILLA_CALAVERA_H

#include "Casilla.h"

class CasillaCalavera : public Casilla {
public:
    CasillaCalavera(int n);
    void ejecutarAccion(Jugador* jugador) override;
    string tipo() const override;
};

#endif
