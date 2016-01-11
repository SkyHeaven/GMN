#ifndef CONTROLE_H
#define CONTROLE_H
#include <QImage>
#include <iostream>
#include <string>
#include <vector>
#include "Image.h"
#include "Pixel.h"
#include "Histogramme.h"

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
    int* affichageCouleurYUV(int h, int l);
    int affichageCouleurGris(int h , int l);
    Pixel affichageCouleur(int h, int l);
    void undo();
    void redo();
    void ajoutOperation(Image img);
    Image filtrage(Image img); //ici creation nouvelle image
    Image amelioration(Image img); //ici creation nouvelle image
    void crop(int h1, int l1, int h2, int l2);
    void afficherGris();
    void redimension(Image img, std::string option, int l, int h);
    Histogramme* afficherHistogramme(Image img, std::string optionCoul);


};
#endif // CONTROLE_H


