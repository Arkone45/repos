// СП_Лаб№3.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "СП_Лаб№3.h"
#include "commctrl.h"

#pragma comment(lib, "comctl32")

#define MAX_LOADSTRING 100
#define ID_MY_BUTTON1 1001
#define ID_MY_BUTTON2 1002
#define ID_MY_BUTTON3 1003
#define ID_MY_BUTTON4 1004
#define ID_MY_BUTTON5 1005
#define ID_MY_BUTTON6 1006
#define ID_MY_BUTTON7 1007
#define ID_MY_BUTTON8 1008
#define ID_MY_BUTTON9 1009
#define ID_MY_COMBOBOX1 1010

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    PanelProc(HWND, UINT, WPARAM, LPARAM, UINT_PTR, DWORD_PTR);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK       EnumWindowsProc(HWND, LPARAM);
BOOL CALLBACK       EnumChildWindowsProc(HWND, LPARAM);
BOOL CALLBACK       TotalEnumWindowsProc(HWND, LPARAM);
BOOL CALLBACK       TotalEnumChildWindowsProc(HWND, LPARAM);
HWND Button1, Button2, Button3, Button4, Button5, Button6, Button7, Button8, Button9, ComboBox1, Panel1;

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
    LoadStringW(hInstance, IDC_MY3, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY3));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY3));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY3);
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
    HWND button1 = CreateWindowW(L"button", L"Скрыть/Показать",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        15, 10, 150, 30, hWnd, (HMENU)ID_MY_BUTTON1, hInstance, nullptr);
    Button1 = button1;
    HWND button2 = CreateWindowW(L"button", L"Сделать доступным/недоступным",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        175, 10, 250, 30, hWnd, (HMENU)ID_MY_BUTTON2, hInstance, nullptr);
    Button2 = button2;
    HWND button3 = CreateWindowW(L"button", L"Закрыть",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        435, 10, 70, 30, hWnd, (HMENU)ID_MY_BUTTON3, hInstance, nullptr);
    Button3 = button3;
    HWND panel1 = CreateWindowW(L"static", L"",
        WS_CHILD | SS_CENTER | SS_CENTERIMAGE | SS_SUNKEN,
        10, 50, 855, 40, hWnd, nullptr, hInstance, nullptr);
    SetWindowSubclass(panel1, PanelProc, 1, 1);
    Panel1 = panel1;
    HWND button4 = CreateWindowW(L"button", L"Нажать на кнопку",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        5, 5, 150, 30, panel1, (HMENU)ID_MY_BUTTON4, hInstance, nullptr);
    Button4 = button4;
    HWND button5 = CreateWindowW(L"button", L"Выполнить команду пункта меню",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        165, 5, 250, 30, panel1, (HMENU)ID_MY_BUTTON5, hInstance, nullptr);
    Button5 = button5;
    HWND button6 = CreateWindowW(L"button", L"ПКМ",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        425, 5, 50, 30, panel1, (HMENU)ID_MY_BUTTON6, hInstance, nullptr);
    Button6 = button6;
    HWND button7 = CreateWindowW(L"button", L"Переместить",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        485, 5, 100, 30, panel1, (HMENU)ID_MY_BUTTON7, hInstance, nullptr);
    Button7 = button7;
    HWND button8 = CreateWindowW(L"button", L"Переименовать все дочерние окна",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        595, 5, 250, 30, panel1, (HMENU)ID_MY_BUTTON8, hInstance, nullptr);
    Button8 = button8;
    HWND combobox1 = CreateWindowW(L"combobox", L"",
        WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL | CBS_SORT,
        15, 50, 400, 300, hWnd, (HMENU)ID_MY_COMBOBOX1, hInstance, nullptr);
    ComboBox1 = combobox1;
    HWND button9 = CreateWindowW(L"button", L"Переименовать всё",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        515, 10, 150, 30, hWnd, (HMENU)ID_MY_BUTTON9, hInstance, nullptr);
    Button9 = button9;

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
WORD Wnum = 0, WCnum = 0;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HWND CurWnd;
    LPCWSTR name;
    int cTxtLen;
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        int nCode = HIWORD(wParam);
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        case ID_MY_BUTTON1:
            cTxtLen = GetWindowTextLength(ComboBox1);
            name = (LPCWSTR)VirtualAlloc((LPVOID)NULL, (DWORD)(cTxtLen + 1), MEM_COMMIT, PAGE_READWRITE);
            GetWindowTextW(ComboBox1, (LPWSTR)name, cTxtLen + 1);
            CurWnd = FindWindowW(NULL, name);
            if (CurWnd)
                if (IsWindowVisible(CurWnd))
                    ShowWindow(CurWnd, SW_HIDE);
                else
                    ShowWindow(CurWnd, SW_RESTORE);
            VirtualFree((LPVOID)name, (DWORD)(cTxtLen + 1), MEM_DECOMMIT);
            break;
        case ID_MY_BUTTON2:
            cTxtLen = GetWindowTextLength(ComboBox1);
            name = (LPCWSTR)VirtualAlloc((LPVOID)NULL, (DWORD)(cTxtLen + 1), MEM_COMMIT, PAGE_READWRITE);
            GetWindowTextW(ComboBox1, (LPWSTR)name, cTxtLen + 1);
            CurWnd = FindWindowW(NULL, name);
            if (CurWnd)
                EnableWindow(CurWnd, !IsWindowEnabled(CurWnd));
            VirtualFree((LPVOID)name, (DWORD)(cTxtLen + 1), MEM_DECOMMIT);
            break;
        case ID_MY_BUTTON3:
            cTxtLen = GetWindowTextLength(ComboBox1);
            name = (LPCWSTR)VirtualAlloc((LPVOID)NULL, (DWORD)(cTxtLen + 1), MEM_COMMIT, PAGE_READWRITE);
            GetWindowTextW(ComboBox1, (LPWSTR)name, cTxtLen + 1);
            CurWnd = FindWindowW(NULL, name);
            if (CurWnd)
                SendMessage(CurWnd, WM_CLOSE, NULL, NULL);
            VirtualFree((LPVOID)name, (DWORD)(cTxtLen + 1), MEM_DECOMMIT);
            break;
        case ID_MY_BUTTON4:
            CurWnd = FindWindowW(NULL, L"СП_Лаб№2");
            if (CurWnd)
            {
                SendMessage(CurWnd, WM_COMMAND, 1001, 0);
                ShowWindow(CurWnd, SW_SHOW);
                BringWindowToTop(CurWnd);
            }
            break;
        case ID_MY_BUTTON5:
            CurWnd = FindWindowW(NULL, L"СП_Лаб№2");
            if (CurWnd)
            {
                SendMessage(CurWnd, WM_COMMAND, IDM_ABOUT, 0);
                ShowWindow(CurWnd, SW_SHOW);
                BringWindowToTop(CurWnd);
            }
            break;
        case ID_MY_BUTTON6:
            CurWnd = FindWindowW(NULL, L"СП_Лаб№2");
            if (CurWnd)
            {
                SendMessage(CurWnd, WM_RBUTTONDOWN, 0, 0);
                ShowWindow(CurWnd, SW_SHOW);
                BringWindowToTop(CurWnd);
            }
            break;
        case ID_MY_BUTTON7:
            POINT crs;
            CurWnd = FindWindowW(NULL, L"СП_Лаб№2");
            if (CurWnd)
            {
                GetCursorPos(&crs);
                SetWindowPos(CurWnd, HWND_TOP, crs.x - 100, crs.y - 200, 0, 0, SWP_NOSIZE | SWP_SHOWWINDOW);
                ShowWindow(CurWnd, SW_SHOW);
                BringWindowToTop(CurWnd);
                SendMessageW(CurWnd, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(100, 200));
            }
            break;
        case ID_MY_BUTTON8:
            CurWnd = FindWindowW(NULL, L"СП_Лаб№2");
            if (CurWnd)
            {
                EnumChildWindows(CurWnd, &EnumChildWindowsProc, NULL);
                ShowWindow(CurWnd, SW_SHOW);
                BringWindowToTop(CurWnd);
            }
            break;
        case ID_MY_BUTTON9:
            EnumWindows(&TotalEnumWindowsProc, MAKELPARAM(&Wnum, &WCnum));
            break;
        case ID_MY_COMBOBOX1:
        {
            switch (nCode)
            {
            case CBN_DROPDOWN:
                SendMessage(ComboBox1, CB_RESETCONTENT, 0, 0);
                EnumWindows(&EnumWindowsProc, NULL);
                break;
            case CBN_SELCHANGE:
                cTxtLen = GetWindowTextLength(ComboBox1);
                name = (LPCWSTR)VirtualAlloc((LPVOID)NULL, (DWORD)(cTxtLen + 1), MEM_COMMIT, PAGE_READWRITE);
                GetWindowTextW(ComboBox1, (LPWSTR)name, cTxtLen + 1);
                if (lstrcmpW(name, L"СП_Лаб№2") == 0)
                {
                    MoveWindow(ComboBox1, 10, 100, 400, 300, TRUE);
                    ShowWindow(Panel1, SW_SHOW);
                }
                else
                {
                    ShowWindow(Panel1, SW_HIDE);
                    MoveWindow(ComboBox1, 10, 50, 400, 300, TRUE);
                }
                VirtualFree((LPVOID)name, (DWORD)(cTxtLen + 1), MEM_DECOMMIT);
                break;
            default:
                break;
            }
        }
		break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
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

