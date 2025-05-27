#include "../controller/functions.c"
#include "interface.h"

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
                                   CW_USEDEFAULT, CW_USEDEFAULT, 350, 390,
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
            cup.empty = 1;
            cup.isUnderCafetiere = 0;
            cup.QUANTITY = QUANTITY_CUP;

            water.quantity = 1000;
            water.QUANTITY_MAX = 2500;
            water.temperature = 14;

            cafetiere.water = water;
            cafetiere.on = 0;
            cafetiere.numberCup = 0;
            cafetiere.numberCofeeDose = 0;
            cafetiere.hasLimestone = 0;

            btnOnOffText[32] = "Allumer la cafetière";

            btnOnOff = CreateWindow("BUTTON", btnOnOffText, WS_CHILD | WS_VISIBLE, 0, 0, 150, HEIGHT_CHAR, hwnd, (HMENU)1, hInstance, NULL);
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
             * Console pour les tests à enelever
             */
            AllocConsole();
            freopen("CONOUT$", "w", stdout);
            /*--------------------------------------------------*/

            // LOWORD(wParam) = ID du contrôle ou du menu
            switch(LOWORD(wParam))
            {
                case 1:
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