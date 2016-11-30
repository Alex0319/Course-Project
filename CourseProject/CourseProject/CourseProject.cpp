// CourseProject.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"

#define MAX_LOADSTRING 100

using namespace Gdiplus;
// Глобальные переменные:
HINSTANCE hInst;								// текущий экземпляр
TCHAR szTitle[MAX_LOADSTRING];					// Текст строки заголовка
TCHAR szWindowClass[MAX_LOADSTRING];			// имя класса главного окна

PlayingField* playingField;
int mouseX = 0, mouseY = 0;
HBITMAP hBitmap;
BITMAP bm;

//GdiplusStartupInput startupInput = {0};
//ULONG_PTR token;
//Image* ourImage;
//HGLOBAL hGlobal;
//LPSTREAM pStream;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	ResultWindow(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: разместите код здесь.
	MSG msg;
	HACCEL hAccelTable;

	// Инициализация глобальных строк
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_COURSEPROJECT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);
	// Выполнить инициализацию приложения:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_COURSEPROJECT));

	// Цикл основного сообщения:
	while (GetMessage(&msg, NULL, 0, 0))
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
//  НАЗНАЧЕНИЕ: регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GAMEICON));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);;
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_COURSEPROJECT);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   НАЗНАЧЕНИЕ: сохраняет обработку экземпляра и создает главное окно.
//
//   КОММЕНТАРИИ:
//
//        В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится на экран главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;
   hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной
   int screenWidth = GetSystemMetrics(SM_CXSCREEN), screenHeight = GetSystemMetrics(SM_CYSCREEN);
   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME,
	   (screenWidth - WINDOW_WIDTH) / 2, (screenHeight - WINDOW_HEIGHT) / 2, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, hInstance, NULL);

//   startupInput.GdiplusVersion = 1;
//   GdiplusStartup(&token, &startupInput, NULL);
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
//  НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//
//  WM_COMMAND	- обработка меню приложения
//  WM_PAINT	-Закрасить главное окно
//  WM_DESTROY	 - ввести сообщение о выходе и вернуться.
//
//


void DrawScore(HDC hdc,int x)
{
	char buffer[100];
	SIZE scoreStringSize;
	HFONT newFont = CreateFont(35, 0, 0, 0, 350, 1, 0, 0,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Century Gothic"));
	COLORREF oldTextColor = SetTextColor(hdc, RGB(0, 144, 180));
	HFONT oldFont = SelectFont(hdc, newFont);
	SetBkMode(hdc, TRANSPARENT);
	sprintf_s(buffer, sizeof(buffer), "%d", playingField->GetCurrentScore());
	GetTextExtentPointA(hdc, buffer, strlen(buffer), &scoreStringSize);
	TabbedTextOutA(hdc, x - scoreStringSize.cx-5,FIELD_START-scoreStringSize.cy-10, buffer, strlen(buffer), 0, 0, 0);
	sprintf_s(buffer, sizeof(buffer), "%d", playingField->GetGameRecord());
	SetTextColor(hdc, RGB(72, 250, 5));
	TabbedTextOutA(hdc, x + 2*BLOCK_SIZE, FIELD_START - scoreStringSize.cy - 10, buffer, strlen(buffer), 0, 0, 0);
	SelectFont(hdc, oldFont);
	DeleteObject(newFont);
	SetTextColor(hdc, oldTextColor);
}


void InitResources(HWND hWnd)
{
	playingField = new PlayingField();
	hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_CUP));
	GetObject(hBitmap, sizeof(BITMAP), &bm);
}

void FreeResources()
{
	delete playingField;
	DeleteObject(hBitmap);
	//	delete ourImage;
//	GdiplusShutdown(token);
}

int UpdateScore(HWND hWnd,HDC hdc,COLORREF crTransparent,int x,int y)
{
//	Graphics* gh = new Graphics(hdc);
//	gh->DrawImage(ourImage, 20, 20);
//	delete gh;
	int result = BitmapModificator::CreateBitmapMask(hWnd, hBitmap, bm, hdc, crTransparent, x, y);
	return bm.bmWidth;
}

