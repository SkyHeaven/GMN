#include <iostream>
#include <string>
#include "Image.h"

using namespace std;

//Image::~Image(){
//    for(int i = 0 ; i < getHauteur() ; i++){
//        delete[] tableauPixel[i];
//     }
//     delete[] tableauPixel;
//}


Pixel **Image::getTableauPixel() const
{
    return tableauPixel;
}

void Image::setTableauPixel(int h, int l){

//    tableauPixel = new Pixel*[h];
//    for(int i = 0; i < h; ++i){
//        tableauPixel[i] = new Pixel[l];
//    }

    // A VOIR si on peut enlever l utilisation de malloc

    tableauPixel = (Pixel**)malloc(h * sizeof(Pixel*));
    for(int i = 0; i<h;i++){
        tableauPixel[i] = (Pixel*)malloc(l* sizeof(Pixel));
    }
}

void Image::setPixel(int h, int l, Pixel p){
    tableauPixel[h][l] = p;
}

Pixel Image::getPixel(int h, int l){
    return tableauPixel[h][l];
}

int Image::getHauteur(){
    return hauteur;
}
void Image::setHauteur(int h){
    hauteur = h;
}

int Image::getLargeur(){
    return largeur;
}

void Image::setLargeur(int l){
    largeur = l;
}

int* Image::getRGB(int h, int l){
    return tableauPixel[h][l].getRGBCouleur();
}

int* Image::getYUV(int h, int l){
    return tableauPixel[h][l].getYUVCouleur();
}

int Image::getGray(int h, int l){
    return tableauPixel[h][l].getGrayCouleur();
}

void Image::setGray(){
    for(int i= 0 ; i <hauteur; i++){
        for(int j =0; j < largeur; j++){
            tableauPixel[i][j].setGraywithRGB(tableauPixel[i][j].getRGBCouleur());
        }
    }
}

void Image::setYUV(){
    for(int i= 0 ; i <hauteur; i++){
        for(int j =0; j < largeur; j++){
            tableauPixel[i][j].setYUVwithRGB(tableauPixel[i][j].getRGBCouleur());
        }
    }
}

void Image::setNoRGB(){
    for(int i= 0 ; i <hauteur; i++){
        for(int j =0; j < largeur; j++){
            for(int k=0; k<NBCOULEUR; k++){
                tableauPixel[i][j].setRGBCouleur(k,-1);
            }
        }
    }
}
void Image::setTableauCourant(int c){
    for(int i= 0 ; i <hauteur; i++){
        for(int j =0; j < largeur; j++){
            tableauPixel[i][j].setEtatCourant(c);
        }
    }
}
Image Image::cloneImage(){
    Image img;
    img.setHauteur(hauteur);
    img.setLargeur(largeur);
    img.setTableauPixel(hauteur,largeur);
    for(int i = 0; i < hauteur; i++){
        for(int j = 0; j < largeur; j++){
            Pixel p = Pixel((double)j,(double)i);
            p = tableauPixel[i][j];
            img.setPixel(i,j,p);
        }
    }
    return img;
}

Image Image::cropImage(int h1, int l1, int h2, int l2){
    Image imgRes;
    int minX = min(l1,l2);
    int minY = min(h1,h2);
    int maxX = max(l1,l2);
    int maxY = max(h1,h2);
    int diffX = maxX - minX;
    int diffY = maxY - minY;

    imgRes.setHauteur(maxY - minY);
    imgRes.setLargeur(maxX - minX);
    imgRes.setTableauPixel(maxY - minY,maxX - minX);
    for(int i = minY; i < maxY; i++){
        for(int j = minX; j < maxX; j++){
            Pixel p = Pixel((double)j-minX,(double)i-minY);
            p = tableauPixel[i][j];
            imgRes.setPixel(i-minY,j-minX, p);
        }
    }
    imgRes.setGray();
    imgRes.setYUV();
    return imgRes;
}

Histogramme* Image::initHistogramme(){
    Histogramme *tabHist;
    tabHist = (Histogramme*)malloc(NBCOULEUR* sizeof(Histogramme));
    for(int i = 0; i < NBCOULEUR; i ++){
        tabHist[i]=Histogramme();
    }

    for(int i= 0; i < getHauteur(); i++){
        for(int j = 0; j < getLargeur(); j++){
            Pixel p = getPixel(i,j);
            int* tabRep = p.getEtatCourant();
            for(int k = 0; k < NBCOULEUR; k++){
                tabHist[k].incrementeValeurHistogramme(tabRep[k]);
            }
        }
    }
    return tabHist;
}

