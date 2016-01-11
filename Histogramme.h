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
    void initZero();
    Histogramme egaliser(Histogramme hist);
    void incrementeValeurHistogramme(int val);
};

#endif // HISTOGRAMME_H
