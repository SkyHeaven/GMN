#ifndef DIALOGREDIM_H
#define DIALOGREDIM_H

#include <QDialog>

namespace Ui {
    class DialogRedim;
}

class DialogRedim : public QDialog{
    Q_OBJECT
    private:
        Ui::DialogRedim *ui;
        double coeff;

    private slots:
        void setcheckbox();
        void setValue_L(int x);
        void setValue_H(int x);

    public:
        DialogRedim(QWidget *parent=0);
        ~DialogRedim();
        void setValue(int h, int l);
        int getH();
        int getL();
        void seam();
};

#endif // DIALOGREDIM_H
