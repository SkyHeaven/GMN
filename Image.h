#ifndef IMAGE_H
#define IMAGE_H
#include "Pixel.h"
class Image : public IplImage{
    private:
    Pixel **tableauPixel;
    int hauteur;
    int largeur;

    public:
    void setTableauPixel(int h, int l);
    void setPixel(int x, int y, Pixel p);
    int getHauteur();
    void setHauteur(int h);
    int getLargeur();
    void setLargeur(int l);

};

#endif // IMAGE_H
