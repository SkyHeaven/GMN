#include <iostream>
#include <string>
#include "Histogramme.h"

using namespace std;

void Histogramme::initZero(){
    for(int i = 0; i<NBNUANCES; i++){
        tableauHistogramme[i] = 0;
    }
}

Histogramme egaliser(Histogramme hist){

}

void Histogramme::incrementeValeurHistogramme(int val){
    tableauHistogramme[val]++;
}
