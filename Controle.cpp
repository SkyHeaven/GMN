#include <QApplication>
#include <iostream>
#include <string>
#include "Controle.h"
#include "SeamCarving.h"
using namespace std;

Controle::Controle(){
    indexVecteur =0;
    imageOuverte = false;
}

std::vector<Image> Controle::getSauvegardeImage() const{
    return sauvegardeImage;
}

void Controle::setSauvegardeImage(const std::vector<Image> &value){
    sauvegardeImage = value;
}

int Controle::getIndexVecteur() const{
    return indexVecteur;
}

void Controle::setIndexVecteur(int value){
    indexVecteur = value;
}
void Controle::ouvertureImage(QImage imagef){
    Image image;
    image.setHauteur(imagef.height());
    image.setLargeur(imagef.width());
    image.setTableauPixel(imagef.height(),imagef.width());
    for( int h = 0; h < image.getHauteur(); h++ ){
        for( int l = 0; l < image.getLargeur(); l++ ) {
            Pixel pix = Pixel((double)l,(double)h);
            pix.setRGBCouleur(0, qRed(imagef.pixel(l,h)));
            pix.setRGBCouleur(1, qGreen(imagef.pixel(l,h)));
            pix.setRGBCouleur(2, qBlue(imagef.pixel(l,h)));
            pix.setX(l);
            pix.setY(h);
            image.setPixel(h,l,pix);
        }
    }

    image.setGray();
    image.setYUV();
    image.setTableauCourant(1);
    if (!imageOuverte){
        sauvegardeImage.insert(sauvegardeImage.begin(),image);
        imageOuverte = true;
    }
    else {
        ajoutOperation(image);
    }
}

int* Controle::affichageCouleurRGB(int h, int l){
    Image img = sauvegardeImage.at(indexVecteur);
    return img.getRGB(h,l);
}

double* Controle::affichageCouleurYUV(int h, int l){
    Image img = sauvegardeImage.at(indexVecteur);
    return img.getYUV(h,l);
}

int Controle::affichageCouleurGris(int h , int l){
    Image img = sauvegardeImage.at(indexVecteur);
    return img.getGray(h,l);
}

Pixel Controle::affichageCouleur(int h, int l){ //FAIRE MALLOC ICI EN CAS PROBLEME
    Image img = sauvegardeImage.at(indexVecteur);
    return img.getPixel(h,l);
}

void Controle::undo(){
    if(indexVecteur > 0){
        indexVecteur --;
    }
    else{
        cout << "impossible de continuer a annuler" << endl;
    }
}

void Controle::redo(){
    if( indexVecteur < (int)sauvegardeImage.size()-1){
        indexVecteur ++;
    }
    else{
        cout << "Aucun redo supplementaire" << endl;
    }
}

void Controle::ajoutOperation(Image img){ // GERER DESTRUCTEUR
    indexVecteur ++;
    if ((int)sauvegardeImage.size() > indexVecteur){
        for(int i = sauvegardeImage.size(); i > indexVecteur; i--){
            sauvegardeImage.erase(sauvegardeImage.begin() + i -1);
        }
    }
    sauvegardeImage.insert(sauvegardeImage.begin()+ indexVecteur, img);
}

void Controle::crop(int h1, int l1, int h2, int l2){

    Image imgRes = sauvegardeImage.at(indexVecteur).cropImage(h1,l1,h2,l2);
    ajoutOperation(imgRes);
}

void Controle::afficherGris(){
    Image img = sauvegardeImage.at(indexVecteur).cloneImage();
    img.setTableauCourant(3);
    img.setNoRGB();
    ajoutOperation(img);
}

Histogramme* Controle::afficherHistogramme(){
    Image img = sauvegardeImage.at(indexVecteur).cloneImage();
    Histogramme* tabHist;
    tabHist = new Histogramme[NBCOULEUR];
    tabHist = img.initHistogramme();
    return tabHist;
}

void Controle::rotation(string option){
    Image img = sauvegardeImage.at(indexVecteur).cloneImage();
    Image imgRes = img.rotationTableauPixel(option);
    ajoutOperation(imgRes);
}
void Controle::redimension(int h, int l){
    Image img = sauvegardeImage.at(indexVecteur).cloneImage();
    Image imgRes1, imgRes2;
    if(h < img.getHauteur()){
        if(l < img.getLargeur()){
            imgRes1 = img.reductionHauteurImage(h);
            imgRes2 = imgRes1.reductionLargeurImage(l);
            ajoutOperation(imgRes2);
        }
        else{
            imgRes1 = img.reductionHauteurImage(h);
            ajoutOperation(imgRes1);
        }
    }
    else if(l < img.getLargeur()){
        imgRes1 = img.reductionLargeurImage(l);
        ajoutOperation(imgRes1);
    }
    else if( h > img.getHauteur() && l > img.getLargeur()){
        imgRes1 = img.etirementImage(h,l);
        ajoutOperation(imgRes1);
    }
    else{
        cout << "Operation de redimensionnement non prise en compte" << endl;
    }
}

