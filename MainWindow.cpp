#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Controle.h"
#include "ImageViewer.h"

#include <iostream>
#include <string>
#include <QtWidgets>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    openAct = ui->action_Open;
    fitToWindowAct = ui->actionFitToWindowAct;
    saveAct = ui->action_Save;
    undoAct = ui->actionUndo;
    redoAct = ui->actionRedo;


    imageLabel = new ImageViewer();
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);
    imageLabel->setMouseTracking(true);
    imageLabel->setParent(ui->imageLabel);

    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    setCentralWidget(scrollArea);



    setWindowTitle(tr("GMN"));

    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));
    connect(ui->Grey,SIGNAL(clicked()),this,SLOT(grey()));
    connect(saveAct,SIGNAL(triggered()), this, SLOT(save()));
    connect(undoAct,SIGNAL(triggered()), this, SLOT(undo()));
    connect(redoAct,SIGNAL(triggered()), this, SLOT(redo()));
    connect(ui->Crop, SIGNAL(clicked()), this, SLOT(crop()));
    connect(imageLabel, SIGNAL(sign_pip()), this, SLOT(pipette()));

}

bool MainWindow::loadFile(const QString &fileName)
{
    QImageReader reader(fileName);

    const QImage image = reader.read();
    if (image.isNull()) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1.").arg(QDir::toNativeSeparators(fileName)));
        setWindowFilePath(QString());
        imageLabel->setPixmap(QPixmap());
        imageLabel->adjustSize();
        return false;
    }

    imageLabel->setPixmap(QPixmap::fromImage(image));
    afficherImage(image);
    c.ouvertureImage(image);
    QImage im = recupQImage();
    afficherImage(im);
    return true;
}



void MainWindow::open()
{
    const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
    QFileDialog dialog(this, tr("Open File"),picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
    dialog.setAcceptMode(QFileDialog::AcceptOpen);

    //QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Images (*.png *.gif *.jpg *.jpeg)");
    while (dialog.exec() == QDialog::Accepted && !loadFile(dialog.selectedFiles().first())) {    }
}

void MainWindow::updateActions()
{
}

void MainWindow::scaleImage(double factor)
{
    Q_ASSERT(imageLabel->pixmap());
    scaleFactor *= factor;
    imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

    adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(scrollArea->verticalScrollBar(), factor);

}

void MainWindow::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}

void MainWindow::fitToWindow()
{
    bool fitToWindow = fitToWindowAct->isChecked();
    scrollArea->setWidgetResizable(fitToWindow);

    updateActions();
}

void MainWindow::grey(){
    c.afficherGris();
    QImage image= recupQImage();
    afficherImage(image);
}

QImage MainWindow::recupQImage(){

    QImage image(c.getSauvegardeImage().at(c.getIndexVecteur()).getLargeur(),c.getSauvegardeImage().at(c.getIndexVecteur()).getHauteur(),QImage::Format_RGB32);
    QRgb value;
    for (int h=0;h<image.height();h++){
        for(int l=0;l<image.width();l++){
            int v0 = c.getSauvegardeImage().at(c.getIndexVecteur()).getTableauPixel()[h][l].getEtatCourant()[0];
            int v1 = c.getSauvegardeImage().at(c.getIndexVecteur()).getTableauPixel()[h][l].getEtatCourant()[1];
            int v2 = c.getSauvegardeImage().at(c.getIndexVecteur()).getTableauPixel()[h][l].getEtatCourant()[2];
            value = qRgb(v0, v1, v2);
            image.setPixel(l,h,value);
        }
    }
    return image;
}

void MainWindow::afficherImage(QImage image){
    imageLabel->setPixmap(QPixmap::fromImage(image));
    scaleFactor = 1.0;
    fitToWindowAct->setEnabled(true);
    updateActions();

    if (!fitToWindowAct->isChecked())
        imageLabel->adjustSize();
}

bool MainWindow::save()
{
    QString fichier = QFileDialog::getSaveFileName(this, "Enregistrer un fichier", QString(), "Images (*.png *.gif *.jpg *.jpeg)");
    QImage image = recupQImage();
    image.save(fichier);
    return true;
}

void MainWindow::crop(){

    c.crop(imageLabel->getOrigineSel().y(),imageLabel->getOrigineSel().x(),imageLabel->getFinSel().y(),imageLabel->getFinSel().x());
    QImage image= recupQImage();
    afficherImage(image);

}

void MainWindow::undo(){
    c.undo();
    QImage image= recupQImage();
    afficherImage(image);
}

void MainWindow::redo(){
    c.redo();
    QImage image= recupQImage();
    afficherImage(image);
}



void MainWindow::pipette(){

    if(ui->Pipette->isChecked()){
        cout<<"tamere"<<endl;
        int *rgb = c.affichageCouleurRGB(imageLabel->getPipette().y(),imageLabel->getPipette().x());
        int *yuv = c.affichageCouleurYUV(imageLabel->getPipette().y(),imageLabel->getPipette().x());
        int gris = c.affichageCouleurGris(imageLabel->getPipette().y(),imageLabel->getPipette().x());

         QString st;
         st = QString("Valeur RGB : %1, %2, %3 \n Valeur YUV : %4, %5, %6 \n Valeur gris : %7").arg(rgb[0]).arg(rgb[1]).arg(rgb[2]).arg(yuv[0]).arg(yuv[1]).arg(yuv[2]).arg(gris);
         cout<<pip.y()<<"           "<<pip.x()<<endl;
        ui->AffInfo->setPlainText(st);

    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
