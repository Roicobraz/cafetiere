#include "functions.h"

void initCup(Cup *cup, int isempty, int isUnderCafetiere, int quantityCup)
{
    cup->empty = isempty;
    cup->isUnderCafetiere = isUnderCafetiere;
    cup->QUANTITY = quantityCup;
}

void initWater(Water *water, int quantity, int quantityMax, int temperature)
{
    water->quantity = quantity;
    water->QUANTITY_MAX = quantityMax;
    water->temperature = temperature;
}

void initCafetiere(Cafetiere *cafetiere, Water water, int on, int numberCup, int numberCofeeDose, int hasLimestone)
{
    cafetiere->water = water;
    cafetiere->on = on;
    cafetiere->numberCup = numberCup;
    cafetiere->numberCofeeDose = numberCofeeDose;
    cafetiere->hasLimestone = hasLimestone;
}

void putCup(Cup *cup)
{
    if(cup->isUnderCafetiere)
    {
        printf("La tasse est déjà dans la cafetière.\n");
    }
    else
    {
        cup->isUnderCafetiere = 1;
        printf("Vous avez mis la tasse dans la cafetière.\n");
    }
}

void takeCup(Cup *cup)
{
    if(cup->isUnderCafetiere)
    {
        cup->isUnderCafetiere = 0;
        printf("Vous avez pris la tasse.\n");
    }
    else
    {
        printf("Il n'y a pas de tasse dans la cafetière.\n");
    }
}

void turnOn(Cafetiere *cafetiere, int quantityCup)
{
    if(cafetiere->on)
    {
        printf("La cafetière est déjà allumée.\n");
    }
    else
    {
        cafetiere->on = 1;
        printf("La cafetière est allumée.\n");

        if(cafetiere->water.quantity >= quantityCup)
        {
            waterHeating(cafetiere);
        }
    }
}

void turnOff(Cafetiere *cafetiere)
{
    if(cafetiere->on)
    {
        cafetiere->on = 0;
        printf("La cafetière est éteinte.\n");
    }
    else
    {
        printf("La cafetière est déjà éteinte.\n");
    }
}

void waterHeating(Cafetiere *cafetiere)
{
    if(cafetiere->water.temperature == 100)
    {
        printf("L'eau est déjà chaude.\n");
    }
    else
    {
        printf("L'eau chauffe.\n");
        cafetiere->water.temperature = 100;
        printf("L'eau est chaude.\n");
    }
}

void addWater(Cafetiere *cafetiere, int quantity)
{
    if(quantity >= 2500)
    {
        cafetiere->water.quantity = 2500;
    }
    else
    {
        cafetiere->water.quantity += quantity;
    }
}

void selectDose(Cafetiere *cafetiere, int dose)
{
    cafetiere->numberCofeeDose = dose;
}

void cofeeFlow(Cafetiere *cafetiere, Cup *cup, int dose)
{
    if(cafetiere->water.temperature == 100)
    {
        selectDose(cafetiere, dose);

        cafetiere->water.quantity -= cafetiere->numberCofeeDose*cup->QUANTITY;
    }
}