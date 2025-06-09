#include "functions.h"

#define LOG_FILE "log.txt"
#define DATA_FILE "datas.dat"
#define TAILLE_MAX 100

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
        addLog("La tasse est déjà dans la cafetière.\n");
    }
    else
    {
        cup->isUnderCafetiere = 1;
        addLog("Vous avez mis la tasse dans la cafetière.\n");
    }
}

void takeCup(Cup *cup)
{
    if(cup->isUnderCafetiere)
    {
        cup->isUnderCafetiere = 0;
        addLog("Vous avez pris la tasse.\n");
    }
    else
    {
        addLog("Il n'y a pas de tasse dans la cafetière.\n");
    }
}

void turnOn(Cafetiere *cafetiere, int quantityCup)
{
    if(cafetiere->on)
    {
        addLog("La cafetière est déjà allumée.\n");
    }
    else
    {
        cafetiere->on = 1;
        addLog("La cafetière est allumée.\n");

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
        addLog("La cafetière est éteinte.\n");
    }
    else
    {
        addLog("La cafetière est déjà éteinte.\n");
    }
}

void waterHeating(Cafetiere *cafetiere)
{
    if(cafetiere->water.temperature == 100)
    {
        addLog("L'eau est déjà chaude.\n");
    }
    else
    {
        addLog("L'eau chauffe.\n");
        cafetiere->water.temperature = 100;
        addLog("L'eau est chaude.\n");
    }
}

void addWater(Cafetiere *cafetiere, int quantity)
{
    if(quantity >= 2500)
    {
        cafetiere->water.quantity = 2500;
        addLog("Le réservoir d'eau est plein.\n");
    }
    else
    {
        cafetiere->water.quantity += quantity;
        char WaterStr[31];
        itoa(quantity, WaterStr, 10);

        char logStr[] = "ml ont été ajouté.\n";
        strcat(WaterStr, logStr);
        addLog(WaterStr);
    }
}

void selectDose(Cafetiere *cafetiere, int dose)
{
    cafetiere->numberCofeeDose = dose;

    char doseStr[2];
    char logStr[] = "Le nombre de dose sélectionné est ";
    itoa(cafetiere->numberCofeeDose, doseStr, 10);
    strcat(logStr, doseStr);
    strcat(logStr, ".\n");
    addLog(logStr);
}

void cofeeFlow(Cafetiere *cafetiere, Cup *cup, int dose)
{
    if(cafetiere->water.temperature == 100 && cafetiere->on)
    {
        selectDose(cafetiere, dose);
        cafetiere->water.quantity -= cafetiere->numberCofeeDose*cup->QUANTITY;

        if(cup->isUnderCafetiere)
        {
            addLog("Le café coule.\n");
        }
        else
        {
            addLog("Vous n'avez pas mis de tasse sous la cafetière, le café coule partout.\n");
        }
    }
}

void addLog(char string[])
{
    FILE *logFile = NULL;

    time_t raw;
    time(&raw);

    struct tm *time_ptr;
    time_ptr = localtime(&raw);

    char current_time [124];
    strftime(current_time, sizeof(current_time), "%a %D - %X ", time_ptr);

    logFile = fopen(LOG_FILE, "a");
    if(logFile != NULL)
    {
        strcat(current_time, string);
        fputs(current_time, logFile);
    }
    fclose(logFile);
}

void initDatas()
{
    if (access(DATA_FILE, F_OK) != 0)
    {
        FILE *datasFile = NULL;
        datasFile = fopen(DATA_FILE, "a");

        if(datasFile != NULL)
        {
            char defaultDatas[] = "water quantity : 10\ncup quantity : 250";
            fputs(defaultDatas, datasFile);
        }
        
        fclose(datasFile);
    }
}

int getWater()
{   
    int water_quantity = 0;
    char chaine[TAILLE_MAX] = "";
    FILE *datasFile = NULL;
    datasFile = fopen(DATA_FILE, "rb");

    if(datasFile != NULL)
    {
        char *strToken = NULL;
        int lineFind = 0;
        while (fgets(chaine, TAILLE_MAX, datasFile)) 
        {
            strToken = strtok(chaine, ":");
            if(strcmp(strToken, "water quantity"))
            {
                lineFind = 1;
                water_quantity = 1;
                break;
            }
        }

        if(lineFind == 1)
        {
            strToken = strtok (NULL, strToken);
            water_quantity = atoi(strToken);
            printf("%d", water_quantity); 
        }
    }
    fclose(datasFile);

    return water_quantity;
}

int setWater(int quantityWater)
{
    FILE *datasFile = NULL;
    datasFile = fopen(DATA_FILE, "wb");

    if(datasFile != NULL)
    {

    }
    fclose(datasFile);
    return 1;
    return 0;
}

int getCup()
{
    return 0;
}