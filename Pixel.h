#ifndef PIXEL_H
#define PIXEL_H
#define NBCOULEUR 3
//#include "Couleur.h"
class Pixel {
    private:
        double x;
        double y;
        int rgb[NBCOULEUR];
        double yuv[NBCOULEUR];
        int gris;
        int etatCourant[NBCOULEUR];
        double energie;

    public:
        Pixel(double x , double y);
        void setYUVwithRGB(int rgb[]);
        void setRGBwithYUV(double yuv[]);
        void setGraywithRGB(int rgb[]);
        int getGrayCouleur();
        double *getYUVCouleur();
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
        void setYUV(int ind, double val);
        double getSingleYUV(int ind);
        double getEnergie() const;
        void setEnergie(int value);
};

#endif // PIXEL_H
