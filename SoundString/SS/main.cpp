# include "stdafx.h"
# include "SS.h"

# pragma comment (lib, "opengl32.lib")
# pragma comment (lib, "glu32.lib")
# pragma comment (lib, "glaux.lib")
# pragma comment (lib, "ftgl_dynamic_MT.lib")

# pragma comment (lib, "DevIL.lib")
# pragma comment (lib, "ilut.lib")
# pragma comment (lib, "ilu.lib")

//#pragma comment(lib,"htmlhelp.lib")
//#include <htmlhelp.h>

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib,"comctl32.lib")
 
# include "main.h"
# include "camera.h"
# include "glelements_and_texture.h"
# include "sound.h"
# include "font.h"
# include "Grafics.h"
# include <cstdlib>

# if defined _STRINGPHYSICS_H && defined _CONTROL_H

# define kSpeed 10.0f
GLelements GLE;

bool SoundFlag = false; // treu - звук включен; false - звук выключен

Sound SD;
CTexture *Texture;

CCamera g_Camera;

CFont *Font;

// Необходимые дескрипторы:
HWND  g_hWnd;
RECT  g_rRect;
HDC   g_hDC;
HGLRC g_hRC;
HINSTANCE g_hInstance;

//залипание курсора
bool flag = false;

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;								// текущий экземпляр
TCHAR szTitle[MAX_LOADSTRING];					// Текст строки заголовка
TCHAR szWindowClass[MAX_LOADSTRING];			// имя класса главного окна
HWND hWnd;
MSG msg;
HWND hWndLogo;

LPSTRINGPARAM String;
LPCONTROL cont;
LPGRAFIC Gr;
//////////////WinApi & MainProgram///////////////
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	WinProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	WndProcGr(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
void DrawBackground(HWND hWndBGR, int ID_BGR, HINSTANCE hInst)
{
	HDC dc, bits;
	RECT rt;
	GetClientRect(hWndBGR, &rt);
	int maxX = rt.right, maxY = rt.bottom;
	dc = GetDC(hWndBGR);
	bits = CreateCompatibleDC(dc);
	HBITMAP BGR = LoadBitmap(hInst, MAKEINTRESOURCE(ID_BGR));
	SelectObject(bits, BGR);
	StretchBlt(dc, 0, 0, maxX, maxY, bits, 0, 0, maxX, maxY, SRCCOPY);
	DeleteDC(bits);
	ReleaseDC(hWndBGR, dc);
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	HACCEL hAccelTable;
	LoadString(hInstance, IDC_TEST, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);
#pragma region заставка
	WNDCLASS wc = {0};
	wc.lpszClassName = L"logo";
	wc.lpfnWndProc = DefWindowProc;
	wc.hCursor	= LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetSysColorBrush(COLOR_3DFACE);
	wc.hIcon	= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL));
	RegisterClass(&wc);


	hWndLogo = CreateWindow(L"logo", NULL, WS_POPUPWINDOW, GetSystemMetrics(SM_CXSCREEN) / 2.0f - 295, GetSystemMetrics(SM_CYSCREEN) / 2.0f - 200,
							590, 400, NULL, NULL, hInst, 0);
	// отображение заставки.
	ShowWindow(hWndLogo, nCmdShow);
	
	// замер времени
	LARGE_INTEGER b_start,b_stop,freq;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&b_start);

	// Отображение курсора.
	ShowCursor (true);

	if (!InitInstance (hInstance, nCmdShow))return FALSE;
	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TEST));
	// картинка
	DrawBackground( hWndLogo, IDB_LOGO, hInst);
#pragma endregion
#pragma region загрузка программы
	
	//
	int i = 0;
	int speed = 100;
	String = new STRINGPARAM();
	Gr = new GRAFIC(L"Энергия", hInst);
	cont = new CONTROL(hWnd, hInstance);
	cont->CreateInterfacePanel(WinProc);
	//
	InitOpenGL(cont->GetOGLHWND());
