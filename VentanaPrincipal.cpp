#include "VentanaPrincipal.h"
#include "ui_VentanaPrincipal.h"
#include <QMessageBox>
#include "Estructuras.h"


VentanaPrincipal::VentanaPrincipal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VentanaPrincipal)
{
    ui->setupUi(this);    

    ui->line_Max1->setValidator(new QIntValidator);
    ui->line_Max2->setValidator(new QIntValidator);
    ui->line_Max3->setValidator(new QIntValidator);
    ui->line_Max4->setValidator(new QIntValidator);
    ui->velocidadLimpiadora->setValidator(new QIntValidator);
    ui->velocidadLlenadora1->setValidator(new QIntValidator);
    ui->velocidadLlenadora2->setValidator(new QIntValidator);
    ui->velocidadPersona1->setValidator(new QIntValidator);
    ui->velocidadPersona2->setValidator(new QIntValidator);
    ui->velocidadTapadora->setValidator(new QIntValidator);
    ui->line_probabilidad->setValidator(new QIntValidator);

    iniciado = false;
    tiposDeBotellasIngresado = false;
    reiniciado = false;
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(actualizarDatosGUI()));
}

VentanaPrincipal::~VentanaPrincipal()
{
    delete ui;
}

void VentanaPrincipal::on_btn_play_clicked()
{
    QMessageBox msgBox;
    if(ui->velocidadLimpiadora->text().isEmpty()){
        msgBox.setText("Indique la velocidad de la limpiadora");
        msgBox.exec();
    }else if(ui->velocidadLlenadora1->text().isEmpty()){
        msgBox.setText("Indique la velocidad de la llenadora 1");
        msgBox.exec();
    }else if(ui->velocidadLlenadora2->text().isEmpty()){
        msgBox.setText("Indique la velocidad de la llenadora 2");
        msgBox.exec();
    }else if(ui->velocidadPersona1->text().isEmpty()){
        msgBox.setText("Indique la velocidad del carga botellas");
        msgBox.exec();
    }else if(ui->velocidadPersona2->text().isEmpty()){
        msgBox.setText("Indique la velocidad del inspector de calidad");
        msgBox.exec();
    }else if(ui->velocidadTapadora->text().isEmpty()){
        msgBox.setText("Indique la velocidad de la tapadora");
        msgBox.exec();
    }else if(ui->line_Max1->text().isEmpty()){
        msgBox.setText("Indique la cantidad máxima de la banda transportadora 1");
        msgBox.exec();
    }else if(ui->line_Max2->text().isEmpty()){
        msgBox.setText("Indique la cantidad máxima de la banda transportadora 2");
        msgBox.exec();
    }else if(ui->line_Max3->text().isEmpty()){
        msgBox.setText("Indique la cantidad máxima de la banda transportadora 3");
        msgBox.exec();
    }else if(ui->line_Max4->text().isEmpty()){
        msgBox.setText("Indique la cantidad máxima de la banda transportadora 4");
        msgBox.exec();
    }else if(ui->line_Max5->text().isEmpty()){
        msgBox.setText("Indique la cantidad máxima de la banda transportadora 5");
        msgBox.exec();
    }else{
        if(!iniciado){
            if(tiposDeBotellasIngresado){
                if(validarTablaRechazo()){
                    ListaTiposBotellas * listaTiposCargaBotellas = new ListaTiposBotellas();
                    ListaTiposBotellas * listaTiposInspector = new ListaTiposBotellas();
                    ListaTiposBotellas * listaTiposLimpiadora = new ListaTiposBotellas();
                    ListaTiposBotellas * listaTiposTapadora = new ListaTiposBotellas();
                    ListaTiposBotellas * listaTiposLlenadora1 = new ListaTiposBotellas();
                    ListaTiposBotellas * listaTiposLlenadora2 = new ListaTiposBotellas();


                    ListaProbabilidades * listaProbab = new ListaProbabilidades();
                    ListaProbabilidades * listaProbabilidadRechazo = new ListaProbabilidades();
                    for (int i = 0; i < ui->tabla_Tipos_Botellas->rowCount(); i++) {
                        listaTiposCargaBotellas->insertar(ui->tabla_Tipos_Botellas->item(i, 0)->text(), ui->tabla_Tipos_Botellas->item(i,1)->text(), 0, 0);
                        listaTiposInspector->insertar(ui->tabla_Tipos_Botellas->item(i, 0)->text(), ui->tabla_Tipos_Botellas->item(i,1)->text(), 0, 0);
                        listaTiposLimpiadora->insertar(ui->tabla_Tipos_Botellas->item(i, 0)->text(), ui->tabla_Tipos_Botellas->item(i,1)->text(), 0, 0);
                        listaTiposTapadora->insertar(ui->tabla_Tipos_Botellas->item(i, 0)->text(), ui->tabla_Tipos_Botellas->item(i,1)->text(), 0, 0);
                        listaTiposLlenadora1->insertar(ui->tabla_Tipos_Botellas->item(i, 0)->text(), ui->tabla_Tipos_Botellas->item(i,1)->text(), 0, 0);
                        listaTiposLlenadora2->insertar(ui->tabla_Tipos_Botellas->item(i, 0)->text(), ui->tabla_Tipos_Botellas->item(i,1)->text(), 0, 0);

                        listaProbab->insertarAlFinal(ui->tabla_Tipos_Botellas->item(i, 0)->text(), ui->tabla_Tipos_Botellas->item(i, 2)->text().toInt());                        
                        listaProbabilidadRechazo->insertarAlFinal(ui->tabla_Tipos_Botellas->item(i, 0)->text(), ui->tabla_Rechazo_Botellas->item(i, 3)->text().toInt());
                    }

                    controlador = new Controlador(ui->velocidadPersona1->text().toInt(), ui->velocidadPersona2->text().toInt(),
                                                  ui->velocidadLimpiadora->text().toInt(), ui->velocidadLlenadora1->text().toInt(),
                                                  ui->velocidadLlenadora2->text().toInt(), ui->velocidadTapadora->text().toInt(),
                                                  ui->line_Max1->text().toInt(), ui->line_Max2->text().toInt(), ui->line_Max3->text().toInt(),
                                                  ui->line_Max4->text().toInt(), ui->line_Max5->text().toInt());

                    controlador->cargaBotellas->agregarListaBotellas(listaTiposCargaBotellas);
                    controlador->cargaBotellas->agregarListaProbabilidades(listaProbab);


                    controlador->inspector->agregarListaBotellas(listaTiposInspector);
                    controlador->inspector->agregarListaProbabilidades(listaProbabilidadRechazo);


                    controlador->limpiadora->agregarListaTiposBotellas(listaTiposLimpiadora);

                    controlador->llenadora1->agregarListaTiposBotellas(listaTiposLlenadora1);

                    controlador->llenadora2->agregarListaTiposBotellas(listaTiposLlenadora2);

                    controlador->tapadora->agregarListaTiposBotellas(listaTiposTapadora);

                    ListaTiposBotellas * listaTemporal = controlador->cargaBotellas->obtenerListaBotellas();
                    TipoBotella * temporal = listaTemporal->primerNodo;
                    QTableWidgetItem * item;
                    int filas = 0;
                    if(!this->reiniciado){
                        filas = ui->tabla_Limpiadora->rowCount();

                        do{
                            ui->tabla_Limpiadora->setRowCount(filas + 1);
                            ui->tabla_Llenadora1->setRowCount(filas + 1);
                            ui->tabla_Llenadora2->setRowCount(filas + 1);
                            ui->tabla_Persona1->setRowCount(filas + 1);
                            ui->tabla_Tapadora->setRowCount(filas + 1);

                            item = new QTableWidgetItem(temporal->tipoBotellas + " / " + temporal->medida);
                            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                            ui->tabla_Limpiadora->setItem(filas, 0, item);

                            item = new QTableWidgetItem("0");
                            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                            ui->tabla_Limpiadora->setItem(filas, 1, item);

                            item = new QTableWidgetItem(temporal->tipoBotellas + " / " + temporal->medida);
                            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                            ui->tabla_Llenadora1->setItem(filas, 0, item);

                            item = new QTableWidgetItem("0");
                            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                            ui->tabla_Llenadora1->setItem(filas, 1, item);

                            item = new QTableWidgetItem(temporal->tipoBotellas + " / " + temporal->medida);
                            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                            ui->tabla_Llenadora2->setItem(filas, 0, item);

                            item = new QTableWidgetItem("0");
                            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                            ui->tabla_Llenadora2->setItem(filas, 1, item);

                            item = new QTableWidgetItem(temporal->tipoBotellas + " / " + temporal->medida);
                            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                            ui->tabla_Persona1->setItem(filas, 0, item);

                            item = new QTableWidgetItem("0");
                            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                            ui->tabla_Persona1->setItem(filas, 1, item);

                            item = new QTableWidgetItem(temporal->tipoBotellas + " / " + temporal->medida);
                            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                            ui->tabla_Tapadora->setItem(filas, 0, item);

                            item = new QTableWidgetItem("0");
                            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                            ui->tabla_Tapadora->setItem(filas, 1, item);
                            temporal = temporal->siguiente;
                            filas++;
                        }while(temporal != listaTemporal->primerNodo);
                        this->reiniciado = true;
                    }
                    controlador->cambiarEstado(1);
                    controlador->start();
                    iniciado = true;
                    timer->start(250);
                }
            }else{
                msgBox.setText("Indique los tipos de botellas y sus respectivas probabilidades");
                msgBox.exec();
            }
        }
    }
    validarTablaRechazo();
}

