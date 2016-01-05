#include <QApplication>

#include <QPushButton>



int main(int argc, char *argv[])

{

    QApplication app(argc, argv);



    QPushButton bouton("Salut les Zeros, la forme ?");

    bouton.show();



    return app.exec();

}
