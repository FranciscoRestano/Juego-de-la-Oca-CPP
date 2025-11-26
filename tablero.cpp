#include "Tablero.h"
#include "CasillaNormal.h"
#include "CasillaOca.h"
#include "CasillaPuente.h"
#include "CasillaPosada.h"
#include "CasillaPozo.h"
#include "CasillaLaberinto.h"
#include "CasillaCarcel.h"
#include "CasillaCalavera.h"
#include "CasillaJardinOca.h"
#include <cstdlib> // Para rand()

Tablero::Tablero(int cantCasillas, bool modoAleatorio) {
    this->cantidadCasillas = cantCasillas;
    casillas.resize(cantidadCasillas + 1, nullptr);

    // Creamos TODAS las casillas como normales
    for (int i = 1; i <= cantidadCasillas; i++) {
        casillas[i] = new CasillaNormal(i);
    }

    auto reemplazar = [&](int n, Casilla* nueva) {
        if (n <= cantidadCasillas) {
            delete casillas[n];
            casillas[n] = nueva;
        }
    };

    // La ÚLTIMA casilla SIEMPRE es el Jardin de la OCA
    reemplazar(cantidadCasillas, new CasillaJardinOca(cantidadCasillas));


    // Decidimos cómo poner las casillas especiales
    if (modoAleatorio) {

        for (int i = 2; i < cantidadCasillas; i++) { // de 2 a la anteúltima
            int chance = rand() % 20;
            switch (chance) {
            case 0: reemplazar(i, new CasillaOca(i)); break;
            case 1: reemplazar(i, new CasillaPosada(i)); break;
            case 2: reemplazar(i, new CasillaPozo(i)); break;
            case 3: reemplazar(i, new CasillaLaberinto(i)); break;
            case 4: reemplazar(i, new CasillaCarcel(i)); break;
            case 5: reemplazar(i, new CasillaCalavera(i)); break;
            }
        }
    } else {
        // SEGUNDA FORMA
        // Ponemos las casillas CLÁSICAS
        if (cantidadCasillas >= 63) {
            reemplazar(6,  new CasillaPuente(6));
            reemplazar(9,  new CasillaOca(9));
            reemplazar(18, new CasillaOca(18));
            reemplazar(19, new CasillaPosada(19));
            reemplazar(27, new CasillaOca(27));
            reemplazar(31, new CasillaPozo(31));
            reemplazar(36, new CasillaOca(36));
            reemplazar(42, new CasillaLaberinto(42));
            reemplazar(45, new CasillaOca(45));
            reemplazar(54, new CasillaOca(54));
            reemplazar(56, new CasillaCarcel(56));
            reemplazar(58, new CasillaCalavera(58));

            if (cantidadCasillas == 63) {
                reemplazar(63, new CasillaJardinOca(63));
            }
        }

        //  Rellenamos el SOBRANTE con casillas al azar
        // (Solo si el tablero es MÁS GRANDE que 63)
        if (cantidadCasillas > 63) {
            // Empezamos desde la 64 hasta la anteúltima
            for (int i = 64; i < cantidadCasillas; i++) {
                int chance = rand() % 20; // 5% de chance
                switch (chance) {
                case 0: reemplazar(i, new CasillaOca(i)); break;
                case 1: reemplazar(i, new CasillaPosada(i)); break;
                case 2: reemplazar(i, new CasillaPozo(i)); break;
                case 3: reemplazar(i, new CasillaLaberinto(i)); break;
                case 4: reemplazar(i, new CasillaCarcel(i)); break;
                case 5: reemplazar(i, new CasillaCalavera(i)); break;
                }
            }
        }
    }
}

// Destructor
Tablero::~Tablero() {
    for (int i = 1; i <= cantidadCasillas; i++) {
        delete casillas[i];
    }
}

Casilla* Tablero::getCasilla(int posicion) {
    if (posicion < 1) return casillas[1];
    if (posicion > cantidadCasillas) return casillas[cantidadCasillas];
    return casillas[posicion];
}

int Tablero::getCantidadCasillas() const {
    return cantidadCasillas;
}
