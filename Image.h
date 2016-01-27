#ifndef IMAGE_H
#define IMAGE_H
#include <QImage>
#include <iostream>
#include <stdlib.h>
#include <string>
#include "Pixel.h"
#include "Histogramme.h"
#include "Masque.h"
#include <math.h>

class Image {
    private:
        Pixel **tableauPixel;
        int hauteur;
        int largeur;

    public:
    //~Image();
    void setTableauPixel(int h, int l);
    Pixel **getTableauPixel() const;
    void setPixel(int h, int l, Pixel p);
    Pixel getPixel(int h, int l);
    int getHauteur();
    void setHauteur(int h);
    int getLargeur();
    void setLargeur(int l);
    int* getRGB(int h, int l);
    double* getYUV(int h, int l);
    int getGray(int h, int l);
    void setGray();
    void setYUV();
    void setNoYUV();
    void setNoRGB();
    void setTableauCourant(int c);
    Image cloneImage();    
    std::string quelleCouleur();
    int min(double a, double b);
    int max(double a, double b);
    int arrondiSuperieur(double d);
    void augmentationContraste(int ind, int nMax, int nMin);
    void eclaircissementImage(int ind);
    void assombrissementmage(int ind);

    //Rotation
    Image rotationTableauPixel(std::string option);
    Pixel rotationPixel(int h, int l, int i,int j,std::string option);

    //Histogramme
    Histogramme* initHistogramme();
    void egalisation(int val, int h, int l, bool rgb);

    //Fusion
    Image fusion(Image im, int h, int l);

    //Redimension
    double distance(double x1, double y1, int x2, int y2);
    Image cropImage(int h1, int l1, int h2, int l2);
    Image reductionHauteurImage(int valeur);
    Image reductionLargeurImage(int valeur);
    Image etirementImage(int h,int l);

    //Les filtres
    Image flouImage();
    Image gradienVerticalImage();
    Image gradienHorizontalImage();
    Image rehaussementImage();
    Image negatif();
    Image contourImage();
    Image ameliorationContour();
    Image appliquerMasque(Masque mask, int coeff);
    void remplirBorder(int hImg, int lImg, int lMask);

    //SeamCarving
    void setEnergiePixel();



};

#endif // IMAGE_H
