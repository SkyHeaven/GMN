#ifndef CONTROLE_H
#define CONTROLE_H
#include <QImage>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "Image.h"
#include "Pixel.h"

class Controle{
    //private:
    std::vector<Image> sauvegardeImage;
    int indexVecteur = 0;
    public:

    void ouvertureImage(QImage imagef);
    void affichageImage(IplImage img);
    Image undo();
    Image redo();
    void ajoutOperation(Image img);
    IplImage filtrage(IplImage img); //ici creation nouvelle image
    IplImage amelioration(IplImage img); //ici creation nouvelle image
    IplImage crop(IplImage img, CvScalar pixel1, CvScalar pixel2);
    void redimension(IplImage img, std::string option, int l, int h);
    IplImage afficherHistogramme(CvScalar pixel, std::string optionCoul);
};
#endif // CONTROLE_H


