#ifndef HISTOGRAMME_H
#include <malloc.h>
#include <iostream>
#include <string>
#define HISTOGRAMME_H
#define NBNUANCES 256

class Histogramme{
    private:
    int tableauHistogramme[NBNUANCES];
    public:
    Histogramme();
    int* getTableauHistogramme();
    void initZero();
    bool gris(Histogramme h1, Histogramme h2);
    Histogramme egaliser(Histogramme hist);
    void incrementeValeurHistogramme(int val);
    int getValeurIndiceHistogramme(int ind);
};

#endif // HISTOGRAMME_H
