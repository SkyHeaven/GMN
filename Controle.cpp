#include <QApplication>
#include <iostream>
#include <string>
#include "Controle.h"
using namespace std;



std::vector<Image> Controle::getSauvegardeImage() const
{
    return sauvegardeImage;
}

void Controle::setSauvegardeImage(const std::vector<Image> &value)
{
    sauvegardeImage = value;
}
int Controle::getIndexVecteur() const
{
    return indexVecteur;
}

void Controle::setIndexVecteur(int value)
{
    indexVecteur = value;
}
void Controle::ouvertureImage(QImage imagef){
    
    //        QImageReader reader(chemin);
    //        reader.setAutoTransform(true);
    //        const QImage imagef = reader.read();

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
        image.setPixel(h,l,pix);
       }

        //Couleur c = rgbE;
        //Couleur::enumCouleur c;
//        c = Couleur.enumCouleur. rgb;
//        Couleur.enumCouleur c = Couleur.rgb;

//        c.enumCouleur enumC  = Couleur.rgb;

    }

    image.setGray();
    image.setYUV();
    image.setTableauCourant(1);
    indexVecteur =0;
    sauvegardeImage.insert(sauvegardeImage.begin(),image);

}

    void Controle::affichageImage(Image img){

    }
    int* Controle::affichageCouleurRGB(int h, int l){
        Image img = sauvegardeImage.at(indexVecteur);
        return img.getRGB(h,l);
    }

    int* Controle::affichageCouleurYUV(int h, int l){
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
        if(indexVecteur < sauvegardeImage.size()-1){
            indexVecteur ++;
        }
        else{
            cout << "Aucun redo supplementaire" << endl;
        }
    }

    void Controle::ajoutOperation(Image img){ // GERER DESTRUCTEUR
        indexVecteur ++;
        if (sauvegardeImage.size() > indexVecteur){
            for(int i = sauvegardeImage.size(); i > indexVecteur; i--){
//                Image imgDel = sauvegardeImage.at(i-1); //copie superficielle
//                imgDel.~Image(); //DESALOCATION tableauPixel
                sauvegardeImage.erase(sauvegardeImage.begin() + i -1);
            }
        }
        sauvegardeImage.insert(sauvegardeImage.begin()+ indexVecteur, img);
    }

    void Controle::flou(){
        Image img = sauvegardeImage.at(indexVecteur).cloneImage();
        img.flouImage();
        ajoutOperation(img);
    }

    void Controle::filtrage(Image img){ //ici creation nouvelle image
        //return NULL;
    }

    void Controle::amelioration(Image img){ //ici creation nouvelle image
        //return NULL;
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
        Image imgRes;
        if(h < img.getHauteur()){
            if(l < img.getLargeur()){
                imgRes = img.reductionHauteurImage(h);
                imgRes = imgRes.reductionLargeurImage(l);
                ajoutOperation(imgRes);
            }
            else{
                 imgRes = img.reductionHauteurImage(h);
                 ajoutOperation(imgRes);
            }
        }
        else if(l < img.getLargeur()){
                imgRes = img.reductionLargeurImage(l);
                ajoutOperation(imgRes);
            }
        else if( h > img.getHauteur() && l > img.getLargeur()){
                imgRes = img.etirementImage(h,l);
                ajoutOperation(imgRes);
            }
        else{
                cout << "Operation de redimensionnement non prise en compte" << endl;
            }

}

