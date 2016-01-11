#include <iostream>
#include <string>
#include "Masque.h"

using namespace std;

Masque::Masque(int nb){
  longueur =nb;
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

int Masque::sommeMasque(){
    int cpt=0;
    for(int i=0; i<longueur; i++){
        for(int j=0; j<longueur; j++){
            cpt += tableauMasque[i][j];
        }
    }
    return cpt;
}
