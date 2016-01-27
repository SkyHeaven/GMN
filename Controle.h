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
#define VALSUPPR 2

class Controle{
    private:
        std::vector<Image> sauvegardeImage;
        int indexVecteur;
        bool imageOuverte;

    public:
        Controle();
        std::vector<Image> getSauvegardeImage() const;
        Pixel affichageCouleur(int h, int l);
        Histogramme* afficherHistogramme();

        void ouvertureImage(QImage imagef);
        int getIndexVecteur() const;
        void setIndexVecteur(int value);
        void setSauvegardeImage(const std::vector<Image> &value);
        int* affichageCouleurRGB(int h, int l);
        double* affichageCouleurYUV(int h, int l);
        int affichageCouleurGris(int h , int l);
        void undo();
        void redo();
        void ajoutOperation(Image img);

        void afficherGris();
        void crop(int h1, int l1, int h2, int l2);
        void rotation(std::string option);

        //Redimension
        void redimension(int h, int l);
        void redimensionHauteur(int valeur, Image img);
        void redimensionLargeur(int valeur, Image img);

        //Histogramme
        void etalementHistogramme();
        void egalisation();

        //Fusion
        void fusion(int h1, int l1, int h2, int l2, int h, int l);

        //Les filtres
        void flou();
        void gradientX();
        void gradientY();
        void contour();
        void ameliorationContour();
        void rehaussement();
        void negatif();
        void appliquerMasque(Masque mask,int coeff);

        //Seam Carving
        void seamCarving(int h, int l);


};
#endif // CONTROLE_H


