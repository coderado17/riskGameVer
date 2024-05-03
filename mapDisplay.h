#ifndef MAPDISPLAY_H
#define MAPDISPLAY_H

#include "N5110.h"

class mapDisplay{

    public:

    mapDisplay();
    void copyTerr (int outline[48][84], int terr[], int countryIndex);
    int* addressRet (int countryIndex);
    int* manoeOnMap (int* curr, int mov);
    int sizeOfTerr (int* curr);
    void test (N5110& lcd);
    //void nextTerr(int dynArr[48][84], int& curr, int caseMv);
    //void copyArray(int arrPaste[48][84], int arrCopy[48][84]);
    //void nextTerr(N5110 screen, int country);

    private:

};

#endif