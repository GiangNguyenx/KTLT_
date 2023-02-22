#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include "main.h"

void readFile(string fileName, int line1_param[], int line2_param[], string line3_param[]);
void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue);
void adventureToKoopa(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue);
void initArray(int knight_param[], int event_param[], string file_param[]);
void initKnight(int knight_param[], int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue);


void eventZero(int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue);
void eventOneToFive(int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue);
void eventSix(int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue);
void eventSeven(int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue);
void eventEleven(int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue);
void eventTwelve(int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue);
void eventThirteen(int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue);
void eventFifteen2Seventeen(int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue);
void eventNineteen(int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue);
void hpIs999(int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue);
void hpIsPrime(int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue);
void event99th(int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue);
void eventEighteen(int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue);

#endif // __KNIGHT_H__