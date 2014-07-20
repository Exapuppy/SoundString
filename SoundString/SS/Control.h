# ifndef _CONTROL_H
# define _CONTROL_H

# include <Windows.h>

# define ButtonStop_ID 1
# define ButtonStandart_ID 3
# define L_TB_ID 4
# define L_Ed_ID 5
# define L_UpB_ID 6
# define L_DownB_ID 7
# define p_TB_ID 12
# define p_Ed_ID 13
# define p_UpB_ID 14
# define p_DownB_ID 15
# define Fn_TB_ID 16
# define Fn_Ed_ID 17
# define Fn_UpB_ID 18
# define Fn_DownB_ID 19
# define Ao_TB_ID 20
# define Ao_Ed_ID 21
# define Ao_UpB_ID 22
# define Ao_DownB_ID 23
# define vol_CB_ID 24
# define time_TB_ID 25

# define OGL_ID 40

typedef class tagCONTROL
{
private:
	char FirstEditsIndex[5];
	// панель настроек высотой 120-130
	// дескрипторы контролов и OGL окна
	HWND ButtonStop, ButtonStandart;
	HWND OGL;
	HWND L_TB, L_St,L_St1, L_Ed, L_UpB, L_DownB;
	HWND p_TB, p_St,p_St1, p_Ed, p_UpB, p_DownB;
	HWND Fn_TB, Fn_St, Fn_Ed, Fn_UpB, Fn_DownB;
	HWND Ao_TB, Ao_St, Ao_St1, Ao_Ed, Ao_UpB, Ao_DownB;
	HWND vol_St, vol_CB;
	HWND time_TB, time_St,time_St2;
	//главные дескрипторы
	HWND _hWnd;
	HINSTANCE _hInst;
	//вспомогательные параметры
	int maxX, maxY, FmaxX, FmaxY;
	HDC hdc;
	HFONT hFont;
	HPEN MainPen, OldPen;
	HBRUSH MainBrush, OldBrush;
	int par;
	wchar_t lpch[20];

	//установка значений по умолчанию
	void Standart();
	//установка шрифтов
	inline void set_Font( __in LPCWSTR, __in int);
	inline void Font_to_Ctrl_Buttons();
	inline void Font_to_Ctrl_StringParam();
	inline void Font_to_TimeTB();
	inline void Font_to_volTB();
	//загрузка дескрипторов
	inline void set_hWnd( __in HWND);
	inline void set_hInstance( __in HINSTANCE);
	//создание панелей и окон
	inline void CreateButtons();
	inline void CreateOGLWindow( __in WNDPROC);
	inline void CreateStringParamOption();
	inline void CreateTimeSpeedPanel();
	inline void CreateVolumeButton();
	
public:
	//конструктор
	tagCONTROL( __in HWND, __in HINSTANCE);
	//создание панели
	void CreateInterfacePanel( __in WNDPROC WndProc);
	//команда реакции
	LRESULT CALLBACK ReactionAllButtonsAndEdits(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK ReactionAllTrackBars(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	//команда, вызываемая при изменении размеров окна
	void MoveAllWnd();
	//get-set parameter
	HWND GetOGLHWND();

	int _message_value;
	int _message_typename;
}CONTROL,*LPCONTROL;

# endif