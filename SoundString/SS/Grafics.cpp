
# include "stdafx.h"
# include "Grafics.h"

# ifdef _GRAFICS_H

tagGrafic::tagGrafic(wchar_t *WindowsName, HINSTANCE hInst)
{
	wcscpy_s(this->WindowsName, WindowsName);
	this->hInst = hInst;
	Open = false;
	//
	correctX = 5;
	correctY = 5;

	GcorrectX = 1.0f;
	GcorrectY = 1.0f;
}
void tagGrafic::ReInit()
{	
	wglMakeCurrent ( hDC, hRC );
	Render();
	wglMakeCurrent ( g_hDC, g_hRC );
}
bool tagGrafic::GetEnd()
{
	if(MassSize >= 32768)
		return true;
	return false;
}
void tagGrafic::Deinit()
{
	if (hRC)
	{
		wglMakeCurrent ( NULL, NULL );
		wglDeleteContext (hRC);
	}
	if (hDC)
		ReleaseDC (hWnd, hDC);	
}
void tagGrafic::Init ()
{
	//GetClientRect ( hWnd, &Rect );
	InitializeOpenGL ();//int width, int heigth
	hRC = wglCreateContext (hDC);
}
void tagGrafic::InitializeOpenGL ()//int width, int heigth
{
	hDC = GetDC ( hWnd );
	if ( !bSetupPixelFormat ( hDC ) )
		CloseWindow (hWnd);
	hRC = wglCreateContext (hDC);
	wglMakeCurrent ( hDC, hRC );
	glEnable ( GL_DEPTH_TEST );
	
	//glViewport ( 0.0f, 0.0f, 700.0f, 440.0f );
	glMatrixMode ( GL_PROJECTION );
	glLoadIdentity ( );		
	gluOrtho2D ( 0.0f, 800.0f, 0.0f, 440.0f );
	glDepthRange ( 0, 1 );
	glMatrixMode ( GL_MODELVIEW );
	glLoadIdentity ( );

	Font = new CFont ( "framd.ttf", 10, 10 );
}
void tagGrafic::OpenMsg(WNDPROC WndProc)
{
	WNDCLASS wndclass;
	memset ( &wndclass, 0, sizeof ( WNDCLASS ) );
	wndclass.style			= CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc	= WndProc;
	wndclass.hIcon			= LoadIcon ( hInst, MAKEINTRESOURCE(108) );
	wndclass.hCursor		= LoadCursor ( NULL, IDC_ARROW );
	wndclass.hbrBackground	= ( HBRUSH ) ( COLOR_WINDOW + 1 );
	wndclass.lpszClassName	= L"MyOpenWindow";
	RegisterClass ( &wndclass );

	hWnd = CreateWindow(L"MyOpenWindow", this->WindowsName, WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU, 200, 200, 800, 440, NULL,(HMENU)0, hInst, 0l);
	if (!hWnd)return;
	//SetWindowLong(hWnd,GWL_WNDPROC, WndProc);
	Init();
	ShowWindow ( hWnd, SW_SHOWNORMAL );
	Open = true;
}
void tagGrafic::Render()
{
	glClearColor ( 0.95f, 0.95f, 0.95f, 1 );
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode ( GL_MODELVIEW );
	glPushMatrix ( );
	glLoadIdentity();
	glOrtho ( 0, 800, 0, 440, 0, 1 );
	
#pragma region Сетка
	//сетка и цена деления
	glColor3ub ( 70, 70, 70 );
	//сетка
	for ( int i = 50;  i <= 750; i += 5 * correctX )
	{		
		glBegin ( GL_LINES );
			glVertex2i ( i, 50 );	//Y
			glVertex2i ( i, 400 );
		glEnd ( );
	}
	for ( int i = 50;  i <= 750; i += 5 * correctY )
	{		
		glBegin ( GL_LINES );			
			if ( i >= 50 && i <= 400 )
			{
				glVertex2i ( 50, i );	//X
				glVertex2i ( 750, i );
			}
		glEnd ( );
	}
	//	
	glBegin ( GL_LINES );		
		// линия оси OY
		glVertex2i ( 50, 50 );	
		glVertex2i ( 50, 410 );
		// линия оси OX		
		glVertex2i ( 50, 50 );
		glVertex2i ( 760, 50 );		
	glEnd ( );
	glBegin ( GL_TRIANGLES );
		// стрелочка оси OY
		glVertex2i ( 45, 410 );
		glVertex2i ( 55, 410 );			
		glVertex2i ( 50, 420 );
		//
		// стрелочка оси OX
		glVertex2i ( 760, 55 );
		glVertex2i ( 760, 45 );		
		glVertex2i ( 770, 50 );
		//
	glEnd ( );	
	glColor3f ( 0.95f, 0.95f, 0.95f );
		glBegin ( GL_QUADS );
			glVertex2i ( 50, 401 );			glVertex2i ( 800, 401 );
			glVertex2i ( 800, 440 );		glVertex2i ( 50, 440 );
		glEnd ( );
#pragma endregion
#pragma region отрисовка графика
	glPushMatrix();
	glColor3ub ( 200, 50, 50 );
		glBegin ( GL_QUADS );
			glVertex2i ( 50, 15 );		glVertex2i ( 70, 15 );
			glVertex2i ( 70, 25 );		glVertex2i ( 50, 25 );
		glEnd ( );
	glColor3ub ( 50, 200, 50 );
		glBegin ( GL_QUADS );
			glVertex2i ( 320, 15 );		glVertex2i ( 340, 15 );
			glVertex2i ( 340, 25 );		glVertex2i ( 320, 25 );
		glEnd ( );
	glTranslatef ( 50.0f, 50.0f, 0.0f );
	glEnable ( GL_LINE );
		glLineWidth ( 2.0f );
		glBegin ( GL_LINE_STRIP );
		glColor3ub ( 200, 50, 50 );
		int k = 0, p = 0;
			for ( int u = 0; u < MassSize; u++ )
			{
				if ( MassX [ u ] * GcorrectX <= 700 )
					glVertex2f ( MassX [ u ] * GcorrectX, MassY1 [ u ] * GcorrectY );
				k = u;
			}			
		glEnd ( );				
		glBegin ( GL_LINE_STRIP );
		glColor3ub ( 50, 200, 50 );
			for ( int u = 0; u < MassSize; u++ )
			{
				if ( MassX [ u ] * GcorrectX <= 700 )
					glVertex2f ( MassX [ u ] * GcorrectX, MassY2 [ u ] * GcorrectY );
				p = u;
			}
		glEnd ( );
		glLineWidth ( 1.0f );
	glDisable ( GL_LINE );
	
	glPopMatrix();
	glPopMatrix ( );
#pragma endregion
	glMatrixMode ( GL_PROJECTION );
	glPushMatrix ( );
	glLoadIdentity ( );
	glOrtho ( 0, 800, 0, 440, 0, 1 );
	glMatrixMode ( GL_MODELVIEW );
	glLoadIdentity ( );
#pragma region text

	glDisable ( GL_DEPTH_TEST );
		glColor3f ( 0.0f, 0.0f, 0.0f );												
		swprintf ( Buffer, sizeof ( Buffer ), L"Время:  %.3f, с", MassX [ k ] );
		Font -> Font -> FaceSize ( 13 );
		Font -> Print ( 640, 410, Buffer );  
	glEnable ( GL_DEPTH_TEST );

	glDisable ( GL_DEPTH_TEST );
		glColor3f ( 0.0f, 0.0f, 0.0f );												
		swprintf ( Buffer, sizeof ( Buffer ), L"Потенциальная энергия:  %.2f, Дж", MassY1 [ k ] );
		Font -> Font -> FaceSize ( 13 );
		Font -> Print ( 80, 15, Buffer );  
	glEnable ( GL_DEPTH_TEST );

	glDisable ( GL_DEPTH_TEST );
		glColor3f ( 0.0f, 0.0f, 0.0f );												
		swprintf ( Buffer, sizeof ( Buffer ), L"Кинетическая энергия:  %.2f, Дж", MassY2 [ p ] );
		Font -> Font -> FaceSize ( 13 );
		Font -> Print ( 350, 15, Buffer );  
	glEnable ( GL_DEPTH_TEST );

	glDisable ( GL_DEPTH_TEST );
		glColor3f ( 0.0f, 0.0f, 0.0f );												
		swprintf ( Buffer, sizeof ( Buffer ), L"t [с]" );
		Font -> Font -> FaceSize ( 12 );
		Font -> Print ( 760, 30, Buffer );  
	glEnable ( GL_DEPTH_TEST );

	glDisable ( GL_DEPTH_TEST );
		glColor3f ( 0.0f, 0.0f, 0.0f );												
		swprintf ( Buffer, sizeof ( Buffer ), L"E [Дж]" );
		Font -> Font -> FaceSize ( 12 );
		Font -> Print ( 12, 410, Buffer );  
	glEnable ( GL_DEPTH_TEST );
	
#pragma endregion
#pragma region Деления
	// цена деления оси OX
	for ( GLfloat i = 0.0f, iv = 50; iv <= 725; iv += 0 )
	{		
		glDisable ( GL_DEPTH_TEST );
			glColor3f ( 0.0f, 0.0f, 0.0f );												
			swprintf ( Buffer, sizeof ( Buffer ), L"%.3f", i );
			Font -> Font -> FaceSize ( 10 );
			Font -> Print ( iv, 35, Buffer );
		glEnable ( GL_DEPTH_TEST );
		if ( correctX == 5 )
		{
			GcorrectX = 710.0f * 8.0f;			
			iv += 5 * correctX * 5;
			i += 0.0041661875f;
		}
		if ( correctX == 4 )
		{
			GcorrectX = 710.0f * 6.0f;			
			iv += 5 * correctX * 5;
			i += 0.008332375f ;
		}
		if ( correctX == 3 )
		{	
			GcorrectX = 710.0f * 4.0f;			
			iv += ( 5 * correctX ) * 5;
			i += 0.01666475f;
		}
		if ( correctX == 2 )
		{	
			GcorrectX = 710.0f * 2.0f;			
			iv += ( 5 * correctX ) * 5;
			i += 0.0333295f;
		}
		if ( correctX == 1 )
		{	
			GcorrectX = 710.0f * 1.0f;			
			iv += ( 5 * correctX ) * 9;
			i += 0.066659f;
		}
	}
	// цена деления оси OY
	int ic = 0;
	int ivc = 0;
	if ( correctY == 5 )
	{
		GcorrectY = 2.5f;
		ic = 10;
		ivc = 50 + 5 * correctY;
	}
	if ( correctY == 4 )
	{
		GcorrectY = 0.8f;
		ic = 50;
		ivc = 50 + 5 * correctY * 2;
	}
	if ( correctY == 3 )
	{
		GcorrectY = 0.3017241379310345f;
		ic = 100;
		ivc = 50 + 5 * correctY * 2;
	}
	if ( correctY == 2 )
	{
		GcorrectY = 0.02f;
		ic = 1000;
		ivc = 50 + 5 * correctY * 2;
	}
	if ( correctY == 1 )
	{
		GcorrectY = 0.01f;
		ic = 5000;
		ivc = 50 + 5 * correctY * 10;
	}
	for ( int i = ic, iv = ivc; iv <= 395; iv += 0 )
	{
		glDisable ( GL_DEPTH_TEST );
			glColor3f ( 0.0f, 0.0f, 0.0f );												
			swprintf ( Buffer, sizeof ( Buffer ), L"%d", i );
			Font -> Font -> FaceSize ( 10 );
			if ( i < 999 )
				Font -> Print ( 30, iv, Buffer );
			else
				if ( i > 99999 )
					Font -> Print ( 11, iv, Buffer );
				else
					if ( i > 9999 )
						Font -> Print ( 18, iv, Buffer );
					else
						if ( i > 999 )
							Font -> Print ( 23, iv, Buffer );
			
		glEnable ( GL_DEPTH_TEST );
		if ( correctY == 5 )
		{
			iv += 5 * correctY;
			i += 10;
		}
		if ( correctY == 4 )
		{
			iv += 5 * correctY * 2;
			i += 50;
		}
		if ( correctY == 3 )
		{	
			iv += 5 * correctY * 2;
			i += 100;
		}
		if ( correctY == 2 )
		{	
			iv += ( 5 * correctY ) * 2;
			i += 1000;
		}
		if ( correctY == 1 )
		{	
			iv += ( 5 * correctY ) * 10;
			i += 5000;
		}
	}
#pragma endregion
	glMatrixMode ( GL_PROJECTION );
	glPopMatrix ( );
	glMatrixMode ( GL_MODELVIEW );

	glFlush();
	
	SwapBuffers (hDC);
}
void tagGrafic::Push(float X, float Y_1, float Y_2)
{
	this->MassX[MassSize] = X;
	this->MassY1[MassSize] = Y_1;
	this->MassY2[MassSize] = Y_2;
	this->MassSize ++;
}
void tagGrafic::Reset()
{
	this->MassSize = 0;
}

# endif