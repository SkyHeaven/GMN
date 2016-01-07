#ifndef PIXEL_H
#define PIXEL_H
#define NBCOULEUR 3
#include <opencv2/opencv.hpp>

class Pixel : public CvScalar{
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
    void setX(double x);
    void setY(double y);
    void setRGBCouleur(int ind, int val);
    // methodes de conversion (grisToRGB grisToYUV...)
};

#endif // PIXEL_H
