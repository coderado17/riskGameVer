#include "gamePlay.h"
#include <algorithm>
#include <cstdio>
#include <string>
#include <random>
#include "mbed.h"

DigitalIn conButton(PH_0, PullDown);
DigitalIn cancButton(PH_1, PullDown);
DigitalIn joyButton(PC_0, PullUp);
InterruptIn selO (PA_11, PullDown);
InterruptIn selT (PB_12, PullDown);
InterruptIn selThr (PB_11, PullDown);

AnalogIn force (PC_0);

DigitalIn seleOne (PA_15, PullDown);
DigitalIn seleTwo (PA_14, PullDown);
DigitalIn seleThree (PA_13, PullDown);



int nAmerica[429][2] = {
    {9,63},{9,64},{9,65},{9,66},{10,60},{10,61},{10,62},{10,67},{11,57},{11,58},{11,59},{11,60},{11,68},{12,53},{12,54},{12,55},{12,56},{12,57},{12,69},{12,70},{12,71},{12,72},{12,73},{12,74},{13,52},{13,74},{13,75},{14,50},{14,51},{14,75},{15,49},{15,50},{15,74},{16,49},{16,73},{16,74},{17,49},{17,50},{17,51},{17,52},{17,53},{17,54},{17,55},{17,73},{18,55},{18,56},{18,71},{18,72},{18,73},{19,39},{19,40},{19,56},{19,57},{19,70},{19,71},{19,73},{19,74},{20,39},{20,41},{20,58},{20,70},{20,74},{21,12},{21,13},{21,14},{21,39},{21,41},{21,55},{21,56},{21,57},{21,58},{21,59},{21,70},{21,74},{21,75},{22,9},{22,10},{22,11},{22,12},{22,15},{22,16},{22,17},{22,18},{22,24},{22,25},{22,26},{22,39},{22,41},{22,51},{22,52},{22,53},{22,54},{22,55},{22,56},{22,57},{22,59},{22,71},{22,76},{23,8},{23,18},{23,19},{23,20},{23,21},{23,22},{23,23},{23,26},{23,27},{23,28},{23,39},{23,42},{23,44},{23,45},{23,46},{23,47},{23,48},{23,49},{23,50},{23,53},{23,54},{23,57},{23,59},{23,60},{23,71},{23,76},{23,77},{23,78},{23,79},{23,80},{23,81},{24,8},{24,16},{24,29},{24,30},{24,31},{24,32},{24,34},{24,35},{24,36},{24,37},{24,38},{24,39},{24,42},{24,43},{24,44},{24,46},{24,52},{24,53},{24,57},{24,60},{24,68},{24,69},{24,70},{24,75},{24,76},{24,81},{25,8},{25,32},{25,33},{25,34},{25,46},{25,50},{25,51},{25,52},{25,57},{25,60},{25,67},{25,75},{25,81},{25,82},{26,3},{26,5},{26,8},{26,17},{26,45},{26,46},{26,48},{26,49},{26,50},{26,56},{26,57},{26,60},{26,66},{26,74},{26,81},{26,82},{27,1},{27,2},{27,3},{27,4},{27,5},{27,6},{27,7},{27,8},{27,42},{27,43},{27,44},{27,47},{27,48},{27,56},{27,60},{27,66},{27,74},{27,78},{27,79},{27,80},{27,81},{28,2},{28,4},{28,7},{28,42},{28,46},{28,47},{28,56},{28,60},{28,65},{28,66},{28,74},{28,75},{28,76},{28,77},{28,80},{29,7},{29,36},{29,41},{29,42},{29,45},{29,46},{29,48},{29,49},{29,50},{29,51},{29,55},{29,60},{29,61},{29,65},{29,79},{29,80},{30,8},{30,15},{30,16},{30,17},{30,18},{30,19},{30,24},{30,32},{30,41},{30,44},{30,47},{30,48},{30,52},{30,53},{30,55},{30,61},{30,64},{30,78},{30,80},{31,9},{31,14},{31,15},{31,19},{31,22},{31,34},{31,41},{31,42},{31,43},{31,44},{31,47},{31,53},{31,54},{31,55},{31,62},{31,63},{31,77},{31,81},{32,8},{32,13},{32,14},{32,19},{32,20},{32,21},{32,42},{32,43},{32,44},{32,47},{32,54},{32,55},{32,74},{32,75},{32,77},{32,80},{33,7},{33,11},{33,12},{33,13},{33,21},{33,22},{33,44},{33,47},{33,55},{33,73},{33,74},{33,76},{33,78},{33,80},{34,6},{34,9},{34,10},{34,11},{34,23},{34,24},{34,34},{34,44},{34,45},{34,47},{34,48},{34,56},{34,73},{34,76},{34,81},{35,6},{35,8},{35,9},{35,24},{35,25},{35,45},{35,46},{35,48},{35,57},{35,73},{35,74},{35,75},{35,78},{35,81},{35,83},{35,84},{36,6},{36,7},{36,8},{36,25},{36,26},{36,28},{36,46},{36,47},{36,48},{36,57},{36,58},{36,77},{36,80},{36,82},{36,83},{37,26},{37,37},{37,44},{37,46},{37,51},{37,52},{37,53},{37,54},{37,55},{37,58},{37,78},{37,79},{37,82},{38,26},{38,27},{38,42},{38,51},{38,55},{38,56},{38,57},{38,58},{38,81},{38,82},{39,27},{39,51},{39,52},{39,81},{40,27},{40,49},{40,52},{40,53},{40,79},{40,80},{40,81},{41,27},{41,51},{41,52},{41,78},{41,79},{42,27},{42,28},{42,49},{42,50},{42,78},{42,83},{42,84},{43,28},{43,49},{43,78},{43,79},{43,80},{43,81},{43,82},{43,83},{44,28},{44,29},{44,40},{44,49},{44,84},{45,29},{45,38},{45,48},{45,82},{45,83},{45,84},{46,29},{46,30},{46,46},{46,47},{46,79},{46,80},{46,81},{47,30},{47,39},{47,46},{47,79},{48,30},{48,46},{48,78}
};
std::string abbs [12] = {"ALS - ", "NWT - ", "ALB - ", "ONT - ", "WUS - ", "EUS - ", "", "QBC - ", "GRL - ", "GRB - ", "ICL - ", "WEU - "};
int solNumTerr [12] = {12, 4, 3, 1, 5, 30, 15, 2, 4, 3, 11, 7};
bool territories [12] = {true, true, true, true, false, false, true, true, true, true, true, true};
char borders[12][6] = {{'B', 'C', 'B', 'C', 'C', 'C'}, {'A', 'C', 'D', 'I', 'I', 'I'}, {'A', 'B', 'D', 'E', 'E', 'E'}, 
                       {'B', 'C', 'E', 'F', 'H', 'I'}, {'C', 'D', 'F', 'F', 'F', 'F'}, {'D', 'H', 'E', 'E', 'E', 'E'},
                       {'D', 'H', 'E', 'E', 'E', 'E'}, {'D', 'E', 'I', 'I', 'I', 'I'}, {'B', 'D', 'H', 'K', 'K', 'K'},
                       {'K', 'K', 'K', 'K', 'K', 'K'}, {'I', 'J', 'J', 'J', 'J', 'J'}, {'J', 'J', 'J', 'J', 'J', 'J'}};
