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
    bool saveAs();
    void grey();
    void documentWasModified();

private:
    Ui::MainWindow *ui;
    bool loadFile(const QString &fileName);
    void updateActions();
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);
    QImage recupQImage();
    bool maybeSave();
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);

    Controle c;

    QLabel *imageLabel;
    QScrollArea *scrollArea;
    double scaleFactor;
    QString curFile;
    QPlainTextEdit *textEdit;

    QAction *openAct;
    QAction *fitToWindowAct;
    QAction *saveAct;
    QAction *saveAsAct;

};

#endif // MAINWINDOW_H
