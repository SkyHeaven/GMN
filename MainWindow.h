#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "Controle.h"

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

private:
    Ui::MainWindow *ui;
    bool loadFile(const QString &fileName);
    void updateActions();
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);
    QImage recupQImage();
    void afficherImage(QImage image);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    Controle c;

    QLabel *imageLabel;
    QScrollArea *scrollArea;
    double scaleFactor;
    QString curFile;
    QPlainTextEdit *textEdit;
    QPoint origineSel,finSel;
    QGraphicsView *sel;
    QRubberBand *r;

    QAction *openAct;
    QAction *fitToWindowAct;
    QAction *saveAct;
    QAction *undoAct;
    QAction *redoAct;

};

#endif // MAINWINDOW_H
