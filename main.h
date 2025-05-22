#include <stdio.h>
#include <unistd.h>

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

void turnOn(Cafetiere *cafetiere);
void waterHeating();

void putCup(Cup cup);
void addWater(Cafetiere *cafetiere, int waterDose);
int selectDose();
void cofeeFlow();

void takeCup(Cup cup);

void turnOff(Cafetiere *cafetiere);
