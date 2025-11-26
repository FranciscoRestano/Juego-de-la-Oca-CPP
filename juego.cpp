#include "Juego.h"
#include "Casilla.h"
#include "Jugador.h"
#include <sstream>

Juego::Juego(int cantidadJugadores, int cantCasillas, bool modoAleatorio, bool reglaSuma9)
{
    // Creamos el tablero con las condiciones que elegimos
    tablero = new Tablero(cantCasillas, modoAleatorio);

    this->config_cantCasillas = cantCasillas;
    this->config_modoAleatorio = modoAleatorio;
    this->config_reglaSuma9 = reglaSuma9;

    this->reglaSuma9Activada = reglaSuma9;
    srand(time(nullptr));
    turnoActual = 0;
    terminado = false;
    ultimaTirada1 = 0;
    ultimaTirada2 = 0;

    for (int i = 0; i < cantidadJugadores; ++i) {
        string nombre = "Jugador " + to_string(i + 1);
        jugadores.push_back(new Jugador(nombre));
    }
}

// Destructor
Juego::~Juego() {
    for (auto j : jugadores)
        delete j;
    jugadores.clear();

    delete tablero;
}

Jugador* Juego::getJugador(int indice) {
    if (indice >= 0 && indice < (int)jugadores.size())
        return jugadores[indice];
    return nullptr;
}

Jugador* Juego::getJugadorActual() {
    return jugadores[turnoActual];
}

int Juego::getTurnoActual() const {
    return turnoActual;
}

string Juego::moverJugador(int pasos) {
    Jugador* jugador = getJugadorActual();
    int posActual = jugador->getPos();
    int nuevaPos = posActual + pasos;

    ostringstream narrador;

    if (nuevaPos > tablero->getCantidadCasillas()) {
        int rebote = nuevaPos - tablero->getCantidadCasillas();
        nuevaPos = tablero->getCantidadCasillas() - rebote;
        narrador << "¡Te pasaste! Rebotás a la casilla " << nuevaPos << ". ";
    } else if (nuevaPos == tablero->getCantidadCasillas()) {
        jugador->marcarGanador();
    }

    jugador->setPos(nuevaPos);

    Casilla* casilla = tablero->getCasilla(nuevaPos);

    narrador << jugador->getNombre() << " cae en la casilla " << nuevaPos << ": " << casilla->tipo() << ". ";
    casilla->ejecutarAccion(jugador);

    if (casilla->tipo() == "Oca") {
        // Chequeamos si la Oca nos mandó a la 63
        // PERO el tablero es más grande
        if (jugador->getPos() == 63 && tablero->getCantidadCasillas() != 63) {

            // Corregimos la posición.
            jugador->setPos(tablero->getCantidadCasillas());
            jugador->marcarGanador(); // Ahora sí gana de verdad
            narrador << "¡La Oca te lleva directo al final! ";
        }
    }

    // Chequeamos si la casilla donde cayó es un Pozo
    if (casilla->tipo() == "Pozo") {
        // si entra libera a los demas jugadores
        for (Jugador* j : jugadores) {
            if (j != jugador && j->estaAtrapadoEnPozo()) {
                j->liberarDelPozo();
                narrador << " ¡" << j->getNombre() << " ha sido liberado del pozo! ";
            }
        }
    }

    if (jugador->gano()) {
        narrador << "🎉 ¡" << jugador->getNombre() << " ha ganado el juego!";
        terminado = true;
    }

    return narrador.str();
}

void Juego::avanzarTurno() {
    turnoActual++;
    if (turnoActual >= (int)jugadores.size())
        turnoActual = 0;
}

