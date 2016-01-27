#ifndef MASQUE_H
#define MASQUE_H

class Masque{
    private:
        int **tableauMasque;
        int longueur; // un masqaue normalement est un carre
        //int largeur;

    public:
        Masque(int nb);
        //~Masque();
        int getLongueur();//const;
        void setLongueur(int value);
        int sommeMasque();
        int getValeurTableauMasque(int h, int l);
        void setValeurTableauMasque(int h, int l, int v);

        void masqueFlou();
        void masqueGradienY();
        void masqueGradienX();
        void masqueRehaussement();
};

#endif // MASQUE_H
