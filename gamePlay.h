#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "N5110.h"
#include "Joystick.h"
#include "mapDisplay.h"

class gamePlay{

    public:
    gamePlay();
    void displayDecisions(N5110& lcd, Joystick& joys, int* attInd, int* defInd);
    bool checkBorders(int target, int ref);
    bool isUserTerritory(int target);
    void diceThrow(N5110& screen, int diceVal, int diceNo, bool attDef);
    void diceThrow(N5110& screen, int diceNo, bool attDef);
    float reLUWithSatur (float passVal, int lowL, int upL, int multip, bool rev);
    float reLUWithSaturNeg (float passVal, int lowL, int upL, int multip);
    void diffCalc();
    void minMaxMultiply();
    void testArray();
    void solOneISR();
    void playRISK(N5110& lcd, Joystick& joys);
    void resetAllParams();
    void diceRun (N5110& lcd, bool userAtt);
    void resetFav();
    void pcDecide(N5110& lcd, mapDisplay map);


    private:
    std::string solNumtoString (int num);
    void sortArray(bool attORdef);
    void showSolNoandTerr(N5110& lcd, int index);
    void calcOutcome(int defNo);
    void resetArrays();
    void initSolArrays();
    void sortUserSols();
    void sortPCSols();
    void reinforce(N5110& lcd, Joystick& joys);
    void test(N5110& screen, int attNo, int defNo);

};

#endif