#include "CasillaCarcel.h"
#include "Jugador.h"
#include <iostream>
using namespace std;

CasillaCarcel::CasillaCarcel(int n) : Casilla(n) {}

void CasillaCarcel::ejecutarAccion(Jugador* jugador) {
    cout << "Casilla " << numero << ": Estás en la cárcel, perdés 2 turnos." << endl;
    jugador->setTurnosPerdidos(2);
}

string CasillaCarcel::tipo() const {
    return "Carcel";
}
