#ifndef CONTROLE_H
#define CONTROLE_H
class Controle{
    //private:

    public:
    IplImage ouvertureImage(string chemin);
    void affichageImage(IplImage img);
    IplImage filtrage(IplImage img); //ici creation nouvelle image
    IplImage amelioration(IplImage img); //ici creation nouvelle image
    IplImage crop(IplImage img, CvScalar pixel1, CvScalar pixel2);
    void redimension(IplImage img, string option, int l, int h);
    IplImage afficherHistogramme(CvScalar pixel, string optionCoul);
};
#endif // CONTROLE_H


