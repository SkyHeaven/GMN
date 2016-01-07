#include "MainWindow.h"
#include "ui_mainwindow.h"
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

    imageLabel = new QLabel;
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    setCentralWidget(scrollArea);

    setWindowTitle(tr("Image Viewer"));
    resize(500, 400);

    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));
    connect(ui->Grey,SIGNAL(clicked()),this,SLOT(grey()));
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
    scaleFactor = 1.0;
    fitToWindowAct->setEnabled(true);
    updateActions();

    if (!fitToWindowAct->isChecked())
        imageLabel->adjustSize();

    setWindowFilePath(fileName);
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

    QImage image(c.getSauvegardeImage().at(c.getIndexVecteur()).getLargeur(),c.getSauvegardeImage().at(c.getIndexVecteur()).getHauteur(),QImage::Format_RGB32);
    QRgb value;
    for (int h=0;h<image.height();h++){
        for(int l=0;l<image.width();l++){
            int v = c.getSauvegardeImage().at(c.getIndexVecteur()).getTableauPixel()[h][l].getGris();
            value = qRgb(v, v, v);
            image.setPixel(l,h,value);

        }
    }
    imageLabel->setPixmap(QPixmap::fromImage(image));
    scaleFactor = 1.0;
    fitToWindowAct->setEnabled(true);
    updateActions();

    if (!fitToWindowAct->isChecked())
        imageLabel->adjustSize();
}

MainWindow::~MainWindow()
{
    delete ui;
}
