#include "CasillaPosada.h"
#include <iostream>
#include "jugador.h"
using namespace std;

CasillaPosada::CasillaPosada(int n) : Casilla(n) {}

void CasillaPosada::ejecutarAccion(Jugador* jugador) {
    cout << "Casilla " << numero << ": Caíste en la posada, perdés 1 turno." << endl;
    jugador->setTurnosPerdidos(1);
}

string CasillaPosada::tipo() const {
    return "Posada";
}
