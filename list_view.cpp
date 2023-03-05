// list_view.cpp : Определяет точку входа для приложения.
//
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "comctl32.lib")
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include "framework.h"
#include "list_view.h"
#include "commctrl.h"
#include "windows.h"
#include <stdio.h>

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
static HWND hwndListView;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
        /*AllocConsole();
        AttachConsole(GetCurrentProcessId());
        HWND Handle = GetConsoleWindow();
        freopen("CON", "w", stdout);*/

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

#define ID_LISTVIEW  2000

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
        LVS_REPORT |
        LVS_OWNERDATA
        //| LVS_OWNERDRAWFIXED;
        ;

    hwndListView = CreateWindowEx(
        WS_EX_CLIENTEDGE,          // ex style
        L"SysListView32",          // class name - defined in commctrl.h
        TEXT(""),                  // dummy text
        dwStyle,                   // style
        0,                         // x position
        0,                         // y position
        100,                       // width
        100,                       // height
        hwndParent,                // parent
        (HMENU)ID_LISTVIEW,        // ID
        hInst,                     // instance
        NULL);                     // no extra data

    if (!hwndListView)
        return NULL;
    
    //ListView_SetExtendedListViewStyleEx(hwndListView, 0, LVS_EX_DOUBLEBUFFER);

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
    himlSmall = ImageList_Create(16, 16, ILC_COLORDDB | ILC_MASK, 1, 0);
    //himlLarge = ImageList_Create(32, 32, ILC_COLORDDB | ILC_MASK, 1, 0);

    if (himlSmall)
    {
        HICON hIcon;

        //set up the small image list
        hIcon = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
        ImageList_AddIcon(himlSmall, hIcon);
        hIcon = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDI_DISK), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
        ImageList_AddIcon(himlSmall, hIcon);


    //    //set up the large image list
    //    hIcon = LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_DISK));
    //    ImageList_AddIcon(himlLarge, hIcon);

        ListView_SetImageList(hwndListView, himlSmall, LVSIL_SMALL);
        //ListView_SetImageList(hwndListView, himlSmall, LVSIL_STATE);
    //    ListView_SetImageList(hwndListView, himlLarge, LVSIL_NORMAL);
    }

    return hwndListView;
}

COMCTL32_SysColor comctl32_color;
#define INDENT(x) ((x /4 ) % ((x /7) * 7 % 25+1) )

static int prevSibling(int itemid, int iIndent) {
    int prevSibling = itemid - 1;
    while ((prevSibling > 0) && INDENT(prevSibling) >= iIndent) {
        if (INDENT(prevSibling) == iIndent) return prevSibling;
        prevSibling--;
    };
    return -1;
}
static int nextSibling(int itemid, int iIndent) {
    int nextSibling = itemid + 1;
    while ((nextSibling > 0) && INDENT(nextSibling) >= iIndent) {
        if (INDENT(nextSibling) == iIndent) return nextSibling;
        nextSibling++;
    };
    return -1;
}
static int getParent(int itemid) {
    int iIndent = INDENT(itemid) - 1;
    if (iIndent < 0) return -1;
    int itemparent = itemid - 1;
    while (1) {
        if (itemparent < 0) return -1;
        if (INDENT(itemparent) <= iIndent) return itemparent;
        itemparent--;
    }
    return -1;
}

