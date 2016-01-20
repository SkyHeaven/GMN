#ifndef SEAMCARVING_H
#define SEAMCARVING_H
#include "Image.h"
#include "Pixel.h"
class SeamCarving{
private:
    Image img;
public:
    void SeamCarving_algo();
   Image getImg();
    void setImg(Image value);
};

#endif // SEAMCARVING_H
