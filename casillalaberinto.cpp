#include "CasillaLaberinto.h"
#include "jugador.h"
#include <iostream>
using namespace std;

CasillaLaberinto::CasillaLaberinto(int n) : Casilla(n) {}

void CasillaLaberinto::ejecutarAccion(Jugador* jugador) {
    cout << "Casilla " << numero << ": ¡El laberinto te hace retroceder hasta la casilla 30!" << endl;
    jugador->setPos(30);
}

string CasillaLaberinto::tipo() const {
    return "Laberinto";
}
