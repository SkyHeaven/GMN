#ifndef CONTROLE_H
#define CONTROLE_H
#include <QImage>
#include <iostream>
#include <string>
#include <vector>
#include "Image.h"
#include "Pixel.h"

class Controle{
    private:
    std::vector<Image> sauvegardeImage;
    int indexVecteur;

    public:
    int getIndexVecteur() const;
    void setIndexVecteur(int value);
    std::vector<Image> getSauvegardeImage() const;
    void setSauvegardeImage(const std::vector<Image> &value);
    void ouvertureImage(QImage imagef);
    void affichageImage(Image img);
    int* affichageCouleurRGB(int h, int l);
    Image undo();
    Image redo();
    void ajoutOperation(Image img);
    Image filtrage(Image img); //ici creation nouvelle image
    Image amelioration(Image img); //ici creation nouvelle image
    Image crop(Image img, Pixel pixel1, Pixel pixel2);
    void afficherGris();
    void redimension(Image img, std::string option, int l, int h);
    Image afficherHistogramme(Pixel pixel, std::string optionCoul);


};
#endif // CONTROLE_H


