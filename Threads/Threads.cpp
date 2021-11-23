// Threads.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Threads.h"

#define MAX_LOADSTRING 100

#define CMD_BUTTON_START_THREAD 1001
#define CMD_BUTTON_START_THREAD2 1002
#define CMD_BUTTON_START_THREAD3 1003


// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
INT n;
HWND combo;
// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void                StartThread();
void                StartThread2();
void                StartThread3();


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
    LoadStringW(hInstance, IDC_THREADS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_THREADS));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_THREADS));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+22);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_THREADS);
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
    case WM_CREATE:
        CreateWindowW(L"Button", L"Thread", WS_CHILD | WS_VISIBLE, 10, 10, 75, 23, hWnd, (HMENU)CMD_BUTTON_START_THREAD, hInst, 0);
        CreateWindowW(L"Button", L"Thread2", WS_CHILD | WS_VISIBLE, 10, 40, 75, 23, hWnd, (HMENU)CMD_BUTTON_START_THREAD2, hInst, 0);
        CreateWindowW(L"Button", L"Thread3", WS_CHILD | WS_VISIBLE, 10, 70, 75, 23, hWnd, (HMENU)CMD_BUTTON_START_THREAD3, hInst, 0);
        combo =  CreateWindowW(L"Listbox", L"", WS_CHILD | WS_VISIBLE, 100, 10, 250, 200, hWnd, NULL, hInst, 0);
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case CMD_BUTTON_START_THREAD:
                StartThread();
                break;
            case CMD_BUTTON_START_THREAD2:
                StartThread2();
                break;
            case CMD_BUTTON_START_THREAD3:
                StartThread3();
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
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
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

DWORD WINAPI ThreadProc(LPVOID params) {
    int res = MessageBoxW(NULL, L"Hello from thread", L"Works", MB_OK);
    if (res == IDOK) {

    }
    //DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), NULL, About);
    return 0;
}

DWORD WINAPI ThreadProc2(LPVOID params) {
    int res = MessageBoxW(NULL, L"Hello from thread2", (WCHAR*)params, MB_OK);
    if (res == IDOK) {

    }
    //DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), NULL, About);
    return 0;
}

float deposit;
struct DepData {
    int month;
    float percent;
    DepData(int m, float p) : month{m}, percent {p} {}
};

DWORD WINAPI ThreadProc3(LPVOID params) {
    DepData* data = (DepData*)params;
    WCHAR txt[100];
    deposit *= 1 + data->percent / 100.0;
    _snwprintf_s(
        txt, 100,
        L"moth %d perc %.2f, total %.2f",
        data->month, data->percent, deposit);
    SendMessage(combo, LB_ADDSTRING, 100, (LPARAM)txt);
 
    return 0;
}

void StartThread(){
    CreateThread(
        NULL, 
        0,      //stack limit
        ThreadProc,    //adress of threar function
        NULL, //pointers to paramentr(s)
        0,  //Creation flags 
        NULL //Thread Id Pointer
        );
   // DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), NULL, About);
}

void StartThread2() {
    CreateThread(
        NULL,
        0,      //stack limit
        ThreadProc2,    //adress of threar function
        szTitle, //pointers to paramentr(s)
        0,  //Creation flags 
        NULL //Thread Id Pointer
    );
   // DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), NULL, About);
}


HANDLE hts[12];
void StartThread3()
{
    deposit = 100;
    for (size_t i = 0; i < 12; i++) {
        hts[i] = CreateThread(
            NULL,
            0,      //stack limit
            ThreadProc3,    //adress of threar function
            new DepData(1+i, 10), //pointers to paramentr(s)
            0,  //Creation flags 
            NULL //Thread Id Pointer
           
        );
    }
    SendMessage(combo, LB_ADDSTRING, 100, (LPARAM)L"End-for");
}


