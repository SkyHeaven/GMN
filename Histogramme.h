#ifndef HISTOGRAMME_H
#define HISTOGRAMME_H
#define NBNUANCES 256
#define NBMAX 100

class Histogramme{
    private:
    int tabHist[NBMAX][NBNUANCES];
    public:
    Histogramme egaliser(Histogramme hist);

};

#endif // HISTOGRAMME_H
