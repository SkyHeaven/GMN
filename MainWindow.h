#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <iostream>
#include <string>
#include "Controle.h"
#include "ImageViewer.h"
#include "FenHisto.h"
#include "DialogRedim.h"
#include "DialogFusion.h"
#include "DialogMasque_T.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
    private:
    Ui::MainWindow *ui;
    bool loadFile(const QString &fileName);
    void updateActions();
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);
    QImage recupQImage();
    void afficherImage(QImage image);
    bool eventFilter(QObject *obj, QEvent *event);
    Controle *c;
    ImageViewer *imageLabel;
    ImageViewer *imageFusion;
    QScrollArea *scrollArea;
    QScrollArea *scrollAreaFusion;
    double scaleFactor;
    QString curFile;
    QPlainTextEdit *textEdit;
    QPoint origineSel,finSel,pip;
    QGraphicsView *sel;
    QRubberBand *r;
    qint64  pixmapKey;
    QAction *openAct;
    QAction *fitToWindowAct;
    QAction *saveAct;
    QAction *undoAct;
    QAction *redoAct;
    void open_fusion();
    bool loadFile_fusion(const QString &fileName);

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();
        void Redimension();

private slots:
        void open();
        void fitToWindow();
        bool save();
        void grey();
        void crop();
        void undo();
        void redo();

        //Couleur pixel
        void pipette();

        //Rotation
        void rotation90D();
        void rotation90G();
        void rotation180();

        //Histogramme
        void histogramme();
        void recadrer();
        void egaliser();

        //Redimension
        void redimension();

        //Fusion
        void fusion();
        void fusionner();

        //Les filtres
        void masque();
        void flou();
        void negatif();
        void gradientX();
        void gradientY();
        void contour();
        void ameliorationContour();
        void rehaussement();

        //SeamCarving
        void seamCarving();
};

#endif // MAINWINDOW_H
