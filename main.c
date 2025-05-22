#include "main.h"

int main(int argc, char const *argv[])
{
    // default datas
    Cup cup = {1, 0, 250};
    Water water = {0, 14};
    Cafetiere cafetiere = {water, 0, 0, 0, 0}; 

    // Actions
    // putCup(cup);
    // takeCup(cup);
    addWater(&cafetiere, 250);
    // int dose = selectDose();
    turnOn(&cafetiere);
    // turnOff(&cafetiere);

    return 0;
}



void putCup(Cup cup)
{
    cup.isUnderCafetiere = 1;
    printf("Vous avez mis la tasse dans la cafetière.\n");
}

void takeCup(Cup cup)
{
    cup.isUnderCafetiere = 0;
    printf("Vous avez pris la tasse.\n");
}

void turnOn(Cafetiere *cafetiere)
{
    cafetiere->on = 1;
    printf("La cafetière est allumée.\n");

    if(cafetiere->water.quantity >= 250)
    {
        waterHeating();
    }
    else
    {
        printf("Veuillez ajouté de l'eau.\n");
    }
}

void turnOff(Cafetiere *cafetiere)
{
    cafetiere->on = 0;
    printf("La cafetière est éteinte.\n");
}

void waterHeating()
{
    printf("L'eau chauffe.\n");
    sleep(10);
    printf("L'eau est chaude.\n");
}

void addWater(Cafetiere *cafetiere, int waterDose)
{
    printf("Vous rajoutez %dml d'eau\n", waterDose);
    cafetiere->water.quantity += waterDose;
}

int selectDose()
{
    int dose;
    printf("Combien de dose voulez-vous? 1 ou 2?\n");
    scanf("%d", &dose);
    while(dose != 1 && dose != 2)
    {
        printf("Veuillez sélectionner un nombre de dose conforme (1 ou 2).\n");
        scanf("%d", &dose);
    }
    return(dose);
}

void cofeeFlow()
{
    printf("Le café coule.\n");
}

