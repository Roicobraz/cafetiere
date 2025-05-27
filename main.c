#include "main.h"

int main(int argc, char const *argv[])
{
    // default datas
    int const QUANTITY_CUP = 250;
    Cup cup = {1, 0, QUANTITY_CUP};
    Water water = {1000, 2500, 14};
    Cafetiere cafetiere = {water, 0, 0, 0, 0}; 

    possibleActions();
    int response;
    while(response != 8)
    {
        // Bug si on entre une caractère
        int result = scanf("%d", &response);
        
        if (result != 1) {
            printf("Entrée invalide. Veuillez entrer un nombre.\n");

            // Vider le tampon d'entrée
            while (getchar() != '\n');

            continue;
        }

        if(response < 9 && response > 0)
        {
            switch (response)
            {
                case 1:
                    turnOn(&cafetiere, QUANTITY_CUP);
                    break;
                case 2:
                    addWater(&cafetiere);
                    break;
                case 3:
                    putCup(&cup);
                    break;
                case 4:
                    selectDose(&cafetiere);   
                    break;   
                case 5:
                    cofeeFlow(&cafetiere, &cup, QUANTITY_CUP);   
                    break;
                case 6:
                    takeCup(&cup);
                    break;
                case 7:
                    turnOff(&cafetiere);
                    break;
                case 8:
                    printf("Merci d'avoir utilisé cette application console.");
                    break;
                default:
                    // possibleActions();
                    break;
            }
        }
    }

    return 0;
}

void possibleActions()
{
    printf("Actions possible: \n\
1. Allumer la cafetière\n\
2. Ajouter de l'eau\n\
3. Mettre la tasse dans la cafetière\n\
4. Choisir sa dose de café\n\
5. Se servir un cafés\n\
6. Reprendre la tasse\n\
7. Éteindre la cafetière\n\
8. Quitter l'application\n\
");
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
        else
        {
            printf("Vous devez ajouter de l'eau.\n");
            addWater(cafetiere);
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
        sleep(2);
        cafetiere->water.temperature = 100;
        printf("L'eau est chaude.\n");
    }
}

void addWater(Cafetiere *cafetiere)
{
    char response[4];
    int waterDose;
    printf("Voulez-vous remplir entièrement le réservoir d'eau? (O/N)\n");
    scanf("%s", &response);

    if(strcmp(response, "o") == 0 || strcmp(response, "O") == 0)
    {
        waterDose = cafetiere->water.QUANTITY_MAX - cafetiere->water.quantity;
    }
    else if(strcmp(response, "n") == 0 || strcmp(response, "N") == 0)
    {
        printf("De combien de millilitres?\n");
        scanf("%d", &waterDose);
    }

    if((waterDose+cafetiere->water.quantity) >= cafetiere->water.QUANTITY_MAX)
    {
        waterDose = cafetiere->water.QUANTITY_MAX - cafetiere->water.quantity;
        cafetiere->water.quantity = cafetiere->water.QUANTITY_MAX;
    }
    else
    {
        cafetiere->water.quantity += waterDose;
    }
    printf("Vous rajoutez %d ml d'eau.\n", waterDose);

    if(cafetiere->water.quantity == cafetiere->water.QUANTITY_MAX)
    {
        printf("Le réservoir d'eau est entièrement rempli.\n");
    }
}

void selectDose(Cafetiere *cafetiere)
{
    int dose;
    printf("Combien de dose voulez-vous? 1 ou 2?\n");
    scanf("%d", &dose);
    while(dose != 1 && dose != 2)
    {
        printf("Veuillez sélectionner un nombre de dose conforme (1 ou 2).\n");
        scanf("%d", &dose);
    }
    printf("Vous avez sélectionné %d dose(s).\n", dose);
    cafetiere->numberCofeeDose = dose;
}

void cofeeFlow(Cafetiere *cafetiere, Cup *cup, int const QUANTITY_CUP)
{
    if(cafetiere->water.temperature == 100)
    {
        if(cafetiere->numberCofeeDose == 0)
        {
            printf("Veuillez choisir une dose pour votre café.\n");
            selectDose(cafetiere);
        }
        printf("Le café coule.\n");
        sleep(2);
        cafetiere->water.quantity -= cafetiere->numberCofeeDose*QUANTITY_CUP;
        if(cup->isUnderCafetiere)
        {
            printf("Le café est prêt.\n");
        }
        else
        {
            printf("Bah bravo, vous en avez mis partout... Pensez à mettre une tasse la prochaine fois.\n");
        }
    }
    else 
    {
        printf("Veuillez chauffer l'eau avant.\n");
    }
}