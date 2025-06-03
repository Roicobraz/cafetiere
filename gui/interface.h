#include <windows.h>
#include <windowsx.h>
#include <shlwapi.h>

#define HEIGHT_CHAR 20
#define FULL_WATER 2500

// Window's procedures

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK AddWaterWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


HBITMAP hBitmap;
/**
 * If you add a new bitmap you must destroy that in the WM_DESTROY.
 * You can do that with: 
 * DeleteObject(same_hwnd);
 */
HBITMAP addBitmap(HWND hwnd, char bitmapLink[]);

HWND btnOnOff;
char btnOnOffText[32]; 

HWND btnWater;

HWND btnputTake;
char btnputTakeText[32]; 

HWND addWaterWindow;

HWND btnDose1;
HWND btnDose2;


int const QUANTITY_CUP = 250;


void turnOnOff(Cafetiere *cafetiere, int quantityCup, HWND btnOnOff, char test[32]);

Cup cup;
Water water;
Cafetiere cafetiere;