// JUGAR TURNO CON DOS DADOS
string Juego::jugarTurno() {
    Jugador* actual = getJugadorActual();
    ostringstream narrador;

    if (estaTerminado()) {
        narrador << "El juego ya ha terminado.";
        return narrador.str();
    }

    // Miramos estados (turnos perdidos, pozo)
    if (actual->getTurnosPerdidos() > 0) {
        narrador << actual->getNombre() << " pierde un turno (le quedan " << actual->getTurnosPerdidos() << ").";
        actual->restarTurno();
        avanzarTurno();
        return narrador.str();
    }

    if (actual->estaAtrapadoEnPozo()) {
        narrador << actual->getNombre() << " está atrapado en el pozo y pierde el turno.";
        avanzarTurno();
        return narrador.str();
    }

    // Tirar DOS dados y aplicar reglas
    ultimaTirada1 = dado1.lanzar();
    ultimaTirada2 = dado2.lanzar();
    int suma = ultimaTirada1 + ultimaTirada2;

    narrador << actual->getNombre() << " saca un " << ultimaTirada1 << " y un " << ultimaTirada2 << " (Suma: " << suma << "). ";

    if (reglaSuma9Activada && actual->getPos() == 1 && suma == 9) {
        int nuevaPos = 0;
        if ((ultimaTirada1 == 3 && ultimaTirada2 == 6) || (ultimaTirada1 == 6 && ultimaTirada2 == 3))
            nuevaPos = 36;
        if ((ultimaTirada1 == 4 && ultimaTirada2 == 5) || (ultimaTirada1 == 5 && ultimaTirada2 == 4))
            nuevaPos = 54;

        if (nuevaPos != 0) {
            narrador << "¡Regla especial Suma 9! Salta directo a la casilla " << nuevaPos << ". ";
            actual->setPos(nuevaPos);

            Casilla* casillaLlegada = tablero->getCasilla(nuevaPos);
            casillaLlegada->ejecutarAccion(actual); // Esto activa la Oca

            if (casillaLlegada->tipo() == "Oca") {
                // Chequeamos si la Oca nos mandó a la 63,
                // PERO el tablero es más grande
                if (actual->getPos() == 63 && tablero->getCantidadCasillas() != 63) {

                    // ¡La Oca se equivocó! Corregimos la posición.
                    actual->setPos(tablero->getCantidadCasillas());
                    actual->marcarGanador(); // Ahora sí gana de verdad
                    narrador << "¡La Oca te lleva directo al final! ";
                }
            }

            if (actual->gano()) {
                narrador << "🎉 ¡" << actual->getNombre() << " ha ganado el juego!";
                terminado = true;
                return narrador.str();
            }

            if (actual->puedeVolverATirar() && !estaTerminado()) {
                narrador << " ¡Vuelve a tirar!";
                actual->deshabilitarRepeticion();
            } else if (!estaTerminado()) {
                avanzarTurno();
            }
            return narrador.str();
        }
    }

    // Regla especial
    // A partir de la casilla 60, solo un dado...
    int pasos;
    if (actual->getPos() > 60) {
        pasos = ultimaTirada1; // Usamos solo el primer dado
        narrador << "(Solo se usa un dado después de la casilla 60: Mueve " << pasos << "). ";
    } else {
        pasos = suma;
    }

    // Mover y activar casilla
    string msgCasilla = moverJugador(pasos);
    narrador << msgCasilla;

    // Chequear repetición de turno
    if (actual->puedeVolverATirar() && !estaTerminado()) {
        narrador << " ¡Vuelve a tirar!";
        actual->deshabilitarRepeticion();
    } else if (!estaTerminado()) {
        avanzarTurno();
    }

    return narrador.str();
}

bool Juego::estaTerminado() const {
    return terminado;
}

int Juego::getUltimaTirada1() const {
    return ultimaTirada1;
}

int Juego::getUltimaTirada2() const {
    return ultimaTirada2;
}

string Juego::getCasillaTipo(int numero) const {
    if (!tablero) return "Normal"; // Por si el tablero no existe

    Casilla* c = tablero->getCasilla(numero);
    if (!c) return "Normal"; // Seguridad por si la casilla no existe

    return c->tipo(); // Devuelve el tipo de casilla.
}


void Juego::guardarPartida(QDataStream &out) const
{
    // Guardamos la Configuración
    out << (qint32)config_cantCasillas;
    out << (bool)config_modoAleatorio;
    out << (bool)config_reglaSuma9;
    out << (qint32)jugadores.size();

    // Guardamos el Estado del Juego
    out << (qint32)turnoActual;
    out << (bool)terminado;

    // Guardamos cada Jugador
    for (Jugador* j : jugadores) {
        j->guardar(out);
    }
}

// Carga el ESTADO (asume que la config ya se leyó)
void Juego::cargarPartida(QDataStream &in)
{
    // La config la lee MainWindow
    // El número de jugadores lo lee MainWindow

    // Cargamos el Estado del Juego
    qint32 qTurno;
    bool qTerminado;
    in >> qTurno;
    in >> qTerminado;
    turnoActual = qTurno;
    terminado = qTerminado;

    // Cargamos cada Jugador
    for (Jugador* j : jugadores) {
        j->cargar(in);
    }
}