//from COMCTL32.dll systreeview
static void TREEVIEW_DrawItemLines(HDC hdc, const LVITEM* item, INT scrollX, RECT* rect, INT cwidth)
{
    if (item->iIndent <= 0) return;

    LONG centerx, centery;
    HBRUSH hbr, hbrOld;
    COLORREF clrBk = comctl32_color.clrWindow;

    //hbr = CreateSolidBrush(clrBk);
    hbr = GetSysColorBrush(COLOR_WINDOW);
    hbrOld = (HBRUSH)SelectObject(hdc, hbr);

    //RECT rect = { 0 };
    //ListView_GetItemRect(hwndListView, item->iItem, &rect, LVIR_BOUNDS);
    //INT cwidth = ListView_GetColumnWidth(hwndListView, 0);
    //int scrollX = GetScrollPos(hwndListView, SB_HORZ);
    int uIndent = 16;
    int stateImageWidth = 16;
    int normalImageWidth = 16;
    int linesOffset = uIndent * (item->iIndent-1) - scrollX;
    int stateOffset = linesOffset + uIndent;
    int imageOffset = stateOffset + stateImageWidth;
    int textOffset = imageOffset + normalImageWidth;
    centerx = (linesOffset + stateOffset) / 2;
    centery = (rect->top + rect->bottom) / 2;

    if (stateOffset > cwidth - scrollX && centerx < cwidth - scrollX) {
        stateOffset = cwidth - scrollX;
    }
    else if (centerx >= cwidth - scrollX) {
        return;
    }

    //if (infoPtr->dwStyle & TVS_HASLINES)
    {
        HPEN hOldPen, hNewPen;
        //HTREEITEM parent;
        LOGBRUSH lb;

        /* Get a dotted grey pen */
        lb.lbStyle = BS_SOLID;
        lb.lbColor = comctl32_color.clrGrayText;
        hNewPen = ExtCreatePen(PS_COSMETIC | PS_ALTERNATE, 1, &lb, 0, NULL);
        hOldPen = (HPEN)SelectObject(hdc, hNewPen);

        /* Make sure the center is on a dot (using +2 instead
         * of +1 gives us pixel-by-pixel compat with native) */
        centery = (centery + 2) & ~1;

        MoveToEx(hdc, stateOffset, centery, NULL);
        LineTo(hdc, centerx - 1, centery);

        int IprevSibling = prevSibling(item->iItem, item->iIndent);
        int InextSibling = nextSibling(item->iItem, item->iIndent);
        int itemparent = getParent(item->iItem);
       
        //if (item->prevSibling || item->parent != infoPtr->root)
        if ((IprevSibling >= 0 && INDENT(IprevSibling) == item->iIndent) || (INDENT(itemparent) >= 0) )
        {
            MoveToEx(hdc, centerx, rect->top, NULL);
            LineTo(hdc, centerx, centery);
        }

        if (InextSibling >= 0 && INDENT(InextSibling) == item->iIndent)
        {
            MoveToEx(hdc, centerx, centery, NULL);
            LineTo(hdc, centerx, rect->bottom + 1);
        }

        /* Draw the line from our parent to its next sibling. */
        int parent = itemparent;
        while (parent > 0)
        {
            int indentPar = INDENT(parent);
            linesOffset = uIndent * (indentPar - 1) - scrollX;
            stateOffset = linesOffset + uIndent;
            int pcenterx = (linesOffset + stateOffset) / 2;
            int InextSibling = nextSibling(parent, indentPar);
            if (//parent->nextSibling
                InextSibling >=0
                // skip top-levels unless TVS_LINESATROOT 
                && stateOffset > linesOffset)
            {
                MoveToEx(hdc, pcenterx, rect->top, NULL);
                LineTo(hdc, pcenterx, rect->bottom + 1);
            }

            parent = getParent(parent);// parent->parent;
        }
        
        SelectObject(hdc, hOldPen);
        DeleteObject(hNewPen);
    }

    SelectObject(hdc, hbrOld);
    //DeleteObject(hbr);
}


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
                lpdi->item.iIndent = INDENT(lpdi->item.iItem); // (lpdi->item.iItem % (lpdi->item.iItem * 7 % 24 + 1));
                lpdi->item.mask |= LVIF_INDENT;
                if (lpdi->item.mask & LVIF_TEXT)
                {
                    _sntprintf_s(szString, _countof(szString), _TRUNCATE,
                        TEXT("Item%dHiTim"), lpdi->item.iItem + 1);
                    _tcsncpy_s(lpdi->item.pszText, lpdi->item.cchTextMax,
                        szString, _TRUNCATE);
                }

                if (lpdi->item.mask & LVIF_IMAGE)
                {                    
                    lpdi->item.iImage = lpdi->item.iItem % 2 == 0 ? 0 : -1;
                }
            }
        }
        return 0;

        //https://www.c-plusplus.net/forum/topic/87580/nm_customdraw-mit-listview/2
        case NM_CUSTOMDRAW: 
        {

            LPNMLVCUSTOMDRAW  lplvcd = (LPNMLVCUSTOMDRAW)lParam;

            switch (lplvcd->nmcd.dwDrawStage) {

                case CDDS_PREPAINT:
                    return CDRF_NOTIFYITEMDRAW;

                case CDDS_ITEMPREPAINT:

                    HBRUSH			hBrushBack = NULL;
                    //RECT			rc = { 0 };
                    RECT            rc_label = { 0 };
                    HIMAGELIST himl;
                    INT iSubItem = lplvcd->iSubItem;

                    SetBkMode(lplvcd->nmcd.hdc, TRANSPARENT);

                    while (iSubItem < Header_GetItemCount(ListView_GetHeader(hwndListView)))
                    {

                        LVITEM				lvi = { 0 };
                        TCHAR wcBuffer[256] = { 0 };

                        lvi.iItem = lplvcd->nmcd.dwItemSpec;
                        lvi.iSubItem = iSubItem;
                        lvi.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
                        lvi.stateMask = (UINT)-1;
                        lvi.pszText = wcBuffer;
                        lvi.cchTextMax = sizeof(wcBuffer) / 2 - 1;

                        if (!ListView_GetItem(hwndListView, &lvi))
                            break;

                        if (iSubItem == 0)
                        {
                            ListView_GetItemRect(hwndListView, lplvcd->nmcd.dwItemSpec, &lplvcd->nmcd.rc, LVIR_BOUNDS);
                            ListView_GetItemRect(hwndListView, lplvcd->nmcd.dwItemSpec, &rc_label, LVIR_LABEL);
                            himl = ListView_GetImageList(hwndListView, LVSIL_SMALL);
                            INT cwidth = ListView_GetColumnWidth(hwndListView, 0);
                            int scrollX = GetScrollPos(hwndListView, SB_HORZ);

                            lplvcd->nmcd.rc.left = rc_label.left - 2;
                            BOOL isselected = ListView_GetItemState(hwndListView, lplvcd->nmcd.dwItemSpec, LVIS_SELECTED) & LVIS_SELECTED;

                            // разные цвета для выбранного
                            if (isselected) {
                                // selected
                                hBrushBack = GetSysColorBrush(COLOR_HIGHLIGHT);
                                SetTextColor(lplvcd->nmcd.hdc, GetSysColor(COLOR_HIGHLIGHTTEXT));
                            }
                            else {
                                // не выбран
                                hBrushBack = GetSysColorBrush(COLOR_WINDOW);
                                SetTextColor(lplvcd->nmcd.hdc, GetSysColor(COLOR_WINDOWTEXT));
                            }

                            if (lplvcd->nmcd.rc.left > cwidth - scrollX) {
                                lplvcd->nmcd.rc.left = cwidth - scrollX;
                            }

                            //memcpy(&rc, &lplvcd->nmcd.rc, sizeof(rc));
                            FillRect(lplvcd->nmcd.hdc, &lplvcd->nmcd.rc, hBrushBack);
                            //DeleteObject(hBrushBack);

                            bool bFocus = GetFocus() == hwndListView;
                            if (himl && lvi.iImage >= 0)
                            {
                                RECT rcIcon;
                                ListView_GetItemRect(hwndListView, lplvcd->nmcd.dwItemSpec, &rcIcon, LVIR_ICON);

                                OffsetRect(&rcIcon, -2, 0);
                                rcIcon.bottom = rcIcon.top + 16;

                                if (rcIcon.right > cwidth - scrollX) {
                                    rcIcon.right = cwidth - scrollX;
                                }

                                if (!IsRectEmpty(&rcIcon) && rcIcon.right <= cwidth - scrollX) {
                                    UINT style;
                                    if (lvi.state & (LVIS_SELECTED | LVIS_CUT) && bFocus)
                                        style = ILD_SELECTED;
                                    else
                                        style = ILD_NORMAL;

                                    COLORREF clrBk = ListView_GetBkColor(hwndListView);

                                    ImageList_DrawEx(himl, lvi.iImage, lplvcd->nmcd.hdc, rcIcon.left, rcIcon.top,
                                        rcIcon.right - rcIcon.left, rcIcon.bottom - rcIcon.top, clrBk,
                                        lvi.state & LVIS_CUT ? RGB(255, 255, 255) : CLR_DEFAULT,
                                        style | (lvi.state & LVIS_OVERLAYMASK));

                                }
                            }

                            RECT rcpart = rc_label;
                            int textlen = lstrlen(lvi.pszText);
                            int part1 = textlen / 2;
                            int part2 = part1 + 3;
                            DrawText(lplvcd->nmcd.hdc, lvi.pszText, part1, &rcpart, DT_CALCRECT | DT_LEFT | DT_VCENTER | DT_NOPREFIX | DT_EDITCONTROL | DT_SINGLELINE);
                            int part1_x = rcpart.right;
                            rcpart = rc_label;
                            rcpart.left = part1_x;
                            DrawText(lplvcd->nmcd.hdc, lvi.pszText + part1, part2 - part1, &rcpart, DT_CALCRECT | DT_LEFT | DT_VCENTER | DT_NOPREFIX | DT_EDITCONTROL | DT_SINGLELINE);
                            int part2_x = rcpart.right;

                            rcpart = rc_label;
                            DrawText(lplvcd->nmcd.hdc, lvi.pszText, part1, &rcpart, DT_LEFT | DT_VCENTER | DT_NOPREFIX | DT_EDITCONTROL | DT_SINGLELINE);

                            SetTextColor(lplvcd->nmcd.hdc, RGB(0, 150, 127));
                            rcpart = rc_label;
                            rcpart.left = part1_x;
                            DrawText(lplvcd->nmcd.hdc, lvi.pszText + part1, part2 - part1, &rcpart, DT_LEFT | DT_VCENTER | DT_NOPREFIX | DT_EDITCONTROL | DT_SINGLELINE);
                            SetTextColor(lplvcd->nmcd.hdc, isselected ? GetSysColor(COLOR_HIGHLIGHTTEXT) : GetSysColor(COLOR_WINDOWTEXT));
                            rcpart = rc_label;
                            rcpart.left = part2_x;
                            DrawText(lplvcd->nmcd.hdc, lvi.pszText + part2, textlen - part2, &rcpart, DT_LEFT | DT_VCENTER | DT_NOPREFIX | DT_EDITCONTROL | DT_SINGLELINE | DT_WORD_ELLIPSIS | DT_END_ELLIPSIS);

                            TREEVIEW_DrawItemLines(lplvcd->nmcd.hdc, &lvi, scrollX, &lplvcd->nmcd.rc, cwidth);
                        }
                        else
                        {
                            // SubItems 
                            ListView_GetSubItemRect(hwndListView, lplvcd->nmcd.dwItemSpec, iSubItem, LVIR_BOUNDS, &rc_label);
                            // отступ
                            rc_label.left += 6;
                            // Text
                            DrawText(lplvcd->nmcd.hdc, lvi.pszText, lstrlen(lvi.pszText), &rc_label, DT_LEFT | DT_VCENTER | DT_NOPREFIX | DT_EDITCONTROL | DT_SINGLELINE | DT_WORD_ELLIPSIS | DT_END_ELLIPSIS);
                        }

                        iSubItem++;
                    }

                    if (ListView_GetItemState(hwndListView, lplvcd->nmcd.dwItemSpec, LVIS_FOCUSED) & LVIS_FOCUSED) {
                        // ленточная рама
                        DrawFocusRect(lplvcd->nmcd.hdc, &lplvcd->nmcd.rc);
                    }
                    return CDRF_SKIPDEFAULT;
            }
            break;
        }


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
            /*default:
                return DefWindowProc(hWnd, message, wParam, lParam);*/
            }
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        break;
        
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
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
