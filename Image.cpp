#include <iostream>
#include <string>
#include "Image.h"

using namespace std;

//Image::~Image(){
//    for(int i = 0 ; i < getHauteur() ; i++){
//        delete[] tableauPixel[i];
//     }
//     delete[] tableauPixel;
//}


Pixel **Image::getTableauPixel() const
{
    return tableauPixel;
}

void Image::setTableauPixel(int h, int l){

//    tableauPixel = new Pixel*[h];
//    for(int i = 0; i < h; ++i){
//        tableauPixel[i] = new Pixel[l];
//    }

    // A VOIR si on peut enlever l utilisation de malloc

    tableauPixel = (Pixel**)malloc(h * sizeof(Pixel*));
    for(int i = 0; i<h;i++){
        tableauPixel[i] = (Pixel*)malloc(l* sizeof(Pixel));
    }
}

void Image::setPixel(int h, int l, Pixel p){
    tableauPixel[h][l] = p;
}

Pixel Image::getPixel(int h, int l){
    return tableauPixel[h][l];
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

int* Image::getYUV(int h, int l){
    return tableauPixel[h][l].getYUVCouleur();
}

int Image::getGray(int h, int l){
    return tableauPixel[h][l].getGrayCouleur();
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

void Image::setNoRGB(){
    for(int i= 0 ; i <hauteur; i++){
        for(int j =0; j < largeur; j++){
            for(int k=0; k<NBCOULEUR; k++){
                tableauPixel[i][j].setRGBCouleur(k,-1);
            }
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

Image Image::cropImage(int h1, int l1, int h2, int l2){
    Image imgRes;
    int minX = min(l1,l2);
    int minY = min(h1,h2);
    int maxX = max(l1,l2);
    int maxY = max(h1,h2);
    int diffX = maxX - minX;
    int diffY = maxY - minY;

    imgRes.setHauteur(maxY - minY);
    imgRes.setLargeur(maxX - minX);
    imgRes.setTableauPixel(maxY - minY,maxX - minX);
    for(int i = minY; i < maxY; i++){
        for(int j = minX; j < maxX; j++){
            Pixel p = Pixel((double)j-minX,(double)i-minY);
            p = tableauPixel[i][j];
            imgRes.setPixel(i-minY,j-minX, p);
        }
    }
    imgRes.setGray();
    imgRes.setYUV();
    return imgRes;
}

Histogramme* Image::initHistogramme(string optionCoul){
    Histogramme tabHist[NBCOULEUR];
    for(int i = 0; i < NBCOULEUR; i ++){
        tabHist[i].initZero();
    }

    for(int i= 0; i < getHauteur(); i++){
        for(int j = 0; j < getLargeur(); j++){
            Pixel p = getPixel(i,j);

            if(optionCoul == "rgb"){
                int* rgbRep = p.getRGBCouleur();
                for(int k = 0; k < NBCOULEUR; k++){
                    tabHist[k].incrementeValeurHistogramme(rgbRep[k]);
                }
            }

            else if(optionCoul == "yuv"){
                int* yuvRep = p.getYUVCouleur();
                for(int k = 0; k < NBCOULEUR; k++){
                    tabHist[k].incrementeValeurHistogramme(yuvRep[k]);
                }
            }
//            else if(optionCoul == "gris"){

//            }
        }
    }
    return tabHist;
}

Image Image::rotationTableauPixel(string option){
    Image imgRes;
    int h,l=0;

    if(option == "180"){
        h = getHauteur();
        l = getLargeur();
    }

    else{
        l = getHauteur();
        h = getLargeur();
    }

     imgRes.setHauteur(h);
     imgRes.setLargeur(l);
     imgRes.setTableauPixel(h,l);

    for(int i=0; i<h; i++){
        for(int j=0; j<l; j++){
            Pixel p = rotationPixel(h,l,i,j,option);
            imgRes.setPixel(i,j,p);
        }
    }
    return imgRes;
}

Pixel Image::rotationPixel(int h, int l, int i, int j, string option){
    if(option == "180"){
        Pixel p = getPixel(h-i-1,l-j-1);
        return p;
    }

    else if(option == "90D"){
        Pixel p = getPixel(l-j-1,i);
        //cout<<"tuti"<<endl;
        return p;
    }

    else if(option =="90G"){
        Pixel p = getPixel(j,h-i-1);
        return p;
    }
}

void Image::flouImage(){
    Masque mask = Masque(3);
    mask.remplirMasque();
    int hImg = getHauteur();
    int lImg = getLargeur();
    int lMask = mask.getLongueur();
    int sumMask =0;
    int *tabCol = new int[NBCOULEUR];
    int *tabSum = new int[NBCOULEUR];
    string coul = quelleCouleur();
    for(int i=0; i<NBCOULEUR; i++){ //init tabCouleur
        tabSum[i] = 0;
    }
    for(int i= lMask/2; i<hImg - lMask/2; i++){
        for(int j=lMask/2; j<lImg - lMask/2; j++){
            Pixel p = Pixel(j,i);
            sumMask = mask.sommeMasque();

            for(int i2=i -lMask/2; i2<lMask+i-lMask/2; i2++){
                for(int j2=j-lMask/2; j2<lMask+j -lMask/2; j2++){
                    tabCol = getPixel(i2,j2).getEtatCourant();
                    for(int k=0; k<NBCOULEUR; k++){
                        tabSum[k] += mask.getValeurTableauMasque(i2,j2)*tabCol[k];
                    }
                }
            }

            for(int k=0; k<NBCOULEUR; k++){
                tabSum[k] = tabSum[k]/sumMask;

                if(coul == "rgb"){
                    p.setRGBCouleur(k,tabSum[k]);
                    p.setEtatCourant(1);
                }
                else if(coul == "gris"){
                    p.setGris(tabSum[k]);
                    p.setEtatCourant(3);
                }

            }

            if(coul == "rgb"){
                p.setYUVwithRGB(p.getRGBCouleur());
                p.setGraywithRGB(p.getRGBCouleur());
            }

            setPixel(i,j,p);
            // ATTENTION NE PAS OUBLIER DE SET COULEUR + ETAT COURANT
            // MALLOC masque

        }
    }
    for(int i=0; i<lMask/2; i++){ // remplissage du contour de l image
        for(int j=0; j<lMask/2; j++){
            Pixel p = Pixel(j,i);
            setPixel(i,j,p);
        }
    }
    mask.~Masque();
}

string Image::quelleCouleur(){

    Pixel p =getPixel(0,0);
    int *tab = p.getRGBCouleur();
    if(tab[0] == -1) return "gris";
    else return "rgb";


            /* bool boolean = true;
    int i =0; int j =0;
    int *tmpRGB;
    int *tmpEtatCourant;
    Pixel p = Pixel(j,i);
    tmpRGB = p.getRGBCouleur();
    tmpEtatCourant = p.getEtatCourant();
    int tmp;
    while(boolean){
        for(int k=0; k<NBCOULEUR; k++){
            boolean = boolean && (tmpRGB[k] == tmpEtatCourant[k]) && (getGray(i,j) == tmpEtatCourant[0]);
            if(!boolean){
                tmp = k;
                break;
            }
        }
        if(boolean){
            if(j < getLargeur()) j++;
            else{
                j=0; i++;
            }
        }
        else{
            if(tmpRGB[tmp] == tmpEtatCourant[tmp]) return "rgb";
            else return "gris";
        }
    }
*/
}

