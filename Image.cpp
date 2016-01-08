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
    for(int i = 0; i < hauteur; i++){
        for(int j = 0; j < largeur; j++){
            Pixel p = Pixel(j,i);
            img.setPixel(j,i,p);

        }
    }
    return img;
}

Image Image::cropImage(Pixel pixel1,Pixel pixel2){
    Image imgRes;
    imgRes.setHauteur(pixel2.getY() - pixel1.getY());
    imgRes.setLargeur(pixel2.getX() - pixel1.getX());
    int diffX = pixel1.getX();
    int diffY = pixel1.getY();

    for(int i = pixel1.getY(); i < pixel2.getY(); i++){
        for(int j = pixel1.getX(); j < pixel2.getX(); j++){
            imgRes.setPixel(j-diffY,i-diffX, this->getTableauPixel()[i][j]);
        }
    }
    return imgRes;
}
