#ifndef TABLERO_H
#define TABLERO_H

#include <vector>
#include "Casilla.h"
#include "Jugador.h"
using namespace std;

class Tablero {
private:
    vector<Casilla*> casillas;
    int cantidadCasillas;

public:
    Tablero(int cantCasillas, bool modoAleatorio);

    ~Tablero();

    Casilla* getCasilla(int posicion);
    int getCantidadCasillas() const;
};

#endif
