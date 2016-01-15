#ifndef DIALOGREDIM_H
#define DIALOGREDIM_H

#include <QDialog>

namespace Ui {
class DialogRedim;
}

class DialogRedim : public QDialog
{
    Q_OBJECT

public:
    DialogRedim(QWidget *parent=0);
    ~DialogRedim();


    void setValue(int h, int l);
    int getH();
    int getL();

private slots:
    void setcheckbox();
    void setValue_L(int x);
    void setValue_H(int x);

private:
    Ui::DialogRedim *ui;
    double coeff;
};

#endif // DIALOGREDIM_H
