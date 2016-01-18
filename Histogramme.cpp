#include <iostream>
#include <string>
#include "Histogramme.h"

using namespace std;


Histogramme::Histogramme(){
    this->initZero();
}

int *Histogramme::getTableauHistogramme(){
    return tableauHistogramme;
}

void Histogramme::initZero(){
    for(int i = 0; i<NBNUANCES; i++){
        tableauHistogramme[i] = 0;
    }
}

bool Histogramme::gris(Histogramme h1, Histogramme h2){
    bool egal = true;
    for(int i=0;i<NBNUANCES;i++){
        if (!(h1.getTableauHistogramme()[i]==h2.getTableauHistogramme()[i] && h1.getTableauHistogramme()[i]==tableauHistogramme[i] && h2.getTableauHistogramme()[i]==tableauHistogramme[i])){
            egal = false;
        }
    }
    return egal;
}

Histogramme egaliser(Histogramme hist){

}

void Histogramme::incrementeValeurHistogramme(int val){
    tableauHistogramme[val]++;
}

int Histogramme::getValeurIndiceHistogramme(int ind){
    return tableauHistogramme[ind];
}
