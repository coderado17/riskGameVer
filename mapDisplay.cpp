#include "mbed.h"
#include "mapDisplay.h"
#include <string>


int norAmerica[429][2] = {
    {9,63},{9,64},{9,65},{9,66},{10,60},{10,61},{10,62},{10,67},{11,57},{11,58},{11,59},{11,60},{11,68},{12,53},{12,54},{12,55},{12,56},{12,57},{12,69},{12,70},{12,71},{12,72},{12,73},{12,74},{13,52},{13,74},{13,75},{14,50},{14,51},{14,75},{15,49},{15,50},{15,74},{16,49},{16,73},{16,74},{17,49},{17,50},{17,51},{17,52},{17,53},{17,54},{17,55},{17,73},{18,55},{18,56},{18,71},{18,72},{18,73},{19,39},{19,40},{19,56},{19,57},{19,70},{19,71},{19,73},{19,74},{20,39},{20,41},{20,58},{20,70},{20,74},{21,12},{21,13},{21,14},{21,39},{21,41},{21,55},{21,56},{21,57},{21,58},{21,59},{21,70},{21,74},{21,75},{22,9},{22,10},{22,11},{22,12},{22,15},{22,16},{22,17},{22,18},{22,24},{22,25},{22,26},{22,39},{22,41},{22,51},{22,52},{22,53},{22,54},{22,55},{22,56},{22,57},{22,59},{22,71},{22,76},{23,8},{23,18},{23,19},{23,20},{23,21},{23,22},{23,23},{23,26},{23,27},{23,28},{23,39},{23,42},{23,44},{23,45},{23,46},{23,47},{23,48},{23,49},{23,50},{23,53},{23,54},{23,57},{23,59},{23,60},{23,71},{23,76},{23,77},{23,78},{23,79},{23,80},{23,81},{24,8},{24,16},{24,29},{24,30},{24,31},{24,32},{24,34},{24,35},{24,36},{24,37},{24,38},{24,39},{24,42},{24,43},{24,44},{24,46},{24,52},{24,53},{24,57},{24,60},{24,68},{24,69},{24,70},{24,75},{24,76},{24,81},{25,8},{25,32},{25,33},{25,34},{25,46},{25,50},{25,51},{25,52},{25,57},{25,60},{25,67},{25,75},{25,81},{25,82},{26,3},{26,5},{26,8},{26,17},{26,45},{26,46},{26,48},{26,49},{26,50},{26,56},{26,57},{26,60},{26,66},{26,74},{26,81},{26,82},{27,1},{27,2},{27,3},{27,4},{27,5},{27,6},{27,7},{27,8},{27,42},{27,43},{27,44},{27,47},{27,48},{27,56},{27,60},{27,66},{27,74},{27,78},{27,79},{27,80},{27,81},{28,2},{28,4},{28,7},{28,42},{28,46},{28,47},{28,56},{28,60},{28,65},{28,66},{28,74},{28,75},{28,76},{28,77},{28,80},{29,7},{29,36},{29,41},{29,42},{29,45},{29,46},{29,48},{29,49},{29,50},{29,51},{29,55},{29,60},{29,61},{29,65},{29,79},{29,80},{30,8},{30,15},{30,16},{30,17},{30,18},{30,19},{30,24},{30,32},{30,41},{30,44},{30,47},{30,48},{30,52},{30,53},{30,55},{30,61},{30,64},{30,78},{30,80},{31,9},{31,14},{31,15},{31,19},{31,22},{31,34},{31,41},{31,42},{31,43},{31,44},{31,47},{31,53},{31,54},{31,55},{31,62},{31,63},{31,77},{31,81},{32,8},{32,13},{32,14},{32,19},{32,20},{32,21},{32,42},{32,43},{32,44},{32,47},{32,54},{32,55},{32,74},{32,75},{32,77},{32,80},{33,7},{33,11},{33,12},{33,13},{33,21},{33,22},{33,44},{33,47},{33,55},{33,73},{33,74},{33,76},{33,78},{33,80},{34,6},{34,9},{34,10},{34,11},{34,23},{34,24},{34,34},{34,44},{34,45},{34,47},{34,48},{34,56},{34,73},{34,76},{34,81},{35,6},{35,8},{35,9},{35,24},{35,25},{35,45},{35,46},{35,48},{35,57},{35,73},{35,74},{35,75},{35,78},{35,81},{35,83},{35,84},{36,6},{36,7},{36,8},{36,25},{36,26},{36,28},{36,46},{36,47},{36,48},{36,57},{36,58},{36,77},{36,80},{36,82},{36,83},{37,26},{37,37},{37,44},{37,46},{37,51},{37,52},{37,53},{37,54},{37,55},{37,58},{37,78},{37,79},{37,82},{38,26},{38,27},{38,42},{38,51},{38,55},{38,56},{38,57},{38,58},{38,81},{38,82},{39,27},{39,51},{39,52},{39,81},{40,27},{40,49},{40,52},{40,53},{40,79},{40,80},{40,81},{41,27},{41,51},{41,52},{41,78},{41,79},{42,27},{42,28},{42,49},{42,50},{42,78},{42,83},{42,84},{43,28},{43,49},{43,78},{43,79},{43,80},{43,81},{43,82},{43,83},{44,28},{44,29},{44,40},{44,49},{44,84},{45,29},{45,38},{45,48},{45,82},{45,83},{45,84},{46,29},{46,30},{46,46},{46,47},{46,79},{46,80},{46,81},{47,30},{47,39},{47,46},{47,79},{48,30},{48,46},{48,78}
};
char idx[12][4] = {{'A', 'A', 'B', 'A'}, {'B' ,'C' ,'I' ,'A'}, {'B' ,'E' ,'D' ,'C'}, {'B' ,'F' ,'H' ,'C'}, 
                   {'C' ,'E' ,'F' ,'E'}, {'D' ,'F' ,'F' ,'E'}, {'E' ,'G' ,'E' ,'E'}, {'I' ,'F' ,'H' ,'D'},
                   {'I' ,'H' ,'K' ,'B'}, {'K' ,'L' ,'J' ,'J'}, {'I' ,'J' ,'K' ,'I'}, {'J' ,'L' ,'L' ,'L'}};

