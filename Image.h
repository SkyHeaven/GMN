#ifndef IMAGE_H
#define IMAGE_H
#include <QImage>
#include <iostream>
#include <string>
#include "Pixel.h"
#include "Histogramme.h"
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
    void setTableauCourant(int c);
    Image cloneImage();
    Image cropImage(int h1, int l1, int h2, int l2);
    Histogramme* initHistogramme(std::string optionCoul);

};

#endif // IMAGE_H
