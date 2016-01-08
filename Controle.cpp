#include <QApplication>
#include <iostream>
#include <string>
#include "Controle.h"
#include <opencv2/opencv.hpp>

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

    int x, y, couleur;
    CvScalar p;
    Image image;


    image.setHauteur(imagef.height());
    image.setLargeur(imagef.width());
    image.setTableauPixel(imagef.height(),imagef.width());

    for( int h = 0; h < image.getHauteur(); h++ ){
      for( int l = 0; l < image.getLargeur(); l++ ) {
        Pixel pix = Pixel((double)x,(double)y);

        pix.setRGBCouleur(0, qRed(imagef.pixel(l,h)));
        pix.setRGBCouleur(1, qGreen(imagef.pixel(l,h)));
        pix.setRGBCouleur(2, qBlue(imagef.pixel(l,h)));

    //                for( couleur = 0; couleur < NBCOULEUR; couleur++ ){
    //                    pix.setRGBCouleur(couleur, p.val[couleur]);
    //                }
        image.setPixel(h,l,pix);
       }
    }

    indexVecteur =0;
    sauvegardeImage.insert(sauvegardeImage.begin(),image);
}

    void Controle::affichageImage(Image img){
        cout << "beubeu" << endl;
    }
    int* Controle::affichageCouleurRGB(int h, int l){
        Image img = sauvegardeImage.at(indexVecteur);
        return img.getRGB(h,l);
    }

    Image Controle::undo(){
        if(indexVecteur > 0){
            indexVecteur --;
            return sauvegardeImage.at(indexVecteur);
        }
        else{
            cout << "impossible de continuer a annuler" << endl;
        }
    }

    Image Controle::redo(){
        if(indexVecteur < sauvegardeImage.size()-1){
            indexVecteur ++;
            return sauvegardeImage.at(indexVecteur);
        }
        else{
            cout << "Aucun redo supplementaire" << endl;
        }
    }

    void Controle::ajoutOperation(Image img){ // A VERIFIER EN CAS DE SEG FAULT
        indexVecteur ++;
        for(int i = sauvegardeImage.size(); i >= indexVecteur; i--){
            sauvegardeImage.erase(sauvegardeImage.begin() + i);
        }
        sauvegardeImage.insert(sauvegardeImage.begin()+ indexVecteur, img);
    }

    Image Controle::filtrage(Image img){ //ici creation nouvelle image
        //return NULL;
    }

    Image Controle::amelioration(Image img){ //ici creation nouvelle image
        //return NULL;
    }

    Image Controle::crop(Image img, Pixel pixel1, Pixel pixel2){
        //return NULL;
    }

    void Controle::redimension(Image img, string option, int l, int h){
        //return NULL;
    }

    Image Controle::afficherHistogramme(Pixel pixel, string optionCoul){
        //return NULL;
    }
