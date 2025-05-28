#include <windows.h>
#include <shlwapi.h>

#define HEIGHT_CHAR 16

HBITMAP hBitmap;

HWND btnOnOff;
char btnOnOffText[32]; 

HWND btnputTake;
char btnputTakeText[32]; 

int const QUANTITY_CUP = 250;


void turnOnOff(Cafetiere *cafetiere, int quantityCup, HWND btnOnOff, char test[32]);

Cup cup;
Water water;
Cafetiere cafetiere;
