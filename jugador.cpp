#include "Jugador.h"
#include <QString>
#include <QDebug>

Jugador::Jugador(const string& n)
    : nombre(n), posicion(1), turnosPerdidos(0), // Inicia en casilla 1
    atrapadoEnPozo(false), puedeRepetirTurno(false),
    esGanador(false) {}

string Jugador::getNombre() const { return nombre; }
int Jugador::getPos() const { return posicion; }
int Jugador::getTurnosPerdidos() const { return turnosPerdidos; }
bool Jugador::estaAtrapadoEnPozo() const { return atrapadoEnPozo; }
bool Jugador::puedeVolverATirar() const { return puedeRepetirTurno; }
bool Jugador::gano() const { return esGanador; }

void Jugador::setPos(int nuevaPos) { posicion = nuevaPos; }

void Jugador::setTurnosPerdidos(int cantidad) {
    turnosPerdidos = cantidad;
}

void Jugador::restarTurno() {
    if (turnosPerdidos > 0) {
        turnosPerdidos--;
    }
}

void Jugador::caerEnPozo() { atrapadoEnPozo = true; }
void Jugador::liberarDelPozo() { atrapadoEnPozo = false; }

void Jugador::habilitarRepeticion() { puedeRepetirTurno = true; }
void Jugador::deshabilitarRepeticion() { puedeRepetirTurno = false; }

void Jugador::marcarGanador() { esGanador = true; }

// Escribe el estado del jugador en el archivo
void Jugador::guardar(QDataStream &out) const
{
    // Escribimos en QString para compatibilidad
    out << QString::fromStdString(nombre);
    out << (qint32)posicion;
    out << (qint32)turnosPerdidos;
    out << (bool)atrapadoEnPozo;
    out << (bool)esGanador;
    out << (bool)puedeRepetirTurno;
}

// Lee el estado del jugador desde el archivo
void Jugador::cargar(QDataStream &in)
{
    QString qNombre;
    qint32 qPosicion, qTurnosPerdidos;
    bool qAtrapado, qGanador;
    bool qPuedeRepetirTurno;

    // Leemos en el MISMO ORDEN en que guardamos
    in >> qNombre;
    in >> qPosicion;
    in >> qTurnosPerdidos;
    in >> qAtrapado;
    in >> qGanador;
    in >> qPuedeRepetirTurno;

    // Actualizamos el objeto
    nombre = qNombre.toStdString();
    posicion = qPosicion;
    turnosPerdidos = qTurnosPerdidos;
    atrapadoEnPozo = qAtrapado;
    esGanador = qGanador;

    puedeRepetirTurno = qPuedeRepetirTurno;
}
