#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "juego.h"
#include <QMainWindow>
#include <QLabel>
#include <QVector>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnIniciar_clicked();
    void on_btnTirarDado_clicked();

    void on_btnGuardar_clicked();

    void on_btnCargar_clicked();

    void on_btnCargarConfig_clicked();

    void on_btnGuardarConfig_clicked();

private:
    Ui::MainWindow *ui;
    Juego* juego=nullptr;
    QVector<QLabel*> fichasJugadores;

    void actualizarFichas();

    void appendNarrador(const QString &msg);
    void prepararTableroUI(int cantidadCasillas, int cantidadJugadores);
};
#endif // MAINWINDOW_H
