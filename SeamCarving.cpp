#include "SeamCarving.h"
#include <QApplication>
#include <iostream>
#include <string>
using namespace std;

SeamCarving::SeamCarving(){
    ind_min = 0;
}

void SeamCarving::setImg(Image image){
    this->img = image;
    this->img.setEnergiePixel();
    int h = img.getHauteur();
    int l = img.getLargeur();

    tabChemin = (Pixel**)malloc(h * sizeof(Pixel*));
    for(int i = 0; i<h;i++){
        tabChemin[i] = (Pixel*)malloc(l* sizeof(Pixel));
    }

    tabEnergy = (int**)malloc(h * sizeof(int*));
    for(int i = 0; i<h;i++){
        tabEnergy[i] = (int*)malloc(l* sizeof(int));
    }
}
void SeamCarving::resetEnergy(){
    for(int i=0; i<img.getHauteur(); i++){
        for(int j=0; j<img.getLargeur(); j++){
            tabEnergy[i][j]=0;
        }
    }
}

Image SeamCarving::getImg(){
    return img;
}

void SeamCarving::seamVertical(){
    int h = img.getHauteur();
    int l = img.getLargeur();
    string coul = img.quelleCouleur();

    for(int i = 0; i<h;i++){
        for(int j = 0; j<l;j++){
            tabEnergy[i][j] = img.getPixel(i,j).getEnergie();
        }
    }

    //Chercher chemin
    for(int i=1; i<img.getHauteur();i++){
        for(int j=0; j<img.getLargeur(); j++){
            Pixel vois1 = img.getPixel(0,0);
            Pixel vois2 = img.getPixel(0,0);
            Pixel vois3 = img.getPixel(0,0);
            int nombreVoisin,energyVois1,energyVois2,energyVois3,energymin;

            if ( j == 0){
                nombreVoisin = 2;
                vois1 = img.getPixel(i-1,j); //voisM
                vois2 = img.getPixel(i-1,j+1);//voisD
            }
            else if(j == l-1){
                nombreVoisin = 2;
                vois1 = img.getPixel(i-1,j-1);//voisG
                vois2 = img.getPixel(i-1,j);//voisM
            }
            else {
                nombreVoisin = 3;
                vois1 = img.getPixel(i-1,j-1);
                vois2 = img.getPixel(i-1,j);
                vois3 = img.getPixel(i-1,j+1);
            }

            if (nombreVoisin == 2){
                energyVois1 = tabEnergy[vois1.getY()][vois1.getX()];
                energyVois2 = tabEnergy[vois2.getY()][vois2.getX()];
                energymin = min(energyVois1,energyVois2);
            }
            else {
                energyVois1 = tabEnergy[vois1.getY()][vois1.getX()];
                energyVois2 = tabEnergy[vois2.getY()][vois2.getX()];
                energyVois3 = tabEnergy[vois3.getY()][vois3.getX()];
                energymin = min(min(energyVois1,energyVois2),energyVois3);
            }

            if (energymin == energyVois1) {
                tabChemin[i][j] = vois1;
                tabEnergy[i][j] += tabEnergy[vois1.getY()][vois1.getX()];
            }
            else if (energymin == energyVois2) {
                tabChemin[i][j] = vois2;
                tabEnergy[i][j] += tabEnergy[vois2.getY()][vois2.getX()];
            }
            else {
                tabChemin[i][j] = vois3;
                tabEnergy[i][j] += tabEnergy[vois3.getY()][vois3.getX()];
            }
        }
    }

    int sumc,summ;
    summ = INT_MAX;
    for(int j=1; j<l; j++){
        sumc = abs(tabEnergy[h-1][j]);
        if (sumc < summ) {
            summ = sumc;
            ind_min = j ;
        }
    }

    int ch = tabChemin[h-1][ind_min].getX();
    for(int i = h-1; i>0; i--){
        Pixel p = img.getPixel(i-1,ch);
        p.setRGBCouleur(0,255);
        p.setRGBCouleur(1,0);
        p.setRGBCouleur(2,0);
        img.setPixel(i-1,ch,p);
        ch = tabChemin[i-1][ch].getX();
    }
    if(coul == "rgb"){
        img.setTableauCourant(1);
    }
    else{
        img.setTableauCourant(3);
    }
}

Image SeamCarving::removeVertical(){
    int h = img.getHauteur();
    int l = img.getLargeur();
    Image imgRes;
    imgRes.setHauteur(h);
    imgRes.setLargeur(l-1);
    imgRes.setTableauPixel(h,l-1);

    for(int row=h-1;row>=0;--row){
            for(int col=0;col<l;col++){
                Pixel p = img.getPixel(row,col);
                if(col<ind_min) {
                    imgRes.setPixel(row,col,p);
                }
                else if(col==ind_min) {
                    continue;
                }
                else {
                    p.setX(col-1);
                    imgRes.setPixel(row,col-1,p);
                }
            }
        ind_min = tabChemin[row][ind_min].getX();
    }
    free(tabChemin);
    free(tabEnergy);
    return imgRes;
}

