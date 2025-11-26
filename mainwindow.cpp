#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "juego.h"
#include <QLabel>
#include <QPushButton>
#include <QStringList>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QDataStream>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableroWidget->hide();
    ui->btnTirarDado->setEnabled(false);

    // Conexion de botones
    connect(ui->btnIniciar, &QPushButton::clicked, this, &MainWindow::on_btnIniciar_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
    if (juego) {
        delete juego;
    }
}

// Funcion que prepara tablero, colores y demas.
// Segun cantidad de casillas
void MainWindow::prepararTableroUI(int cantidadCasillas, int cantidadJugadores)
{
    qDebug() << "Preparando UI para" << cantidadCasillas << "casillas y" << cantidadJugadores << "jugadores.";
    QLayoutItem* item;
    while ( ( item = ui->gridLayout_tablero->takeAt( 0 ) ) != nullptr ) {
        delete item->widget();
        delete item;
    }
    int tamBoton = 45;
    for (int i = 1; i <= cantidadCasillas; ++i) {
        QPushButton* btn = new QPushButton(QString::number(i), ui->tableroWidget);
        btn->setFixedSize(tamBoton, tamBoton);
        btn->setObjectName(QString("casilla%1").arg(i));
        string tipo = juego->getCasillaTipo(i);
        QString style = "font-weight: bold; border-radius: 5px;";
        if (tipo == "Oca") style += "background-color: #F39C12; color: black;";
        else if (tipo == "Puente") style += "background-color: #E67E22; color: white;";
        else if (tipo == "Posada") style += "background-color: #8B4513; color: white;";
        else if (tipo == "Pozo") style += "background-color: #1C1C1C; color: white;";
        else if (tipo == "Laberinto") style += "background-color: #3498DB; color: white;";
        else if (tipo == "Carcel") style += "background-color: #E74C3C; color: white;";
        else if (tipo == "Calavera") style += "background-color: #9B59B6; color: white;";
        else if (tipo == "Jardin de la Oca") style += "background-color: #2ECC71; color: white;";
        else style += "background-color: #333; color: white;";
        btn->setStyleSheet(style);
        int fila = (i - 1) / 10;
        int col = (i - 1) % 10;
        ui->gridLayout_tablero->addWidget(btn, fila, col);
    }
    qDeleteAll(fichasJugadores);
    fichasJugadores.clear();
    const QStringList colores{"red","blue","green","orange"};
    for (int i = 0; i < cantidadJugadores; ++i) {
        QLabel* ficha = new QLabel(ui->tableroWidget);
        ficha->setFixedSize(20,20);
        ficha->setStyleSheet(QString("background-color:%1; border-radius:10px;").arg(colores.value(i)));
        ficha->setAttribute(Qt::WA_TransparentForMouseEvents);
        ficha->show();
        fichasJugadores.append(ficha);
    }
}

void MainWindow::on_btnIniciar_clicked()
{
    int cantidadJugadores = ui->spinJugadores->value();
    int cantidadCasillas = ui->spinCasillas->value();
    bool modoAleatorio = false; // METODO PARA QUE TODO EL TABLERO SEA ALEATORIO
    bool activarReglaSuma9 = ui->checkSuma9->isChecked();

    if (juego != nullptr) {
        delete juego;
        juego = nullptr;
    }
    juego = new Juego (cantidadJugadores, cantidadCasillas, modoAleatorio, activarReglaSuma9);
    prepararTableroUI(cantidadCasillas, cantidadJugadores);
    ui->tableroWidget->show();
    ui->controlsWidget->hide();
    ui->txtNarrador->clear();
    appendNarrador("Comienza la partida...");
    ui->lblTurnoActual->setText(QString("Turno: Jugador %1").arg(juego->getTurnoActual() + 1));
    ui->btnTirarDado->setEnabled(true);
    actualizarFichas();
}

void MainWindow::on_btnTirarDado_clicked()
{
    if (!juego) return;

    string msg = juego->jugarTurno();

    appendNarrador(QString::fromStdString(msg));

    int d1 = juego->getUltimaTirada1();
    int d2 = juego->getUltimaTirada2();

    if (juego->getJugadorActual()->getPos() > 60) {
        ui->labelResultado->setText(QString("Resultado: %1").arg(d1));
    } else {
        ui->labelResultado->setText(QString("Resultado: %1 y %2").arg(d1).arg(d2));
    }

    actualizarFichas();

    if (!juego->estaTerminado()) {
        ui->lblTurnoActual->setText(QString("Turno: Jugador %1").arg(juego->getTurnoActual() + 1));
    }
    if (juego->estaTerminado()) {
        appendNarrador("🎉🎉 ¡FIN DEL JUEGO! 🎉🎉");
        ui->btnTirarDado->setEnabled(false);
    }
}

void MainWindow::appendNarrador(const QString &msg) {
    ui->txtNarrador->append(msg);
}

