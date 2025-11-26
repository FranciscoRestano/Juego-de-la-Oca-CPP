#ifndef CASILLA_JARDINOCA_H
#define CASILLA_JARDINOCA_H

#include "Casilla.h"

class CasillaJardinOca : public Casilla {
public:
    CasillaJardinOca(int n);
    void ejecutarAccion(Jugador* jugador) override;
    string tipo() const override;
};

#endif
