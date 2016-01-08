#ifndef IMAGE_H
#define IMAGE_H
#include <QImage>
#include <iostream>
#include <string>
#include "Pixel.h"
class Image {
    private:
    Pixel **tableauPixel;
    int hauteur;
    int largeur;

    public:
    void setTableauPixel(int h, int l);
    Pixel **getTableauPixel() const;
    void setPixel(int h, int l, Pixel p);
    int getHauteur();
    void setHauteur(int h);
    int getLargeur();
    void setLargeur(int l);
    int* getRGB(int h, int l);
    void setGray();
    void setYUV();
    void setTableauCourant(int c);
    Image cloneImage();
    Image cropImage(Pixel pixel1,Pixel pixel2);

};

#endif // IMAGE_H
