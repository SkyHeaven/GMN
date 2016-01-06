#include <iostream>
#include <string>
#include "Image.h"

using namespace std;

void Image::setPixel(int x, int y, Pixel p){
    tableauPixel[x][y] = p;
}

int Image::getHauteur(){
    return hauteur;
}
void Image::setHauteur(int h){
    hauteur = h;
}

int Image::getLargeur(){
    return largeur;
}

void Image::setLargeur(int l){
    largeur = l;
}