void VentanaPrincipal::on_btn_stop_clicked()
{
    iniciado = false;
    controlador->cambiarEstado(2);
}

void VentanaPrincipal::actualizarDatosGUI(){
    //qDebug() << "Iniciando: " << i++;
    ui->line_Actu1->setText(QString::number(controlador->cola1->cantidadActual));
    ui->line_Actu2->setText(QString::number(controlador->cola2->cantidadActual));
    ui->line_Actu3->setText(QString::number(controlador->cola3->cantidadActual));
    ui->line_Actu4->setText(QString::number(controlador->cola4->cantidadActual));
    ui->line_Actu5->setText(QString::number(controlador->cola5->cantidadActual));

    ListaTiposBotellas * listaTemporalPersona1 = controlador->cargaBotellas->obtenerListaBotellas();
    ListaTiposBotellas * listaPersona2 = controlador->inspector->obtenerListaBotellas();
    ListaTiposBotellas * listaLimpiadora = controlador->limpiadora->obtenerListaTiposBotellas();
    ListaTiposBotellas * listaLlenadora1 = controlador->llenadora1->obtenerListaTiposBotellas();
    ListaTiposBotellas * listaLlenadora2 = controlador->llenadora2->obtenerListaTiposBotellas();
    ListaTiposBotellas * listaTapadora = controlador->tapadora->obtenerListaTiposBotellas();

    TipoBotella * temporalPersona1 = listaTemporalPersona1->primerNodo;
    TipoBotella * temporalPersona2 = listaPersona2->primerNodo;
    TipoBotella * temporalLimpiadora = listaLimpiadora->primerNodo;
    TipoBotella * temporalLlenadora1 = listaLlenadora1->primerNodo;
    TipoBotella * temporalLlenadora2 = listaLlenadora2->primerNodo;
    TipoBotella * temporalTapadora = listaTapadora->primerNodo;
    int j = 0;
    do{
        ui->tabla_Limpiadora->item(j, 1)->setText(QString::number(temporalLimpiadora->cantidadAceptadas));
        ui->tabla_Persona1->item(j, 1)->setText(QString::number(temporalPersona1->cantidadAceptadas));
        ui->tabla_Llenadora1->item(j, 1)->setText(QString::number(temporalLlenadora1->cantidadAceptadas));
        ui->tabla_Llenadora2->item(j, 1)->setText(QString::number(temporalLlenadora2->cantidadAceptadas));
        ui->tabla_Tapadora->item(j, 1)->setText(QString::number(temporalTapadora->cantidadAceptadas));
        ui->tabla_Rechazo_Botellas->item(j, 1)->setText(QString::number(temporalPersona2->cantidadAceptadas));
        ui->tabla_Rechazo_Botellas->item(j, 2)->setText(QString::number(temporalPersona2->cantidadRechazadas));

        j++;
        temporalPersona1 = temporalPersona1->siguiente;
        temporalLimpiadora = temporalLimpiadora->siguiente;
        temporalLlenadora1 = temporalLlenadora1->siguiente;
        temporalLlenadora2 = temporalLlenadora2->siguiente;
        temporalTapadora = temporalTapadora->siguiente;
        temporalPersona2 = temporalPersona2->siguiente;
    }while(temporalPersona1 != listaTemporalPersona1->primerNodo);

    controlador->modificarParametros(ui->velocidadPersona1->text().toInt(), ui->velocidadPersona2->text().toInt(),
                                     ui->velocidadLimpiadora->text().toInt(), ui->velocidadLlenadora1->text().toInt(),
                                     ui->velocidadLlenadora2->text().toInt(), ui->velocidadTapadora->text().toInt(),
                                     ui->line_Max1->text().toInt(), ui->line_Max2->text().toInt(), ui->line_Max3->text().toInt(),
                                     ui->line_Max4->text().toInt(), ui->line_Max5->text().toInt());
}

