// СП_Лаб№2.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "windowsx.h"
#include "СП_Лаб№2.h"

#define MAX_LOADSTRING 100
#define ID_MY_BUTTON1 1001
#define ID_MY_BUTTON2 1002
#define ID_MY_EDIT 1003
#define ID_MY_STATIC 1004

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void                GetWindowPos(HWND, PLONG, PLONG);
HWND Button1, Button2, Edit1, Static1;
BOOL IsDraged;
LONG DX, DY, Wx_start_pos, Wy_start_pos;

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
    LoadStringW(hInstance, IDC_MY2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY2));

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

    wcex.style          = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY2);
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
       100, 100, 500, 500, nullptr, nullptr, hInstance, nullptr);
   HWND button1 = CreateWindowW(L"button", L"Кнопка 1", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
       10, 10, 100, 30, hWnd, (HMENU)ID_MY_BUTTON1, hInstance, nullptr);
   Button1 = button1;
   HWND button2 = CreateWindowW(L"button", L"Кнопка 2", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
       10, 50, 100, 30, hWnd, (HMENU)ID_MY_BUTTON2, hInstance, nullptr);
   Button2 = button2;
   HWND edit1 = CreateWindowW(L"edit", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
       120, 10, 300, 30, hWnd, nullptr, hInstance, nullptr);
   Edit1 = edit1;
   HWND static1 = CreateWindowW(L"static", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
       120, 50, 300, 30, hWnd, nullptr, hInstance, nullptr);
   Static1 = static1;
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
    int cTxtLen;
    LPCWSTR temp_num;
    POINT curs;
    LONG x, y;
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case ID_MY_BUTTON1:
                cTxtLen = GetWindowTextLength(Edit1);
                temp_num = (LPCWSTR)VirtualAlloc((LPVOID)NULL, (DWORD)(cTxtLen + 1), MEM_COMMIT, PAGE_READWRITE);
                GetWindowText(Edit1, (LPWSTR)temp_num, cTxtLen+1);
                TCHAR buf[100];
                _itow_s(_wtoi(temp_num) * _wtoi(temp_num), buf, 10);
                SetWindowText(Static1, (LPCWSTR)buf);
                VirtualFree((LPVOID)temp_num, (DWORD)(cTxtLen + 1), MEM_DECOMMIT);
                break;
            case ID_MY_BUTTON2:
                SendMessage(Button1, BM_CLICK, NULL, NULL);
                //SendMessage(hWnd, WM_COMMAND, ID_MY_BUTTON1, NULL);
                //GetWindowPos(Button1, &x, &y);
                //SetCursorPos(x+10, y+5);
                //mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, x, y, NULL, NULL);
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
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_CLOSE:
        if (1 == MessageBoxW(hWnd, L"Программа будет закрыта. Продолжить?", L"My App", MB_OKCANCEL | MB_APPLMODAL))
        {
            PostQuitMessage(0);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_RBUTTONDOWN:
        TCHAR buf1[100], buf2[100];
        _ltow_s(LOWORD(lParam), buf1, 10);
        _ltow_s(HIWORD(lParam), buf2, 10);
        wcscat_s(buf1, L" ");
        wcscat_s(buf1, buf2);
        SetWindowText(Static1, (LPCWSTR)buf1);
        break;
    case WM_LBUTTONDOWN:
        IsDraged = IsDraged ? FALSE : TRUE;
        break;
    case WM_MOUSEMOVE:
    {
        curs = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
        MapWindowPoints(hWnd, NULL, &curs, 1);
        if (IsDraged)
        {
            SetWindowPos(hWnd, HWND_TOP, curs.x - DX, curs.y - DY, 0, 0, SWP_NOSIZE | SWP_SHOWWINDOW);
        }
        else
        {
            GetWindowPos(hWnd, &x, &y);
            DX = curs.x - x;
            DY = curs.y - y;
        }
    }
    break;
    default:
        if (DefWindowProc(hWnd, WM_NCHITTEST, wParam, lParam) != HTCAPTION)
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

void GetWindowPos(HWND hWnd, long* x, long* y)
{
    POINT p = { 0 };
    RECT wrect, crect;
    GetWindowRect(hWnd, &wrect);
    GetClientRect(hWnd, &crect);
    POINT lefttop = { crect.left, crect.top };
    ClientToScreen(hWnd, &lefttop);
    POINT rightbottom = { crect.right, crect.bottom };
    ClientToScreen(hWnd, &rightbottom);

    int LB = lefttop.x - wrect.left;
    int RB = wrect.right - rightbottom.x;
    int BB = wrect.bottom - rightbottom.y;
    int TB = lefttop.y - wrect.top;
    ClientToScreen(hWnd, &p);

    (*x) = p.x - LB;
    (*y) = p.y - TB;
}
