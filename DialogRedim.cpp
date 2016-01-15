#include "DialogRedim.h"
#include "ui_DialogRedim.h"

#include <iostream>
#include <string>

DialogRedim::DialogRedim(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogRedim)
{
    ui->setupUi(this);


    connect(ui->checkBox_H,SIGNAL(clicked(bool)),this,SLOT(setcheckbox()));
    connect(ui->checkBox_L,SIGNAL(clicked(bool)),this,SLOT(setcheckbox()));
    connect(ui->spinBox_H,SIGNAL(valueChanged(int)),this,SLOT(setValue_L(int)));
    connect(ui->spinBox_L,SIGNAL(valueChanged(int)),this,SLOT(setValue_H(int)));

}

void DialogRedim::setValue_L(int x){
    double res = (double)x*coeff;
    if(ui->checkBox_H->isChecked()){
        ui->spinBox_L->setValue((int)res);
    }
}

void DialogRedim::setValue_H(int x){
    double res = (double)x/coeff;
    if(ui->checkBox_L->isChecked()){
        ui->spinBox_H->setValue((int)res);
    }
}

void DialogRedim::setcheckbox(){
    if(ui->checkBox_H->isChecked()){
        ui->checkBox_L->setChecked(false);
    }
    else if (ui->checkBox_L->isChecked()){
        ui->checkBox_H->setChecked(false);
    }
}


void DialogRedim::setValue(int h,int l){
    ui->spinBox_H->setValue(h);
    ui->spinBox_L->setValue(l);
    coeff = (double)l/(double)h;
}

int DialogRedim::getH(){
    return ui->spinBox_H->value();
}

int DialogRedim::getL(){
    return ui->spinBox_L->value();
}

DialogRedim::~DialogRedim()
{
    delete ui;
}