int idxSize[12] = {125, 225, 80, 88, 147, 114, 0, 99, 312, 44, 42, 42};

int ALS [125][2] = {
    {21,12},{21,13},{21,14},{22,9},{22,10},{22,11},{22,12},{22,13},{22,14},{22,15},{22,16},{23,8},{23,9},{23,10},{23,11},{23,12},{23,13},{23,14},{23,15},{24,8},{24,9},{24,10},{24,11},{24,12},{24,13},{24,14},{24,15},{24,16},{25,8},{25,9},{25,10},{25,11},{25,12},{25,13},{25,14},{25,15},{25,16},{26,8},{26,9},{26,10},{26,11},{26,12},{26,13},{26,14},{26,15},{26,16},{26,17},{27,7},{27,8},{27,9},{27,10},{27,11},{27,12},{27,13},{27,14},{27,15},{27,16},{27,17},{28,6},{28,7},{28,8},{28,9},{28,10},{28,11},{28,12},{28,13},{28,14},{28,15},{28,16},{28,17},{28,18},{29,7},{29,8},{29,9},{29,10},{29,11},{29,12},{29,13},{29,14},{29,15},{29,16},{29,17},{29,18},{30,8},{30,9},{30,10},{30,11},{30,12},{30,13},{30,14},{30,15},{30,16},{30,17},{30,18},{31,9},{31,10},{31,11},{31,12},{31,13},{31,14},{31,15},{32,8},{32,9},{32,10},{32,11},{32,12},{32,13},{32,14},{33,7},{33,8},{33,9},{33,10},{33,11},{33,12},{33,13},{34,6},{34,7},{34,8},{34,9},{34,10},{34,11},{35,7},{35,8},{35,9},{36,8}
};
int ALB [80][2] = {
    {30,24},{30,25},{30,26},{30,27},{30,28},{30,29},{30,30},{30,31},{30,32},{31,23},{31,24},{31,25},{31,26},{31,27},{31,28},{31,29},{31,30},{31,31},{31,32},{31,33},{32,21},{32,22},{32,23},{32,24},{32,25},{32,26},{32,27},{32,28},{32,29},{32,30},{32,31},{32,32},{32,33},{32,34},{33,21},{33,22},{33,23},{33,24},{33,25},{33,26},{33,27},{33,28},{33,29},{33,30},{33,31},{33,32},{33,33},{33,34},{34,23},{34,24},{34,25},{34,26},{34,27},{34,28},{34,29},{34,30},{34,31},{34,32},{34,33},{34,34},{35,24},{35,25},{35,26},{35,27},{35,28},{35,29},{35,30},{35,31},{35,32},{35,33},{35,34},{36,25},{36,26},{36,27},{36,28},{36,29},{36,30},{36,31},{36,32},{36,33}
};
int EUS [114][2] = {
    {36,46},{36,47},{36,48},{37,44},{37,45},{37,46},{38,40},{38,41},{38,42},{38,43},{38,44},{38,45},{38,46},{38,47},{38,48},{39,39},{39,40},{39,41},{39,42},{39,43},{39,44},{39,45},{39,46},{39,47},{39,48},{39,51},{40,39},{40,40},{40,41},{40,42},{40,43},{40,44},{40,45},{40,46},{40,47},{40,48},{40,49},{41,39},{41,40},{41,41},{41,42},{41,43},{41,44},{41,45},{41,46},{41,47},{41,48},{41,49},{41,51},{42,40},{42,41},{42,42},{42,43},{42,44},{42,45},{42,46},{42,47},{42,48},{42,49},{42,50},{43,40},{43,41},{43,42},{43,43},{43,44},{43,45},{43,46},{43,47},{43,48},{43,49},{44,40},{44,41},{44,42},{44,43},{44,44},{44,45},{44,46},{44,47},{44,48},{44,49},{45,38},{45,39},{45,40},{45,41},{45,42},{45,43},{45,44},{45,45},{45,46},{45,47},{45,48},{46,39},{46,40},{46,41},{46,42},{46,43},{46,44},{46,45},{46,46},{46,47},{47,40},{47,41},{47,42},{47,43},{47,44},{47,45},{47,46},{48,40},{48,41},{48,42},{48,43},{48,44},{48,45},{48,46}
};
int GRB[44][2] = {
    {28,80},{29,79},{29,80},{30,78},{30,79},{30,80},{31,77},{31,78},{31,79},{31,80},{31,81},{32,74},{32,75},{32,77},{32,78},{32,79},{32,80},{33,73},{33,74},{33,75},{33,76},{33,78},{33,79},{33,80},{34,73},{34,74},{34,75},{34,76},{34,79},{34,80},{34,81},{35,73},{35,74},{35,75},{35,78},{35,79},{35,80},{35,81},{36,77},{36,78},{36,79},{36,80},{37,78},{37,79}
};
int GRL[312][2] = {
    {9,63},{9,64},{9,65},{9,66},{10,60},{10,61},{10,62},{10,63},{10,64},{10,65},{10,66},{10,67},{11,57},{11,58},{11,59},{11,60},{11,61},{11,62},{11,63},{11,64},{11,65},{11,66},{11,67},{11,68},{12,53},{12,54},{12,55},{12,56},{12,57},{12,58},{12,59},{12,60},{12,61},{12,62},{12,63},{12,64},{12,65},{12,66},{12,67},{12,68},{12,69},{12,70},{12,71},{12,72},{12,73},{12,74},{13,52},{13,53},{13,54},{13,55},{13,56},{13,57},{13,58},{13,59},{13,60},{13,61},{13,62},{13,63},{13,64},{13,65},{13,66},{13,67},{13,68},{13,69},{13,70},{13,71},{13,72},{13,73},{13,74},{13,75},{14,50},{14,51},{14,52},{14,53},{14,54},{14,55},{14,56},{14,57},{14,58},{14,59},{14,60},{14,61},{14,62},{14,63},{14,64},{14,65},{14,66},{14,67},{14,68},{14,69},{14,70},{14,71},{14,72},{14,73},{14,74},{14,75},{15,49},{15,50},{15,51},{15,52},{15,53},{15,54},{15,55},{15,56},{15,57},{15,58},{15,59},{15,60},{15,61},{15,62},{15,63},{15,64},{15,65},{15,66},{15,67},{15,68},{15,69},{15,70},{15,71},{15,72},{15,73},{15,74},{16,49},{16,50},{16,51},{16,52},{16,53},{16,54},{16,55},{16,56},{16,57},{16,58},{16,59},{16,60},{16,61},{16,62},{16,63},{16,64},{16,65},{16,66},{16,67},{16,68},{16,69},{16,70},{16,71},{16,72},{16,73},{16,74},{17,49},{17,50},{17,51},{17,52},{17,53},{17,54},{17,55},{17,56},{17,57},{17,58},{17,59},{17,60},{17,61},{17,62},{17,63},{17,64},{17,65},{17,66},{17,67},{17,68},{17,69},{17,70},{17,71},{17,72},{17,73},{18,55},{18,56},{18,57},{18,58},{18,59},{18,60},{18,61},{18,62},{18,63},{18,64},{18,65},{18,66},{18,67},{18,68},{18,69},{18,70},{18,71},{18,72},{19,56},{19,57},{19,58},{19,59},{19,60},{19,61},{19,62},{19,63},{19,64},{19,65},{19,66},{19,67},{19,68},{19,69},{19,70},{19,71},{20,58},{20,59},{20,60},{20,61},{20,62},{20,63},{20,64},{20,65},{20,66},{20,67},{20,68},{20,69},{20,70},{21,58},{21,59},{21,60},{21,61},{21,62},{21,63},{21,64},{21,65},{21,66},{21,67},{21,68},{21,69},{21,70},{22,59},{22,60},{22,61},{22,62},{22,63},{22,64},{22,65},{22,66},{22,67},{22,68},{22,69},{22,70},{22,71},{23,59},{23,60},{23,61},{23,62},{23,63},{23,64},{23,65},{23,66},{23,67},{23,68},{23,69},{23,70},{23,71},{24,60},{24,61},{24,62},{24,63},{24,64},{24,65},{24,66},{24,67},{24,68},{24,69},{24,70},{25,60},{25,61},{25,62},{25,63},{25,64},{25,65},{25,66},{25,67},{26,60},{26,61},{26,62},{26,63},{26,64},{26,65},{26,66},{27,60},{27,61},{27,62},{27,63},{27,64},{27,65},{27,66},{28,60},{28,61},{28,62},{28,63},{28,64},{28,65},{28,66},{29,48},{29,60},{29,61},{29,62},{29,63},{29,64},{29,65},{30,61},{30,62},{30,63},{30,64},{31,62},{31,63}
};
int ICL[42][2] = {
    {23,77},{23,78},{23,79},{23,80},{23,81},{24,75},{24,76},{24,77},{24,78},{24,79},{24,80},{24,81},{25,74},{25,75},{25,76},{25,77},{25,78},{25,79},{25,80},{25,81},{25,82},{26,74},{26,75},{26,76},{26,77},{26,78},{26,79},{26,80},{26,81},{26,82},{27,74},{27,75},{27,76},{27,77},{27,78},{27,79},{27,80},{27,81},{28,74},{28,75},{28,76},{28,77}
};
int NWT[225][2] = {
    {19,39},{19,40},{20,39},{20,40},{20,41},{21,39},{21,40},{21,41},{22,16},{22,17},{22,18},{22,24},{22,25},{22,26},{22,39},{22,40},{22,41},{23,16},{23,17},{23,18},{23,19},{23,20},{23,21},{23,22},{23,23},{23,24},{23,25},{23,26},{23,27},{23,28},{23,39},{23,40},{23,41},{23,42},{23,44},{23,45},{23,46},{24,16},{24,17},{24,18},{24,19},{24,20},{24,21},{24,22},{24,23},{24,24},{24,25},{24,26},{24,27},{24,28},{24,29},{24,30},{24,31},{24,32},{24,34},{24,35},{24,36},{24,37},{24,38},{24,39},{24,40},{24,41},{24,42},{24,43},{24,44},{24,45},{24,46},{25,16},{25,17},{25,18},{25,19},{25,20},{25,21},{25,22},{25,23},{25,24},{25,25},{25,26},{25,27},{25,28},{25,29},{25,30},{25,31},{25,32},{25,33},{25,34},{25,35},{25,36},{25,37},{25,38},{25,39},{25,40},{25,41},{25,42},{25,43},{25,44},{25,45},{25,46},{26,17},{26,18},{26,19},{26,20},{26,21},{26,22},{26,23},{26,24},{26,25},{26,26},{26,27},{26,28},{26,29},{26,30},{26,31},{26,32},{26,33},{26,34},{26,35},{26,36},{26,37},{26,38},{26,39},{26,40},{26,41},{26,42},{26,43},{26,44},{26,45},{26,46},{27,18},{27,19},{27,20},{27,21},{27,22},{27,23},{27,24},{27,25},{27,26},{27,27},{27,28},{27,29},{27,30},{27,31},{27,32},{27,33},{27,34},{27,35},{27,36},{27,37},{27,38},{27,39},{27,40},{27,41},{27,42},{27,43},{27,44},{28,18},{28,19},{28,20},{28,21},{28,22},{28,23},{28,24},{28,25},{28,26},{28,27},{28,28},{28,29},{28,30},{28,31},{28,32},{28,33},{28,34},{28,35},{28,36},{28,37},{28,38},{28,39},{28,40},{28,41},{28,42},{28,46},{29,20},{29,21},{29,22},{29,23},{29,24},{29,25},{29,26},{29,27},{29,28},{29,29},{29,30},{29,31},{29,32},{29,33},{29,34},{29,35},{29,36},{29,37},{29,38},{29,39},{29,40},{29,41},{29,42},{29,45},{29,46},{30,16},{30,17},{30,18},{30,19},{30,22},{30,23},{30,24},{30,25},{30,26},{30,27},{30,28},{30,29},{30,30},{30,31},{30,32},{30,33},{30,34},{30,41},{30,44}
};
int ONT[88][2] = {
    {29,36},{29,37},{29,38},{29,39},{29,40},{29,41},{29,42},{30,41},{30,44},{31,34},{31,35},{31,36},{31,37},{31,38},{31,39},{31,40},{31,41},{31,42},{31,43},{31,44},{32,34},{32,35},{32,36},{32,37},{32,38},{32,39},{32,40},{32,41},{32,42},{32,43},{32,44},{33,34},{33,35},{33,36},{33,37},{33,38},{33,39},{33,40},{33,41},{33,42},{33,43},{33,44},{34,34},{34,35},{34,36},{34,37},{34,38},{34,39},{34,40},{34,41},{34,42},{34,43},{34,44},{35,34},{35,35},{35,36},{35,37},{35,38},{35,39},{35,40},{35,41},{35,42},{35,43},{35,44},{36,34},{36,35},{36,36},{36,37},{36,38},{36,39},{36,40},{36,41},{36,42},{36,43},{36,44},{37,36},{37,37},{37,38},{37,39},{37,40},{37,41},{37,42},{37,43},{37,44},{38,39},{38,40},{38,41},{38,42}
};
int QBC[99][2] = {
    {29,48},{29,49},{29,50},{29,51},{30,47},{30,48},{30,49},{30,50},{30,51},{30,52},{30,53},{31,47},{31,48},{31,49},{31,50},{31,51},{31,52},{31,53},{31,54},{31,55},{32,47},{32,48},{32,49},{32,50},{32,51},{32,52},{32,53},{32,54},{32,55},{33,47},{33,48},{33,49},{33,50},{33,51},{33,52},{33,53},{33,54},{33,55},{34,47},{34,48},{34,49},{34,50},{34,51},{34,52},{34,53},{34,54},{34,55},{34,56},{35,48},{35,49},{35,50},{35,51},{35,52},{35,53},{35,54},{35,55},{35,56},{35,57},{36,48},{36,49},{36,50},{36,51},{36,52},{36,53},{36,54},{36,55},{36,56},{36,57},{36,58},{37,48},{37,49},{37,50},{37,51},{37,52},{37,53},{37,54},{37,55},{37,56},{37,57},{37,58},{38,48},{38,49},{38,50},{38,51},{38,55},{38,56},{38,57},{38,58},{39,49},{39,50},{39,51},{39,52},{40,49},{40,50},{40,51},{40,52},{40,53},{41,51},{41,52}
};
int WUS[147][2] = {
    {36,28},{36,29},{36,30},{36,31},{36,32},{36,33},{36,34},{37,27},{37,28},{37,29},{37,30},{37,31},{37,32},{37,33},{37,34},{37,35},{37,36},{37,37},{38,27},{38,28},{38,29},{38,30},{38,31},{38,32},{38,33},{38,34},{38,35},{38,36},{38,37},{38,38},{38,39},{39,27},{39,28},{39,29},{39,30},{39,31},{39,32},{39,33},{39,34},{39,35},{39,36},{39,37},{39,38},{39,39},{40,27},{40,28},{40,29},{40,30},{40,31},{40,32},{40,33},{40,34},{40,35},{40,36},{40,37},{40,38},{40,39},{41,27},{41,28},{41,29},{41,30},{41,31},{41,32},{41,33},{41,34},{41,35},{41,36},{41,37},{41,38},{41,39},{42,27},{42,28},{42,29},{42,30},{42,31},{42,32},{42,33},{42,34},{42,35},{42,36},{42,37},{42,38},{42,39},{43,28},{43,29},{43,30},{43,31},{43,32},{43,33},{43,34},{43,35},{43,36},{43,37},{43,38},{43,39},{44,28},{44,29},{44,30},{44,31},{44,32},{44,33},{44,34},{44,35},{44,36},{44,37},{44,38},{44,39},{45,29},{45,30},{45,31},{45,32},{45,33},{45,34},{45,35},{45,36},{45,37},{45,38},{46,29},{46,30},{46,31},{46,32},{46,33},{46,34},{46,35},{46,36},{46,37},{46,38},{47,30},{47,31},{47,32},{47,33},{47,34},{47,35},{47,36},{47,37},{47,38},{47,39},{48,30},{48,31},{48,32},{48,33},{48,34},{48,35},{48,36},{48,37},{48,38},{48,39}
};
int WEU[42][2] = {
    {35,83},{35,84},{36,82},{36,83},{36,84},{37,82},{37,83},{37,84},{38,81},{38,82},{38,83},{38,84},{39,81},{39,82},{39,83},{39,84},{40,79},{40,80},{40,81},{40,82},{40,83},{40,84},{41,78},{41,79},{41,80},{41,81},{41,82},{41,83},{41,84},{42,78},{42,79},{42,80},{42,81},{42,82},{42,83},{42,84},{43,78},{43,79},{43,80},{43,81},{43,82},{43,83}
};
mapDisplay::mapDisplay(){};