#pragma endregion
#pragma region закрытие заставки (обработка сообщений)
	while(1)
	{
		if ( PeekMessage ( &msg, NULL, 0, 0, PM_REMOVE ) )
		{
			if ( msg.message == WM_QUIT )				
				break;
			// выходит по нажатию клавиши(любой).
			if ( msg.message == WM_KEYDOWN || msg.message == WM_MBUTTONDOWN )
			{
				DestroyWindow(hWndLogo);
				break;
			}
			TranslateMessage ( &msg );
			DispatchMessage ( &msg );
		}
		// выходит после 10 секунд
		QueryPerformanceCounter(&b_stop);
		b_stop.QuadPart = (b_stop.QuadPart - b_start.QuadPart)/(freq.QuadPart);
		if(b_stop.QuadPart == 10)
		{
			DestroyWindow(hWndLogo);
			break;
		}
	}
#pragma endregion
#pragma region отображение главного окна
	ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
#pragma endregion
	return (int) MainLoop();
}
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TEST));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_TEST);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

   hWnd = CreateWindow(szWindowClass, L"Sound String", WS_OVERLAPPEDWINDOW,
      120, 50, 860, 650, NULL, NULL, hInstance, NULL);

   if (!hWnd)
      return FALSE;
   return TRUE;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	LONG    lRet = 0;
	switch (message)
	{
	case WM_GETMINMAXINFO: //Получили сообщение от Винды
       {
           MINMAXINFO *pInfo = (MINMAXINFO *)lParam;
           POINT Min = { 860, 600 };
           pInfo->ptMinTrackSize = Min; // Установили минимальный размер
           return lRet;
       }
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_E_m:
			Gr->OpenMsg(WndProcGr);
			break;
		case ID_HELP:
			//HtmlHelp( hWnd, L"help.chm::/Index.htm", HH_DISPLAY_TOPIC, NULL);
			break;
		default:
			lRet = cont->ReactionAllButtonsAndEdits(hWnd, message, wParam, lParam);
			if(cont->_message_typename)
			{
				String->Ctrl_Reaction(cont->_message_value, cont->_message_typename);
				Gr->Reset();
				String->t = 0;
				if(cont->_message_typename == 18)
					SoundFlag = !SoundFlag;
			}
			break;
		}
		break;
	case WM_SIZE:
		cont->MoveAllWnd();
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_HSCROLL:
		lRet = cont->ReactionAllTrackBars(hWnd, message, wParam, lParam);
		if(cont->_message_typename == 19)
			String->Ctrl_Reaction(cont->_message_value, 19);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return lRet;
}
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
LRESULT CALLBACK WinProc(HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LONG    lRet = 0;

    switch (uMsg)
	{
    case WM_SIZE:		// Если изменён размер окна
		SizeOpenGLScreen(LOWORD(lParam),HIWORD(lParam));// LoWord=Width, HiWord=Height
		GetClientRect(hWnd, &g_rRect);					// получаем window rectangle
        break; 
	case WM_MOUSEACTIVATE:
		flag = !flag;
		break;
	case WM_KEYDOWN:
		if(wParam==VK_ESCAPE)		// Если нажат ESCAPE
			PostQuitMessage(0);	// Выходим		
		break;
    case WM_CLOSE:		// Если окно было закрыто
        PostQuitMessage(0);	// Выходим
        break;	
    default:		// Return по умолчанию
        lRet = DefWindowProc (hWnd, uMsg, wParam, lParam);
        break;
    }
    return lRet;
}
WPARAM MainLoop()
{
	String->Create_First_String_Pos();
	int ind = 0;
	while(1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
			if(msg.message == WM_QUIT)
				break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
		else
		{
			if(flag)
			{
				g_Camera.SetViewByMouse ( );
				g_Camera.Update ( kSpeed );
			}
			if(String->Go)
			for(ind = 0; ind < String->timespeed; ind ++)
			{
				String->WaveProcess();
				if(!Gr->GetEnd())
					Gr->Push(String->t, String->Ep, String->Ek);
				else
				{
					String->t = 0;
					Gr->Reset();
				}
			}
			SD.set_frequency ( String -> v_nyu );
			SD.SoundString ( SoundFlag );
			RenderScene();
			if(Gr->Open)
				Gr->ReInit();
        }
	}
	DeInit ( );
	Gr->Deinit();

	return(msg.wParam);
}
LRESULT CALLBACK WndProcGr(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_DESTROY:
		CloseWindow(hWnd);
		if(hWnd == Gr->hWnd)
			Gr->Open = false;
		return 0;
	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_NUMPAD2:
			if ( Gr->correctY > 1 )	Gr->correctY--;
			break;
		case VK_NUMPAD4:
			if ( Gr->correctX > 1 ) Gr->correctX--;
			break;
		case VK_NUMPAD6:
			if ( Gr->correctX < 5 ) Gr->correctX++;
			break;
		case VK_NUMPAD8:
			if ( Gr->correctY < 5 ) Gr->correctY++;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
};
///////////Grafics & Sound//////////
void DrawCorrectLenghtString ( GLfloat l_segment, int segment, GLfloat radius )
{
	int y = 0;
	for ( float i = 0.0f; i < l_segment * segment; i+= l_segment, y++ )
		GLE.CreateOctagon ( i, String -> y [ y ] * 0.00825f, - 0.1f, l_segment, radius );
}
void NumViewCorrect ( int NUM, GLfloat X, GLfloat Y, GLfloat Z, int R, int G, int B )
{
	switch ( NUM )
	{
		case 0:	GLE.CreateTimeNum_0 ( X, Y, Z, 0.38f, 0.1f, 0.4f, R, G, B ); break;
		case 1:	GLE.CreateTimeNum_1 ( X, Y, Z, 0.38f, 0.1f, 0.4f, R, G, B ); break;
		case 2: GLE.CreateTimeNum_2 ( X, Y, Z, 0.38f, 0.1f, 0.4f, R, G, B ); break;
		case 3:	GLE.CreateTimeNum_3 ( X, Y, Z, 0.38f, 0.1f, 0.4f, R, G, B ); break;
		case 4:	GLE.CreateTimeNum_4 ( X, Y, Z, 0.38f, 0.1f, 0.4f, R, G, B ); break;
		case 5:	GLE.CreateTimeNum_5 ( X, Y, Z, 0.38f, 0.1f, 0.4f, R, G, B ); break;
		case 6:	GLE.CreateTimeNum_6 ( X, Y, Z, 0.38f, 0.1f, 0.4f, R, G, B ); break;
		case 7:	GLE.CreateTimeNum_7 ( X, Y, Z, 0.38f, 0.1f, 0.4f, R, G, B ); break;
		case 8: GLE.CreateTimeNum_8 ( X, Y, Z, 0.38f, 0.1f, 0.4f, R, G, B ); break;
		case 9:	GLE.CreateTimeNum_9 ( X, Y, Z, 0.38f, 0.1f, 0.4f, R, G, B ); break;
	}
}
void HELP_NUM_A ( int NumA100, int NumA10, int NumA1 )
{
	for ( float i = 21.15f; i <= 23.9f; i += 0.55f )
		NumViewCorrect ( 0, i, 1.5f, 0.56f, 5, 69, 0 );
	
	NumA100 = fmod ( String -> Ao, 1000 ) * 0.01;
	NumA10 = fmod ( String -> Ao, 100 ) * 0.1;
	NumA1 = fmod ( String -> Ao, 10 );
	
	if ( NumA100 == 0 )
		NumViewCorrect ( NumA100, 22.8f, 1.5f, 0.57f, 5, 69, 0 );
	else	
		NumViewCorrect ( NumA100, 22.8f, 1.5f, 0.57f, 167, 222, 0 );
	if ( NumA100 == 0 && NumA10 == 0 )
		NumViewCorrect ( NumA10, 23.35f, 1.5f, 0.57f, 5, 69, 0 );
	else
		NumViewCorrect ( NumA10, 23.35f, 1.5f, 0.57f, 167, 222, 0 );
	NumViewCorrect ( NumA1, 23.9f, 1.5f, 0.57f, 167, 222, 0 );
}
void HELP_NUM_L ( int NumL1000, int NumL100, int NumL10, int NumL1 )
{
	for ( float i = 21.15f; i <= 23.9f; i += 0.55f )
		NumViewCorrect ( 0, i, 0.0f, 0.56f, 5, 69, 0 );
	
	NumL1000 = fmod ( String -> l, 10000 ) * 0.001;
	NumL100 = fmod ( String -> l, 1000 ) * 0.01;
	NumL10 = fmod ( String -> l, 100 ) * 0.1;
	NumL1 = fmod ( String -> l, 10 );		

	if ( NumL1000 == 0 )
		NumViewCorrect ( NumL1000, 22.25f, 0.0f, 0.57f, 5, 69, 0 );
	else	
		NumViewCorrect ( NumL1000, 22.25f, 0.0f, 0.57f, 167, 222, 0 );	
	if ( NumL1000 == 0 && NumL100 == 0 )
		NumViewCorrect ( NumL100, 22.8f, 0.0f, 0.57f, 5, 69, 0 );
	else	
		NumViewCorrect ( NumL100, 22.8f, 0.0f, 0.57f, 167, 222, 0 );
	if ( NumL1000 == 0 && NumL100 == 0 && NumL10 == 0 )
		NumViewCorrect ( NumL10, 23.35f, 0.0f, 0.57f, 5, 69, 0 );
	else
		NumViewCorrect ( NumL10, 23.35f, 0.0f, 0.57f, 167, 222, 0 );
	NumViewCorrect ( NumL1, 23.9f, 0.0f, 0.57f, 167, 222, 0 );
}
void HELP_NUM_F ( int NumF10000, int NumF1000, int NumF100,	int NumF10,	int NumF1 )
{
	for ( float i = 21.15f; i <= 23.9f; i += 0.55f )
		NumViewCorrect ( 0, i, -1.5f, 0.56f, 5, 69, 0 );

	NumF10000 = String -> v_nyu * 0.0001;
	NumF1000 = fmod ( String -> v_nyu, 10000 ) * 0.001;
	NumF100 = fmod ( String -> v_nyu, 1000 ) * 0.01;
	NumF10 = fmod ( String -> v_nyu, 100 ) * 0.1;
	NumF1 = fmod ( String -> v_nyu, 10 );		

	if ( NumF10000 == 0 )
		NumViewCorrect ( NumF10000, 21.7f, -1.5f, 0.57f, 5, 69, 0 );
	else		
		NumViewCorrect ( NumF10000, 21.7f, -1.5f, 0.57f, 167, 222, 0 );	
	if ( NumF10000 == 0 && NumF1000 == 0 )
		NumViewCorrect ( NumF1000, 22.25f, -1.5f, 0.57f, 5, 69, 0 );
	else	
		NumViewCorrect ( NumF1000, 22.25f, -1.5f, 0.57f, 167, 222, 0 );	
	if ( NumF10000 == 0 && NumF1000 == 0 && NumF100 == 0 )
		NumViewCorrect ( NumF100, 22.8f, -1.5f, 0.57f, 5, 69, 0 );
	else	
		NumViewCorrect ( NumF100, 22.8f, -1.5f, 0.57f, 167, 222, 0 );
	if ( NumF10000 == 0 && NumF1000 == 0 && NumF100 == 0 && NumF10 == 0 )
		NumViewCorrect ( NumF10, 23.35f, -1.5f, 0.57f, 5, 69, 0 );
	else
		NumViewCorrect ( NumF10, 23.35f, -1.5f, 0.57f, 167, 222, 0 );
	NumViewCorrect ( NumF1, 23.9f, -1.5f, 0.57f, 167, 222, 0 );
}
void HELP_NUM_O ( int NumO, int &NOT )
{
	for ( float i = 21.15f; i <= 23.9f; i += 0.55f )
		NumViewCorrect ( 0, i, -3.0f, 0.56f, 5, 69, 0 );

	NumO = String -> v_nyu;

	if ( NumO >= 32 && NumO <= 65 )
	{
		NumViewCorrect ( 1, 23.9f, -3.0f, 0.57f, 167, 222, 0 );
		NOT = 26;
		return;
	}
	if ( NumO >= 65 && NumO <= 131 )
	{
		NumViewCorrect ( 2, 23.9f, -3.0f, 0.57f, 167, 222, 0 );
		NOT = 27;
		return;
	}
	if ( NumO >= 131 && NumO <= 261 )
	{
		NumViewCorrect ( 3, 23.9f, -3.0f, 0.57f, 167, 222, 0 );
		NOT = 28;
		return;
	}
	if ( NumO >= 261 && NumO <= 523 )
	{
		NumViewCorrect ( 4, 23.9f, -3.0f, 0.57f, 167, 222, 0 );
		NOT = 29;
		return;
	}
	if ( NumO >= 523 && NumO <= 1046 )
	{
		NumViewCorrect ( 5, 23.9f, -3.0f, 0.57f, 167, 222, 0 );
		NOT = 30;
		return;
	}
	if ( NumO >= 1046 && NumO <= 2093 )
	{
		NumViewCorrect ( 6, 23.9f, -3.0f, 0.57f, 167, 222, 0 );
		NOT = 31;
		return;
	}
	if ( NumO >= 2093 && NumO <= 4186 )
	{
		NumViewCorrect ( 7, 23.9f, -3.0f, 0.57f, 167, 222, 0 );
		NOT = 32;
		return;
	}
	if ( NumO >= 4186 && NumO <= 8375 )
	{
		NumViewCorrect ( 8, 23.9f, -3.0f, 0.57f, 167, 222, 0 );
		NOT = 33;
		return;
	}
	if ( NumO >= 8375 && NumO <= 16749 )
	{
		NumViewCorrect ( 9, 23.9f, -3.0f, 0.57f, 167, 222, 0 );
		NOT = 34;
		return;
	}
	if ( NumO >= 16749 && NumO <= 33497 )
	{
		NumViewCorrect ( 1, 23.35f, -3.0f, 0.57f, 167, 222, 0 );
		NumViewCorrect ( 0, 23.9f, -3.0f, 0.57f, 167, 222, 0 );
		NOT = 35;
		return;
	}
}
void CorrectNoteLine ( GLfloat F )
{
	GLfloat Correct = 0.0f;
	float norm = 16.291 / 7;
	if ( F < 32 )
	{
		Correct = 0.0f;
		GLE.CreateQuadNoteLine ( 1.894f + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}	
#pragma region AAAA
	if(F>=32 && F<36)
	{
		Correct=0.581821*(F-32);
		GLE.CreateQuadNoteLine ( 1.894f + norm*0 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=36 && F<41)
	{
		Correct=0.465457*(F-36);
		GLE.CreateQuadNoteLine ( 1.894f + norm*1 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=41 && F<43)
	{
		Correct=1.163643*(F-41);
		GLE.CreateQuadNoteLine ( 1.894f + norm*2 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=43 && F<49)
	{
		Correct=0.387881*(F-43);
		GLE.CreateQuadNoteLine ( 1.894f + norm*3 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=49 && F<55)
	{
		Correct=0.387881*(F-49);
		GLE.CreateQuadNoteLine ( 1.894f + norm*4 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=55 && F<61)
	{
		Correct=0.387881*(F-55);
		GLE.CreateQuadNoteLine ( 1.894f + norm*5 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=61 && F<65)
	{
		Correct=0.581821*(F-61);
		GLE.CreateQuadNoteLine ( 1.894f + norm*6 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=65 && F<73)
	{
		Correct=0.290911*(F-65);
		GLE.CreateQuadNoteLine ( 1.894f + norm*0 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=73 && F<82)
	{
		Correct=0.258587*(F-73);
		GLE.CreateQuadNoteLine ( 1.894f + norm*1 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=82 && F<87)
	{
		Correct=0.465457*(F-82);
		GLE.CreateQuadNoteLine ( 1.894f + norm*2 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=87 && F<98)
	{
		Correct=0.211571*(F-87);
		GLE.CreateQuadNoteLine ( 1.894f + norm*3 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=98 && F<110)
	{
		Correct=0.193940*(F-98);
		GLE.CreateQuadNoteLine ( 1.894f + norm*4 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=110 && F<123)
	{
		Correct=0.179022*(F-110);
		GLE.CreateQuadNoteLine ( 1.894f + norm*5 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=123 && F<131)
	{
		Correct=0.290911*(F-123);
		GLE.CreateQuadNoteLine ( 1.894f + norm*6 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=131 && F<146)
	{
		Correct=0.155152*(F-131);
		GLE.CreateQuadNoteLine ( 1.894f + norm*0 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=146 && F<164)
	{
		Correct=0.290911*(F-146);
		GLE.CreateQuadNoteLine ( 1.894f + norm*1 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=164 && F<174)
	{
		Correct=0.232729*(F-164);
		GLE.CreateQuadNoteLine ( 1.894f + norm*2 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=174 && F<196)
	{
		Correct=0.193940*(F-174);
		GLE.CreateQuadNoteLine ( 1.894f + norm*3 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=196 && F<220)
	{
		Correct=0.096970*(F-196);
		GLE.CreateQuadNoteLine ( 1.894f + norm*4 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=220 && F<246)
	{
		Correct=0.089511*(F-220);
		GLE.CreateQuadNoteLine ( 1.894f + norm*5 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=246 && F<261)
	{
		Correct=0.155152*(F-246);
		GLE.CreateQuadNoteLine ( 1.894f + norm*6 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=261 && F<293)
	{
		Correct=0.083117*(F-261);
		GLE.CreateQuadNoteLine ( 1.894f + norm*0 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=293 && F<329)
	{
		Correct=0.064647*(F-293);
		GLE.CreateQuadNoteLine ( 1.894f + norm*1 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=329 && F<349)
	{
		Correct=0.116364*(F-329);
		GLE.CreateQuadNoteLine ( 1.894f + norm*2 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=349 && F<391)
	{
		Correct=0.055412*(F-349);
		GLE.CreateQuadNoteLine ( 1.894f + norm*3 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=391 && F<440)
	{
		Correct=0.047496*(F-391);
		GLE.CreateQuadNoteLine ( 1.894f + norm*4 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=440 && F<493)
	{
		Correct=0.043911*(F-440);
		GLE.CreateQuadNoteLine ( 1.894f + norm*5 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=493 && F<523)
	{
		Correct=0.077576*(F-493);
		GLE.CreateQuadNoteLine ( 1.894f + norm*6 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=523 && F<587)
	{
		Correct=0.043098*(F-523);
		GLE.CreateQuadNoteLine ( 1.894f + norm*0 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=587 && F<659)
	{
		Correct=0.032323*(F-587);
		GLE.CreateQuadNoteLine ( 1.894f + norm*1 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=659 && F<698)
	{
		Correct=0.059674*(F-659);
		GLE.CreateQuadNoteLine ( 1.894f + norm*2 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=698 && F<783)
	{
		Correct=0.027380*(F-698);
		GLE.CreateQuadNoteLine ( 1.894f + norm*3 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=783 && F<880)
	{
		Correct=0.023993*(F-783);
		GLE.CreateQuadNoteLine ( 1.894f + norm*4 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=880 && F<987)
	{
		Correct=0.021750*(F-880);
		GLE.CreateQuadNoteLine ( 1.894f + norm*5 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=987 && F<1046)
	{
		Correct=0.039446*(F-987);
		GLE.CreateQuadNoteLine ( 1.894f + norm*6 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=1046 && F<1174)
	{
		Correct=0.018182*(F-1046);
		GLE.CreateQuadNoteLine ( 1.894f + norm*0 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=1174 && F<1318)
	{
		Correct=0.016162*(F-1174);
		GLE.CreateQuadNoteLine ( 1.894f + norm*1 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=1318 && F<1396)
	{
		Correct=0.029837*(F-1318);
		GLE.CreateQuadNoteLine ( 1.894f + norm*2 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=1396 && F<1567)
	{
		Correct=0.013610*(F-1396);
		GLE.CreateQuadNoteLine ( 1.894f + norm*3 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=1567 && F<1760)
	{
		Correct=0.012058*(F-1567);
		GLE.CreateQuadNoteLine ( 1.894f + norm*4 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=1760 && F<1975)
	{
		Correct=0.010343*(F-1760);
		GLE.CreateQuadNoteLine ( 1.894f + norm*5 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=1975 && F<2093)
	{
		Correct=0.019723*(F-1975);
		GLE.CreateQuadNoteLine ( 1.894f + norm*6 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=2093 && F<2349)
	{
		Correct=0.009091*(F-2093);
		GLE.CreateQuadNoteLine ( 1.894f + norm*0 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=2349 && F<2637)
	{
		Correct=0.008081*(F-2349);
		GLE.CreateQuadNoteLine ( 1.894f + norm*1 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=2637 && F<2793)
	{
		Correct=0.014918*(F-2637);
		GLE.CreateQuadNoteLine ( 1.894f + norm*2 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=2793 && F<3135)
	{
		Correct=0.006805*(F-2793);
		GLE.CreateQuadNoteLine ( 1.894f + norm*3 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=3135 && F<3520)
	{
		Correct=0.006045*(F-3135);
		GLE.CreateQuadNoteLine ( 1.894f + norm*4 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=3520 && F<3951)
	{
		Correct=0.005400*(F-3520);
		GLE.CreateQuadNoteLine ( 1.894f + norm*5 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=3951 && F<4186)
	{
		Correct=0.009903*(F-3951);
		GLE.CreateQuadNoteLine ( 1.894f + norm*6 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=4186 && F<4698)
	{
		Correct=0.004545*(F-4186);
		GLE.CreateQuadNoteLine ( 1.894f + norm*0 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=4698 && F<5274)
	{
		Correct=0.004040*(F-4698);
		GLE.CreateQuadNoteLine ( 1.894f + norm*1 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=5274 && F<5586)
	{
		Correct=0.007459*(F-5274);
		GLE.CreateQuadNoteLine ( 1.894f + norm*2 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=5586 && F<6270)
	{
		Correct=0.003402*(F-5586);
		GLE.CreateQuadNoteLine ( 1.894f + norm*3 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=6270 && F<7040)
	{
		Correct=0.003022*(F-6270);
		GLE.CreateQuadNoteLine ( 1.894f + norm*4 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=7040 && F<7902)
	{
		Correct=0.002700*(F-7040);
		GLE.CreateQuadNoteLine ( 1.894f + norm*5 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=7902 && F<8375)
	{
		Correct=0.004920*(F-7902);
		GLE.CreateQuadNoteLine ( 1.894f + norm*6 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=8375 && F<9396)
	{
		Correct=0.002279*(F-8375);
		GLE.CreateQuadNoteLine ( 1.894f + norm*0 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=9396 && F<10548)
	{
		Correct=0.002212*(F-9396);
		GLE.CreateQuadNoteLine ( 1.894f + norm*1 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=10548 && F<11172)
	{
		Correct=0.003730*(F-10548);
		GLE.CreateQuadNoteLine ( 1.894f + norm*2 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=11172 && F<12540)
	{
		Correct=0.001701*(F-11172);
		GLE.CreateQuadNoteLine ( 1.894f + norm*3 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=12540 && F<14080)
	{
		Correct=0.001511*(F-12540);
		GLE.CreateQuadNoteLine ( 1.894f + norm*4 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=14080 && F<15804)
	{
		Correct=0.001350*(F-14080);
		GLE.CreateQuadNoteLine ( 1.894f + norm*5 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=15804 && F<16749)
	{
		Correct=0.002463*(F-15804);
		GLE.CreateQuadNoteLine ( 1.894f + norm*6 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=16749 && F<18792)
	{
		Correct=0.001139*(F-16749);
		GLE.CreateQuadNoteLine ( 1.894f + norm*0 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=18792 && F<21096)
	{
		Correct=0.001010*(F-18792);
		GLE.CreateQuadNoteLine ( 1.894f + norm*1 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=21096 && F<22344)
	{
		Correct=0.001865*(F-21096);
		GLE.CreateQuadNoteLine ( 1.894f + norm*2 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=22344 && F<25080)
	{
		Correct=0.000851*(F-22344);
		GLE.CreateQuadNoteLine ( 1.894f + norm*3 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=25080 && F<28160)
	{
		Correct=0.000756*(F-25080);
		GLE.CreateQuadNoteLine ( 1.894f + norm*4 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=28160 && F<31608)
	{
		Correct=0.000675*(F-28160);
		GLE.CreateQuadNoteLine ( 1.894f + norm*5 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}
	if(F>=31608 && F<33497)
	{
		Correct=0.001232*(F-31608);
		GLE.CreateQuadNoteLine ( 1.894f + norm*6 + Correct, 0.0f, 0.0f, 255, 0, 0 );
		return;
	}

#pragma endregion
}
void RenderScene ( )
{	
# pragma region Инициализация переменных для числовых дисплеев
	int NumA100 = 0;
	int NumA10 = 0;
	int NumA1 = 0;
	
	int NumL1000 = 0;
	int NumL100 = 0;
	int NumL10 = 0;
	int NumL1 = 0;

	int NumF10000 = 0;
	int NumF1000 = 0;
	int NumF100 = 0;
	int NumF10 = 0;
	int NumF1 = 0;	

	int NumO = 0;
# pragma endregion

	int NOT = 26;
	GLfloat radius = 0.008f;

	glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
	glLoadIdentity ( );
	
	GLfloat length = String -> l * 0.00007265625f;

	glClearColor ( 0.95f, 0.95f, 0.95f, 1 );

	glInitNames ( );
	
	g_Camera.Look ( );

	HELP_NUM_A ( NumA100, NumA10, NumA1 );
	HELP_NUM_L ( NumL1000, NumL100, NumL10, NumL1 );	
	HELP_NUM_F ( NumF10000, NumF1000, NumF100, NumF10, NumF1 );
	HELP_NUM_O ( NumO, NOT );

	GLE.CreateBigStend ( Texture, NOT );
	GLE.CreateHolderStrings ( Texture, 0.5f, 0.0f, 0.025f );
	glTranslatef ( 0.7f, 0.225f, 0.4f );
	if ( String -> p > 1.3f )
		DrawCorrectLenghtString ( length, 256, String -> p * 0.007f );	// max радиус струны 0.04
	else
		DrawCorrectLenghtString ( length, 256, radius );	// max радиус струны 0.04
	glTranslatef ( -0.7f, -0.225f, -0.4f );
	glTranslatef ( length * 256 + 0.7f, 0.0f, 0.0f );
	GLE.CreateHolderStrings ( Texture, 0.0f, 0.0f, 0.025f );
	glTranslatef ( - length * 256 - 0.7f, 0.0f, 0.0f );
	CorrectNoteLine ( String -> v_nyu );

	glMatrixMode ( GL_PROJECTION );
	glPushMatrix ( );
	glLoadIdentity ( );
	glOrtho ( 0, 800, 0, 600, 0, 1 );
	glMatrixMode ( GL_MODELVIEW );
	glLoadIdentity ( );

	wchar_t Buffer [ 256 ];
	glDisable ( GL_DEPTH_TEST );
		glColor3f ( 0.0f, 0.0f, 0.0f );		
		swprintf ( Buffer, sizeof ( Buffer ), L"Время: %.3f, с", String->t );
		Font -> Font -> FaceSize ( 20 );
		Font -> Print ( 40, 45, Buffer );  
	glEnable ( GL_DEPTH_TEST );

	glMatrixMode ( GL_PROJECTION );
	glPopMatrix ( );
	glMatrixMode ( GL_MODELVIEW );

	glFlush();

	SwapBuffers ( g_hDC );
} 
void InitOpenGL (HWND hWnd)
{
	g_hWnd = hWnd;
	GetClientRect(g_hWnd, &g_rRect);
	InitializeOpenGL(g_rRect.right, g_rRect.bottom);
	
	Texture = new CTexture ( );
	Texture -> InitTextures ( Texture );

	Font = new CFont ( "framd.ttf", 10, 10 );

	g_Camera.PositionCamera ( 12.5f, -1.5f, 18.0f,	12.5, -1.5, 1,	0, 1, 0);	
}

# endif