void SeamCarving::seamHorizontal(){
    int h = img.getHauteur();
    int l = img.getLargeur();
    string coul = img.quelleCouleur();
    for(int i=0; i<h;i++){
        for(int j=0; j<l;j++){
            tabEnergy[i][j] = img.getPixel(i,j).getEnergie();
        }
    }
    //Chercher chemin
    for(int j=1; j<img.getLargeur(); j++){
        for(int i=0; i<img.getHauteur();i++){
            Pixel vois1 = img.getPixel(0,0);
            Pixel vois2 = img.getPixel(0,0);
            Pixel vois3 = img.getPixel(0,0);
            int nombreVoisin,energyVois1,energyVois2,energyVois3,energymin;

            if ( i == 0){
                nombreVoisin = 2;
                vois1 = img.getPixel(i,j-1); //voisM
                vois2 = img.getPixel(i+1,j-1);//voisB
            }
            else if(i == h-1){
                nombreVoisin = 2;
                vois1 = img.getPixel(i-1,j-1);//voisH
                vois2 = img.getPixel(i,j-1);//voisM
            }
            else {
                nombreVoisin = 3;
                vois1 = img.getPixel(i-1,j-1); //voisH
                vois2 = img.getPixel(i,j-1); //voisM
                vois3 = img.getPixel(i+1,j-1); //voisB
            }

            if (nombreVoisin == 2){
                energyVois1 = tabEnergy[vois1.getY()][vois1.getX()];
                energyVois2 = tabEnergy[vois2.getY()][vois2.getX()];
                energymin = min(energyVois1,energyVois2);
            }
            else {
                energyVois1 = tabEnergy[vois1.getY()][vois1.getX()];
                energyVois2 = tabEnergy[vois2.getY()][vois2.getX()];
                energyVois3 = tabEnergy[vois3.getY()][vois3.getX()];
                energymin = min(min(energyVois1,energyVois2),energyVois3);
            }

            if (energymin == energyVois1) {
                tabChemin[i][j] = vois1;
                tabEnergy[i][j] += tabEnergy[vois1.getY()][vois1.getX()];
            }
            else if (energymin == energyVois2) {
                tabChemin[i][j] = vois2;
                tabEnergy[i][j] += tabEnergy[vois2.getY()][vois2.getX()];
            }
            else {
                tabChemin[i][j] = vois3;
                tabEnergy[i][j] += tabEnergy[vois3.getY()][vois3.getX()];
            }
        }
    }
    int sumc,summ;
    summ = INT_MAX;
    for(int i=1; i<h; i++){
        sumc = abs(tabEnergy[i][l-1]);
        if (sumc < summ) {
            summ = sumc;
            ind_min = i ;
        }
    }
    //    //Show seam
    //    int ch = tabChemin[ind_min][l-1].getY();
    //    for(int j = l-1; j>0; j--){
    //        Pixel p = img.getPixel(ch,j-1);
    //        p.setRGBCouleur(0,255);
    //        p.setRGBCouleur(1,0);
    //        p.setRGBCouleur(2,0);
    //        img.setPixel(ch,j-1,p);
    //        ch = tabChemin[ch][j-1].getY();
    //    }
    if(coul == "rgb"){
        img.setTableauCourant(1);
    }
    else{
        img.setTableauCourant(3);
    }
}

Image SeamCarving::removeHorizontal(){
    int h = img.getHauteur();
    int l = img.getLargeur();
    Image imgRes;
    imgRes.setHauteur(h-1);
    imgRes.setLargeur(l);
    imgRes.setTableauPixel(h-1,l);

    for(int col=l-1; col>=0; --col){
        for(int row=0; row<h; row++){
            Pixel p = img.getPixel(row,col);
            if(row<ind_min) {
                imgRes.setPixel(row,col,p);
            }
            else if(row==ind_min) {
                continue;
            }
            else {
                p.setY(row-1);
                imgRes.setPixel(row-1,col,p);
            }
        }
        ind_min = tabChemin[ind_min][col].getY();
    }
    return imgRes;
}

void SeamCarving::seamCarvingHorizontal(int nb){
    for(int i=1; i< nb; i++){
        seamHorizontal();
        Image img = removeHorizontal();
        setImg(img);
        resetEnergy();
        this->img.setEnergiePixel();
    }
}

void SeamCarving::seamCarvingVertical(int nb){
    for(int i=1; i< nb; i++){
        seamVertical();
        Image img = removeVertical();
        setImg(img);
        resetEnergy();
        this->img.setEnergiePixel();
    }
}



