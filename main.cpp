#include "VentanaPrincipal.h"
#include <QApplication>
#include <random>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VentanaPrincipal w;
    //w.setStyleSheet();
    w.show();

    return a.exec();
}
