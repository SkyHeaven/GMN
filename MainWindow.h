#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <iostream>
#include <string>

#include "Controle.h"
#include "ImageViewer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void open();
    void fitToWindow();
    bool save();
    void grey();
    void crop();
    void undo();
    void redo();
    void pipette();
    void rotation90();
    void rotation180();
    void flou();

private:
    Ui::MainWindow *ui;
    bool loadFile(const QString &fileName);
    void updateActions();
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);
    QImage recupQImage();
    void afficherImage(QImage image);
    bool eventFilter(QObject *obj, QEvent *event);
//    void mousePressEvent(QMouseEvent *event);
//    void mouseMoveEvent(QMouseEvent *event);
//    void mouseReleaseEvent(QMouseEvent *event);


    Controle c;

    ImageViewer *imageLabel;
    QScrollArea *scrollArea;
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

};

#endif // MAINWINDOW_H
