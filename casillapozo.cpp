#include "CasillaPozo.h"
#include <iostream>
#include "jugador.h"
using namespace std;

CasillaPozo::CasillaPozo(int n) : Casilla(n) {}

void CasillaPozo::ejecutarAccion(Jugador* jugador) {
    cout << "Casilla " << numero << ": Caíste en el pozo, quedás atrapado hasta que otro jugador caiga." << endl;
    jugador->caerEnPozo();
}

string CasillaPozo::tipo() const {
    return "Pozo";
}
