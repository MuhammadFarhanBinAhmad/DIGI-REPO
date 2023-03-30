// WindowsProjectA.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "WindowsProjectA.h"
#include <stdio.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

HWND hWnd;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
    if (AllocConsole())
    {
        FILE* file;

        freopen_s(&file, "CONOUT$", "wt", stdout);
        freopen_s(&file, "CONOUT$", "wt", stderr);
        freopen_s(&file, "CONOUT$", "wt", stdin);

        SetConsoleTitle(L"CRUNDLE QUESTV...");

        printf("Simulation Starting...\n");
    }
    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECTA, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);//

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECTA));

    MSG msg;
    bool loop = true;
    while (loop)
    {
        //while (GetMessage(&msg, NULL, 0, 0))//Only start counting when an event occurs(button click,mouse move etc.)
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                loop = false;
                //break;
            }

            /*if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            static int counterLoop;
            if (counterLoop < 100000)
                counterLoop++;
            printf("counterLoop = %d\n", counterLoop);*/
        }
        static int counterLoop;
        if (counterLoop < 100000)
            counterLoop++;
        printf("counterLoop = %d\n", counterLoop);
    }
    // Main message loop:
    /*while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }*/
    FreeConsole();
    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW; //| CS_NOCLOSE;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECTA));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)CreateSolidBrush(RGB(0,255,0));
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECTA);//set to null to make full use of window
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);//stop user from maximising window
   //WS_SIZEBOX STOP USER FROM RESIZE WINDOW
   //WS_MAXIMIXEBOX STOP USER FROM MAX SIZING WINDOW

   if (!hWnd)
   {
      return FALSE;
   }
   //Done only once
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//

//Where events are being handled
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    //HBITMAP hBtp;//add this at the beginning before the switch case
    int x, y;
    int j;
    POINT pt[10] = { 100, 200, 300, 400, 500, 600, 700, 600, 500, 100 };
    RECT rect, rect2;
    switch (message)
    {
    /*case WM_CREATE:
        hBtp = LoadBitmap(hInst, (LPCTSTR)IDB_BITMAP1);
        SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (ULONG_PTR)CreatePatternBrush(hBtp));
        break;*/
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case ID_FILE_TESTBUTTON:
                SetWindowText(hWnd, L"CSD1130-A");
                break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
        //Use to draw/render stuff in the cilent area/window area
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            GetClientRect(hWnd, &rect);
            for (x = 0; x < rect.right; x += 100)
            {
                MoveToEx(hdc, x, 0, NULL);
                LineTo(hdc, x, rect.bottom);
            }

            for (y = 0; y < rect.bottom; y += 100)
            {
                MoveToEx(hdc, 0, y, NULL);
                LineTo(hdc, rect.right, y);
            }

            MoveToEx(hdc, pt[0].x, pt[0].y, NULL);
            PolylineTo(hdc, pt + 1, 5);

            for (j = 0; j < 5; j++)
            {
                rect2.top = j * 100;
                rect2.left = j * 100;
                rect2.bottom = (j + 1) * 100;
                rect2.right = (j + 1) * 100;

                FillRect(hdc, &rect2, CreateSolidBrush(RGB(20 * (j + 1), 40 * (j + 1), 53 * (j + 1))));
            }
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);//responsible for killing the window(call the x button)
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
//Handle the small about box
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        RECT rect;
        GetWindowRect(hWnd, &rect);
        SetWindowPos(hDlg, 0, rect.left + 100, rect.top + 100, 600, 600, SWP_SHOWWINDOW);
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
