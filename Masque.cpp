#include <iostream>
#include <string>
#include "Masque.h"

using namespace std;

Masque::Masque(const int nb){
  longueur = nb;
  tableauMasque = new int *[nb];
  for(int i =0; i <nb; i++){
      tableauMasque[i] = new int[nb];
  }
}

int Masque::getLongueur(){
    return longueur;
}

void Masque::setLongueur(int value){
    longueur = value;
}

int Masque::getValeurTableauMasque(int h, int l){
    return tableauMasque[h][l];
}

void Masque::setValeurTableauMasque(int h, int l, int v){
    tableauMasque[h][l] = v;
}

int Masque::sommeMasque(){
    int cpt=0;
    for(int i=0; i<longueur; i++){
        for(int j=0; j<longueur; j++){
            cpt += tableauMasque[i][j];
        }
    }
    return cpt;
}

void Masque::masqueFlou(){
    for(int i=0; i<longueur; i++){
        for(int j=0; j<longueur; j++){
            tableauMasque[i][j] = 1;
        }
    }
}

void Masque::masqueGradienY(){
    tableauMasque[0][0] = 1;
    tableauMasque[0][1] = 2;
    tableauMasque[0][2] = 1;
    tableauMasque[1][0] = 0;
    tableauMasque[1][1] = 0;
    tableauMasque[1][2] = 0;
    tableauMasque[2][0] = -1;
    tableauMasque[2][1] = -2;
    tableauMasque[2][2] = -1;
}

void Masque::masqueGradienX(){
    tableauMasque[0][0] = 1;
    tableauMasque[0][1] = 0;
    tableauMasque[0][2] = -1;
    tableauMasque[1][0] = 2;
    tableauMasque[1][1] = 0;
    tableauMasque[1][2] = -2;
    tableauMasque[2][0] = 1;
    tableauMasque[2][1] = 0;
    tableauMasque[2][2] = -1;
}

void Masque::masqueRehaussement(){
    tableauMasque[0][0] = -1;
    tableauMasque[0][1] = -1;
    tableauMasque[0][2] = -1;
    tableauMasque[1][0] = -1;
    tableauMasque[1][1] = 18;
    tableauMasque[1][2] = -1;
    tableauMasque[2][0] = -1;
    tableauMasque[2][1] = -1;
    tableauMasque[2][2] = -1;
}
