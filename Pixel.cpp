#include <iostream>
#include <string>
#include "Pixel.h"

using namespace std;

int Pixel::getGris() const
{
    return gris;
}

void Pixel::setGris(int value)
{
    gris = value;
}

Pixel::Pixel(double x , double y){
    x = x;
    y = y;
}

void Pixel::setYUVwithRGB(int rgb[]){
        double y,u,v = 0;
        double tab[NBCOULEUR];
        for(int i =0; i<NBCOULEUR; i++){
            tab[i] = (double)rgb[i];
        }
        y = 0.299* tab[0] + 0.587*tab[1] + 0.114*tab[2];
        u = -0.147* tab[0] - 0.289*tab[1] + 0.436*tab[2];
        v = 0.615* tab[0] -0.515*tab[1] - 0.1*tab[2];

        yuv[0] = (int)y;
        yuv[1] = (int)u;
        yuv[2] = (int)v;

}



void Pixel::setGraywithRGB(int rgb[]){
    double g =0;
    double tab[NBCOULEUR];
    for(int i =0; i<NBCOULEUR; i++){
        tab[i] = (double)rgb[i];
    }
    g = (tab[0] + tab[1] +tab[2])/ 3;
    gris = (int)g;
}

int Pixel::getGrayCouleur(){
    return gris;
}

int* Pixel::getYUVCouleur(){
    return yuv;
}

int Pixel::getX(){
    return x;
}

void Pixel::setX(int value){
    x = value;
}

int Pixel::getY(){
    return y;
}

void Pixel::setY(int value){
    y = value;
}

void Pixel::setRGBCouleur(int ind, int val){
    rgb[ind] = val;
}

int* Pixel::getRGBCouleur(){
    return rgb;
}

void Pixel::setEtatCourant(int c){
    switch(c){
    case 1 :
        for(int ind=0; ind <NBCOULEUR; ind++){
            etatCourant[ind] = rgb[ind];
        }
        break;
    case 2 :
        for(int ind=0; ind <NBCOULEUR; ind++){
            etatCourant[ind] = yuv[ind];
        }
        break;
    case 3 :
        for(int ind=0; ind <NBCOULEUR; ind++){
            etatCourant[ind] = gris;
        }
        break;
    }
}

int* Pixel::getEtatCourant(){
    return etatCourant;
}

