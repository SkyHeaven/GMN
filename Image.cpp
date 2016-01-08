#include <iostream>
#include <string>
#include "Image.h"

using namespace std;

Pixel **Image::getTableauPixel() const
{
    return tableauPixel;
}

void Image::setTableauPixel(int h, int l){
    tableauPixel = (Pixel**)malloc(h * sizeof(Pixel*));
    for(int i = 0; i<h;i++){
        tableauPixel[i] = (Pixel*)malloc(l* sizeof(Pixel));
    }
}

void Image::setPixel(int h, int l, Pixel p){
    tableauPixel[h][l] = p;
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
    for(int i= 0 ; i <hauteur; i++){
        for(int j =0; j < largeur; j++){
            tableauPixel[i][j].setGraywithRGB(tableauPixel[i][j].getRGBCouleur());
        }
    }
}

void Image::setYUV(){
    for(int i= 0 ; i <hauteur; i++){
        for(int j =0; j < largeur; j++){
            tableauPixel[i][j].setYUVwithRGB(tableauPixel[i][j].getRGBCouleur());
        }
    }
}

void Image::setTableauCourant(int c){
    for(int i= 0 ; i <hauteur; i++){
        for(int j =0; j < largeur; j++){
            tableauPixel[i][j].setEtatCourant(c);
        }
    }
}
Image Image::cloneImage(){
    Image img;
    img.setHauteur(hauteur);
    img.setLargeur(largeur);
    img.setTableauPixel(hauteur,largeur);
    for(int i = 0; i < hauteur; i++){
        for(int j = 0; j < largeur; j++){
            Pixel p = Pixel((double)j,(double)i);
            p = tableauPixel[i][j];
            img.setPixel(i,j,p);
        }
    }
    return img;
}

Image Image::cropImage(Pixel pixel1,Pixel pixel2){
    Image imgRes;
    int minX = min(pixel1.getX(), pixel2.getX());
    int minY = min(pixel1.getY(), pixel2.getY());
    int maxX = max(pixel1.getX(), pixel2.getX());
    int maxY = max(pixel1.getY(), pixel2.getY());
    int diffX = maxX - minX;
    int diffY = maxY - minY;

    imgRes.setHauteur(maxY - minY);
    imgRes.setLargeur(maxX - minX);
    for(int i = minY; i < maxY; i++){
        for(int j = minX; j < maxX; j++){
            imgRes.setPixel(j-diffY,i-diffX, this->getTableauPixel()[i][j]);
        }
    }
    return imgRes;
}