Image Image::rotationTableauPixel(string option){
    Image imgRes;
    int h,l=0;

    if(option == "180"){
        h = getHauteur();
        l = getLargeur();
    }

    else{
        l = getHauteur();
        h = getLargeur();
    }

     imgRes.setHauteur(h);
     imgRes.setLargeur(l);
     imgRes.setTableauPixel(h,l);

    for(int i=0; i<h; i++){
        for(int j=0; j<l; j++){
            Pixel p = rotationPixel(h,l,i,j,option);
            imgRes.setPixel(i,j,p);
        }
    }
    return imgRes;
}

Pixel Image::rotationPixel(int h, int l, int i, int j, string option){
    if(option == "180"){
        Pixel p = getPixel(h-i-1,l-j-1);
        return p;
    }

    else if(option == "90D"){
        Pixel p = getPixel(l-j-1,i);
        //cout<<"tuti"<<endl;
        return p;
    }

    else if(option =="90G"){
        Pixel p = getPixel(j,h-i-1);
        return p;
    }
}

void Image::flouImage(){
    Masque mask = Masque(9);
    mask.remplirMasque();

    int hImg = getHauteur();
    int lImg = getLargeur();
    int lMask = mask.getLongueur();
    int sumMask =mask.sommeMasque();;
    int *tabCol = new int[NBCOULEUR];
    int *tabSum = new int[NBCOULEUR];
    string coul = quelleCouleur();
    int tabZero[3] = {0,0,0};

    for(int i= lMask/2; i<hImg - lMask/2; i++){
        for(int j=lMask/2; j<lImg - lMask/2; j++){

            for(int i=0; i<NBCOULEUR; i++){ //init tabSum
                tabSum[i] = 0;
            }

            Pixel p = Pixel(j,i);
            for(int i2=0; i2<lMask; i2++){
                for(int j2=0; j2<lMask; j2++){
                    tabCol = getPixel(i -lMask/2+i2,j-lMask/2+j2).getEtatCourant();
                    for(int k=0; k<NBCOULEUR; k++){
                        tabSum[k] += mask.getValeurTableauMasque(i2,j2)*tabCol[k];
                    }
                }
            }

            for(int k=0; k<NBCOULEUR; k++){
                tabSum[k] = tabSum[k]/sumMask;
            }
            p.setCouleur(coul,tabSum);

            setPixel(i,j,p);
            // ATTENTION NE PAS OUBLIER DE SET COULEUR + ETAT COURANT
            // MALLOC masque

        }
    }
    for(int i=0; i<hImg; i++){
         for(int ind=0; ind <lMask/2; ind++){
             Pixel p1 = Pixel(ind,i);
             Pixel p2 = Pixel(lImg-1-ind,i);
             for(int k =0; k<NBCOULEUR; k++){
                 p1.setRGBCouleur(k,0);
                 p2.setRGBCouleur(k,0);
             }
             p1.setCouleur(coul,tabZero);
             p2.setCouleur(coul,tabZero);
             setPixel(i,ind,p1);
             setPixel(i,lImg-1-ind,p2);
         }
    }

    for(int j=1; j<lImg-1; j++){
        for(int ind=0; ind <lMask/2; ind++){
            Pixel p1 = Pixel(j,ind);
            Pixel p2 = Pixel(j,hImg-1-ind);
            for(int k =0; k<NBCOULEUR; k++){
             p1.setRGBCouleur(k,0);
             p2.setRGBCouleur(k,0);
            }
            p1.setCouleur(coul,tabZero);
            p2.setCouleur(coul,tabZero);
            setPixel(ind,j,p1);
            setPixel(hImg-1-ind,j,p2);
        }
    }


//    for(int i=0; i<lMask/2; i++){ // remplissage du contour de l image
//        for(int j=0; j<lMask/2; j++){
//            Pixel p = Pixel(j,i);
//             Pixel p = Pixel(j,i);
//        }
//    }
    //mask.~Masque();
}

string Image::quelleCouleur(){

    Pixel p =getPixel(0,0);
    int *tab = p.getRGBCouleur();
    if(tab[0] == -1) return "gris";
    else return "rgb";


            /* bool boolean = true;
    int i =0; int j =0;
    int *tmpRGB;
    int *tmpEtatCourant;
    Pixel p = Pixel(j,i);
    tmpRGB = p.getRGBCouleur();
    tmpEtatCourant = p.getEtatCourant();
    int tmp;
    while(boolean){
        for(int k=0; k<NBCOULEUR; k++){
            boolean = boolean && (tmpRGB[k] == tmpEtatCourant[k]) && (getGray(i,j) == tmpEtatCourant[0]);
            if(!boolean){
                tmp = k;
                break;
            }
        }
        if(boolean){
            if(j < getLargeur()) j++;
            else{
                j=0; i++;
            }
        }
        else{
            if(tmpRGB[tmp] == tmpEtatCourant[tmp]) return "rgb";
            else return "gris";
        }
    }
*/
}

