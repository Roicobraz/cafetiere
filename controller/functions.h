#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

typedef struct Cup Cup;
struct Cup
{
    int empty;
    int isUnderCafetiere;
    int QUANTITY;
};
void initCup(Cup *cup, int empty, int isUnderCafetiere, int QUANTITY);

typedef struct Water Water;
struct Water
{
    unsigned int quantity;
    unsigned int QUANTITY_MAX;
    int temperature;
};
void initWater(Water *water, int quantity, int QUANTITY_MAX, int temperature);

typedef struct Cafetiere Cafetiere;
struct Cafetiere
{
    Water water;
    int on;
    int numberCup;
    int numberCofeeDose;
    int hasLimestone;
};

void initCafetiere(Cafetiere *cafetiere, Water water, int on, int numberCup, int numberCofeeDose, int hasLimestone);

void turnOn(Cafetiere *cafetiere, int quantityCup);
void turnOff(Cafetiere *cafetiere);

void takeCup(Cup *cup);
void putCup(Cup *cup);

void waterHeating(Cafetiere *cafetiere);
void addWater(Cafetiere *cafetiere, int quantity);

void selectDose(Cafetiere *cafetiere, int dose);
void cofeeFlow(Cafetiere *cafetiere, Cup *cup, int const QUANTITY_CUP);


void addLog(char string[]);

void initDatas();
int getWater();
int setWater();

int getCup();
