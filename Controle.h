#ifndef CONTROLE_H
#define CONTROLE_H
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
class Controle{
    //private:

    public:
    IplImage ouvertureImage(std::string chemin);
    void affichageImage(IplImage img);
    IplImage filtrage(IplImage img); //ici creation nouvelle image
    IplImage amelioration(IplImage img); //ici creation nouvelle image
    IplImage crop(IplImage img, CvScalar pixel1, CvScalar pixel2);
    void redimension(IplImage img, std::string option, int l, int h);
    IplImage afficherHistogramme(CvScalar pixel, std::string optionCoul);
};
#endif // CONTROLE_H


