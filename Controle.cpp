#include <QApplication>
#include <iostream>
#include <string>
#include "Controle.h"
#include <opencv2/opencv.hpp>

using namespace std;

void Controle::ouvertureImage(QImage imagef){

//        QImageReader reader(chemin);
//        reader.setAutoTransform(true);
//        const QImage imagef = reader.read();

    //IplImage *imagef = cvLoadImage(chemin, 1);
    int x, y, couleur;
    CvScalar p;
    Image image;


    image.setHauteur(imagef.height());
    image.setLargeur(imagef.width());
    image.setTableauPixel(imagef.width(),imagef.height());
      //printf("Image chargée : largeur=%d, hauteur=%d, profondeur=%d, couleur=%d\n", image->width, image->height, image->depth, image->nChannels);

      //if ( ( image->nChannels == 3 ) && ( largeur == image->width) && ( hauteur == image->height ) ) {

        for( x = 0; x < image.getLargeur(); x++ ){
          for( y = 0; y < image.getHauteur(); y++ ) {
            Pixel pix = Pixel((double)x,(double)y);

            pix.setRGBCouleur(0, qRed(imagef.pixel(x,y)));
            pix.setRGBCouleur(1, qGreen(imagef.pixel(x,y)));
            pix.setRGBCouleur(2, qBlue(imagef.pixel(x,y)));

//                for( couleur = 0; couleur < NBCOULEUR; couleur++ ){
//                    pix.setRGBCouleur(couleur, p.val[couleur]);
//                }
            image.setPixel(x,y,pix);
          }
        }
     // }
    //return NULL;
}

    void Controle::affichageImage(IplImage img){
        cout << "beubeu" << endl;
    }

    Image Controle::undo(){
        indexVecteur --;
        return sauvegardeImage.at(indexVecteur);
    }

    Image Controle::redo(){
        indexVecteur ++;
        return sauvegardeImage.at(indexVecteur);
    }

    void Controle::ajoutOperation(Image img){ // A VERIFIER EN CAS DE SEG FAULT
        indexVecteur ++;
        for(int i = sauvegardeImage.size(); i >= indexVecteur; i--){
            sauvegardeImage.erase(sauvegardeImage.begin() + i);
        }
        sauvegardeImage.insert(sauvegardeImage.begin()+ indexVecteur, img);
    }

    IplImage Controle::filtrage(IplImage img){ //ici creation nouvelle image
        //return NULL;
    }

    IplImage Controle::amelioration(IplImage img){ //ici creation nouvelle image
        //return NULL;
    }

    IplImage Controle::crop(IplImage img, CvScalar pixel1, CvScalar pixel2){
        //return NULL;
    }

    void Controle::redimension(IplImage img, string option, int l, int h){
        //return NULL;
    }

    IplImage Controle::afficherHistogramme(CvScalar pixel, string optionCoul){
        //return NULL;
    }
