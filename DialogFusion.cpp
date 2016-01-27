#include <iostream>
#include <string>
#include "DialogFusion.h"
#include "ui_DialogFusion.h"

DialogFusion::DialogFusion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogFusion)
{
    ui->setupUi(this);
}

void DialogFusion::setValue(int x,int y){
    ui->spinBoxX->setValue(x);
    ui->spinBoxY->setValue(y);
}

void DialogFusion::setValueMax(int x,int y){
    ui->spinBoxX->setMaximum(x);
    ui->spinBoxY->setMaximum(y);
}

int DialogFusion::getX(){
    return ui->spinBoxX->value();
}

int DialogFusion::getY(){
    return ui->spinBoxY->value();
}

DialogFusion::~DialogFusion(){
    delete ui;
}
