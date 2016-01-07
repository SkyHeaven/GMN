#ifndef PIXEL_H
#define PIXEL_H
#define NBCOULEUR 3
#include <opencv2/opencv.hpp>

class Pixel {
    private:
    double x;
    double y;
    int rgb[NBCOULEUR];
    int yuv[NBCOULEUR];
    int gris;

    public:
    Pixel(double x , double y);
    int* getYUV(int y, int u, int v);
    void setYUVwithRGB(int rgb[]);
    void setGraywithRGB(int rgb[]);
    void setX(double x);
    void setY(double y);
    void setRGBCouleur(int ind, int val);
    int* getRGBCouleur();

    // methodes de conversion (grisToRGB grisToYUV...)
};

#endif // PIXEL_H