void Controle::etalementHistogramme(){
    Image img = sauvegardeImage.at(indexVecteur).cloneImage();
    Histogramme* tabHist = afficherHistogramme();
    bool condMin = true;
    bool condMax = true;
    double sum =0;
    int min = NBNUANCES;
    int max = 0;
    int tmp = 0;
    double nbPix = img.getHauteur()*img.getLargeur();
    if(img.quelleCouleur() == "rgb"){
        for(int j=0; j<NBNUANCES; j++){
            tmp = tabHist->getValeurIndiceHistogramme(j);
            sum += tmp;

            if(sum > nbPix*((double)VALSUPPR/100.0) && condMin){
                min = j;
                condMin = false;
            }

            if((sum > nbPix - nbPix*((double)VALSUPPR/100.0)) && condMax){
                max = j;
                condMax = false;
            }
        }
        sum /= NBNUANCES;
        if(true){
            img.augmentationContraste(0, max, min);
//            img.setYUV();
//            img.setGray();
//            img.setTableauCourant(1);
        }

        else{
            cout << "pas de transformation disponible pour cette image" << endl;
        }
        sum =0;min = NBNUANCES;max = 0;tmp=0;
    }
    else{
        sum = 0;
        for(int j=0; j<NBNUANCES; j++){
            tmp = tabHist->getValeurIndiceHistogramme(j);
            sum += tmp;

            if(sum > nbPix*((double)VALSUPPR/100.0) && condMin){
                min = j;
                condMin = false;
            }

            if((sum > nbPix*((100.0-(double)VALSUPPR)/100.0)) && condMax){
                max = j;
                condMax = false;
            }
        }
        if(true){
            //if( max - min < MINECARTTYPE){
            cout << min << " " << max << endl;
            img.augmentationContraste(0, max, min);
            img.setTableauCourant(3);
        }
        else{
            cout << "pas de transformation disponible pour cette image" << endl;
        }
        sum =0;min = NBNUANCES;max = 0;tmp=0;
    }
    ajoutOperation(img);
}

void Controle::fusion(int h1, int l1, int h2, int l2,int h,int l){
    Image imgRes = sauvegardeImage.at(indexVecteur).cropImage(h1,l1,h2,l2);
    Image imgfu = sauvegardeImage.at(indexVecteur-1).fusion(imgRes,h,l);
    if (imgfu.getHauteur() != 0){
        ajoutOperation(imgfu);
    }
    else {
        indexVecteur--;
    }
}

void Controle::egalisation(){
    Image img = sauvegardeImage.at(indexVecteur).cloneImage();
    Histogramme *h = afficherHistogramme();
    int l;
    if(img.quelleCouleur() != "rgb"){
        for (int i=0;i<NBNUANCES;i++){
            if (h->getValeurIndiceHistogramme(i) !=0){
                l=i;
            }
        }
        for (int i =0;i<img.getHauteur();i++){
            for (int j =0; j<img.getLargeur();j++){
                img.egalisation(h->egaliser(img.getPixel(i,j).getGris(),l),i,j,false);
            }
        }
        img.setTableauCourant(3);
        ajoutOperation(img);
    }
    else {
        for (int i=0;i<NBNUANCES;i++){
            if (h->getValeurIndiceHistogramme(i) !=0){
                l=i;
            }
        }
        for (int i =0;i<img.getHauteur();i++){
            for (int j =0; j<img.getLargeur();j++){
                img.egalisation(h->egaliser((int)img.getPixel(i,j).getSingleYUV(0),l),i,j,true);
            }
        }
        img.setTableauCourant(1);
        ajoutOperation(img);
    }

}

void Controle::negatif(){
    Image img = sauvegardeImage.at(indexVecteur).negatif();
    ajoutOperation(img);
}

void Controle::gradientX(){
    Image img = sauvegardeImage.at(indexVecteur).cloneImage();
    img = img.gradienHorizontalImage();
    ajoutOperation(img);
}

void Controle::gradientY(){
    Image img = sauvegardeImage.at(indexVecteur).cloneImage();
    img = img.gradienVerticalImage();
    ajoutOperation(img);
}

void Controle::appliquerMasque(Masque mask,int coeff){
    Image img = sauvegardeImage.at(indexVecteur).cloneImage();
    img = img.appliquerMasque(mask,coeff);
    ajoutOperation(img);
}

void Controle::flou(){
    Image img = sauvegardeImage.at(indexVecteur).cloneImage();
    img = img.flouImage();
    ajoutOperation(img);
}

void Controle::rehaussement(){
    Image img = sauvegardeImage.at(indexVecteur).cloneImage();
    img = img.rehaussementImage();
    ajoutOperation(img);
}


void Controle::contour(){
    Image img = sauvegardeImage.at(indexVecteur).cloneImage();
    img = img.contourImage();
    ajoutOperation(img);
}

void Controle::ameliorationContour(){\
    Image img = sauvegardeImage.at(indexVecteur).cloneImage();
    img = img.ameliorationContour();
    ajoutOperation(img);
}

void Controle::seamCarving(int h, int l){
    SeamCarving s;
    s.setImg(sauvegardeImage.at(indexVecteur).cloneImage());
    int oldH = s.getImg().getHauteur();
    int oldL = s.getImg().getLargeur();
    if(h < oldH){
        if(l < oldL){
            s.seamCarvingHorizontal(oldH-h);
            s.seamCarvingVertical(oldL-l);
            Image img = s.getImg();
            ajoutOperation(img);
        }
        else{
            s.seamCarvingHorizontal(oldH-h);
            Image img = s.getImg();
            ajoutOperation(img);
        }
    }
    else if(l < s.getImg().getLargeur()){
        s.seamCarvingVertical(oldL-l);
        Image img = s.getImg();
        ajoutOperation(img);
    }
    else if( h > s.getImg().getHauteur() && l > s.getImg().getLargeur()){
        cout <<" a faire" << endl;
    }
    else{
        cout << "Operation de redimensionnement non prise en compte" << endl;
    }
}
