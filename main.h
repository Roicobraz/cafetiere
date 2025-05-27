#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct Cup Cup;
struct Cup
{
    int empty;
    int isUnderCafetiere;
    int const QUANTITY;
};

typedef struct Water Water;
struct Water
{
    int quantity;
    int const QUANTITY_MAX;
    int temperature;
};

typedef struct Cafetiere Cafetiere;
struct Cafetiere
{
    Water water;
    int on;
    int numberCup;
    int numberCofeeDose;
    int hasLimestone;
};

void turnOn(Cafetiere *cafetiere, int quantityCup);
void turnOff(Cafetiere *cafetiere);

void takeCup(Cup *cup);
void putCup(Cup *cup);

void waterHeating(Cafetiere *cafetiere);
void addWater(Cafetiere *cafetiere);

void selectDose(Cafetiere *cafetiere);
void cofeeFlow(Cafetiere *cafetiere, Cup *cup, int const QUANTITY_CUP);

void possibleActions();