#ifndef SEAMCARVING_H
#define SEAMCARVING_H
#include "Image.h"
#include "Pixel.h"
class SeamCarving{
private:
    Image img;
    Pixel **tabChemin;
    int **tabEnergy;
    int ind_min;
public:
    SeamCarving();
    void SeamCarving_algo();
    Image getImg();
    void setImg(Image value);
    void resetEnergy();
    //void resetChemin();
    void seamVertical();
    Image removeVertical();
    void seamHorizontal();
    Image removeHorizontal();
    void seamCarvingHorizontal(int nb);
    void seamCarvingVertical(int nb);
};

#endif // SEAMCARVING_H
