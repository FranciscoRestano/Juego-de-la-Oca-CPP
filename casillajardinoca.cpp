#include "CasillaJardinOca.h"
#include "jugador.h"
#include <iostream>
using namespace std;

CasillaJardinOca::CasillaJardinOca(int n) : Casilla(n) {}

void CasillaJardinOca::ejecutarAccion(Jugador* jugador) {
    cout << "Casilla " << numero << ": ¡El jardín de la OCA! " << endl;

    jugador->marcarGanador();
}

string CasillaJardinOca::tipo() const {
    return "Jardin de la Oca";
}
