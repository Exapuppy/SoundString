# include "stdafx.h"
# include "Control.h"
# include "resource.h"

# ifdef _CONTROL_H

tagCONTROL::tagCONTROL( __in HWND hWnd, __in HINSTANCE hInstance)
{
	InitCommonControls();
	set_hInstance(hInstance);
	set_hWnd(hWnd);
	RECT rt;
	GetClientRect (_hWnd, &rt);
	maxX = rt.right, maxY = rt.bottom;
	FmaxX = maxX; FmaxY = maxY;
	ZeroMemory(FirstEditsIndex,sizeof(bool)*5);
}

void tagCONTROL::set_hWnd( __in HWND hWnd)
{
	_hWnd = hWnd;
}
void tagCONTROL::set_hInstance( __in HINSTANCE hInst)
{
	_hInst = hInst;
}

void tagCONTROL::set_Font( __in LPCWSTR font_name, __in int Height)
{
	hFont = CreateFont(	Height, 0, 0, 0, 500, 
						0, 0, 0, 1, 0, 
						CLIP_DEFAULT_PRECIS, PROOF_QUALITY,  
						FIXED_PITCH, font_name);
}

void tagCONTROL::Font_to_Ctrl_Buttons()
{
	set_Font(L"MS Sans Serif",14);
	SendMessage( ButtonStop, WM_SETFONT, (WPARAM) hFont, 0 );
	SendMessage( ButtonStandart, WM_SETFONT, (WPARAM) hFont, 0 );
}
void tagCONTROL::Font_to_Ctrl_StringParam()
{
	set_Font(L"Arial",16);

	SendMessage( L_Ed, WM_SETFONT, (WPARAM) hFont, 0 );
	SendMessage( p_Ed, WM_SETFONT, (WPARAM) hFont, 0 );
	SendMessage( Fn_Ed, WM_SETFONT, (WPARAM) hFont, 0 );
	SendMessage( Ao_Ed, WM_SETFONT, (WPARAM) hFont, 0 );

	set_Font(L"Arial",14);

	SendMessage( L_St, WM_SETFONT, (WPARAM) hFont, 0 );
	SendMessage( p_St, WM_SETFONT, (WPARAM) hFont, 0 );
	SendMessage( Fn_St, WM_SETFONT, (WPARAM) hFont, 0 );
	SendMessage( Ao_St, WM_SETFONT, (WPARAM) hFont, 0 );
	
	set_Font(L"Arial", 10);
	
	SendMessage( L_UpB, WM_SETFONT, (WPARAM) hFont, 0 );
	SendMessage( p_UpB, WM_SETFONT, (WPARAM) hFont, 0 );
	SendMessage( Fn_UpB, WM_SETFONT, (WPARAM) hFont, 0 );
	SendMessage( Ao_UpB, WM_SETFONT, (WPARAM) hFont, 0 );

	SendMessage( L_DownB, WM_SETFONT, (WPARAM) hFont, 0 );
	SendMessage( p_DownB, WM_SETFONT, (WPARAM) hFont, 0 );
	SendMessage( Fn_DownB, WM_SETFONT, (WPARAM) hFont, 0 );
	SendMessage( Ao_DownB, WM_SETFONT, (WPARAM) hFont, 0 );
	
	SendMessage( L_St1, WM_SETFONT, (WPARAM) hFont, 0 );
	SendMessage( p_St1, WM_SETFONT, (WPARAM) hFont, 0 );
	SendMessage( Ao_St1, WM_SETFONT, (WPARAM) hFont, 0 );
}
void tagCONTROL::Font_to_TimeTB()
{
	set_Font(L"MS Sans Serif",14);
	SendMessage( time_St, WM_SETFONT, (WPARAM) hFont, 0 );
	SendMessage( time_St2, WM_SETFONT, (WPARAM) hFont, 0 );
}
void tagCONTROL::Font_to_volTB()
{
	set_Font(L"MS Sans Serif",12);
	SendMessage( vol_CB, WM_SETFONT, (WPARAM) hFont, 0 );
	SendMessage( vol_St, WM_SETFONT, (WPARAM) hFont, 0 );
}