Image Image::reductionHauteurImage(int valeur){
    Image imgRes;
    imgRes.setLargeur(getLargeur());
    imgRes.setHauteur(valeur);
    imgRes.setTableauPixel(valeur, getLargeur());
    int h,l;
    h = imgRes.getHauteur();
    l = imgRes.getLargeur();

    double coeffReduc = (double)getHauteur()/(double)h;
    double borneInf, borneSup;
    int tabSum[3];
    int ind;
    int cpt;
    string coul = quelleCouleur();
    for(int i=0; i<h; i++){
        for(int j=0; j<l; j++){
            for(int i=0; i<NBCOULEUR; i++){ //init tabSum
                tabSum[i] = 0;
            }

            Pixel p = Pixel(j,i);
            borneInf = (double)i*coeffReduc;
            borneSup = ((double)i+1.0)*coeffReduc;
            ind = (int)borneInf;
            cpt =0;
            while(ind < borneSup){
                for(int k=0; k<NBCOULEUR; k++){
                    tabSum[k] += getPixel(ind,j).getSingleRGB(k);
                }
                cpt++;
                ind++;
            }

            for(int k=0; k<NBCOULEUR; k++){
                tabSum[k] = tabSum[k]/cpt;
            }
            p.setCouleur(coul,tabSum);
            imgRes.setPixel(i,j,p);
        }
    }
    return imgRes;
}

Image Image::reductionLargeurImage(int valeur){
    Image imgRes;
    imgRes.setLargeur(valeur);
    imgRes.setHauteur(getHauteur());
    imgRes.setTableauPixel(getHauteur(),valeur);
    int h,l;
    h = imgRes.getHauteur();
    l = imgRes.getLargeur();

    double coeffReduc = (double)getLargeur()/(double)l;
    double borneInf, borneSup;
    int tabSum[3];
    int ind;
    int cpt;
    string coul = quelleCouleur();
    for(int i=0; i<h; i++){
        for(int j=0; j<l; j++){
            for(int i=0; i<NBCOULEUR; i++){ //init tabSum
                tabSum[i] = 0;
            }

            Pixel p = Pixel(j,i);
            borneInf = (double)j*coeffReduc;
            borneSup = ((double)j+1.0)*coeffReduc;
            ind = (int)borneInf;
            cpt =0;
            while(ind < borneSup){
                for(int k=0; k<NBCOULEUR; k++){
                    tabSum[k] += getPixel(i,ind).getSingleRGB(k);
                }
                cpt++;
                ind++;
            }

            for(int k=0; k<NBCOULEUR; k++){
                tabSum[k] = tabSum[k]/cpt;
            }
            p.setCouleur(coul,tabSum);
            imgRes.setPixel(i,j,p);
        }
    }
    return imgRes;
}

