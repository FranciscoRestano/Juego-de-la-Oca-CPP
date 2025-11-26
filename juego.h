#ifndef JUEGO_H
#define JUEGO_H

#include "Tablero.h"
#include "Jugador.h"
#include <vector>
#include "Dado.h"
#include <string>
#include <cstdlib>
#include <ctime>
#include <QDataStream>
using namespace std;

class Juego {
private:
    Tablero* tablero;
    vector<Jugador*> jugadores;
    int turnoActual;
    bool terminado;
    bool reglaSuma9Activada;

    Dado dado1;
    Dado dado2;
    int ultimaTirada1;
    int ultimaTirada2;

    // Configuracion del juego
    int config_cantCasillas;
    bool config_modoAleatorio;
    bool config_reglaSuma9;
public:
    Juego(int cantidadJugadores, int cantCasillas, bool modoAleatorio, bool reglaSuma9);
    ~Juego();

    Jugador* getJugador(int indice);
    Jugador* getJugadorActual();
    int getTurnoActual() const;

    string moverJugador(int pasos);
    void avanzarTurno();
    string jugarTurno ();
    bool estaTerminado() const;

    int getUltimaTirada1() const;
    int getUltimaTirada2() const;
    string getCasillaTipo(int numero) const;

    void guardarPartida(QDataStream &out) const;
    void cargarPartida(QDataStream &in);

    int getConfigCasillas() const { return config_cantCasillas; }
    int getConfigJugadores() const { return jugadores.size(); }

    bool getConfigModoAleatorio() const { return config_modoAleatorio; }
    bool getConfigReglaSuma9() const { return config_reglaSuma9; }
};

#endif