void tagCONTROL::CreateButtons()
{
	ButtonStop = CreateWindow	(L"button",	L"Остановить",	WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|BS_PUSHBUTTON,	maxX - 105, maxY - 100,	100, 40,	_hWnd,(HMENU)ButtonStop_ID,	   _hInst,NULL);
	//ButtonSetting = CreateWindow(L"button",	L"Настройка",	WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|BS_PUSHBUTTON,	maxX - 105, maxY - 75,	100, 30,	_hWnd,(HMENU)ButtonSetting_ID, _hInst,NULL);
	ButtonStandart = CreateWindow(L"button",L"По умолчанию",WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|BS_PUSHBUTTON,	maxX - 105, maxY - 50,	100, 40,	_hWnd,(HMENU)ButtonStandart_ID,_hInst,NULL);
	Font_to_Ctrl_Buttons();
}
void tagCONTROL::CreateOGLWindow( __in WNDPROC WndProc1)
{
	WNDCLASS wndclass;
	memset ( &wndclass, 0, sizeof ( WNDCLASS ) );
	wndclass.style			= CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc	= WndProc1;
	wndclass.hbrBackground	= CreateSolidBrush(RGB(255,255,255));
	wndclass.lpszClassName	= L"OGLWNDCL";
	wndclass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	RegisterClass ( &wndclass );


	OGL = CreateWindow( L"OGLWNDCL", NULL, WS_CHILD|WS_CLIPSIBLINGS|WS_VISIBLE, 0, 0,maxX, maxY - 130,	_hWnd, (HMENU) OGL_ID, _hInst, NULL);
}
void tagCONTROL::CreateStringParamOption()
{
	L_TB = CreateWindow(TRACKBAR_CLASS, NULL, WS_CHILD|WS_VISIBLE|TBS_HORZ|TBS_TOOLTIPS,	20, maxY - 33, 240, 30,	_hWnd,(HMENU)L_TB_ID, _hInst, NULL);
	SendMessage(L_TB, TBM_SETRANGE,	(WPARAM) TRUE,	(LPARAM) MAKELONG(10, 1000));		// min. & max. positions
    SendMessage(L_TB, TBM_SETPAGESIZE, 0, (LPARAM) 1);					// скорость перетаскивания бегунка
	SendMessage(L_TB, TBM_SETSEL,(WPARAM) FALSE,(LPARAM) MAKELONG(0, 1)); 
	SendMessage(L_TB, TBM_SETPOS,(WPARAM) TRUE,	(LPARAM) 1000);					// положение бегунка
	L_St = CreateWindow(L"static",L"Длина, 10    м",		WS_CHILD|WS_VISIBLE|SS_CENTER,	25, maxY - 48, 75,15,	_hWnd,(HMENU)0,_hInst,NULL);
	L_St1 = CreateWindow(L"static",L"-3",	WS_CHILD|WS_VISIBLE|SS_CENTER,	78, maxY - 50, 10,10,	_hWnd,(HMENU)0,_hInst,NULL);
	L_Ed = CreateWindow(L"edit", L"1000",	WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_BORDER|ES_LEFT|ES_AUTOHSCROLL,	262, maxY - 33,	50, 20,	_hWnd,(HMENU)L_Ed_ID, _hInst, NULL);
	L_UpB = CreateWindow(L"button",L"Ʌ",	WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|BS_PUSHBUTTON,						314, maxY - 33,	14, 11,	_hWnd,(HMENU)L_UpB_ID,_hInst,NULL);
	L_DownB = CreateWindow(L"button",L"V",	WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|BS_PUSHBUTTON,						314, maxY - 23,	14, 11,	_hWnd,(HMENU)L_DownB_ID,_hInst,NULL);
	
	p_TB = CreateWindow(TRACKBAR_CLASS, NULL, WS_CHILD|WS_VISIBLE|TBS_HORZ|TBS_TOOLTIPS,	335, maxY - 33, 170, 30,	_hWnd,(HMENU)p_TB_ID, _hInst, NULL);
	SendMessage(p_TB, TBM_SETRANGE,	(WPARAM) TRUE,	(LPARAM) MAKELONG(1, 50));
    SendMessage(p_TB, TBM_SETPAGESIZE, 0, (LPARAM) 1);
	SendMessage(p_TB, TBM_SETSEL,(WPARAM) FALSE,(LPARAM) MAKELONG(0, 10)); 
	SendMessage(p_TB, TBM_SETPOS,(WPARAM) TRUE,	(LPARAM) 10);
	p_St = CreateWindow(L"static",L"Плотность, 10   гр/мм",		WS_CHILD|WS_VISIBLE|SS_CENTER,	345, maxY - 48, 113,15,	_hWnd,(HMENU)0,_hInst,NULL);
	p_St1= CreateWindow(L"static",L"-1",		WS_CHILD|WS_VISIBLE|SS_CENTER,	419, maxY - 50, 10,10,	_hWnd,(HMENU)0,_hInst,NULL);
	p_Ed = CreateWindow(L"edit", L"10",	WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_BORDER|ES_LEFT|ES_AUTOHSCROLL,	510, maxY - 33,	40, 20,	_hWnd,(HMENU)p_Ed_ID, _hInst, NULL);
	p_UpB = CreateWindow(L"button",L"Ʌ",	WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|BS_PUSHBUTTON,						552, maxY - 33,	14, 11,	_hWnd,(HMENU)p_UpB_ID,_hInst,NULL);
	p_DownB = CreateWindow(L"button",L"V",	WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|BS_PUSHBUTTON,						552, maxY - 23,	14, 11,	_hWnd,(HMENU)p_DownB_ID,_hInst,NULL);
	
	Fn_TB = CreateWindow(TRACKBAR_CLASS, NULL, WS_CHILD|WS_VISIBLE|TBS_HORZ|TBS_TOOLTIPS,	335, maxY - 78, 170, 30,	_hWnd,(HMENU)Fn_TB_ID, _hInst, NULL);
	SendMessage(Fn_TB, TBM_SETRANGE,	(WPARAM) TRUE,	(LPARAM) MAKELONG(1, 5000));		// min. & max. positions
    SendMessage(Fn_TB, TBM_SETPAGESIZE, 0, (LPARAM) 1);					// скорость перетаскивания бегунка
	SendMessage(Fn_TB, TBM_SETSEL,(WPARAM) FALSE,(LPARAM) MAKELONG(0, 10)); 
	SendMessage(Fn_TB, TBM_SETPOS,(WPARAM) TRUE,	(LPARAM) 40);					// положение бегунка
	Fn_St = CreateWindow(L"static",L"Натяжение, H",		WS_CHILD|WS_VISIBLE|SS_CENTER,	345, maxY - 94, 70,15,	_hWnd,(HMENU)0,_hInst,NULL);
	Fn_Ed = CreateWindow(L"edit", L"40",	WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_BORDER|ES_LEFT|ES_AUTOHSCROLL,	510, maxY - 78,	40, 20,	_hWnd,(HMENU)Fn_Ed_ID, _hInst, NULL);
	Fn_UpB = CreateWindow(L"button",L"Ʌ",	WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|BS_PUSHBUTTON,						552, maxY - 78,	14, 11,	_hWnd,(HMENU)Fn_UpB_ID,_hInst,NULL);
	Fn_DownB = CreateWindow(L"button",L"V",	WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|BS_PUSHBUTTON,						552, maxY - 68,	14, 11,	_hWnd,(HMENU)Fn_DownB_ID,_hInst,NULL);
	
	Ao_TB = CreateWindow(TRACKBAR_CLASS, NULL, WS_CHILD|WS_VISIBLE|TBS_HORZ|TBS_TOOLTIPS,	20, maxY - 78, 240, 30,	_hWnd,(HMENU)Ao_TB_ID, _hInst, NULL);
	SendMessage(Ao_TB, TBM_SETRANGE,	(WPARAM) TRUE,	(LPARAM) MAKELONG(1, 100));		// min. & max. positions
    SendMessage(Ao_TB, TBM_SETPAGESIZE, 0, (LPARAM) 1);					// скорость перетаскивания бегунка
	SendMessage(Ao_TB, TBM_SETSEL,(WPARAM) FALSE,(LPARAM) MAKELONG(0, 10)); 
	SendMessage(Ao_TB, TBM_SETPOS,(WPARAM) TRUE,	(LPARAM) 100);					// положение бегунка
	Ao_St = CreateWindow(L"static",L"Амплитуда, 10    м",		WS_CHILD|WS_VISIBLE|SS_CENTER,	30, maxY - 94, 100,15,	_hWnd,(HMENU)0,_hInst,NULL);
	Ao_St1 = CreateWindow(L"static",L"-3",	WS_CHILD|WS_VISIBLE|SS_CENTER,						108, maxY - 98, 10,15,	_hWnd,(HMENU)0,_hInst,NULL);
	Ao_Ed = CreateWindow(L"edit", L"100",	WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_BORDER|ES_LEFT|ES_AUTOHSCROLL,	262, maxY - 78,	50, 20,	_hWnd,(HMENU)Ao_Ed_ID, _hInst, NULL);
	Ao_UpB = CreateWindow(L"button",L"Ʌ",	WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|BS_PUSHBUTTON,						314, maxY - 78,	14, 11,	_hWnd,(HMENU)Ao_UpB_ID,_hInst,NULL);
	Ao_DownB = CreateWindow(L"button",L"V",	WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|BS_PUSHBUTTON,						314, maxY - 68,	14, 11,	_hWnd,(HMENU)Ao_DownB_ID,_hInst,NULL);
	Font_to_Ctrl_StringParam();
}
void tagCONTROL::CreateTimeSpeedPanel()
{
	time_St = CreateWindow(L"static",L"Время:        %",	WS_CHILD|WS_VISIBLE|SS_CENTER,	587, maxY - 48, 70,15,	_hWnd,(HMENU)0,_hInst,NULL);
	time_St2 = CreateWindow(L"static",L"1",	WS_CHILD|WS_VISIBLE|SS_CENTER,	627, maxY - 48, 20,15,	_hWnd,(HMENU)0,_hInst,NULL);
	time_TB = CreateWindow(TRACKBAR_CLASS, NULL, WS_CHILD|WS_VISIBLE|TBS_HORZ|TBS_TOOLTIPS,	577, maxY - 33, 160, 30,	_hWnd,(HMENU)time_TB_ID, _hInst, NULL);
	SendMessage(time_TB, TBM_SETRANGE,	(WPARAM) TRUE,	(LPARAM) MAKELONG(0, 100));		// min. & max. positions
    SendMessage(time_TB, TBM_SETPAGESIZE, 0,				(LPARAM) 10);					// скорость перетаскивания бегунка
	SendMessage(time_TB, TBM_SETSEL,		(WPARAM) FALSE,	(LPARAM) MAKELONG(0, 10)); 
	SendMessage(time_TB, TBM_SETPOS,		(WPARAM) TRUE,	(LPARAM) 1);					// положение бегунка
	Font_to_TimeTB();
}
void tagCONTROL::CreateVolumeButton()
{
	vol_St = CreateWindow(L"static",L"Звук",	WS_CHILD|WS_VISIBLE|SS_CENTER,			610, maxY - 75, 30, 15,	_hWnd,(HMENU)0,_hInst,NULL);
	vol_CB = CreateWindow(L"button",NULL, WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|BS_AUTOCHECKBOX, 650, maxY - 75, 15, 15,_hWnd,(HMENU)vol_CB_ID,_hInst, NULL);
	Font_to_volTB();
}
void tagCONTROL::MoveAllWnd()
{
	RECT rt;
	GetClientRect (_hWnd, &rt);
	maxX = rt.right, maxY = rt.bottom;
	float kx = (float)maxX / (float)FmaxX;
	kx = kx*sqrt(sqrt(kx));
	MoveWindow(ButtonStop,			maxX - 105, maxY - 110,	100, 40,	true);
	MoveWindow(ButtonStandart,		maxX - 105, maxY - 55,	100, 40,	true);

	MoveWindow(OGL,					0, 0,maxX, maxY - 130,	true);

	MoveWindow(L_TB,			20, maxY - 33, 240*kx, 30,	true);
	MoveWindow(L_St,			25, maxY - 48, 75,15,	true);
	MoveWindow(L_St1,			78, maxY - 50, 10,10,	true);
	MoveWindow(L_Ed,			262*kx, maxY - 33,	50*kx, 20,	true);
	MoveWindow(L_UpB,			314*kx, maxY - 33,	14, 11,	true);
	MoveWindow(L_DownB,			314*kx, maxY - 23,	14, 11,	true);

	MoveWindow(Ao_TB,			20, maxY - 78, 240*kx, 30,	true);
	MoveWindow(Ao_St,			30, maxY - 94, 100,15,	true);
	MoveWindow(Ao_St1,			108, maxY - 98, 10,15,	true);
	MoveWindow(Ao_Ed,			262*kx, maxY - 78,	50*kx, 20,	true);
	MoveWindow(Ao_UpB,			314*kx, maxY - 78,	14, 11,	true);
	MoveWindow(Ao_DownB,		314*kx, maxY - 68,	14, 11,	true);

	MoveWindow(Fn_TB,			335*kx, maxY - 78, 170*kx, 30,true);
	MoveWindow(Fn_St,			345*kx, maxY - 94, 70,15,	true);
	MoveWindow(Fn_Ed,			510*kx, maxY - 78,	40*kx, 20,	true);
	MoveWindow(Fn_UpB,			552*kx, maxY - 78,	14, 11,	true);
	MoveWindow(Fn_DownB,		552*kx, maxY - 68,	14, 11,	true);

	MoveWindow(p_TB,			335*kx, maxY - 33, 170*kx, 30,	true);
	MoveWindow(p_St,			345*kx, maxY - 48, 113,15,	true);
	MoveWindow(p_St1,			345*kx+74, maxY - 50, 10,10,	true);
	MoveWindow(p_Ed,			510*kx, maxY - 33,	40*kx, 20,	true);
	MoveWindow(p_UpB,			552*kx, maxY - 33,	14, 11,	true);
	MoveWindow(p_DownB,		    552*kx, maxY - 23,	14, 11,	true);

	MoveWindow(time_St,		587*kx, maxY - 48, 70,15,	true);
	MoveWindow(time_St2,	587*kx+40, maxY - 48, 20,15,	true);
	MoveWindow(time_TB,		577*kx, maxY - 33, 160, 30,	true);

	MoveWindow(vol_St,		maxX - 234, maxY - 75, 30, 15,	true);
	MoveWindow(vol_CB,		maxX - 194, maxY - 75, 15, 15,	true);
}
void tagCONTROL::CreateInterfacePanel( __in WNDPROC WndProc1)
{
	CreateButtons();
	CreateOGLWindow( WndProc1);
	CreateStringParamOption();
	CreateTimeSpeedPanel();
	CreateVolumeButton();
}