void MainWindow::actualizarFichas()
{
    if (!juego) return;

    for (int i = 0; i < fichasJugadores.size(); ++i) {
        int pos = juego->getJugador(i)->getPos();
        int casillaNumero = pos;
        QString nombre = QString("casilla%1").arg(casillaNumero);
        auto* celda = ui->tableroWidget->findChild<QPushButton*>(nombre);

        if (!celda) {
            celda = ui->tableroWidget->findChild<QPushButton*>("casilla1");
            if (!celda) continue;
        }

        QPoint local = celda->mapTo(ui->tableroWidget, QPoint(0, 0));
        int x = local.x() + (celda->width()  - fichasJugadores[i]->width())  / 2;
        int y = local.y() + (celda->height() - fichasJugadores[i]->height()) / 2;

        fichasJugadores[i]->move(x, y);
        fichasJugadores[i]->raise();
    }
}

void MainWindow::on_btnGuardar_clicked()
{
    if (!juego) return;

    QString rutaArchivo = QFileDialog::getSaveFileName(this, "Guardar Partida", "", "Partidas de la Oca (*.dat)");

    if (rutaArchivo.isEmpty()) return;
    QFile file(rutaArchivo);
    if (!file.open(QIODevice::WriteOnly)) {
        appendNarrador("¡Error! No se pudo guardar el archivo.");
        return;
    }

    QDataStream out(&file);
    juego->guardarPartida(out);
    file.close();
    appendNarrador(QString("¡Partida guardada en %1!").arg(rutaArchivo));
}

void MainWindow::on_btnCargar_clicked()
{
    QString rutaArchivo = QFileDialog::getOpenFileName(this, "Cargar Partida", "", "Partidas de la Oca (*.dat)");
    if (rutaArchivo.isEmpty()) return;
    QFile file(rutaArchivo);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error al abrir el archivo para leer.";
        return;
    }
    QDataStream in(&file);
    qint32 cantCasillas, cantJugadores;
    bool modoAleatorio, reglaSuma9;

    in >> cantCasillas;
    in >> modoAleatorio;
    in >> reglaSuma9;
    in >> cantJugadores;

    if (juego != nullptr) delete juego;

    juego = new Juego(cantJugadores, cantCasillas, modoAleatorio, reglaSuma9);
    juego->cargarPartida(in);
    file.close();

    prepararTableroUI(cantCasillas, cantJugadores);
    ui->tableroWidget->show();
    ui->controlsWidget->hide();
    ui->txtNarrador->clear();

    appendNarrador(QString("¡Partida cargada desde %1!").arg(rutaArchivo));

    ui->lblTurnoActual->setText(QString("Turno: Jugador %1").arg(juego->getTurnoActual() + 1));
    ui->btnTirarDado->setEnabled(!juego->estaTerminado());

    actualizarFichas();
}


void MainWindow::on_btnGuardarConfig_clicked()
{
    // Chequeamos que el juego exista
    if (!juego) {
        appendNarrador("Error: No hay una partida iniciada para guardar la config.");
        return;
    }

    // Abrimos la ventana "Guardar como"
    QString rutaArchivo = QFileDialog::getSaveFileName(this,"Guardar Configuración", "", "Configuración de Oca (*.txt)");

    if (rutaArchivo.isEmpty()) return; // El usuario canceló

    QFile file(rutaArchivo);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        appendNarrador("¡Error! No se pudo guardar el archivo de config.");
        return;
    }

    QTextStream out(&file);

    // Le pedimos la configuracion al 'juego' activo
    int casillas = juego->getConfigCasillas();
    bool aleatorio = juego->getConfigModoAleatorio();
    bool reglaSuma9 = juego->getConfigReglaSuma9();
    int jugadores = juego->getConfigJugadores();

    // Escribimos en formato "llave: valor", como un MAP
    out << "casillas:" << casillas << "\n";
    out << "aleatorio:" << (aleatorio ? "true" : "false") << "\n";
    out << "jugadores:" << jugadores << "\n";
    out << "reglaSuma9:" << (reglaSuma9 ? "true" : "false") << "\n";

    file.close();

    appendNarrador(QString("¡Configuración guardada en %1!").arg(rutaArchivo));
}


void MainWindow::on_btnCargarConfig_clicked()
{
    // Abrimos la ventana "Abrir..."
    QString rutaArchivo = QFileDialog::getOpenFileName(this,"Cargar Configuración", "", "Configuración de Oca (*.txt)");

    if (rutaArchivo.isEmpty()) return; // El usuario canceló

    QFile file(rutaArchivo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error al abrir el archivo de config.";
        return;
    }

    QTextStream in(&file);

    // Leemos el archivo línea por línea y actualizamos la UI
    while (!in.atEnd()) {
        QString linea = in.readLine();
        QStringList partes = linea.split(":");

        if (partes.size() != 2) {
            continue;
        }

        QString clave = partes[0].trimmed();
        QString valor = partes[1].trimmed();

        // Actualizamos los widgets del menú de INICIO con la configuracion CARGADA
        if (clave == "casillas") {
            ui->spinCasillas->setValue(valor.toInt());
        } else if (clave == "jugadores") {
            ui->spinJugadores->setValue(valor.toInt());
        } else if (clave == "reglaSuma9") {
            ui->checkSuma9->setChecked(valor == "true");
        }
    }

    file.close();
    qDebug() << "Configuración cargada desde" << rutaArchivo;
}
