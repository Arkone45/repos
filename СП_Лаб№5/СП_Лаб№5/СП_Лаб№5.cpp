﻿// СП_Лаб№5.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "СП_Лаб№5.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
HWND st;
RECT rct, rct1, rct2, rct3, rct4, rct5, rct6;

// Отправить объявления функций, включенных в этот модуль кода:
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

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY5, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY5));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY5));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY5);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
   HWND static1 = CreateWindowW(L"static", L"_",
       WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
       200, 200, 150, 30, hWnd, (HMENU)nullptr, hInstance, nullptr);
   st = static1;
   GetWindowRect(hWnd, &rct);
   rct.left = 0;
   rct.top = 0;
   rct1.left = 0; rct1.right = 200; rct1.top = 0; rct1.bottom = 50;
   rct2.left = 0; rct2.right = 200; rct2.top = 50; rct2.bottom = 100;
   rct3.left = 0; rct3.right = 200; rct3.top = 100; rct3.bottom = 150;
   rct4.left = 200; rct4.right = 400; rct4.top = 0; rct4.bottom = 50;
   rct5.left = 200; rct5.right = 400; rct5.top = 50; rct5.bottom = 100;
   rct6.left = 200; rct6.right = 400; rct6.top = 100; rct6.bottom = 150;
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_MOUSEMOVE:
        WCHAR buf;
        TCHAR buf1[100], buf2[100];
        POINT pt;
        pt.x = LOWORD(lParam);
        pt.y = HIWORD(lParam);
        ClientToScreen(hWnd, &pt);
        _ltow_s(pt.x, buf1, 10);
        _ltow_s(pt.y, buf2, 10);
        wcscat_s(buf1, L" ");
        wcscat_s(buf1, buf2);
        SetWindowText(st, (LPCWSTR)buf1);
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
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
    case WM_PAINT:
        {
            PAINTSTRUCT ps1;
            HDC hdc1 = BeginPaint(hWnd, &ps1);
            FillRect(hdc1, &rct, (HBRUSH)CreateSolidBrush(RGB(20, 20, 100)));
            FillRect(hdc1, &rct1, (HBRUSH)CreateSolidBrush(RGB(255, 255, 255)));
            FillRect(hdc1, &rct2, (HBRUSH)CreateSolidBrush(RGB(0, 0, 255)));
            FillRect(hdc1, &rct3, (HBRUSH)CreateSolidBrush(RGB(255, 0, 0)));
            EndPaint(hWnd, &ps1);
            HDC hdc2 = GetWindowDC(hWnd);
            FillRect(hdc2, &rct4, (HBRUSH)CreateSolidBrush(RGB(255, 255, 255)));
            FillRect(hdc2, &rct5, (HBRUSH)CreateSolidBrush(RGB(0, 0, 255)));
            FillRect(hdc2, &rct6, (HBRUSH)CreateSolidBrush(RGB(255, 0, 0)));
            ReleaseDC(hWnd, hdc2);
            HWND desk = GetDesktopWindow();
            HDC dc = GetWindowDC(desk);
            FillRect(dc, &rct1, (HBRUSH)CreateSolidBrush(RGB(255, 255, 255)));
            FillRect(dc, &rct2, (HBRUSH)CreateSolidBrush(RGB(0, 0, 255)));
            FillRect(dc, &rct3, (HBRUSH)CreateSolidBrush(RGB(255, 0, 0)));
            ReleaseDC(desk, dc);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
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
