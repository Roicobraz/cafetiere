#include "gui/interface.c"

LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    HWND hwnd;
    MSG msg;
    WNDCLASS wc;
    HRGN hrgn;

    wc.style = 0;
    wc.lpfnWndProc = MainWndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hinstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(1 + COLOR_BTNFACE);
    wc.lpszMenuName =  NULL;
    wc.lpszClassName = "MaWinClass";

    if(!RegisterClass(&wc)) return FALSE;

    hBitmap = (HBITMAP)LoadImage(NULL, "medias/img/cafetiere.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    // Création de la fenêtre
    hwnd = CreateWindow("MaWinClass", "Titre", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                                   CW_USEDEFAULT, CW_USEDEFAULT, 600, 390,
                                                   NULL, NULL, hinstance, NULL);

    if (!hwnd) return FALSE;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

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
            initWater(&water, 1000, 2500, 14);
            initCafetiere(&cafetiere, water, 0, 0, 0, 0);

            strcpy(btnOnOffText, "Allumer la cafetière");
            strcpy(btnputTakeText, "Mettre une tasse");

            int posX = 360;
            int initPosY = 10;
            int marginY = 5;

            btnOnOff = CreateWindow("BUTTON", btnOnOffText, WS_CHILD | WS_VISIBLE, posX, initPosY, 150, HEIGHT_CHAR, hwnd, (HMENU)1, hInstance, NULL);
            CreateWindow("BUTTON", "Ajouter de l'eau", WS_CHILD | WS_VISIBLE, posX, initPosY+(marginY+HEIGHT_CHAR)*1, 150, HEIGHT_CHAR, hwnd, (HMENU)2, hInstance, NULL);
            btnputTake = CreateWindow("BUTTON", btnputTakeText, WS_CHILD | WS_VISIBLE, posX, initPosY+(marginY+HEIGHT_CHAR)*2, 150, HEIGHT_CHAR, hwnd, (HMENU)3, hInstance, NULL);
            CreateWindow("BUTTON", "Dose", WS_CHILD | WS_VISIBLE, posX, initPosY+(marginY+HEIGHT_CHAR)*3, 150, HEIGHT_CHAR, hwnd, (HMENU)4, hInstance, NULL);

            return 0;
        }
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            HDC hdcMem = CreateCompatibleDC(hdc);
            SelectObject(hdcMem, hBitmap);

            BITMAP bmp;
            GetObject(hBitmap, sizeof(BITMAP), &bmp);

            BitBlt(hdc, 0, 0, bmp.bmWidth, bmp.bmHeight, hdcMem, 0, 0, SRCCOPY);

            DeleteDC(hdcMem);
            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_COMMAND:
        {
            /**
             * Console pour les tests à enlever
             */
            AllocConsole();
            freopen("CONOUT$", "w", stdout);
            /*--------------------------------------------------*/

            switch(LOWORD(wParam))
            {
                case 1:
                {
                    if (HIWORD(wParam) == BN_CLICKED)
                    {
                        turnOnOff(&cafetiere, QUANTITY_CUP, btnOnOff, btnOnOffText);
                    }
                    break;
                } 
                case 2:
                {
                    if (HIWORD(wParam) == BN_CLICKED)
                    {
                        addWater(&cafetiere);
                        // afficher une nouvelle fenetre qui demande le comment on veux faire pour l'ajout de l'eau
                    }
                    break;
                }  
                case 3:
                {
                    if (HIWORD(wParam) == BN_CLICKED)
                    {
                        putTakeCup(&cup, btnputTake, btnputTakeText);
                    }
                    break;
                }  
                case 4:
                {
                    // HIWORD(wParam) = Raison du message (notification)
                    if (HIWORD(wParam) == BN_CLICKED)
                    {
                        turnOnOff(&cafetiere, QUANTITY_CUP, btnOnOff, btnOnOffText);
                    }
                    break;
                } 
            }
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