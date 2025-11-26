#include "CasillaOca.h"
#include "Jugador.h"
#include <iostream>
using namespace std;

CasillaOca::CasillaOca(int n) : Casilla(n) {}

void CasillaOca::ejecutarAccion(Jugador* jugador) {
    cout << "Casilla " << numero << ": ¡De oca a oca y tiro porque me toca!" << endl;

    // Lógica para saltar a la siguiente oca
    int proximaOca = 0;
    switch (numero) {
    case 9:  proximaOca = 18; break;
    case 18: proximaOca = 27; break;
    case 27: proximaOca = 36; break;
    case 36: proximaOca = 45; break;
    case 45: proximaOca = 54; break;
    case 54: proximaOca = 63; break; // La última oca te lleva al Jardín
    }

    if (proximaOca != 0) {
        jugador->setPos(proximaOca);
        // Si la oca te hace ganar, lo marco
        if (proximaOca == 63) {
            jugador->marcarGanador();
        }
    }

    jugador->habilitarRepeticion();
}

string CasillaOca::tipo() const {
    return "Oca";
}
