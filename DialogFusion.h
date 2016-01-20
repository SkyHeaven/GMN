#ifndef DIALOGFUSION_H
#define DIALOGFUSION_H

#include <QDialog>

namespace Ui {
class DialogFusion;
}

class DialogFusion : public QDialog
{
    Q_OBJECT

public:
    explicit DialogFusion(QWidget *parent = 0);
    ~DialogFusion();

    int getX();
    int getY();
    void setValueMax(int x, int y);
    void setValue(int x, int y);
private:
    Ui::DialogFusion *ui;
};

#endif // DIALOGFUSION_H
