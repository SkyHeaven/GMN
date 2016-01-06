#include <QApplication>
#include <iostream>
#include <string>
#include "Controle.h"

using namespace std;


    void Controle::affichageImage(IplImage img){
        cout << "beubeu" << endl;
    }

    IplImage Controle::ouvertureImage(string chemin){
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
