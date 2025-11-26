#include "CasillaCalavera.h"
#include "Jugador.h"
#include <iostream>
using namespace std;

CasillaCalavera::CasillaCalavera(int n) : Casilla(n) {}

void CasillaCalavera::ejecutarAccion(Jugador* jugador) {
    cout << "Casilla " << numero << ": ¡Calavera! Volvés a la casilla 1." << endl;
    jugador->setPos(1);
}

string CasillaCalavera::tipo() const {
    return "Calavera";
}
