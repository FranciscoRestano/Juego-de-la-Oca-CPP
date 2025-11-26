#include "dado.h"
#include <cstdlib> // Para rand() y srand()
#include <ctime>

Dado::Dado () {
    srand(time(0));
}
int Dado::lanzar(){
    return rand() % 6 + 1;
};
