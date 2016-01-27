#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <iostream>
#include <string>
#include <QtWidgets>
using namespace std;

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
    c = new Controle();
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
    imageLabel->installEventFilter(this);
    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    setCentralWidget(scrollArea);
    setWindowTitle(tr("GMN"));

    //MENU
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));
    connect(saveAct,SIGNAL(triggered()), this, SLOT(save()));
    connect(undoAct,SIGNAL(triggered()), this, SLOT(undo()));
    connect(redoAct,SIGNAL(triggered()), this, SLOT(redo()));
    connect(ui->action90D, SIGNAL(triggered()), this, SLOT(rotation90D()));
    connect(ui->action90G, SIGNAL(triggered()), this, SLOT(rotation90G()));
    connect(ui->action180, SIGNAL(triggered()), this, SLOT(rotation180()));
    connect(ui->actionOpen_fu,SIGNAL(triggered()),this,SLOT(fusion()));
    connect(ui->actionRecadrer,SIGNAL(triggered()),this,SLOT(recadrer()));
    connect(ui->actionEgaliser,SIGNAL(triggered()),this,SLOT(egaliser()));
    connect(ui->actionNegatif,SIGNAL(triggered()),this,SLOT(negatif()));
    connect(ui->actionGradient,SIGNAL(triggered()),this,SLOT(gradientX()));
    connect(ui->actionGradient_y,SIGNAL(triggered()),this,SLOT(gradientY()));
    connect(ui->actionContour,SIGNAL(triggered()),this,SLOT(contour()));
    connect(ui->actionAmelioration_Contour,SIGNAL(triggered()),this,SLOT(ameliorationContour()));
    connect(ui->actionRehaussement,SIGNAL(triggered()),this,SLOT(rehaussement()));
    connect(ui->actionFlou,SIGNAL(triggered()),this,SLOT(flou()));

    //BOUTON
    connect(ui->Crop, SIGNAL(clicked()), this, SLOT(crop()));
    connect(ui->Grey,SIGNAL(clicked()),this,SLOT(grey()));
    connect(ui->Histogramme,SIGNAL(clicked()),this,SLOT(histogramme()));
    connect(ui->Redimension,SIGNAL(clicked()),this,SLOT(redimension()));
    connect(ui->Fusionner,SIGNAL(clicked()),this,SLOT(fusionner()));
    connect(ui->SeamCarving,SIGNAL(clicked()),this,SLOT(seamCarving()));
    connect(ui->Mask,SIGNAL(clicked()),this,SLOT(masque()));
}

bool MainWindow::loadFile(const QString &fileName){
    QImageReader reader(fileName);
    const QImage image = reader.read();
    if (image.isNull()) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),tr("Cannot load %1.").arg(QDir::toNativeSeparators(fileName)));
        setWindowFilePath(QString());
        imageLabel->setPixmap(QPixmap());
        imageLabel->adjustSize();
        return false;
    }
    imageLabel->setPixmap(QPixmap::fromImage(image));
    afficherImage(image);
    c->ouvertureImage(image);
    QImage im = recupQImage();
    afficherImage(im);
    return true;
}

void MainWindow::open(){
    const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
    QFileDialog dialog(this, tr("Open File"),picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
    dialog.setAcceptMode(QFileDialog::AcceptOpen);

    //QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Images (*.png *.gif *.jpg *.jpeg)");
    while (dialog.exec() == QDialog::Accepted && !loadFile(dialog.selectedFiles().first())) {    }
}

void MainWindow::updateActions(){
}

void MainWindow::scaleImage(double factor){
    Q_ASSERT(imageLabel->pixmap());
    scaleFactor *= factor;
    imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());
    adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(scrollArea->verticalScrollBar(), factor);

}

void MainWindow::adjustScrollBar(QScrollBar *scrollBar, double factor){
    scrollBar->setValue(int(factor * scrollBar->value()+((factor - 1) * scrollBar->pageStep()/2)));
}

void MainWindow::fitToWindow(){
    bool fitToWindow = fitToWindowAct->isChecked();
    scrollArea->setWidgetResizable(fitToWindow);
    updateActions();
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event){
    if (obj == imageLabel) {
        if (event->type() == QEvent::MouseButtonPress) {
            pipette();
            return QMainWindow::eventFilter(obj, event);
        }
        else {
            return QMainWindow::eventFilter(obj, event);
        }
    } else {
        return QMainWindow::eventFilter(obj, event);
    }
}

