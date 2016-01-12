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
                Image img = sauvegardeImage.at(i-1); //copie superficielle
                img.~Image(); //DESALOCATION tableauPixel
                sauvegardeImage.erase(sauvegardeImage.begin() + i -1);
            }
        }
        sauvegardeImage.insert(sauvegardeImage.begin()+ indexVecteur, img);
    }

    void Controle::flou(){
        Image img = sauvegardeImage.at(indexVecteur);
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

    void Controle::redimension(Image img, string option, int l, int h){
        //return NULL;
    }

    Histogramme* Controle::afficherHistogramme(Image img, string optionCoul){
        Histogramme* tabHist;
        tabHist = new Histogramme[NBCOULEUR];
        tabHist = img.initHistogramme(optionCoul);
        return tabHist;
}
    Image Controle::rotation(string option){
        Image img = sauvegardeImage.at(indexVecteur);
        img.rotationTableauPixel(option);
        ajoutOperation(img);
    }
