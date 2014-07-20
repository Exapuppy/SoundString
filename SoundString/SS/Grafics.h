
# ifndef _GRAFICS_H
# define _GRAFICS_H

# include "main.h"

# ifdef _MAIN_H

# include "font.h"
# include <Windows.h>

typedef class tagGrafic
{
	float MassX [32768];
	float MassY1[32768];
	float MassY2[32768];
	int MassSize;
	//
	RECT Rect;
	HDC hDC;
	HGLRC hRC;
	HINSTANCE hInst;
	wchar_t WindowsName[30];
	void InitializeOpenGL ();
	void Init();
	void Render();
	CFont *Font;
	wchar_t Buffer [ 256 ];
public:
	int correctX;
	int correctY;
	GLfloat GcorrectX;
	GLfloat GcorrectY;	

	bool Open;
	HWND hWnd;
	
	void Push(float X, float Y_1, float Y_2);
	void Reset();
	bool GetEnd();

	tagGrafic(wchar_t *WindowsName, HINSTANCE hInst);
	void ReInit();
	void Deinit();
	void OpenMsg(WNDPROC WndProc);
}GRAFIC, *LPGRAFIC;

# endif
# endif