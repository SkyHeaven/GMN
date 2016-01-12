#include <iostream>
#include <string>
#include "Masque.h"

using namespace std;

Masque::Masque(int nb){
  longueur =nb;
  //tableauMasque = new int[longueur][longueur];
  for(int i=0; i<nb; i++){
      for(int j=0; j<nb; j++){
          tableauMasque[i][j] = 1;
      }
  }
}

Masque::~Masque(){
    for(int i = 0 ; i < longueur ; i++){
        delete[] tableauMasque[i];
     }
     delete[] tableauMasque;
}

void Masque::remplirMasque(){
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
