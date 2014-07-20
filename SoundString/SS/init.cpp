
# include "stdafx.h"
# include "main.h"

# ifdef _MAIN_H

bool bSetupPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;	// Дескриптор формата пиксела
	int pixelformat;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);	// Устанавливаем размер структуры
	pfd.nVersion = 1;				// Всегда ставим = 1
			// Передаём нужные флаги OpenGL
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.dwLayerMask = PFD_MAIN_PLANE;		// Стандартная маска (один хрен игнорируется)
    pfd.iPixelType = PFD_TYPE_RGBA;		// Нам нужны RGB and Alpha типа пикселей
    pfd.cColorBits = SCREEN_DEPTH;		// Используем наши #define для цветовой глубины
    pfd.cDepthBits = SCREEN_DEPTH;	// Это игнорируется для RGBA, но все равно передадим
    pfd.cAccumBits = 0;
    pfd.cStencilBits = 0;
 
    // Ф-я ищет формат пиксела, наиболее подходящий заданным требованиям, выход при неудаче
    if ( (pixelformat = ChoosePixelFormat(hdc, &pfd)) == FALSE )
    {
        MessageBox(NULL, L"ChoosePixelFormat failed", L"Error", MB_OK);
        return FALSE;
    }
 
    // Устанавливаем указанный формат пиксела
    if (SetPixelFormat(hdc, pixelformat, &pfd) == FALSE)
    {
        MessageBox(NULL, L"SetPixelFormat failed", L"Error", MB_OK);
        return FALSE;
    }
 
    return TRUE;
}
 
void SizeOpenGLScreen(int width, int height)
{
	if (height==0)		// Предотвратим деление на 0
		height=1;
 
	glViewport(0,0,width,height);
 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
 
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height, .5f ,1000.0f);
 
	glMatrixMode(GL_MODELVIEW);  // Выберем матрицу моделей
	glLoadIdentity();            // И сбросим её
}
 
void InitializeOpenGL(int width, int height)
{
    g_hDC = GetDC(g_hWnd);	// Устанавливаем глобальный дескриптор окна
 
    if (!bSetupPixelFormat(g_hDC))		// Устанавливаем формат пиксела
        PostQuitMessage (0);			// И выходим при ошибке
 
    g_hRC = wglCreateContext(g_hDC);		// Контекст рендеринга для hdc
    wglMakeCurrent(g_hDC, g_hRC);		// Делаем контекст текущим
    glEnable(GL_TEXTURE_2D);			// Включаем текстуры
    glEnable(GL_DEPTH_TEST);			// И тест глубины
 
    // И устанавливаем размер вьюпорта:
    SizeOpenGLScreen(width, height);
}
 
void DeInit()
{
	if (g_hRC)
	{
		wglMakeCurrent(NULL, NULL);	// Освобождает память, занятую для рендера
		wglDeleteContext(g_hRC);	// Удаляет контекст рендеринга OpenGL
	}
 
	if (g_hDC)
		ReleaseDC(g_hWnd, g_hDC);	// Убирает HDC из памяти
 
	UnregisterClass(L" ", g_hInstance);	// Освобождаем класс окна
	PostQuitMessage (0);					// Выходим
}

# endif