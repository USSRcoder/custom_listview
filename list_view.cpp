// list_view.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "list_view.h"
#include "commctrl.h"
#include "windows.h"

#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "UxTheme.lib")

#define MAX_LOADSTRING 100
#define ITEM_COUNT 100000

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                CLSID_VIEW_Register(HINSTANCE hInstance);
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
    InitCommonControls();
    COMCTL32_RefreshSysColors();

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LISTVIEW, szWindowClass, MAX_LOADSTRING);
    CLSID_VIEW_Register(hInstance);
    LISTVIEW_Register();
    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }
  

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LISTVIEW));

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
ATOM CLSID_VIEW_Register(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LISTVIEW));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LISTVIEW);
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


BOOL InsertListViewItems(HWND hwndListView);

BOOL InitListView(HWND hwndListView)
{
    LV_COLUMN   lvColumn;
    int         i;
    TCHAR       szString[5][20] = { TEXT("Main Column"), TEXT("Column 1"), TEXT("Column 2"), TEXT("Column 3"), TEXT("Column 4") };

    //empty the list
    ListView_DeleteAllItems(hwndListView);

    //initialize the columns
    lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
    lvColumn.fmt = LVCFMT_LEFT;
    lvColumn.cx = 120;

    for (i = 0; i < 5; i++)
    {
        lvColumn.pszText = szString[i];
        ListView_InsertColumn(hwndListView, i, &lvColumn);
    }

    InsertListViewItems(hwndListView);

    return TRUE;
}

/******************************************************************************
   InsertListViewItems
******************************************************************************/

BOOL InsertListViewItems(HWND hwndListView)
{
    //empty the list
    ListView_DeleteAllItems(hwndListView);

    //set the number of items in the list
    ListView_SetItemCount(hwndListView, ITEM_COUNT);

    return TRUE;
}

HWND CreateListView(HINSTANCE hInstance, HWND hwndParent)
{
    DWORD       dwStyle;
    HWND        hwndListView;
    HIMAGELIST  himlSmall;
    HIMAGELIST  himlLarge;
    BOOL        bSuccess = TRUE;

    dwStyle = 
        WS_TABSTOP |
        WS_CHILD |
        WS_BORDER |
        WS_VISIBLE |
        LVS_AUTOARRANGE |
        LVS_REPORT |
        LVS_OWNERDATA;
        //| LVS_OWNERDRAWFIXED;
        ;
    //dwStyle = WS_CHILD | LVS_REPORT;

    hwndListView = CreateWindowEx(
        WS_EX_CLIENTEDGE,          // ex style
        L"MySysListView32",               // class name - defined in commctrl.h
        TEXT(""),                        // dummy text
        dwStyle,                   // style
        0,                         // x position
        0,                         // y position
        100,                         // width
        100,                         // height
        hwndParent,                // parent
        (HMENU)0,        // ID
        hInst,                   // instance
        NULL);                     // no extra data

    if (!hwndListView)
        return NULL;

    //ResizeListView(hwndListView, hwndParent);
    RECT  rc;
    GetClientRect(hwndParent, &rc);
    MoveWindow(hwndListView,
        rc.left,
        rc.top,
        rc.right - rc.left,
        rc.bottom - rc.top,
        TRUE);

    //set the image lists
    //himlSmall = ImageList_Create(16, 16, ILC_COLORDDB | ILC_MASK, 1, 0);
    //himlLarge = ImageList_Create(32, 32, ILC_COLORDDB | ILC_MASK, 1, 0);

    //if (himlSmall && himlLarge)
    //{
    //    HICON hIcon;

    //    //set up the small image list
    //    hIcon = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDI_DISK), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
    //    ImageList_AddIcon(himlSmall, hIcon);

    //    //set up the large image list
    //    hIcon = LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_DISK));
    //    ImageList_AddIcon(himlLarge, hIcon);

    //    ListView_SetImageList(hwndListView, himlSmall, LVSIL_SMALL);
    //    ListView_SetImageList(hwndListView, himlLarge, LVSIL_NORMAL);
    //}

    return hwndListView;
}
#define ID_LISTVIEW  2000
LRESULT ListViewNotify(HWND hWnd, LPARAM lParam)
{
    LPNMHDR  lpnmh = (LPNMHDR)lParam;
    HWND     hwndListView = GetDlgItem(hWnd, ID_LISTVIEW);

    switch (lpnmh->code)
    {
        case LVN_GETDISPINFO:
        {
            LV_DISPINFO* lpdi = (LV_DISPINFO*)lParam;
            TCHAR szString[MAX_PATH];

            if (lpdi->item.iSubItem)
            {
                if (lpdi->item.mask & LVIF_TEXT)
                {
                    _sntprintf_s(szString, _countof(szString), _TRUNCATE,
                        TEXT("Item %d - Column %d"),
                        lpdi->item.iItem + 1, lpdi->item.iSubItem);
                    _tcsncpy_s(lpdi->item.pszText, lpdi->item.cchTextMax,
                        szString, _TRUNCATE);
                }
            }
            else
            {
                if (lpdi->item.mask & LVIF_TEXT)
                {
                    _sntprintf_s(szString, _countof(szString), _TRUNCATE,
                        TEXT("Item\n%d"), lpdi->item.iItem + 1);
                    _tcsncpy_s(lpdi->item.pszText, lpdi->item.cchTextMax,
                        szString, _TRUNCATE);
                }

                if (lpdi->item.mask & LVIF_IMAGE)
                {
                    lpdi->item.iImage = 0;
                }
            }
        }
        return 0;

        case LVN_ODCACHEHINT:
        {
            LPNMLVCACHEHINT   lpCacheHint = (LPNMLVCACHEHINT)lParam;
            /*
            This sample doesn't use this notification, but this is sent when the
            ListView is about to ask for a range of items. On this notification,
            you should load the specified items into your local cache. It is still
            possible to get an LVN_GETDISPINFO for an item that has not been cached,
            therefore, your application must take into account the chance of this
            occurring.
            */
        }
        return 0;

        case LVN_ODFINDITEM:
        {
            LPNMLVFINDITEM lpFindItem = (LPNMLVFINDITEM)lParam;
            /*
            This sample doesn't use this notification, but this is sent when the
            ListView needs a particular item. Return -1 if the item is not found.
            */
        }
        return 0;
    }

    return 0;
}


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

static HWND hwndListView;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_CREATE:
            // create the TreeView control
            hwndListView = CreateListView(hInst, hWnd);
            ListView_SetExtendedListViewStyle(hwndListView, LVS_EX_FULLROWSELECT);

            //initialize the TreeView control
            InitListView(hwndListView);

            break;
        case WM_NOTIFY:
            return ListViewNotify(hWnd, lParam);

        case WM_SIZE:
            //ResizeListView(hwndListView, hWnd);
            RECT  rc;
            GetClientRect(hWnd, &rc);
            MoveWindow(hwndListView,
                rc.left,
                rc.top,
                rc.right - rc.left,
                rc.bottom - rc.top,
                TRUE);

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
