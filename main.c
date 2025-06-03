#include "gui/interface.c"
#include "gui/addWater.c"

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASS wc;
    wc.style = 0;
    wc.lpfnWndProc = MainWndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hinstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(1 + COLOR_BTNFACE);
    wc.lpszMenuName =  NULL;
    wc.lpszClassName = "MainWindow";

    if(!RegisterClass(&wc)) return FALSE;

    // Création de la fenêtre
    HWND hwnd = CreateWindow("MainWindow", "Cafetière", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                                   CW_USEDEFAULT, CW_USEDEFAULT, 600, 390,
                                                   NULL, NULL, hinstance, NULL);

    if (!hwnd) return FALSE;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    /**
     * Console pour les tests à enlever
     */
    // AllocConsole();
    // freopen("CONOUT$", "w", stdout);
    /*--------------------------------------------------*/

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}
/****************************************************************************/

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static HINSTANCE hInstance;

    switch (uMsg)
    {
        case WM_CREATE:
        {
            initCup(&cup, 1, 0, QUANTITY_CUP);
            initWater(&water, 1000, FULL_WATER, 14);
            initCafetiere(&cafetiere, water, 0, 0, 0, 0);

            strcpy(btnOnOffText, "Allumer la cafetière");
            strcpy(btnputTakeText, "Mettre une tasse");

            int posX = 360;
            int initPosY = 10;
            int marginY = 5;


            btnOnOff = CreateWindow("BUTTON", btnOnOffText, WS_CHILD | WS_VISIBLE, posX, initPosY, 150, HEIGHT_CHAR, hwnd, (HMENU)1, hInstance, NULL);
            
            btnWater = CreateWindow("BUTTON", "Ajouter de l'eau", WS_CHILD | WS_VISIBLE, posX, initPosY+(marginY+HEIGHT_CHAR)*1, 150, HEIGHT_CHAR, hwnd, (HMENU)2, hInstance, NULL);
            

            btnputTake = CreateWindow("BUTTON", btnputTakeText, WS_CHILD | WS_VISIBLE, posX, initPosY+(marginY+HEIGHT_CHAR)*2, 150, HEIGHT_CHAR, hwnd, (HMENU)3, hInstance, NULL);
            
            CreateWindow("STATIC", "Sélection de la dose de café", WS_CHILD | WS_VISIBLE, posX, initPosY+(marginY+HEIGHT_CHAR)*3, 200, HEIGHT_CHAR, hwnd, NULL, hInstance, NULL);

            btnDose1 = CreateWindow("BUTTON", "1 dose", WS_CHILD | WS_VISIBLE, posX, initPosY+(marginY+HEIGHT_CHAR)*4, 70, HEIGHT_CHAR, hwnd, (HMENU)4, hInstance, NULL);
            btnDose2 = CreateWindow("BUTTON", "2 doses", WS_CHILD | WS_VISIBLE, posX+80, initPosY+(marginY+HEIGHT_CHAR)*4, 70, HEIGHT_CHAR, hwnd, (HMENU)5, hInstance, NULL);
            Button_Enable(btnWater, cafetiere.water.quantity != cafetiere.water.QUANTITY_MAX);
            Button_Enable(btnDose1, cafetiere.water.quantity >= cup.QUANTITY);
            Button_Enable(btnDose2, cafetiere.water.quantity >= (cup.QUANTITY*2));
            
            return 0;
        }
        case WM_PAINT:
        {
            hBitmap = addBitmap(hwnd, "medias/img/cafetiere.bmp");
            return 0;
        }
        case WM_COMMAND:
        {
            if (HIWORD(wParam) == BN_CLICKED)
            {
                switch(LOWORD(wParam))
                {
                    // On/Off 
                    case 1:
                    {
                        turnOnOff(&cafetiere, QUANTITY_CUP, btnOnOff, btnOnOffText);
                        break;
                    } 
                    // Ajout de l'eau
                    case 2:
                    {
                        int test = MessageBox(hwnd, "Voulez-vous remplir entièrement le réservoir d'eau ?", "Ajout d'eau", MB_YESNO);

                        if(test == 6)
                        {
                            addWater(&cafetiere, FULL_WATER);
                        }
                        else if(test == 7) 
                        {
                            winAddWater(hInstance);
                        }
                        break;
                    }  
                    // Prendre / mettre la tasse
                    case 3:
                    {
                        putTakeCup(&cup, btnputTake, btnputTakeText);
                        break;
                    }  
                    // Sélection de la dose de café
                    case 4:
                    {
                        cofeeFlow(&cafetiere, &cup, 1);
                        break;
                    }
                    case 5:
                    {
                        cofeeFlow(&cafetiere, &cup, 2);
                        break;
                    } 
                }
            }
            Button_Enable(btnWater, cafetiere.water.quantity != cafetiere.water.QUANTITY_MAX);
            Button_Enable(btnDose1, cafetiere.water.quantity >= cup.QUANTITY);
            Button_Enable(btnDose2, cafetiere.water.quantity >= (cup.QUANTITY*2));
            return 0;
        }
        case WM_DESTROY:
        {
            DeleteObject(hBitmap);
            PostQuitMessage(0);
            return 0;
        }

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}