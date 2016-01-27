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
        Image getImg();
        void setImg(Image value);
        void resetEnergy();

        //Seam Vertical
        void seamVertical();
        Image removeVertical();
        void seamCarvingVertical(int nb);

        //Seam Horizontal
        void seamHorizontal();
        Image removeHorizontal();
        void seamCarvingHorizontal(int nb);
};

#endif // SEAMCARVING_H
