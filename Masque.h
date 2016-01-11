#ifndef MASQUE_H
#define MASQUE_H

class Masque{
    private:
    int **tableauMasque;
    int longueur; // un masqaue est un carre
    //int largeur;

    public:
    Masque(int nb);
    void remplirMasque();
    int getLongueur() const;
    void setLongueur(int value);
    int sommeMasque();
};

#endif // MASQUE_H
