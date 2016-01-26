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
        u = -0.14713* tab[0] - 0.28886*tab[1] + 0.436*tab[2];
        v = 0.615* tab[0] -0.51499*tab[1] - 0.10001*tab[2];

        yuv[0] = y;
        yuv[1] = u;
        yuv[2] = v;

}

void Pixel::setRGBwithYUV(double yuv[]){
    rgb[0] = yuv[0] + 1.13983*yuv[2];
    rgb[1] = yuv[0] - 0.39465*yuv[1] -0.5806*yuv[2];
    rgb[2] = yuv[0] + 2.03211*yuv[1];
    if (rgb[0]<0){
        rgb[0]=0;
    }
    else if (rgb[0]>255){
        rgb[0]=255;
    }
    if (rgb[1]<0){
        rgb[1]=0;
    }
    else if (rgb[1]>255){
        rgb[1]=255;
    }
    if (rgb[2]<0){
        rgb[2]=0;
    }
    else if (rgb[2]>255){
        rgb[2]=255;
    }
}

void Pixel::setYUV(int ind, double val){
    yuv[ind] = val;
}

double Pixel::getSingleYUV(int ind){
    return yuv[ind];
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

double* Pixel::getYUVCouleur(){
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

int Pixel::getSingleRGB(int ind){
    return rgb[ind];
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

 void Pixel::setCouleur(string coul, int tabCoul[NBCOULEUR]){
     for(int k=0; k<NBCOULEUR; k++){
         if(coul == "rgb"){
             setRGBCouleur(k,tabCoul[k]);
             setEtatCourant(1);
         }
         else if(coul == "gris"){
             setGris(tabCoul[0]);
             setEtatCourant(3);
         }

     }

     if(coul == "rgb"){
         setYUVwithRGB(getRGBCouleur());
         setGraywithRGB(getRGBCouleur());
     }
 }

 double Pixel::getEnergie() const
 {
     return energie;
 }

 void Pixel::setEnergie(int val){
    energie = val;
 }

