#ifndef CASILLA_H
#define CASILLA_H

#include <iostream>
#include <string>
using namespace std;

class Jugador; // declaración adelantada

class Casilla {
protected:
    int numero;
public:
    Casilla(int n);
    virtual ~Casilla();

    virtual void ejecutarAccion(Jugador* jugador) = 0;
    virtual string tipo() const = 0;

    int getNumero() const;
};

#endif
