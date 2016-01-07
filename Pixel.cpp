#include <iostream>
#include <string>
#include "Pixel.h"

using namespace std;

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

int* Pixel::getYUV(int y, int u, int v){
    return yuv;
}

void setX(double x){
    x = x;
}

void setY(double y){
    y = y;
}

void Pixel::setRGBCouleur(int ind, int val){
    rgb[ind] = val;
}

int* Pixel::getRGBCouleur(){
    return rgb;
}
