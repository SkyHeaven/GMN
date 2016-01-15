#ifndef PIXEL_H
#define PIXEL_H
#define NBCOULEUR 3
//#include "Couleur.h"
class Pixel {
    private:
    double x;
    double y;
    int rgb[NBCOULEUR];
    int yuv[NBCOULEUR];
    int gris;    
    int etatCourant[NBCOULEUR];

    public:
    Pixel(double x , double y);
    void setYUVwithRGB(int rgb[]);
    void setGraywithRGB(int rgb[]);
    int getGrayCouleur();
    int* getYUVCouleur();
    int getX();
    void setX(int value);
    int getY();
    void setY(int value);
    void setRGBCouleur(int ind, int val);
    int* getRGBCouleur();
    int getSingleRGB(int ind);
    void setEtatCourant(int c);
    int* getEtatCourant();
    void setCouleur(std::string coul, int tabCoul[NBCOULEUR]);


    // methodes de conversion (grisToRGB grisToYUV...)
    int getGris() const;
    void setGris(int value);
};

#endif // PIXEL_H
