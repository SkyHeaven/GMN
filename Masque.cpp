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

//Masque::~Masque(){
//    for(int i = 0 ; i < longueur ; i++){
//        delete[] tableauMasque[i];
//     }
//     delete[] tableauMasque;
//}

void Masque::remplirMasque(){
    for(int i=0; i<longueur; i++){
        for(int j=0; j<longueur; j++){
            tableauMasque[i][j] = 1;
        }
    }
}


int Masque::getLongueur() const
{
    return longueur;
}

void Masque::setLongueur(int value)
{
    longueur = value;
}

int Masque::getValeurTableauMasque(int h, int l){
    return tableauMasque[h][l];
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