Image Image::etirementImage(int h, int l){
    Image imgRes;
    imgRes.setLargeur(l);
    imgRes.setHauteur(h);
    imgRes.setTableauPixel(h,l);

    double coeffEtirHaut = (double)h/(double)getHauteur();
    double coeffEtirLarg = (double)l/(double)getLargeur();
    double borneInfHaut, borneInfLarg, borneSupHaut, borneSupLarg;
    int tabSum[3];
    double t1,t2,u1,u2,sumCoeff;
    int x,y;
    string coul = quelleCouleur();

    for(int i=0; i<h-1; i++){
        for(int j=0; j<l-1; j++){
            borneInfHaut = (double)i/coeffEtirHaut;
            borneInfLarg = (double)j/coeffEtirLarg;
            borneSupHaut = (double)(i+1)/coeffEtirHaut;
            borneSupLarg = (double)(j+1)/coeffEtirLarg;
            Pixel p = Pixel(j,i);

            if( (((int)borneInfHaut == (int)borneSupHaut) && ((int)borneInfLarg == (int)borneSupLarg)) || (i==j)){
                for(int k=0; k<NBCOULEUR; k++){ //init tabSum
                    tabSum[k] = 0;
                }
                for(int k=0; k<NBCOULEUR; k++){
                   tabSum[k] += getPixel((int)borneInfHaut, (int)borneInfLarg).getSingleRGB(k);
                }
            }

            else if( ((int)borneInfHaut != (int)borneSupHaut) && ((int)borneInfLarg != (int)borneSupLarg)){
                x= (int)borneSupLarg;// + 0.5*coeffEtirLarg;
                y= (int)borneSupHaut;// + 0.5*coeffEtirHaut;
                t1 = distance(borneInfLarg, borneInfHaut, x,y);
                t2 = distance(borneInfLarg, borneSupHaut, x,y); //bizarre
                u1 = distance(borneSupLarg, borneInfHaut, x,y);
                u2 = distance(borneSupLarg, borneSupHaut, x,y);

    //            t1 = 1 - (x-borneInfLarg); // a verif
    //            t2 = borneSupLarg-x;
    //            u1 = 1 -(y-borneInfHaut); // a verif
    //            u2 = borneSupHaut-y;


                sumCoeff = t1 +t2 + u1 + u2;
                if(sumCoeff !=1){
                    t1 /= sumCoeff;
                    t2 /= sumCoeff;
                    u1 /= sumCoeff;
                    u2 /= sumCoeff;
                }

                for(int k=0; k<NBCOULEUR; k++){ //init tabSum
                    tabSum[k] = 0;
                }

                for(int k=0; k<NBCOULEUR; k++){
                   tabSum[k] += getPixel((int)borneInfHaut, (int)borneInfLarg).getSingleRGB(k)*t1; //recupere le pixel de lancienne image et multiplie les valeur de couleur par son coeff
                   tabSum[k] += getPixel((int)borneSupHaut, (int)borneInfLarg).getSingleRGB(k)*t2;
                   tabSum[k] += getPixel((int)borneInfHaut, (int)borneSupLarg).getSingleRGB(k)*u1;
                   tabSum[k] += getPixel((int)borneSupHaut, (int)borneSupLarg).getSingleRGB(k)*u2;
                }
            }

            else if( ((int)borneInfHaut == (int)borneSupHaut) && ((int)borneInfLarg != (int)borneSupLarg)){
                x= (int)borneSupLarg;
                y= (int)borneSupHaut;// + 0.5*coeffEtirHaut;
                t1 = distance(borneInfLarg, borneInfHaut, x,y);
                t2 = distance(borneInfLarg, borneSupLarg, x,y);

                sumCoeff = t1 +t2;
                if(sumCoeff !=1){
                    t1 /= sumCoeff;
                    t2 /= sumCoeff;
                }

                for(int k=0; k<NBCOULEUR; k++){ //init tabSum
                    tabSum[k] = 0;
                }

                for(int k=0; k<NBCOULEUR; k++){
                   tabSum[k] += getPixel((int)borneInfHaut, (int)borneInfLarg).getSingleRGB(k)*t1; //recupere le pixel de lancienne image et multiplie les valeur de couleur par son coeff
                   tabSum[k] += getPixel((int)borneInfHaut, (int)borneSupLarg).getSingleRGB(k)*t2;
                }

            }
            else if( ((int)borneInfHaut != (int)borneSupHaut) && ((int)borneInfLarg == (int)borneSupLarg)){
                x= (int)borneSupLarg;// + 0.5*coeffEtirLarg;
                y= (int)borneSupHaut;
                u1 = distance(borneSupLarg, borneInfHaut, x,y);
                u2 = distance(borneSupLarg, borneSupHaut, x,y);

                sumCoeff =u1 + u2;
                if(sumCoeff !=1){
                    u1 /= sumCoeff;
                    u2 /= sumCoeff;
                }

                for(int k=0; k<NBCOULEUR; k++){ //init tabSum
                    tabSum[k] = 0;
                }

                for(int k=0; k<NBCOULEUR; k++){
                   tabSum[k] += getPixel((int)borneInfHaut, (int)borneSupLarg).getSingleRGB(k)*u1;
                   tabSum[k] += getPixel((int)borneSupHaut, (int)borneSupLarg).getSingleRGB(k)*u2;
                }
            }



            else{ cout << "erreur ici" << endl;}


            p.setCouleur(coul,tabSum);
            imgRes.setPixel(i,j,p);
        }
    }
    return imgRes;
}

int Image::arrondiSuperieur(double d){
    int rep;
    //rep = (int)t;
    if((d- rep) > 0){
        rep++;
    }
    return rep;
}


double Image::distance(double x1, double y1, int x2, int y2){
    return sqrt(pow(((double)x2-x1),2) + pow(((double)y2 - y1),2));
}