void VentanaPrincipal::on_btn_ingresar_tabla_clicked()
{
    if(!this->iniciado){
        if(ui->line_cantidad_botellas->text().isEmpty() || ui->line_probabilidad->text().isEmpty() || ui->line_cantidad_botellas->text().isEmpty()){
            QMessageBox msgBox;
            msgBox.setText("Complete los espacios correspondientes");
            msgBox.exec();
        }else{
            QTableWidgetItem * item;

            int filas = ui->tabla_Tipos_Botellas->rowCount();
            ui->tabla_Tipos_Botellas->setRowCount(filas + 1);
            ui->tabla_Rechazo_Botellas->setRowCount(filas + 1);

            item = new QTableWidgetItem(ui->line_tipo->text());
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui->tabla_Tipos_Botellas->setItem(filas, 0, item);

            item = new QTableWidgetItem(ui->line_cantidad_botellas->text());
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui->tabla_Tipos_Botellas->setItem(filas, 1, item);

            ui->tabla_Tipos_Botellas->setItem(filas, 2, new QTableWidgetItem(ui->line_probabilidad->text()));

            item = new QTableWidgetItem(ui->line_tipo->text() + " / " + ui->line_cantidad_botellas->text());
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui->tabla_Rechazo_Botellas->setItem(filas, 0, item);

            item = new QTableWidgetItem("0");
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui->tabla_Rechazo_Botellas->setItem(filas, 1, item);
            item = new QTableWidgetItem("0");
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui->tabla_Rechazo_Botellas->setItem(filas, 2, item);

            ui->line_tipo->setText("");
            ui->line_cantidad_botellas->setText("");
            ui->line_probabilidad->setText("");
            tiposDeBotellasIngresado = true;
        }
    }else{
        QMessageBox msgBox;
        msgBox.setText("Debe de detener la simulación para agregar otro tipo de botella");
        msgBox.exec();
    }
}

