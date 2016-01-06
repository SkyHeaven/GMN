#include <QApplication>

#include <QPushButton>

#include "Controle.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])

{

    Controle c ;

    QImageReader reader("result6.jpg");
    reader.setAutoTransform(true);
    const QImage imagef = reader.read();
    c.ouvertureImage(imagef);



    return 0;

}
