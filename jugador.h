#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include <QDataStream>
using namespace std;

class Jugador {
private:
    string nombre;
    int posicion;
    int turnosPerdidos;
    bool atrapadoEnPozo;
    bool puedeRepetirTurno;
    bool esGanador;

public:
    // Constructor
    Jugador(const string& n);

    // Getters
    string getNombre() const;
    int getPos() const;
    int getTurnosPerdidos() const;
    bool estaAtrapadoEnPozo() const;
    bool puedeVolverATirar() const;
    bool gano() const;

    // Acciones del jugador
    void setPos(int nuevaPos);
    void setTurnosPerdidos(int cantidad);
    void restarTurno();
    void caerEnPozo();
    void liberarDelPozo();
    void habilitarRepeticion();
    void deshabilitarRepeticion();
    void marcarGanador();

    // para guardar juego
    void guardar(QDataStream &out) const;
    void cargar(QDataStream &in);
};

#endif // JUGADOR_H