bool VentanaPrincipal::validarTablaRechazo(){
    double totalRechazo = 0;
    double totalProbabilidades = 0;
    bool aceptado = false;
    for (int i = 0; i < ui->tabla_Rechazo_Botellas->rowCount(); i++) {
        QTableWidgetItem* item = ui->tabla_Rechazo_Botellas->item(i, 3);
        if (item && !item->text().isEmpty()){
            QByteArray ba = item->text().toLatin1();
            const char *c_str2 = ba.data();
            if(nan(c_str2)){
                totalRechazo += item->text().toDouble() / 100;
            }else{
                QMessageBox msgBox;
                msgBox.setText("Los campos de % de rechazo de la tabla de rechazos solo pueden contener números");
                msgBox.exec();
                return aceptado;
            }
        }else{
            QMessageBox msgBox;
            msgBox.setText("Los campos de % de rechazo de la tabla de rechazos no pueden estar vacios");
            msgBox.exec();
            return aceptado;
        }
        item = ui->tabla_Tipos_Botellas->item(i, 2);
        if (item && !item->text().isEmpty()){
            QByteArray ba = item->text().toLatin1();
            const char *c_str2 = ba.data();
            if(nan(c_str2)){
                totalProbabilidades += item->text().toDouble() / 100;
            }else{
                QMessageBox msgBox;
                msgBox.setText("Los campos de % de probabilidades de la tabla de tipos de botellas solo pueden contener números");
                msgBox.exec();
                return aceptado;
            }
        }
    }
    if(ui->tabla_Tipos_Botellas->rowCount() != 0){
        if(totalProbabilidades != 1){
            QMessageBox msgBox;
            msgBox.setText("Los porcentajes de probabilidades de los tipos de botellas no suman 100%\nModifique los porcentajes de probabilidad de cada botella para que sumen 100");
            msgBox.exec();
            return aceptado;
        }else {
            aceptado = true;
        }
    }
    return aceptado;
}

