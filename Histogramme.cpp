#include <iostream>
#include <string>
#include "Histogramme.h"
#include "Pixel.h"

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

//Retourne la nouvelle valeur du pixel
int Histogramme::egaliser(int k, int l){
    //T(xk) = (L-1)/n * somme (nj) j->k
    int n =0;
    int sum =0;
    for (int i=0;i<NBNUANCES;i++){
        n+=tableauHistogramme[i];
        if (i<=k){
            sum+=tableauHistogramme[i];
        }
    }
    tableauHistogramme[k]--;
    tableauHistogramme[((l-1)*sum)/n]++;
    return ((l-1)*sum)/n;

}

void Histogramme::decrementeValeurHistogramme(int val){
    tableauHistogramme[val]--;
}

void Histogramme::incrementeValeurHistogramme(int val){
    tableauHistogramme[val]++;
}

int Histogramme::getValeurIndiceHistogramme(int ind){
    return tableauHistogramme[ind];
}
