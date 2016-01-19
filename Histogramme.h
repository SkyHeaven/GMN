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
    void incrementeValeurHistogramme(int val);
    int getValeurIndiceHistogramme(int ind);
    int egaliser(int k, int l);
    void decrementeValeurHistogramme(int val);
};

#endif // HISTOGRAMME_H