void VentanaPrincipal::on_btn_Onpersona1_clicked()
{
    controlador->cargaBotellas->modificarEstado(true);
}

void VentanaPrincipal::on_btn_OfPersona1_clicked()
{
    controlador->cargaBotellas->modificarEstado(false);
}

void VentanaPrincipal::on_btn_OnLimpiadora_clicked()
{
    controlador->limpiadora->modificarEstado(true);
}

void VentanaPrincipal::on_btn_OfLimpiadora_clicked()
{
    controlador->limpiadora->modificarEstado(false);
}

void VentanaPrincipal::on_btn_OnLlenadora1_clicked()
{
    controlador->llenadora1->modificarEstado(true);
}

void VentanaPrincipal::on_btn_OfLlenadora1_clicked()
{
    controlador->llenadora1->modificarEstado(false);
}

void VentanaPrincipal::on_btn_OnLlenadora2_clicked()
{
    controlador->llenadora2->modificarEstado(true);
}

void VentanaPrincipal::on_btn_OfLlenadora2_clicked()
{
    controlador->llenadora2->modificarEstado(false);
}

void VentanaPrincipal::on_btn_OnTapadora_clicked()
{
    controlador->tapadora->modificarEstado(true);
}

void VentanaPrincipal::on_btn_OfTapadora_clicked()
{
    controlador->tapadora->modificarEstado(false);
}

void VentanaPrincipal::on_btn_OnPersona2_clicked()
{
    controlador->inspector->modificarEstado(true);
}

void VentanaPrincipal::on_btn_OfPersona2_clicked()
{
    controlador->inspector->modificarEstado(false);
}

void VentanaPrincipal::on_btn_pause_clicked()
{
    controlador->cambiarEstado(2);
}

void VentanaPrincipal::on_btn_resume_clicked()
{
    controlador->cargaBotellas->modificarEstado(true);
    controlador->inspector->modificarEstado(true);
    controlador->limpiadora->modificarEstado(true);
    controlador->llenadora1->modificarEstado(true);
    controlador->llenadora2->modificarEstado(true);
    controlador->tapadora->modificarEstado(true);
}
