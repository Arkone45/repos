// СП_Лаб№1.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "СП_Лаб№1.h"

#define MAX_LOADSTRING 100
#define ID_MY_BUTTON1 1001
#define ID_MY_BUTTON2 1002
#define ID_MY_EDIT 1003
#define ID_MY_STATIC 1004


// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING] = L"ЛР№1_Комляков";                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING] = L"ЛР№1_Комляков";            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    OkonnayaProcedura(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
HWND Button1, Button2, Edit1, Static1;
HRGN Combination1;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    // TODO: Разместите код здесь.
    // Инициализация глобальных строк
    //LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    //LoadStringW(hInstance, IDC_MY1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY1));

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

    wcex.cbSize         = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = OkonnayaProcedura;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY1);
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
   HWND edit1 = CreateWindowW(L"edit", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
       120, 10, 200, 30, hWnd, nullptr, hInstance, nullptr);
   Edit1 = edit1;
   HWND static1 = CreateWindowW(L"static", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
       120, 50, 200, 30, hWnd, nullptr, hInstance, nullptr);
   Static1 = static1;
   HRGN comb = CreateRectRgn(0, 0, 0, 0);
   CombineRgn(comb, CreateRectRgn(0, 0, 500, 300), CreateEllipticRgn(0, 150, 500, 450), RGN_OR);
   CombineRgn(comb, comb, CreateEllipticRgn(150, 145, 350, 345), RGN_DIFF);
   Combination1 = comb;
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
LRESULT CALLBACK OkonnayaProcedura(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HWND edit_hwnd;
    int cTxtLen;
    LPCWSTR temp_name;
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case ID_32771:
                MessageBox(hWnd, L"NEW_MENUITEM", L"Сообщение", MB_OK);
                SetParent(Button1, HWND_DESKTOP);
                for (int i = 10; i < 200; i++)
                {
                    MoveWindow(Button1, i, 10, 100, 30, FALSE);
                    UpdateWindow(Button1);
                    Sleep(1);
                }
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case ID_MY_BUTTON1:
                cTxtLen = GetWindowTextLength(Edit1);
                temp_name = (LPCWSTR)VirtualAlloc((LPVOID)NULL, (DWORD)(cTxtLen + 1), MEM_COMMIT, PAGE_READWRITE);
                GetWindowText(Edit1, (LPWSTR)temp_name, cTxtLen+1);
                SetWindowText(Static1, temp_name);
                VirtualFree((LPVOID)temp_name, (DWORD)(cTxtLen + 1), MEM_DECOMMIT);
                break;
            case ID_MY_BUTTON2:
                cTxtLen = GetWindowTextLength(hWnd);
                temp_name = (LPCWSTR)VirtualAlloc((LPVOID)NULL, (DWORD)(cTxtLen + 1), MEM_COMMIT, PAGE_READWRITE);
                GetWindowText(hWnd, (LPWSTR)temp_name, cTxtLen + 1);
                SetWindowText(Static1, temp_name);
                VirtualFree((LPVOID)temp_name, (DWORD)(cTxtLen + 1), MEM_DECOMMIT);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_RBUTTONDOWN:
        MessageBox(hWnd, L"WM_RBUTTONDOWN", L"Сообщение", MB_OK);
        SetParent(Button1, hWnd);
        MoveWindow(Button1, 10, 10, 100, 30, TRUE);
        break;
    case WM_LBUTTONDOWN:
        MessageBox(hWnd, L"WM_LBUTTONDOWN", L"Сообщение", MB_OK);
        SetWindowRgn(hWnd, Combination1, TRUE);
        break;
    case WM_CREATE:
        MessageBox(hWnd, L"WM_CREATE", L"Сообщение", MB_OK);
        break;
    case WM_DESTROY:
        MessageBox(hWnd, L"WM_DESTROY", L"Сообщение", MB_OK);
        PostQuitMessage(0);
        break;
    case WM_CLOSE:
        MessageBox(hWnd, L"WM_CLOSE", L"Сообщение", MB_OK);
        PostQuitMessage(0);
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        //FillRgn(GetDC(hWnd), Combination1, CreateSolidBrush(RGB(200, 100, 50)));
        // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
        EndPaint(hWnd, &ps);
    }
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