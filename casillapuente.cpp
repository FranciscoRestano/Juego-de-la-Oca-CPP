#include "CasillaPuente.h"
#include <iostream>
#include "jugador.h"
using namespace std;

CasillaPuente::CasillaPuente(int n) : Casilla(n) {}

void CasillaPuente::ejecutarAccion(Jugador* jugador) {
    cout << "Casilla " << numero << ": ¡Del puente a la posada" << endl;
    jugador->setPos(12);
}

string CasillaPuente::tipo() const {
    return "Puente";
}