LRESULT CALLBACK tagCONTROL::ReactionAllButtonsAndEdits(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	int wmId    = LOWORD(wParam);
	int wmEvent = HIWORD(wParam);
	switch(wmId)
	{
	case ButtonStop_ID:
		_message_typename = 1;
		break;
	case ButtonStandart_ID:
		this->Standart();
		_message_typename = 2;
		break;
	case L_Ed_ID:
		if(this->FirstEditsIndex[0] < 2)
		{
			this->FirstEditsIndex[0]++;
		}
		else
		{
			GetWindowText(L_Ed, lpch, 10);
			_message_typename = 3;
			_message_value = _wtoi(lpch);
			if(_message_value <= 10)
			{
				_message_value = 10;
				_itow_s(10, lpch, 10);
				SetWindowText(L_Ed, lpch);
			}
			else
			if(_message_value > 1000)
			{
				_message_value = 1000;
				_itow_s(1000, lpch, 10);
				SetWindowText(L_Ed, lpch);
			}
			SendMessage(L_TB, TBM_SETPOS,(WPARAM) TRUE,(LPARAM) _message_value);
		}
		break;
	case L_UpB_ID:
		_message_typename = 4;
		GetWindowText(L_Ed, lpch, 10);
		par = _wtoi(lpch) + 1;
		_itow_s(par, lpch, 10);
		SetWindowText(L_Ed, lpch);
		break;
	case L_DownB_ID:
		_message_typename = 5;
		GetWindowText(L_Ed, lpch, 10);
		par = _wtoi(lpch) - 1;
		_itow_s(par, lpch, 10);
		SetWindowText(L_Ed, lpch);
		break;
	case p_Ed_ID:
		if(this->FirstEditsIndex[2] < 2)
		{
			this->FirstEditsIndex[2]++;
		}
		else
		{
			GetWindowText(p_Ed, lpch, 10);
			_message_typename = 9;
			_message_value = _wtoi(lpch);
			if(_message_value <= 0)
			{
				_message_value = 1;
				_itow_s(1, lpch, 10);
				SetWindowText(p_Ed, lpch);
			}
			else
			if(_message_value > 50)
			{
				_message_value = 50;
				_itow_s(50, lpch, 10);
				SetWindowText(p_Ed, lpch);
			}
			SendMessage(p_TB, TBM_SETPOS,(WPARAM) TRUE,(LPARAM) _message_value);
		}
		break;
	case p_UpB_ID:
		_message_typename = 10;
		GetWindowText(p_Ed, lpch, 10);
		par = _wtoi(lpch) + 1;
		_itow_s(par, lpch, 10);
		SetWindowText(p_Ed, lpch);
		break;
	case p_DownB_ID:
		_message_typename = 11;
		GetWindowText(p_Ed, lpch, 10);
		par = _wtoi(lpch) - 1;
		_itow_s(par, lpch, 10);
		SetWindowText(p_Ed, lpch);
		break;
	case Fn_Ed_ID:
		if(this->FirstEditsIndex[3] < 2)
		{
			this->FirstEditsIndex[3]++;
		}
		else
		{
			GetWindowText(Fn_Ed, lpch, 10);
			_message_typename = 12;
			_message_value = _wtoi(lpch);
			if(_message_value <= 0)
			{
				_message_value = 1;
				_itow_s(1, lpch, 10);
				SetWindowText(Fn_Ed, lpch);
			}
			else
			if(_message_value > 5000)
			{
				_message_value = 5000;
				_itow_s(5000, lpch, 10);
				SetWindowText(Fn_Ed, lpch);
			}
			SendMessage(Fn_TB, TBM_SETPOS,(WPARAM) TRUE,(LPARAM) _message_value);
		}
		break;
	case Fn_UpB_ID:
		_message_typename = 13;
		GetWindowText(Fn_Ed, lpch, 10);
		par = _wtoi(lpch) + 1;
		_itow_s(par, lpch, 10);
		SetWindowText(Fn_Ed, lpch);
		break;
	case Fn_DownB_ID:
		_message_typename = 14;
		GetWindowText(Fn_Ed, lpch, 10);
		par = _wtoi(lpch) - 1;
		_itow_s(par, lpch, 10);
		SetWindowText(Fn_Ed, lpch);
		break;
	case Ao_Ed_ID:
		if(this->FirstEditsIndex[4] < 2)
		{
			this->FirstEditsIndex[4]++;
		}
		else
		{
			GetWindowText(Ao_Ed, lpch, 10);
			_message_typename = 15;
			_message_value = _wtoi(lpch);
			if(_message_value <= 0)
			{
				_message_value = 1;
				_itow_s(1, lpch, 10);
				SetWindowText(Ao_Ed, lpch);
			}
			else
			if(_message_value > 100)
			{
				_message_value = 100;
				_itow_s(100, lpch, 10);
				SetWindowText(Ao_Ed, lpch);
			}
			SendMessage(Ao_TB, TBM_SETPOS,(WPARAM) TRUE,(LPARAM) _message_value);
		}
		break;
	case Ao_UpB_ID:
		_message_typename = 16;
		GetWindowText(Ao_Ed, lpch, 10);
		par = _wtoi(lpch) + 1;
		_itow_s(par, lpch, 10);
		SetWindowText(Ao_Ed, lpch);
		break;
	case Ao_DownB_ID:
		_message_typename = 17;
		GetWindowText(Ao_Ed, lpch, 10);
		par = _wtoi(lpch) - 1;
		_itow_s(par, lpch, 10);
		SetWindowText(Ao_Ed, lpch);
		break;
	case vol_CB_ID:
		_message_typename = 18;
	default:break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}
LRESULT CALLBACK tagCONTROL::ReactionAllTrackBars(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if((HWND)lParam == GetDlgItem (hWnd, L_TB_ID))
	{
			par = SendMessage(L_TB, TBM_GETPOS, 0, 0l);
			_message_typename = 3;
			_message_value = par;
			_itow_s(par, lpch, 10);
			SetWindowText(L_Ed, lpch);
	}
	else
	if((HWND)lParam == GetDlgItem (hWnd, p_TB_ID))
	{
			par = SendMessage(p_TB, TBM_GETPOS, 0, 0l);
			_message_typename = 9;
			_message_value = par;
			_itow_s(par, lpch, 10);
			SetWindowText(p_Ed, lpch);
	}
	else
	if((HWND)lParam == GetDlgItem (hWnd, Fn_TB_ID))
	{
			par = SendMessage(Fn_TB, TBM_GETPOS, 0, 0l);
			_message_typename = 12;
			_message_value = par;
			_itow_s(par, lpch, 10);
			SetWindowText(Fn_Ed, lpch);
	}
	else
	if((HWND)lParam == GetDlgItem (hWnd, Ao_TB_ID))
	{
			par = SendMessage(Ao_TB, TBM_GETPOS, 0, 0l);
			_message_typename = 15;
			_message_value = par;
			_itow_s(par, lpch, 10);
			SetWindowText(Ao_Ed, lpch);
	}
	else
	if((HWND)lParam == GetDlgItem (hWnd, time_TB_ID))
	{
		_message_typename = 19;
		_message_value = SendMessage(time_TB, TBM_GETPOS, 0, 0l);
		_itow_s(_message_value, lpch, 10);
		SetWindowText(time_St2, lpch);
	}
	else
		return DefWindowProc(hWnd, message, wParam, lParam);
	return 0;
}

HWND tagCONTROL::GetOGLHWND()
{
	return OGL;
}

void tagCONTROL::Standart()
{
	_itow_s(1000,lpch,10);
	SetWindowText(L_Ed,lpch);
	_itow_s(40,lpch,10);
	SetWindowText(Fn_Ed,lpch);
	_itow_s(150,lpch,10);
	SetWindowText(p_Ed,lpch);
	_itow_s(100,lpch,10);
	SetWindowText(Ao_Ed,lpch);
	SendMessage(time_TB,TBM_SETPOS,(WPARAM)1,0l);
	SetWindowText(time_St2,L"1");
}

# endif