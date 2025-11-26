#include "CasillaNormal.h"
#include <iostream>
using namespace std;

CasillaNormal::CasillaNormal(int n) : Casilla(n) {}

void CasillaNormal::ejecutarAccion(Jugador* jugador) {
    cout << "Casilla " << numero << ": Normal." << endl;
}

string CasillaNormal::tipo() const {
    return "Normal";
}
