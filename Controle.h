#ifndef CONTROLE_H
#define CONTROLE_H
#include <QImage>
#include <iostream>
#include <string>
#include <vector>
#include "Image.h"
#include "Pixel.h"
#include "Histogramme.h"
#include "Masque.h"

#define MINECARTTYPE 100
#define MINMOY 60
#define MAXMOY 190
#define VALSUPPR 10

class Controle{
    private:
    std::vector<Image> sauvegardeImage;
    int indexVecteur;
    bool ouvertuneimage;

    public:
    Controle();
    int getIndexVecteur() const;
    void setIndexVecteur(int value);
    std::vector<Image> getSauvegardeImage() const;
    void setSauvegardeImage(const std::vector<Image> &value);
    void ouvertureImage(QImage imagef);
    void affichageImage(Image img);
    int* affichageCouleurRGB(int h, int l);
    double* affichageCouleurYUV(int h, int l);
    int affichageCouleurGris(int h , int l);
    Pixel affichageCouleur(int h, int l);
    void undo();
    void redo();
    void ajoutOperation(Image img);
    void flou();
    void filtrage(Image img); //ici creation nouvelle image
    void amelioration(Image img); //ici creation nouvelle image
    void crop(int h1, int l1, int h2, int l2);
    void afficherGris();
    Histogramme* afficherHistogramme();
    void rotation(std::string option);
    void redimension(int h, int l);
    void redimensionHauteur(int valeur, Image img);
    void redimensionLargeur(int valeur, Image img);


    void fusion(int h1, int l1, int h2, int l2);

    void transformationHistogramme();
    void egalisation();
    void negatif();
    void gradientX();
    void gradientY();
};
#endif // CONTROLE_H


