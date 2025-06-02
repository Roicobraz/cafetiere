#include "../controller/functions.c"
#include "interface.h"

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
    Button_SetText(btnOnOff, btnOnOffText);
}

void putTakeCup(Cup *cup, HWND btnputTake, char btnputTakeText[])
{
    if(cup->isUnderCafetiere)
    {
        takeCup(cup);
        strcpy(btnputTakeText, "Mettre la tasse");
    }
    else
    {
        putCup(cup);
        strcpy(btnputTakeText, "Prendre la tasse");
    }

    Button_SetText(btnputTake, btnputTakeText);
}

HBITMAP addBitmap(HWND hwnd, char bitmapLink[])
{
    hBitmap = (HBITMAP)LoadImage(NULL, bitmapLink, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

        HDC hdcMem = CreateCompatibleDC(hdc);
        SelectObject(hdcMem, hBitmap);

        BITMAP bmp;
        GetObject(hBitmap, sizeof(BITMAP), &bmp);

        BitBlt(hdc, 0, 0, bmp.bmWidth, bmp.bmHeight, hdcMem, 0, 0, SRCCOPY);

        DeleteDC(hdcMem);
        EndPaint(hwnd, &ps);

        return hBitmap;
}