#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Controle.h"

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



    imageLabel = new QLabel;
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    r = new QRubberBand(QRubberBand::Rectangle,imageLabel);

    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    setCentralWidget(scrollArea);



    setWindowTitle(tr("GMN"));

    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));
    connect(ui->Grey,SIGNAL(clicked()),this,SLOT(grey()));
    connect(saveAct,SIGNAL(triggered()), this, SLOT(save()));
    connect(ui->Crop, SIGNAL(toggled(bool)), this, SLOT(Crop()));

}

bool MainWindow::loadFile(const QString &fileName)
{
    QImageReader reader(fileName);

    reader.setAutoTransform(true);

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

    QImage image= recupQImage();
    QRgb value;
    for (int h=0;h<image.height();h++){
        for(int l=0;l<image.width();l++){
            int v = c.getSauvegardeImage().at(c.getIndexVecteur()).getTableauPixel()[h][l].getGris();
            value = qRgb(v, v, v);
            image.setPixel(l,h,value);
        }
    }
    afficherImage(image);

}

QImage MainWindow::recupQImage(){

    QImage image(c.getSauvegardeImage().at(c.getIndexVecteur()).getLargeur(),c.getSauvegardeImage().at(c.getIndexVecteur()).getHauteur(),QImage::Format_RGB32);
    QRgb value;
    c.getSauvegardeImage().at(c.getIndexVecteur()).setGray();
    for (int h=0;h<image.height();h++){
        for(int l=0;l<image.width();l++){
            int* v = c.getSauvegardeImage().at(c.getIndexVecteur()).getTableauPixel()[h][l].getRGBCouleur();
            value = qRgb(v[0], v[1], v[2]);
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


}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    r->hide();
    if (event->button() == Qt::LeftButton && ui->Crop->isChecked()) {
        origineSel.setX(event->pos().x() - ui->Outils->width());
        origineSel.setY(event->pos().y() - ui->Outils->pos().y());
        if(origineSel.x()<9){
            origineSel.setX(0);
        }
        if(origineSel.y()<0){
            origineSel.setY(0);
        }
        cout<<origineSel.x()<<endl;
        cout<<origineSel.y()<<endl;
        cout<<""<<endl;
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (ui->Crop->isChecked()){
        qreal x = origineSel.x(), y = origineSel.y(), w = event->pos().x() - origineSel.x() - ui->Outils->width(), h = event->pos().y() - origineSel.y() - ui->Outils->pos().y();
        if(x > event->x()- ui->Outils->width()) {
            x = event->x()- ui->Outils->width();
            w *= -1;
        }
        if(y > event->y()- ui->Outils->pos().y()) {
            y = event->y()- ui->Outils->pos().y();
            h *= -1;
        }

        if (x + w > imageLabel->width()) {
            w = imageLabel->width() - x;
        }
        if (x < 0) {
            w += x;
            x = 0;
        }
        if (y + h > imageLabel->height()) {
            h = imageLabel->height() - y;
        }
        if (y < 0) {
            h += y;
            y = 0;
        }
        r->setGeometry(x, y, w, h);
        r->show();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && ui->Crop->isChecked()) {
        finSel.setX(event->pos().x() - ui->Outils->width());
        finSel.setY(event->pos().y() - ui->Outils->pos().y());
        if(finSel.x()<9){
            finSel.setX(0);
        }
        if(finSel.y()<0){
            finSel.setY(0);
        }
        cout<<finSel.x()<<endl;
        cout<<finSel.y()<<endl;
        cout<<""<<endl;

    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