void Drawing(HWND hWnd,int mouseX,int mouseY)
{
	RECT windowRect;
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);
	HDC hdc2 = CreateCompatibleDC(hdc);
	HBITMAP hbm = CreateCompatibleBitmap(hdc, WINDOW_WIDTH, WINDOW_HEIGHT);
	HANDLE hold = SelectObject(hdc2, hbm);
	GetClientRect(hWnd, &windowRect);
	FillRect(hdc2, &windowRect, WHITE_BRUSH);
	int bitmapWidth = UpdateScore(hWnd, hdc2, RGB(0, 0, 0), (WINDOW_WIDTH - BLOCK_SIZE / 2) / 2, 5);
	DrawScore(hdc2, (WINDOW_WIDTH - bitmapWidth) / 2);
	playingField->UpdatePlayingField(hdc2, mouseX, mouseY);
	BitBlt(hdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc2, 0, 0, SRCCOPY);
	SelectObject(hdc2, hold);
	EndPaint(hWnd, &ps);
	DeleteObject(hbm);
	DeleteDC(hdc2);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	switch (message)
	{
		case WM_CREATE: InitResources(hWnd);
			break;
		case WM_COMMAND:
			wmId    = LOWORD(wParam);
			wmEvent = HIWORD(wParam);
			// Разобрать выбор в меню:
			switch (wmId)
			{
				case IDM_NEWGAME:
					playingField->InitializeNewGame();
					InvalidateRect(hWnd, NULL, FALSE);
					break;
				case IDM_ABOUT: DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
					break;
				case IDM_CLOSE:
					DestroyWindow(hWnd);
					break;
				default:
					return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_LBUTTONDOWN:
			SetCapture(hWnd);
			mouseX = GET_X_LPARAM(lParam);
			mouseY = GET_Y_LPARAM(lParam);
			if (playingField->CheckClientClick({ mouseX, mouseY }))
				InvalidateRect(hWnd, NULL, FALSE);
			break;
		case WM_MOUSEMOVE:
			mouseX = GET_X_LPARAM(lParam);
			mouseY = GET_Y_LPARAM(lParam);
			if (playingField->CheckFigureChoose())
				InvalidateRect(hWnd, NULL, FALSE);
			break;
		case WM_LBUTTONUP:
			ReleaseCapture();
			if (!playingField->TrySetChoosingFigure())
			{
				InvalidateRect(hWnd, NULL, FALSE);
				DialogBox(hInst, MAKEINTRESOURCE(IDD_SEERESULT), hWnd, ResultWindow);
				playingField->InitializeNewGame();
			}
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case WM_PAINT: Drawing(hWnd,mouseX,mouseY);
			break;
		case WM_DESTROY:
			FreeResources();
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

INT_PTR CALLBACK ResultWindow(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	const COLORREF dialogBackGroundColor = RGB(168, 211, 255);
	UNREFERENCED_PARAMETER(lParam);
	UNREFERENCED_PARAMETER(lParam);
	PAINTSTRUCT ps;
	char* currentPosString="Больше ходов нет";
	char buffer[100] = { "" };
	SIZE defaultStringSize,scoreStringSize;
	switch (message)
	{
		case WM_INITDIALOG:
			return (INT_PTR)TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDRECORDS_OK)
			{
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
			break;
		case WM_PAINT:
			RECT rect;
			GetClientRect(hDlg, &rect);
			int dialogWidth = rect.right - rect.left;
			HDC hdc = BeginPaint(hDlg, &ps);
			FillRect(hdc, &rect, WHITE_BRUSH);
			HFONT newFont = CreateFont(20, 0, 0, 0, 700, 1, 0, 0,
				DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Century Gothic"));
			HFONT oldFont = SelectFont(hdc, newFont);
			sprintf_s(buffer,sizeof(buffer), "%d", playingField->GetCurrentScore());
			GetTextExtentPointA(hdc, currentPosString, strlen(currentPosString), &defaultStringSize);
			GetTextExtentPointA(hdc, buffer, strlen(buffer), &scoreStringSize);
			UpdateScore(hDlg, hdc, RGB(0, 0, 0), dialogWidth / 2, 5);
			int startX = (dialogWidth - defaultStringSize.cx) / 2;
			TabbedTextOutA(hdc, startX+(defaultStringSize.cx-scoreStringSize.cx)/2, 90, buffer, strlen(buffer), 0, 0, 0);
			TabbedTextOutA(hdc, startX, 125, currentPosString, strlen(currentPosString), 0, 0, 0);
			SelectFont(hdc, oldFont);
			EndPaint(hDlg, &ps);
			DeleteObject(newFont);
			break;
	}
	return (INT_PTR)FALSE;
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
