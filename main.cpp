#include "mbed.h"
#include "N5110.h"
#include "Joystick.h"
#include "gamePlay.h"
#include "mapDisplay.h"
#include <cstdio>
//                 y     x
Joystick joystick(PC_3, PC_2);  //attach and create joystick object

//Pin assignment format:  lcd(IO, Ser_TX, Ser_RX, MOSI, SCLK, PWM)  
N5110 screen(PC_7, PA_9, PB_10, PB_5, PB_3, PA_10);


void printDice(int diceNo, int xPoint, int yPoint);

int main(){
    joystick.init();
    screen.init(LPH7366_1);        //initialise for LPH7366-1 LCD (Options are LPH7366_1 and LPH7366_6)
    screen.setContrast(1.0);      //set contrast to 100%
    screen.setBrightness(0.1);     //set brightness to 10% (utilises the PWM)
    int mvm = 0;
    int curr = 0;
    int att = 8;
    int def = 4;
    gamePlay game;
    mapDisplay map;
    int i = 1;

    while (1) {
        
        game.playRISK(screen, joystick);
        ThisThread::sleep_for(500ms);
        
    }
}
