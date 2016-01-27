#include <QApplication>
#include <QPushButton>
#include "Controle.h"
#include "MainWindow.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    MainWindow m;
    m.show();
    return app.exec();
    return 0;
}
