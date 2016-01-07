#include <iostream>
#include <string>
#include "Image.h"

using namespace std;

void Image::setTableauPixel(int h, int l){


    tableauPixel = (Pixel**)malloc(h * sizeof(Pixel*));
    for(int i = 0; i<h;i++){
        tableauPixel[i] = (Pixel*)malloc(l* sizeof(Pixel));
    }
}

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

int* Image::getRGB(int h, int l){
    return tableauPixel[h][l].getRGBCouleur();
}

void Image::setGray(){
    for(int i= 0 ; i <largeur; i++){
        for(int j =0; j < hauteur; j++){
            tableauPixel[i][j].setGraywithRGB(tableauPixel[i][j].getRGBCouleur());
        }
    }
}
