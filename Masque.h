#ifndef MASQUE_H
#define MASQUE_H

class Masque{
    private:
    int **tableauMasque;
    int longueur; // un masqaue est un carre
    //int largeur;

    public:
    Masque(int nb);
  //  ~Masque();
    void remplirMasque();
    int getLongueur() const;
    void setLongueur(int value);
    int getValeurTableauMasque(int h, int l);
    int sommeMasque();
    //destructeur
    void masqueGradienY();
    void masqueGradienX();
    void masqueRehaussement();
    void setValeurTableauMasque(int h, int l, int v);
};

#endif // MASQUE_H
