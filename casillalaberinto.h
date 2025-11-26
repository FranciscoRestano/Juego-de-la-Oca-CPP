#ifndef CASILLA_LABERINTO_H
#define CASILLA_LABERINTO_H

#include "Casilla.h"

class CasillaLaberinto : public Casilla {
public:
    CasillaLaberinto(int n);
    void ejecutarAccion(Jugador* jugador) override;
    string tipo() const override;
};

#endif
