// à revoir
// éviter la répétition
#include <windows.h>
#define HEIGHT_CHAR 20
/*--------------------------------------------*/
#include "addWater.h"
#include <tchar.h>

void ErrorExit();
typedef struct DynSize DynSize;
struct DynSize
{
    char text[100];
    LONG x;
    LONG y;
};
DynSize dynSize(HWND hwnd, char text[]);


int center(int widthWindow, int widthElement);
#define WwndAddWater 250
#define HwndAddWater 175

int WINAPI winAddWater(HINSTANCE hinstance)
{
    HWND newWindow;
    WNDCLASS wc;

    wc.style = 0;
    wc.lpfnWndProc = AddWaterWndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hinstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(1 + COLOR_BTNFACE);
    wc.lpszMenuName =  NULL;
    wc.lpszClassName = "AddWaterWnd";

    RegisterClass(&wc);

    newWindow = CreateWindow("AddWaterWnd", "Ajout d'eau", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                            CW_USEDEFAULT, CW_USEDEFAULT, WwndAddWater, HwndAddWater,
                                            NULL, NULL, hinstance, NULL);

    if (!newWindow) return FALSE;

    ShowWindow(newWindow, SW_SHOWNORMAL);
    UpdateWindow(newWindow);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

LRESULT CALLBACK AddWaterWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static HINSTANCE hInstance;

    switch (uMsg)
    {
        case WM_CREATE:
        {   
            DynSize valueSize = dynSize(hwnd, "Saisir une valeur :");
            CreateWindow("STATIC", valueSize.text, WS_CHILD | WS_VISIBLE, center(WwndAddWater, valueSize.x), (5+HEIGHT_CHAR)*0, valueSize.x + 4, valueSize.y + 4, hwnd, NULL, hInstance, NULL);
            
            int wEdit = 40; 
            valueEdit = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | ES_NUMBER | ES_CENTER, WwndAddWater/2-wEdit/2, (5+HEIGHT_CHAR)*1, wEdit, HEIGHT_CHAR, hwnd, (HMENU)1, hInstance, NULL);
            
            DynSize unitSize = dynSize(hwnd, "ml");
            CreateWindow("STATIC", unitSize.text, WS_CHILD | WS_VISIBLE, center(WwndAddWater, unitSize.x)+wEdit, (5+HEIGHT_CHAR)*1, unitSize.x, unitSize.y + 4, hwnd, NULL, hInstance, NULL);
            
            DynSize btnSize = dynSize(hwnd, "Valider");
            CreateWindow("BUTTON", btnSize.text, WS_CHILD | WS_VISIBLE, center(WwndAddWater, btnSize.x), (5+HEIGHT_CHAR)*2, btnSize.x+4, btnSize.y+4, hwnd, (HMENU)2, hInstance, NULL);
            return 0;
        }
        case WM_COMMAND:
        {
            switch(LOWORD(wParam))
            {
                case 2:
                    if (HIWORD(wParam) == BN_CLICKED)
                    {
                        char value[5];
                        GetWindowText(valueEdit, value, 10);
                        int quantity = StrToInt(value);
                        addWater(&cafetiere, quantity);
                        DestroyWindow(hwnd);
                    }
                    break;
            } 
            return 0;
        }
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}


void ErrorExit() 
{ 
    // Retrieve the system error message for the last-error code

    LPVOID lpMsgBuf;
    DWORD dw = GetLastError(); 

    if (FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL) == 0) {
        MessageBox(NULL, TEXT("FormatMessage failed"), TEXT("Error"), MB_OK);
        ExitProcess(dw);
    }

    MessageBox(NULL, (LPCTSTR)lpMsgBuf, TEXT("Error"), MB_OK);

    LocalFree(lpMsgBuf);
    ExitProcess(dw); 
}

int center(int widthWindow, int widthElement)
{
    int result;
    result = widthWindow/2-widthElement/2;
    return result;
}

DynSize dynSize(HWND hwnd, char string[])
{
    HDC hdc = GetDC(hwnd);
    HFONT hFont = (HFONT)SendMessage(hwnd, WM_GETFONT, 0, 0);
    HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);

    const TCHAR* text = string;
    SIZE size;
    GetTextExtentPoint32(hdc, text, lstrlen(text), &size);

    SelectObject(hdc, hOldFont);
    ReleaseDC(hwnd, hdc);

    DynSize result;
    strcpy(result.text, text);
    result.x = size.cx;
    result.y = size.cy;

    return result;
}