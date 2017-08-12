#ifndef VENTANAPRINCIPAL_H
#define VENTANAPRINCIPAL_H

#include <QMainWindow>
#include <QTimer>
#include "Maquina.h"
#include "CargaBotellas.h"
#include "Controlador.h"

namespace Ui {
class VentanaPrincipal;
}

class VentanaPrincipal : public QMainWindow
{
    Q_OBJECT

public:
    explicit VentanaPrincipal(QWidget *parent = 0);
    ~VentanaPrincipal();
    Controlador * controlador;

private slots:
    void on_btn_play_clicked();
    void actualizarDatosGUI();
    void on_btn_ingresar_tabla_clicked();

    void on_btn_stop_clicked();

    void on_btn_Onpersona1_clicked();

    void on_btn_OfPersona1_clicked();

    void on_btn_OnLimpiadora_clicked();

    void on_btn_OfLimpiadora_clicked();

    void on_btn_OnLlenadora1_clicked();

    void on_btn_OfLlenadora1_clicked();

    void on_btn_OnLlenadora2_clicked();

    void on_btn_OfLlenadora2_clicked();

    void on_btn_OnTapadora_clicked();

    void on_btn_OfTapadora_clicked();

    void on_btn_OnPersona2_clicked();

    void on_btn_OfPersona2_clicked();

    void on_btn_pause_clicked();

    void on_btn_resume_clicked();

private:
    int i = 0;
    QTimer * timer;
    bool iniciado;
    bool tiposDeBotellasIngresado;
    bool reiniciado;
    Ui::VentanaPrincipal * ui;
    void modificarQLineEdit(string);
    bool validarTablaRechazo(void);
};

#endif // VENTANAPRINCIPAL_H