QImage MainWindow::recupQImage(){
    QImage image(c->getSauvegardeImage().at(c->getIndexVecteur()).getLargeur(),c->getSauvegardeImage().at(c->getIndexVecteur()).getHauteur(),QImage::Format_RGB32);
    QRgb value;
    for (int h=0;h<image.height();h++){
        for(int l=0;l<image.width();l++){
            int v0 = c->getSauvegardeImage().at(c->getIndexVecteur()).getTableauPixel()[h][l].getEtatCourant()[0];
            int v1 = c->getSauvegardeImage().at(c->getIndexVecteur()).getTableauPixel()[h][l].getEtatCourant()[1];
            int v2 = c->getSauvegardeImage().at(c->getIndexVecteur()).getTableauPixel()[h][l].getEtatCourant()[2];
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

bool MainWindow::save(){
    QString fichier = QFileDialog::getSaveFileName(this, "Enregistrer un fichier", QString(), "Images (*.png *.gif *.jpg *.jpeg)");
    QImage image = recupQImage();
    image.save(fichier);
    return true;
}

void MainWindow::undo(){
    c->undo();
    QImage image= recupQImage();
    afficherImage(image);
}

void MainWindow::redo(){
    c->redo();
    QImage image= recupQImage();
    afficherImage(image);
}


void MainWindow::grey(){
    c->afficherGris();
    QImage image= recupQImage();
    afficherImage(image);
}

void MainWindow::crop(){
    c->crop(imageLabel->getOrigineSel().y(),imageLabel->getOrigineSel().x(),imageLabel->getFinSel().y(),imageLabel->getFinSel().x());
    QImage image= recupQImage();
    afficherImage(image);
}


void MainWindow::pipette(){
    if(ui->Pipette->isChecked()){
        int *rgb = c->affichageCouleurRGB(imageLabel->getPipette().y(),imageLabel->getPipette().x());
        double *yuv = c->affichageCouleurYUV(imageLabel->getPipette().y(),imageLabel->getPipette().x());
        int gris = c->affichageCouleurGris(imageLabel->getPipette().y(),imageLabel->getPipette().x());

        QString st;
        st = QString("Valeur RGB : %1, %2, %3 \n Valeur YUV : %4, %5, %6 \n Valeur gris : %7").arg(rgb[0]).arg(rgb[1]).arg(rgb[2]).arg(yuv[0]).arg(yuv[1]).arg(yuv[2]).arg(gris);
        ui->AffInfo->setPlainText(st);

    }
}

void MainWindow::rotation90D(){
    c->rotation("90D");
    QImage image = recupQImage();
    afficherImage(image);
}

void MainWindow::rotation90G(){
    c->rotation("90G");
    QImage image = recupQImage();
    afficherImage(image);
}

void MainWindow::rotation180(){
    c->rotation("180");
    QImage image = recupQImage();
    afficherImage(image);
}

void MainWindow::flou(){
    c->flou();
    QImage image = recupQImage();
    afficherImage(image);
}

void MainWindow::histogramme(){
        Histogramme *h = c->afficherHistogramme();
        FenHisto *fr = new FenHisto(h[0],Qt::red);
        FenHisto *fg = new FenHisto(h[1],Qt::green);
        FenHisto *fb = new FenHisto(h[2],Qt::blue);
        FenHisto *fgris = new FenHisto(h[0],Qt::gray);

        if (!(h[0].gris(h[1],h[2]))){
            fr->show();
            fg->show();
            fb->show();
        }
        else {
            fgris->show();
        }
}

void MainWindow::redimension(){
    DialogRedim d;
    d.setValue(c->getSauvegardeImage().at(c->getIndexVecteur()).getHauteur(),c->getSauvegardeImage().at(c->getIndexVecteur()).getLargeur());
    int h,l;
    if(d.exec() == QDialog::Accepted) {
        h=d.getH();
        l=d.getL();
    }
    c->redimension(h,l);
    QImage image = recupQImage();
    afficherImage(image);
}

bool MainWindow::loadFile_fusion(const QString &fileName){
    QImageReader reader(fileName);
    const QImage image = reader.read();
    if (image.isNull()) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1.").arg(QDir::toNativeSeparators(fileName)));
        setWindowFilePath(QString());
        imageFusion->setPixmap(QPixmap());
        imageFusion->adjustSize();
        return false;
    }
    imageFusion->setPixmap(QPixmap::fromImage(image));
    scaleFactor = 1.0;
    fitToWindowAct->setEnabled(true);
    if (!fitToWindowAct->isChecked())
        imageFusion->adjustSize();
    c->ouvertureImage(image);
    return true;
}

void MainWindow::open_fusion(){
    const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
    QFileDialog dialog(this, tr("Open File"),picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
    dialog.setAcceptMode(QFileDialog::AcceptOpen);

    //QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Images (*.png *.gif *.jpg *.jpeg)");
    while (dialog.exec() == QDialog::Accepted && !loadFile_fusion(dialog.selectedFiles().first())) {    }
}

void MainWindow::fusion(){
    imageFusion = new ImageViewer;
    imageFusion->setScaledContents(true);
    scrollAreaFusion = new QScrollArea;
    scrollAreaFusion->setBackgroundRole(QPalette::Dark);
    scrollAreaFusion->setWidget(imageFusion);
    scrollAreaFusion->setMinimumWidth(800);
    scrollAreaFusion->setMinimumHeight(800);
    open_fusion();
    scrollAreaFusion->show();
}

void MainWindow::fusionner(){
    DialogFusion d;
    d.setValue(0,0);
    int hmax,lmax;
    int finSelY = imageFusion->getFinSel().y();
    int finSelX = imageFusion->getFinSel().x();
    int origineSelX = imageFusion->getOrigineSel().x();
    int origineSelY = imageFusion->getOrigineSel().y();
    int minX = min(origineSelX,finSelX);
    int minY = min(origineSelY,finSelY);
    int maxX = max(origineSelX,finSelX);
    int maxY = max(origineSelY,finSelY);
    int hauteur = c->getSauvegardeImage().at(c->getIndexVecteur()).getHauteur();
    int largeur = c->getSauvegardeImage().at(c->getIndexVecteur()).getLargeur();

    if(minX < 0)
        minX = 0;
    if(minY < 0)
        minY = 0;
    if(maxX > largeur)
        maxX = largeur;
    if(maxY > hauteur)
        maxY = hauteur;

    hmax = hauteur + maxX - minX;
    lmax = largeur + maxY - minY;

    d.setValueMax(hmax,lmax);
    int h,l;
    if(d.exec() == QDialog::Accepted) {
        h=d.getY();
        l=d.getX();


        c->fusion(minY,minX,maxY,maxX,h,l);
        QImage image = recupQImage();
        afficherImage(image);
    }
    imageFusion->close();
    scrollAreaFusion->close();


}

void MainWindow::recadrer(){
    c->etalementHistogramme();
    QImage image = recupQImage();
    afficherImage(image);
}

void MainWindow::egaliser(){
    c->egalisation();
    QImage image = recupQImage();
    afficherImage(image);
}

void MainWindow::negatif(){
    c->negatif();
    QImage image = recupQImage();
    afficherImage(image);
}

void MainWindow::gradientX(){
    c->gradientX();
    QImage image = recupQImage();
    afficherImage(image);
}

void MainWindow::gradientY(){
    c->gradientY();
    QImage image = recupQImage();
    afficherImage(image);
}
void MainWindow::contour(){
    c->contour();
    QImage image = recupQImage();
    afficherImage(image);
}

void MainWindow::ameliorationContour(){
    c->ameliorationContour();
    QImage image = recupQImage();
    afficherImage(image);
}

void MainWindow::rehaussement(){
    c->rehaussement();
    QImage image = recupQImage();
    afficherImage(image);
}

void MainWindow::seamCarving(){
    c->seamCarving(150,150);
    QImage image = recupQImage();
    afficherImage(image);
}

void MainWindow::masque(){
    DialogMasque_T d;
    d.setText("hauteur/largeur");
    int tmp;
    if(d.exec() == QDialog::Accepted) {
        tmp = d.getValue();
    }
    Masque m = Masque(tmp);

    for(int i =0;i<m.getLongueur();i++){
        for(int j =0;j<m.getLongueur();j++){
            d.setText(QString("Valeur(%1,%2)").arg(i).arg(j));
            d.setSpin();
            if(d.exec() == QDialog::Accepted) {
                m.setValeurTableauMasque(i,j,d.getValue());
            }
        }
    }

    int coeff = 0;
    int sumMask = m.sommeMasque();
    if (sumMask <=0 ) {
        coeff = 1;
    }
    else {
        coeff = sumMask;
    }

    c->appliquerMasque(m,coeff);
    QImage image = recupQImage();
    afficherImage(image);
}


MainWindow::~MainWindow(){
    delete ui;
}