mapDisplay mapGlobal;

// Interrupt variables for choosing how many user to attack with:
volatile bool selOne = false;
volatile bool selTwo = false;
volatile bool selThree = false;

// PC Player's Decision Making
int userTerrSort[12][2] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}, {0, 8}, {0, 9}, {0, 10}, {0, 11}};
int pcTerrSort[12][2] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}, {0, 8}, {0, 9}, {0, 10}, {0, 11}};
int pcTerrRELUs[12][2] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}, {0, 8}, {0, 9}, {0, 10}, {0, 11}};
float discard[12][2] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}, {0, 8}, {0, 9}, {0, 10}, {0, 11}};
float favorite[12][6] = {{0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, 
                         {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, 
                         {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}};
float reLUUser[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
// ----


// Maximum Attack and Maximum Defence need to be referenced as previous method of feeding attNo and defNo does not work
// properly when it comes to 2 VS 1 for instance.
int maxAtt = 3;
int maxDef = 2;
//-----

bool isOne = false;
bool isTwo = false;
bool isThree = false;

const int diceFrame[11][11]= {
	{ 1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1 }
};
const int diceTOne[1][1]= {
	{ 1 }
};
const int diceTTwo[5][5]= {
	{ 1,0,0,0,0 },
	{ 0,0,0,0,0 },
	{ 0,0,0,0,0 },
	{ 0,0,0,0,0 },
	{ 0,0,0,0,1 }
};
const int diceTThree[5][5]= {
	{ 1,0,0,0,0 },
	{ 0,0,0,0,0 },
	{ 0,0,1,0,0 },
	{ 0,0,0,0,0 },
	{ 0,0,0,0,1 }
};
const int diceTFour[5][5]= {
	{ 1,0,0,0,1 },
	{ 0,0,0,0,0 },
	{ 0,0,0,0,0 },
	{ 0,0,0,0,0 },
	{ 1,0,0,0,1 }
};
const int diceTFive[5][5]= {
	{ 1,0,0,0,1 },
	{ 0,0,0,0,0 },
	{ 0,0,1,0,0 },
	{ 0,0,0,0,0 },
	{ 1,0,0,0,1 }
};
const int diceTSix[5][5]= {
	{ 1,0,1,0,1 },
	{ 0,0,0,0,0 },
	{ 0,0,0,0,0 },
	{ 0,0,0,0,0 },
	{ 1,0,1,0,1 }
};
const int minusSign[1][11]= {
	{ 1,1,1,1,1,1,1,1,1,1,1,}
};
const int plusSign[11][11]= {
	{ 0,0,0,0,0,1,0,0,0,0,0 },
	{ 0,0,0,0,0,1,0,0,0,0,0 },
	{ 0,0,0,0,0,1,0,0,0,0,0 },
	{ 0,0,0,0,0,1,0,0,0,0,0 },
	{ 0,0,0,0,0,1,0,0,0,0,0 },
	{ 1,1,1,1,1,1,1,1,1,1,1 },
	{ 0,0,0,0,0,1,0,0,0,0,0 },
	{ 0,0,0,0,0,1,0,0,0,0,0 },
	{ 0,0,0,0,0,1,0,0,0,0,0 },
	{ 0,0,0,0,0,1,0,0,0,0,0 },
	{ 0,0,0,0,0,1,0,0,0,0,0 }
};

int curr = 0;
int attDice[3] = {0, 0, 0};
int defDice[2] = {0, 0};
int numberLost[2] = {0, 0};
int attNo = 0;
int defNo = 0;
int attFrom = 0;
int defAt = 0;
int attI = 8;
int defI = 4;
std::string owned [2] = {"PC:", "U:"};
int userReinf = 10;
int pcReinf = 10;


gamePlay::gamePlay(){}

void gamePlay::reinforce(N5110& lcd, Joystick& joys){
bool terrChosen = false;
int deploy = 1;
// To print and show how many soldiers each player gets:
    lcd.clear();
    lcd.printString("U:", 5, 2);
    lcd.printString(to_string(userReinf).c_str(), 17, 2);
    lcd.drawLine(37, 1, 37, 47, 1);
    lcd.printString("PC:", 49, 2);
    lcd.printString(to_string(pcReinf).c_str(), 66, 2);
    lcd.refresh();

    ThisThread::sleep_for(2s);

// User deploys V
    lcd.clear();
    while (!terrChosen){

       
        lcd.draw((int*)nAmerica, 429); 
        if(joys.get_angle() > 320){ lcd.clear(); lcd.draw((int*)nAmerica, 429);  lcd.draw(mapGlobal.manoeOnMap(&curr, 0), mapGlobal.sizeOfTerr(&curr));  lcd.printString(to_string(userReinf).c_str(), 20, 0);  lcd.printString("Re", 3, 0);}
        if(joys.get_angle() > 160 && joys.get_angle() < 200){ lcd.clear(); lcd.draw((int*)nAmerica, 429);  lcd.draw(mapGlobal.manoeOnMap(&curr, 1), mapGlobal.sizeOfTerr(&curr));  lcd.printString(to_string(userReinf).c_str(), 20, 0);  lcd.printString("Re", 3, 0);}
        if(joys.get_angle() > 70 && joys.get_angle() < 110){ lcd.clear(); lcd.draw((int*)nAmerica, 429); lcd.draw(mapGlobal.manoeOnMap(&curr, 2), mapGlobal.sizeOfTerr(&curr));  lcd.printString(to_string(userReinf).c_str(), 20, 0);  lcd.printString("Re", 3, 0);}
        if(joys.get_angle() > 250 && joys.get_angle() < 290){ lcd.clear(); lcd.draw((int*)nAmerica, 429); lcd.draw(mapGlobal.manoeOnMap(&curr, 3), mapGlobal.sizeOfTerr(&curr));  lcd.printString(to_string(userReinf).c_str(), 20, 0);  lcd.printString("Re", 3, 0);}
        lcd.refresh();
        terrChosen = conButton.read();
        
        if (terrChosen && !territories[curr]) {
            lcd.clear();
            lcd.printString("NOT", 33, 2);
            lcd.printString("YOUR TERR. !", 18, 3);
            lcd.refresh();
            ThisThread::sleep_for(1s);
            lcd.clear();
            terrChosen = 0;
        }

        else if (terrChosen && territories[curr]){
            terrChosen = 0;
        while (!terrChosen) {
            lcd.clear();
            lcd.printString("-", 1, 2);
            lcd.printString("+", 76, 2);
            lcd.printString(to_string(deploy).c_str(), 33, 2);
            lcd.refresh();
            terrChosen = conButton.read();
            if (seleOne.read() && deploy < userReinf) deploy++; 
            if (seleTwo.read() && deploy > 1) deploy--;
            ThisThread::sleep_for(50ms);
            } // is it user's own territory?
            userReinf -= deploy; // Update user's remnant army
            solNumTerr[curr] += deploy;
            printf("Territory %d at %d soldiers, now at %d \n", curr, solNumTerr[curr] - deploy, solNumTerr[curr]);
        }
        
        ThisThread::sleep_for(500ms);
    }

}

void gamePlay::playRISK(N5110& lcd, Joystick& joys) {
/*mapDisplay map;
resetAllParams();
displayDecisions(lcd, joys, &attI, &defI);
diceRun(lcd, true);
pcDecide(lcd, map);
attNo = 3;

// Ask user with how many are they defending?
lcd.clear();
lcd.printString("DEF. NUMBER?", 1, 1);
lcd.printString("1", 12, 4);
lcd.printString("2", 40, 4);
lcd.refresh();
//HOW MANY IS USER DEFENDING WITH?
        while ((!isOne && !isTwo) && !isThree){
        isOne = seleOne.read();
        isTwo = seleTwo.read();
        isThree = seleThree.read();
        ThisThread::sleep_for(500ms);
        }

if (isOne) defNo = 1;
else if (isTwo) defNo = 2;

while (force.read() < 0.7) {
    lcd.clear();
    lcd.printString("HOLD", 30, 2);
    lcd.refresh();
}
while(force.read() > 0.7) {
    lcd.clear();
    lcd.printString("RELEASE", 10, 2);
    lcd.refresh();
}
diceRun(lcd, false);*/
reinforce(lcd, joys);
ThisThread::sleep_for(15s);

}

void gamePlay::diceRun (N5110& lcd, bool userAtt) {
    lcd.clear();
    for (int i = 1; i <= attNo; i++){
        for (int j = 1; j <= 6; j++){
            diceThrow(lcd, j, i, true);
            lcd.refresh();
            ThisThread::sleep_for(300ms);
        diceThrow(lcd, i, true);
        lcd.refresh();
    }   
    } // ^ To give a sense of rolling
    sortArray(true);
    lcd.refresh();

    lcd.printString("VS", 35, 2);
    lcd.refresh();

    for (int i = 1; i <= defNo; i++){
        for (int j = 1; j <= 6; j++){
            diceThrow(lcd, j, i, false);
            lcd.refresh();
             ThisThread::sleep_for(300ms);
    }
        diceThrow(lcd, i, false);
        lcd.refresh();
    }
    sortArray(false);
    ThisThread::sleep_for(3000ms);

    calcOutcome(defNo);
    solNumTerr[attFrom] -= numberLost[0];
    solNumTerr[defAt] -= numberLost[1];

    // End the outcome at the victory of attacker
    if (solNumTerr[defAt] < 1) {
    if (userAtt) {
    lcd.clear();
    lcd.printString("YOU WON", 20, 2);
    lcd.printString("THE TERRITORY", 1, 3);
    lcd.refresh();
    }
    else {
    lcd.clear();
    lcd.printString("YOU LOST", 20, 2);
    lcd.printString("THE TERRITORY", 1, 3);
    lcd.refresh(); 
    }
    solNumTerr[attFrom]--;
    solNumTerr[defAt] = 1;
    territories[defAt] = !territories[defAt];
    }

    resetArrays();
}

void gamePlay::resetAllParams() {
    curr = 0;
    attNo = 0;
    defNo = 0;
    attFrom = 0;
    defAt = 0;
    maxAtt = 3;
    maxDef = 2;
    isOne = false;
    isTwo = false;
    isThree = false;
    resetArrays();
}

void gamePlay::showSolNoandTerr(N5110& lcd, int index) {
// Show X for PC owned, and O for user owned territories at the top right corner.
if(territories[index]){
    lcd.printString(owned[territories[index]].c_str(), 3, 0);
    lcd.printString(to_string(solNumTerr[index]).c_str(), 22, 0);
    lcd.refresh();
}
else {
    lcd.printString(owned[territories[index]].c_str(), 3, 0);
    lcd.printString(to_string(solNumTerr[index]).c_str(), 22, 0);
    lcd.refresh();
}

}

void gamePlay::displayDecisions(N5110& lcd, Joystick& joys, int* attInd, int* defInd){

    bool terrChosen = false;
    bool defChosen = false;
    bool cancel = true;
    while (cancel) {
         lcd.clear();
        // User chooses the territory to attack from
        while (!terrChosen){
        lcd.draw((int*)nAmerica, 429); 
        if(joys.get_angle() > 320){ lcd.clear(); lcd.draw((int*)nAmerica, 429);  lcd.draw(mapGlobal.manoeOnMap(&curr, 0), mapGlobal.sizeOfTerr(&curr)); showSolNoandTerr(lcd, curr); }
        if(joys.get_angle() > 160 && joys.get_angle() < 200){ lcd.clear(); lcd.draw((int*)nAmerica, 429);  lcd.draw(mapGlobal.manoeOnMap(&curr, 1), mapGlobal.sizeOfTerr(&curr)); showSolNoandTerr(lcd, curr); }
        if(joys.get_angle() > 70 && joys.get_angle() < 110){ lcd.clear(); lcd.draw((int*)nAmerica, 429); lcd.draw(mapGlobal.manoeOnMap(&curr, 2), mapGlobal.sizeOfTerr(&curr)); showSolNoandTerr(lcd, curr); }
        if(joys.get_angle() > 250 && joys.get_angle() < 290){ lcd.clear(); lcd.draw((int*)nAmerica, 429); lcd.draw(mapGlobal.manoeOnMap(&curr, 3), mapGlobal.sizeOfTerr(&curr)); showSolNoandTerr(lcd, curr); }
        lcd.refresh();
        terrChosen = conButton.read();
        if (terrChosen){
            if (isUserTerritory(curr)){
                if(solNumTerr[curr] > 2){
            *attInd = curr;
            lcd.clear();
            lcd.printString(abbs[curr].c_str(), 16, 2);
            lcd.printString((solNumtoString(solNumTerr[curr])).c_str(), 58, 2);
            lcd.printString("CHOSEN!", 20, 3);
            lcd.refresh();
            ThisThread::sleep_for(2000ms);

            lcd.clear();
            lcd.printString("CANCEL?", 20, 3);
            lcd.refresh();
            int cancCount = 1;
            while (cancCount <= 7) {
            cancel = cancButton.read();
            ThisThread::sleep_for(300ms);
            cancCount++;
            }

            }
                else {
                lcd.clear();
                lcd.printString("ARMY NOT", 10, 2);
                lcd.printString("ENOUGH", 20, 3);
                lcd.refresh();
                ThisThread::sleep_for(1s);
                lcd.clear();
                terrChosen = 0;
                }
            } // is it user's own territory?
            else {
            lcd.clear();
            lcd.printString("NOT", 33, 2);
            lcd.printString("YOUR TERR. !", 18, 3);
            lcd.refresh();
            ThisThread::sleep_for(1s);
            lcd.clear();
            terrChosen = 0;
            }
        }
        
        ThisThread::sleep_for(500ms);
        }
        terrChosen = 0;
        }

        lcd.clear();
        lcd.printString("ATTACK NUMBER?", 1, 1);
        lcd.drawRect(5, 21, 21, 24, FILL_TRANSPARENT); // Slot 1
        lcd.printString("1", 12, 4);
        lcd.drawRect(33, 21, 21, 24, FILL_TRANSPARENT); // Slot 2
        lcd.printString("2", 40, 4);
        lcd.drawRect(62, 21, 21, 24, FILL_TRANSPARENT); // Slot 3
        lcd.printString("3", 68, 4);
        lcd.refresh();

        //HOW MANY IS USER ATTACKING WITH?
        while ((!isOne && !isTwo) && !isThree){
        isOne = seleOne.read();
        isTwo = seleTwo.read();
        isThree = seleThree.read();
        printf("%d | %d | %d", isOne, isTwo, isThree);
        ThisThread::sleep_for(500ms);
        }

        if (isOne) attNo = 1;
        else if (isTwo) attNo = 2;
        else if (isThree) attNo = 3;

        lcd.clear();
        lcd.printString("ATTACKING WITH", 1, 2);
        lcd.printString(solNumtoString(attNo).c_str(), 40, 3);
        lcd.refresh();
        ThisThread::sleep_for(2s);
        curr = 0;
        lcd.clear();
        while (!defChosen) {
        lcd.clear();
        lcd.draw((int*)nAmerica, 429);
        if(joys.get_angle() > 320){lcd.draw(mapGlobal.manoeOnMap(&curr, 0), mapGlobal.sizeOfTerr(&curr));lcd.refresh();}
        if(joys.get_angle() > 160 && joys.get_angle() < 200){lcd.draw(mapGlobal.manoeOnMap(&curr, 1), mapGlobal.sizeOfTerr(&curr));lcd.refresh();}
        if(joys.get_angle() > 70 && joys.get_angle() < 110){lcd.draw(mapGlobal.manoeOnMap(&curr, 2), mapGlobal.sizeOfTerr(&curr));lcd.refresh();}
        if(joys.get_angle() > 250 && joys.get_angle() < 290){lcd.draw(mapGlobal.manoeOnMap(&curr, 3), mapGlobal.sizeOfTerr(&curr));lcd.refresh();}
        defChosen = conButton.read();
        

        if (defChosen & territories[curr]){
            lcd.clear();
            lcd.printString("NOT OPPONENT", 8, 2);
            lcd.printString("TERRITORY!", 13, 3);
            lcd.refresh();
            defChosen = 0;
            }
        else {
            bool yesBorder = checkBorders(curr, *attInd);
                if (yesBorder & defChosen){
                *defInd = curr; 
                }
                else if (!yesBorder & defChosen) {
                lcd.clear();
                lcd.printString("NO BORDERS!", 10, 3);
                lcd.refresh();
                defChosen = 0;
                }
            }
            ThisThread::sleep_for(500ms);
        }

        printf("%s%d\n", abbs[curr].c_str(), solNumTerr[curr]);
        ThisThread::sleep_for(500ms);

        if (solNumTerr[*defInd] >= 5) {defNo = 2;}
        if (solNumTerr[*defInd] < 5) {defNo = 1;}
        printf("Defence Index is %d, soldier number is %d, so defNo: %d", *defInd, solNumTerr[*defInd], defNo);
        lcd.clear();
        lcd.printString(abbs[*attInd].append(to_string(solNumTerr[attFrom])).c_str(), 22, 0);
        lcd.printString("VS", 40, 2);
        lcd.printString(abbs[*defInd].append(to_string(solNumTerr[defAt])).c_str(), 22, 4); // temporarily for testing
        lcd.refresh();
        attFrom = *attInd;
        defAt = *defInd;
        ThisThread::sleep_for(10000ms);
    }



bool gamePlay::checkBorders(int target, int ref) {

int conv = 0;
    for (int i = 0; i < 5; i++){
        conv = (int)(borders[ref][i]) - 65;
        if (conv == target) return true;
    }
    return false;
}

bool gamePlay::isUserTerritory(int target) {
    return territories[target];
}

void gamePlay::diceThrow(N5110& screen, int diceVal, int diceNo, bool attDef) {
int xPoint = 0;
int yPoint = 0;

// attDef == true for Attack BUT attDef == false for Defense
if (diceNo == 1) {if(attDef){xPoint = 14; yPoint = 5;} if(!attDef) {xPoint = 56; yPoint = 5;}}
if (diceNo == 2) {if(attDef){xPoint = 14; yPoint = 18;} if(!attDef) {xPoint = 56; yPoint = 18;}}
if (diceNo == 3) {if(attDef){xPoint = 14; yPoint = 31;} if(!attDef) {xPoint = 56; yPoint = 18;}}

screen.drawSprite(xPoint, yPoint, 11, 11, (int*)diceFrame);
    switch(diceVal){
        case 1:
        screen.drawSprite(xPoint + 5, yPoint + 5, 1, 1, (int*)diceTOne);
        break;
        case 2:
        screen.drawSprite(xPoint + 3, yPoint + 3, 5, 5, (int*)diceTTwo);
        break;
        case 3:
        screen.drawSprite(xPoint + 3, yPoint + 3, 5, 5, (int*)diceTThree);
        break;
        case 4:
        screen.drawSprite(xPoint + 3, yPoint + 3, 5, 5, (int*)diceTFour);
        break;
        case 5:
        screen.drawSprite(xPoint + 3, yPoint + 3, 5, 5, (int*)diceTFive);
        break;
        case 6:
        screen.drawSprite(xPoint + 3, yPoint + 3, 5, 5, (int*)diceTSix);
    }
}

void gamePlay::diceThrow(N5110& screen, int diceNo, bool attDef) {
int xPoint = 0;
int yPoint = 0;
int diceVal = 0;
int saveInd = 0; // saving Index

// attDef == true for Attack BUT attDef == false for Defense

if (diceNo == 1) {if(attDef){xPoint = 14; yPoint = 5;} if(!attDef) {xPoint = 56; yPoint = 5;}}
if (diceNo == 2) {if(attDef){xPoint = 14; yPoint = 18;} if(!attDef) {xPoint = 56; yPoint = 18;}}
if (diceNo == 3) {if(attDef){xPoint = 14; yPoint = 31;} if(!attDef) {xPoint = 56; yPoint = 18;}}


    // Seed the random number generator with a unique value
    int lowerBound = 1;
    int upperBound = 6;

    // Seed the random number generator with a random device
    std::random_device rd;
    std::mt19937 gen(rd());

    // Define the distribution for integers in the specified range
    std::uniform_int_distribution<int> distribution(lowerBound, upperBound);
    diceVal = distribution(gen);

    
// saving the random numbers
if (attDef) {attDice[diceNo-1] = diceVal;}
if (!attDef) {defDice[diceNo-1] = diceVal;} 

screen.drawSprite(xPoint, yPoint, 11, 11, (int*)diceFrame);
    switch(diceVal){
        case 1:
        screen.drawSprite(xPoint + 5, yPoint + 5, 1, 1, (int*)diceTOne);
        break;
        case 2:
        screen.drawSprite(xPoint + 3, yPoint + 3, 5, 5, (int*)diceTTwo);
        break;
        case 3:
        screen.drawSprite(xPoint + 3, yPoint + 3, 5, 5, (int*)diceTThree);
        break;
        case 4:
        screen.drawSprite(xPoint + 3, yPoint + 3, 5, 5, (int*)diceTFour);
        break;
        case 5:
        screen.drawSprite(xPoint + 3, yPoint + 3, 5, 5, (int*)diceTFive);
        break;
        case 6:
        screen.drawSprite(xPoint + 3, yPoint + 3, 5, 5, (int*)diceTSix);
    }
}

std::string gamePlay::solNumtoString (int num) {
// The function of this method is to convert soldier numbers into a string, otherwise they cannot be displayed on LCD

    std::string eq = ""; // The result
    
    // This function can only convert up to 99. It is assumed that number of soldiers during the game will not reach
    // 3 digits.

    std::string numsInString [10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    printf("appended:");
    eq.append(numsInString[num/10]);
    printf("%s", eq.c_str());
    eq.append(numsInString[num%10]);
    printf("%s", eq.c_str());
    return eq;

}

void gamePlay::sortArray(bool attORdef){
//attOrdef == true if attack and == false if defense array is being sorted
int temp = 0;

if (attORdef){
    for (int i = 0; i < 2; i++){
    for (int j = 1; j < 3; j++) {
        if (attDice[j] < attDice[j-1]){
            temp = attDice[j];
            attDice[j] = attDice[j-1];
            attDice[j-1] = temp;
        }
    }
    }
}

if (!attORdef){
    for (int i = 1; i < 2; i++) {
        if (defDice[i] < defDice[i-1]){
            temp = defDice[i];
            defDice[i] = defDice[i-1];
            defDice[i-1] = temp;
        }
    }
}

}

void gamePlay::calcOutcome(int defNo){
    numberLost[0] = 0;
    numberLost[1] = 0;
    while(defNo > 0){
        if(attDice[maxAtt - 1] > defDice[maxDef - 1]) numberLost[1]++;
        if(attDice[maxAtt - 1] <= defDice[maxDef - 1]) numberLost[0]++;
        defNo--;
    }
}

void gamePlay::test(N5110& screen, int attNo, int defNo){
    
    screen.clear();

    for (int i = 1; i <= attNo; i++){
        diceThrow(screen, i, true);
        screen.refresh();
    }
    sortArray(true);
    screen.printString("VS", 35, 2);
    for (int i = 1; i <= defNo; i++){
        diceThrow(screen, i, false);
        screen.refresh();
    }
    sortArray(false);
    ThisThread::sleep_for(3000ms);

    calcOutcome(defNo);
    printf("Attack Dices: %d - %d - %d || Defence Dices: %d - %d \n", attDice[0], attDice[1], attDice[2], defDice[0], defDice[1]);
    printf("Attack Lost: %d -- Defence Lost: %d \n", numberLost[0], numberLost[1]);
    resetArrays();
    resetArrays();

}

void gamePlay::resetArrays(){
    for (int i = 0; i <= 1; i++) {
        attDice[i] = 0;
        defDice[i] = 0;
    }
    attDice[2] = 0;
}

void gamePlay::initSolArrays() {
    for(int i = 0; i < 12; i++){
        if(territories[i]) userTerrSort[i][0] = solNumTerr[i];
        else pcTerrSort[i][0] = solNumTerr[i];
    }
}

void gamePlay::sortUserSols() { 
int tempSol = 0;
int tempIndex = 0;
bool isSwap = false; // to optimize code
for (int i = 0; i <= 12; i++){
    for (int j = 1; j < 12; j++) {
        if (userTerrSort[j][0] < userTerrSort[j-1][0]){
            tempSol = userTerrSort[j][0];
            userTerrSort[j][0] = userTerrSort[j-1][0];
            userTerrSort[j-1][0] = tempSol;
            tempIndex = userTerrSort[j][1];
            userTerrSort[j][1] = userTerrSort[j-1][1];
            userTerrSort[j-1][1] = tempIndex;
            isSwap = true;
        }
    }

    if(!isSwap) break;
} 
}

void gamePlay::sortPCSols() { 
int tempSol = 0;
int tempIndex = 0;
bool isSwap = false; // to optimize code
for (int i = 0; i <= 12; i++){
    for (int j = 1; j < 12; j++) {
        if (pcTerrSort[j][0] < pcTerrSort[j-1][0]){
            tempSol = pcTerrSort[j][0];
            pcTerrSort[j][0] = pcTerrSort[j-1][0];
            pcTerrSort[j-1][0] = tempSol;
            tempIndex = pcTerrSort[j][1];
            pcTerrSort[j][1] = pcTerrSort[j-1][1];
            pcTerrSort[j-1][1] = tempIndex;
            isSwap = true;
        }
    }

    if(!isSwap) break;
} 
}

float gamePlay::reLUWithSatur (float passVal, int lowL, int upL, int multip, bool rev){
    // this function is a modified Rectified Linear Unit Function. Inputs specify the lower limit, which if passVal is lower
    // is saturated at 0. If it is greater than the upper limit, 1 is returned. Otherwise, the ratio between them is calculated.
    
    //rev is true if the scale wants to be reversed
    float difference = upL - lowL;
    float sum = upL + lowL;
    int rectify = 1;
    if (rev) rectify = -1;
    /*if (passVal < lowL) return -1 * multip;       DISCUSS IN JOURNAL. NEGATIVE VALUES REDUCE THE ACCURACY
    else if (passVal > upL) return multip;          WHEN THERE IS A CLASH IN EQUAL POLARITY!!
    else return ((1.0/difference) * (2*passVal - (sum))) * multip;*/
    if (passVal < lowL) return 1;
    else if (passVal > upL) return 10;
    else return (rectify * (((9.0/(upL - lowL)) * passVal) - (4.5 * (((float)upL + lowL)/(upL - lowL))))) + 5.5;
}

float gamePlay::reLUWithSaturNeg (float passVal, int lowL, int upL, int multip){
     float difference = upL - lowL;
    float sum = upL + lowL;
    if (passVal < lowL) return -1 * multip;
    else if (passVal > upL) return multip;          
    else return ((1.0/difference) * (2*passVal - (sum))) * multip;
}


void gamePlay::diffCalc() {

    // Soldier Difference Max and Min Finder
    int conv = 0;
    int minDiff = 200; // Non-zero minimum value in the array || 200 is a limit assuming it 
    int maxDiff = 0; // Maximum value in the array
    int diff = 0; // Dummy variable that changes internally in the loop
    for (int i = 0; i < 12; i++){
        for (int j = 0; j < 6; j++){
            conv = (int)(borders[i][j]) - 65;
            if(!territories[i] && territories[conv]){
            diff = solNumTerr[i] - solNumTerr[conv];
            if(diff > maxDiff) maxDiff = diff;
            if(diff < minDiff && diff > 0) minDiff = diff;
            }
            }
        }
    // -------
    // Soldier Difference Calculator
    for (int i = 0; i < 12; i++){
        for (int j = 0; j < 6; j++){
            conv = (int)(borders[i][j]) - 65;
            if(!territories[i] && territories[conv]){
            favorite[i][j] = reLUWithSaturNeg((float)(solNumTerr[i] - solNumTerr[conv]), minDiff, maxDiff, 10);
            }
            else {
            favorite[i][j] = 0;
            }
        }
    }
    // -------

    for (int i = 0; i < 12; i++){
        for (int j = 0; j < 6; j++){
        if (j == 0) printf("[%f, ", favorite[i][j]);
        else if (j == 5) printf("%f] \n", favorite[i][j]);
        else printf("%f, ", favorite[i][j]);
        }
    } printf("Difference ^ ---- \n\n"); //<-- Used for debug too
}

void gamePlay::minMaxMultiply () {

    int maxSolIndexPC = pcTerrSort[11][1]; // Highest number of soldiers of pc's index
    int minSolIndexPC;
    int maxSolIndexUser = userTerrSort[11][1]; // Highest number of soldiers of pc's index
    int minSolIndexUser;

    // Finder for PC's indexes
    for (int i = 0; i < 12; i++){
        if (pcTerrSort[i][0] > 0) {minSolIndexPC = pcTerrSort[i][1]; break;}
        // if the soldier number at index i is 0, this means that territory is not occupied by the PC
        // so that is not the territory that has the least amount of soldiers. If however it is greater than
        // 0, it means it can be counted as the territory that has the least.
    }
    /*printf("Minimum index is: %d || The soldier number is: %d \n", minSolIndexPC, solNumTerr[minSolIndexPC]);
    for (int i = 0; i < 12; i++){
        printf("[%d, %d] . ", pcTerrSort[i][0], pcTerrSort[i][1]);
    }*/ //<- Used to debug
    //------
    // Finder for User's indexes
    for (int i = 0; i < 12; i++){
        if (userTerrSort[i][0] > 0) {minSolIndexUser = userTerrSort[i][1]; break;}
    }
    /*
    printf("Minimum index is: %d || The soldier number is: %d \n", minSolIndexUser, solNumTerr[minSolIndexUser]);
    for (int i = 0; i < 12; i++){
        printf("[%d, %d] . ", userTerrSort[i][0], userTerrSort[i][1]);
    }*/ //<- Used to debug
    //------
    
    // Multiplying by highest number of soldiers of AI
    //printf("Min index: %d || Max index: %d \n", minSolIndexPC, maxSolIndexPC); // DEB DEL
    float xMulti;
    for (int k = 11; k >= 0; k--){
        if (pcTerrSort[k][0] == 0) {
        break;
        }
        xMulti = reLUWithSatur((float)pcTerrSort[k][0], solNumTerr[minSolIndexPC], solNumTerr[maxSolIndexPC], 10, false);
        //printf("xMulti is %f at k: %d \n", xMulti, k); //DEBUG DELETE (DEB DEL)
        for (int m = 0; m < 6; m++){
        //printf("Multiplying territory index %d \n", pcTerrSort[k][1]); // DEB DEL
            favorite[pcTerrSort[k][1]][m] *= xMulti;
        }
    }

    // Orientate RELU values
    float inRELU = 0;
    for (int k = 11; k >= 0; k--){
        if (userTerrSort[k][0] == 0) {
        break;
        }
        inRELU = reLUWithSatur((float)userTerrSort[k][0], solNumTerr[minSolIndexUser], solNumTerr[maxSolIndexUser], 10, true);
        // DEB DEL printf("I'm placing inRELU: %f at userTerrSort[%d][1] \n", inRELU, k);
        reLUUser[userTerrSort[k][1]] = inRELU; 
    }



    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 6; j++) {
            favorite[i][j] *= reLUUser[(((char)borders[i][j]) - 65)];
        }
    }

/*    for (int i = 0; i < 12; i++){
        for (int j = 0; j < 6; j++){
        if(territories[i]){
        favorite[i][j] = reLUWithSatur((float)pcTerrSort[i][0], solNumTerr[minSolIndexPC], solNumTerr[maxSolIndexPC], 10) * favorite[i][j];
        printf("%f RELU1", favorite[i][j]);}
        else{
        favorite[i][j] = (-1 * reLUWithSatur((float)userTerrSort[i][0], solNumTerr[minSolIndexUser], solNumTerr[maxSolIndexUser], 10)) * favorite[i][j];
        printf("%f RELU2", favorite[i][j]);
        }
        }
    }
*/

}

void gamePlay::resetFav() { // This function is to reset the calculated matrix by the PC
    for (int i = 0; i < 12; i++){
        for (int j = 0; j < 6; j++){
        favorite[i][j] = 0;
        }
    }
}

void gamePlay::pcDecide(N5110& lcd, mapDisplay map){
    resetFav();
    initSolArrays();
    sortUserSols();
    sortPCSols();
    diffCalc();
    minMaxMultiply();
    attFrom = 0;
    defAt = 0;
    int max = 0;
    
    lcd.clear(); 
    lcd.printString("PC DECIDING!", 10, 2);
    lcd.refresh();
    ThisThread::sleep_for(1s);
    lcd.printString(".", 40, 3);
    lcd.refresh();
    ThisThread::sleep_for(1s);
    lcd.printString(".", 45, 3);
    lcd.refresh();
    ThisThread::sleep_for(1s);
    lcd.printString(".", 50, 3);
    lcd.refresh();

    for (int i = 0; i < 12; i++){
        for (int j = 0; j < 6; j++){
        if (j == 0) printf("[%f, ", favorite[i][j]);
        else if (j == 5) printf("%f] \n", favorite[i][j]);
        else printf("%f, ", favorite[i][j]);
        }
    }
    
    for (int i = 0; i < 12; i++){
        for (int j = 0; j < 6; j++){
            if (favorite[i][j] > max) {
                max = favorite[i][j];
                attFrom = i;        // PC is deciding, it will decide and show the territories on the map 
                                    // later attack and display the country codes, and will ask the user defending numbers!!
                defAt = (int)borders[i][j] - 65;
            }
        }
    }

    lcd.clear();
    lcd.draw((int*)nAmerica, 429);
    lcd.draw(map.addressRet(attFrom), map.sizeOfTerr(&attFrom));
    lcd.draw(map.addressRet(defAt), map.sizeOfTerr(&defAt));
    lcd.refresh();

    ThisThread::sleep_for(2s);

    lcd.clear();
    lcd.printString(abbs[attFrom].append(to_string(solNumTerr[attFrom])).c_str(), 22, 0);
    lcd.printString("VS", 40, 2);
    lcd.printString(abbs[defAt].append(to_string(solNumTerr[defAt])).c_str(), 22, 4);
    lcd.refresh();


}

void gamePlay::testArray () {
    resetFav();
    initSolArrays();
    sortUserSols();
    sortPCSols();
    diffCalc();
    minMaxMultiply();
    //use in Journal Importante!! The printing to show it is working properly
    for (int i = 0; i < 12; i++){
        for (int j = 0; j < 6; j++){
        if (j == 0) printf("[%f, ", favorite[i][j]);
        else if (j == 5) printf("%f] \n", favorite[i][j]);
        else printf("%f, ", favorite[i][j]);
        }
    }

   /* DEB DEL for (int i = 0; i < 12; i++){
        if (i == 0) printf("[%f, ", reLUUser[i]);
        else if (i == 5) printf("%f] \n", reLUUser[i]);
        else printf("%f, ", reLUUser[i]);
    } */
}

