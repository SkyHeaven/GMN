#ifndef IMAGE_H
#define IMAGE_H
#include <QImage>
#include <iostream>
#include <string>
#include "Pixel.h"
#include "Histogramme.h"
#include "Masque.h"

class Image {
    private:
    Pixel **tableauPixel;
    int hauteur;
    int largeur;

    public:
    void setTableauPixel(int h, int l);
    Pixel **getTableauPixel() const;
    void setPixel(int h, int l, Pixel p);
    Pixel getPixel(int h, int l);
    int getHauteur();
    void setHauteur(int h);
    int getLargeur();
    void setLargeur(int l);
    int* getRGB(int h, int l);
    int* getYUV(int h, int l);
    int getGray(int h, int l);
    void setGray();
    void setYUV();
    void setNoYUV();
    void setNoRGB();
    void setTableauCourant(int c);
    Image cloneImage();
    Image cropImage(int h1, int l1, int h2, int l2);
    Histogramme* initHistogramme(std::string optionCoul);
    Image rotationTableauPixel(std::string option);
    void rotationPixel(int h, int l, int i,int j,std::string option);
    void flouImage();
    std::string quelleCouleur();
    //destructeur
};

#endif // IMAGE_H
