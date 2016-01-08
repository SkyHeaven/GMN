#ifndef IMAGE_H
#define IMAGE_H
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
    Image cropImage(Image img,Pixel pixel1,Pixel pixel2);

};

#endif // IMAGE_H
