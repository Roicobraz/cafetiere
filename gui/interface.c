#include "../controller/functions.c"
#include "interface.h"

void turnOnOff(Cafetiere *cafetiere, int quantityCup, HWND btnOnOff, char btnOnOffText[32])
{
    if(cafetiere->on)
    {
        turnOff(cafetiere);
        strcpy(btnOnOffText, "Allumer la cafetière");
    }
    else
    {
        turnOn(cafetiere, QUANTITY_CUP);
        strcpy(btnOnOffText, "Éteindre la cafetière");
    }
    SetWindowText(btnOnOff, btnOnOffText);
}

void putTakeCup(Cup *cup, HWND btnputTake, char btnputTakeText[])
{
    if(cup->isUnderCafetiere)
    {
        takeCup(cup);
        strcpy(btnputTakeText, "Mettre la tasse");
    }
    else
    {
        putCup(cup);
        strcpy(btnputTakeText, "Prendre la tasse");
    }

    SetWindowText(btnputTake, btnputTakeText);
}

