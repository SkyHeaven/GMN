#include <QApplication>
#include <iostream>
#include <string>
#include "Controle.h"
#include <opencv2/opencv.hpp>

using namespace std;


    void Controle::affichageImage(IplImage img){
        cout << "beubeu" << endl;
    }

    void Controle::ouvertureImage(char chemin[]){

        IplImage *imagef = cvLoadImage(chemin, 1);
        int x, y, couleur;
        CvScalar p;
        Image image;
        Pixel pix;

        image.setHauteur(imagef->height);
        image.setLargeur(imagef->width);
          //printf("Image chargée : largeur=%d, hauteur=%d, profondeur=%d, couleur=%d\n", image->width, image->height, image->depth, image->nChannels);

          //if ( ( image->nChannels == 3 ) && ( largeur == image->width) && ( hauteur == image->height ) ) {

            for( x = 0; x < image.getLargeur(); x++ ){
              for( y = 0; y < image.getHauteur(); y++ ) {
                p = cvGet2D(imagef, y, x);
                pix.setX(x);
                pix.setY(y);
                for( couleur = 0; couleur < NBCOULEUR; couleur++ ){
                    pix.setRGBCouleur(couleur, p.val[couleur]);
                }
                image.setPixel(x,y,pix);
              }
            }
         // }
        //return NULL;
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
