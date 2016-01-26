#ifndef DIALOGMASQUE_T_H
#define DIALOGMASQUE_T_H

#include <QDialog>

namespace Ui {
class DialogMasque_T;
}

class DialogMasque_T : public QDialog
{
    Q_OBJECT

public:
    explicit DialogMasque_T(QWidget *parent = 0);
    ~DialogMasque_T();

    void setText(QString s);
    int getValue();
    void setSpin();
private:
    Ui::DialogMasque_T *ui;
};

#endif // DIALOGMASQUE_T_H