int* mapDisplay::addressRet(int countryIndex){
    switch(countryIndex){
        case 0:
            ThisThread::sleep_for(20ms);
            return (int*)ALS;
        case 1:
            ThisThread::sleep_for(20ms);
            return (int*)NWT;
        case 2:
            ThisThread::sleep_for(20ms);
            return (int*)ALB;
        case 3:
            ThisThread::sleep_for(20ms);
            return (int*)ONT;
        case 4:
            ThisThread::sleep_for(20ms);
            return (int*)WUS;
        case 5:
            ThisThread::sleep_for(20ms);
            return (int*)EUS;
        case 6:
            ThisThread::sleep_for(20ms);
            return (int*)ONT;
        case 7:
            ThisThread::sleep_for(20ms);
            return (int*)QBC;
        case 8:
            ThisThread::sleep_for(20ms);
            return (int*)GRL;
        case 9:
            ThisThread::sleep_for(20ms);
            return (int*)GRB;
        case 10:
            ThisThread::sleep_for(20ms);
            return (int*)ICL;
        case 11:
            ThisThread::sleep_for(20ms);
            return (int*)WEU;
    }
    return nullptr;
}

int* mapDisplay::manoeOnMap (int* curr, int mov) {
    int countryIndex = *curr;
    int cToBeDrawn = (int)(idx[countryIndex][mov])-65;
    *curr = cToBeDrawn;
    int* eq = addressRet(cToBeDrawn);
    ThisThread::sleep_for(20ms);
    return eq;

}

int mapDisplay::sizeOfTerr (int* curr) {
    int countryIndex = *curr;
    return *(idxSize + countryIndex);

}