LRESULT CALLBACK PanelProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    return WndProc(hWnd, message, wParam, lParam);
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

BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam)
{
    int cTxtLen = GetWindowTextLength(hWnd);
    if ((cTxtLen > 0) && IsWindowVisible(hWnd) && IsWindowEnabled(hWnd))
    {
        LPCWSTR temp_name = (LPCWSTR)VirtualAlloc((LPVOID)NULL, (DWORD)(cTxtLen + 1), MEM_COMMIT, PAGE_READWRITE);
        GetWindowTextW(hWnd, (LPWSTR)temp_name, cTxtLen + 1);
        SendMessageW(ComboBox1, CB_INSERTSTRING, 0, (LPARAM)temp_name);
        VirtualFree((LPVOID)temp_name, (DWORD)(cTxtLen + 1), MEM_DECOMMIT);
    }
    return TRUE;
}

BOOL CALLBACK EnumChildWindowsProc(HWND hWnd, LPARAM lParam)
{
    SendMessageW(hWnd, WM_SETTEXT, NULL, (LPARAM)L"???");
    return TRUE;
}

BOOL CALLBACK TotalEnumWindowsProc(HWND hWnd, LPARAM lParam)
{
    TCHAR buf1[100], buf2[100] = L"Окно";
    Wnum += 1;
    _itow_s(Wnum, buf1, 10);
    SendMessageW(hWnd, WM_SETTEXT, NULL, (LPARAM)wcscat_s(buf2, buf1));
    EnumChildWindows(hWnd, &TotalEnumChildWindowsProc, NULL);
    return TRUE;
}

BOOL CALLBACK TotalEnumChildWindowsProc(HWND hWnd, LPARAM lParam)
{
    TCHAR buf1[100], buf2[100] = L"Дочернее";
    WCnum += 1;
    _itow_s(WCnum, buf1, 10);
    SendMessageW(hWnd, WM_SETTEXT, NULL, (LPARAM)wcscat_s(buf2, buf1));
    return TRUE;
}