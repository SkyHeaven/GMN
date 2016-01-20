#include "SeamCarving.h"
#include <QApplication>
#include <iostream>
#include <string>
using namespace std;


Image SeamCarving::getImg(){
    return img;
}

void SeamCarving::setImg(Image value){
    img = value.cloneImage();
}

void SeamCarving::SeamCarving_algo(){
    Pixel **tabChemin;
    int h = img.getHauteur();
    int l = img.getLargeur();

    Pixel voisH = img.getPixel(0,0);
    Pixel voisM = img.getPixel(0,0);
    Pixel voisB = img.getPixel(0,0);

    tabChemin = (Pixel**)malloc(h * sizeof(Pixel*));

    for(int i = 0; i<h;i++){
        tabChemin[i] = (Pixel*)malloc(l* sizeof(Pixel));
    }
    img.setEnergiePixel();
    for(int k=0;k<25;k++){
        //Chercher chemin
        for(int i=0; i<h-k; i++){
            tabChemin[i][0] = img.getPixel(i,0);
            for(int j=0; j<l; j++){
                if (j<l-1){
                    if(tabChemin[i][j].getY()>0){
                        if (tabChemin[i][j].getY()<h-1){
                            voisH = img.getPixel(tabChemin[i][j].getY()-1,j+1);
                            voisM = img.getPixel(tabChemin[i][j].getY(),j+1);
                            voisB = img.getPixel(tabChemin[i][j].getY()+1,j+1);
                        }
                        else {
                            voisH = img.getPixel(tabChemin[i][j].getY()-1,j+1);
                            voisM = img.getPixel(tabChemin[i][j].getY(),j+1);
                            voisB = img.getPixel(0,0);
                        }
                    }
                    else {
                        voisH = img.getPixel(0,0);
                        voisM = img.getPixel(tabChemin[i][j].getY(),j+1);
                        voisB = img.getPixel(tabChemin[i][j].getY()+1,j+1);
                    }
                }
                if (voisB.getX() == 0 && voisB.getY() == 0){
                    if (voisM.getEnergie()<voisH.getEnergie()){
                        tabChemin[i][j+1] = voisM;
                    }
                    else {
                        tabChemin[i][j+1] = voisH;
                    }
                }
                else if(voisH.getX() == 0 && voisH.getY() == 0){
                    if (voisM.getEnergie()<voisB.getEnergie()){
                        tabChemin[i][j+1] = voisM;
                    }
                    else {
                        tabChemin[i][j+1] = voisH;
                    }
                }
                else {
                    if (voisM.getEnergie()<voisB.getEnergie()){
                        if (voisM.getEnergie()<voisH.getEnergie()){
                            tabChemin[i][j+1] = voisM;
                        }
                        else {
                            tabChemin[i][j+1] = voisH;
                        }
                    }
                    else {
                        if (voisB.getEnergie()<voisH.getEnergie()){
                            tabChemin[i][j+1] = voisB;
                        }
                        else {
                            tabChemin[i][j+1] = voisH;
                        }
                    }
                }

            }

        }
        //Chemin mini
        int sumc, summ,ind =0;
        sumc =0;
        summ = INT_MAX;
        for(int i=0; i<h-k; i++){
            for(int j=0; j<l; j++){
                sumc+=tabChemin[i][j].getEnergie();
            }
            if(sumc<summ){
                summ = sumc;
                ind = i;
            }
            sumc =0;
        }
        //Supprimer chemin
        tabChemin[ind][0].setY(ind);
        for(int j=0; j<l; j++){
            while(tabChemin[ind][j].getY() != h-k-1){
                Pixel tmp = img.getPixel(tabChemin[ind][j].getY()+1,j);
                tabChemin[ind][j].setY(tabChemin[ind][j].getY()+1);
                img.setPixel(tabChemin[ind][j].getY(),j,tabChemin[ind][j]);
                tmp.setY(tabChemin[ind][j].getY()-1);
                img.setPixel(tmp.getY(),j,tmp);
            }
        }
        //img.setHauteur(h-1);
    }
    cout<<"done   "<<img.getHauteur()<<"   "<<img.getLargeur()<<endl;
}

