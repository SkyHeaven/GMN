#include "DialogMasque_T.h"
#include "ui_DialogMasque_T.h"

DialogMasque_T::DialogMasque_T(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogMasque_T)
{
    ui->setupUi(this);
}

void DialogMasque_T::setText(QString s){
    ui->lineEdit->setText(s);
}

int DialogMasque_T::getValue(){
    return ui->spinBox->value();
}

void DialogMasque_T::setSpin(){
    ui->spinBox->setRange(-500,500);
    ui->spinBox->setSingleStep(1);
    ui->spinBox->setValue(0);
}

DialogMasque_T::~DialogMasque_T()
{
    delete ui;
}
