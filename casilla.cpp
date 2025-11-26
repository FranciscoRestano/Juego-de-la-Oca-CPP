#include "Casilla.h"

Casilla::Casilla(int n) : numero(n) {}

Casilla::~Casilla() {}

int Casilla::getNumero() const {
    return numero;
}
