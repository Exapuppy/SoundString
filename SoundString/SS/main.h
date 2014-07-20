
# ifndef _MAIN_H
# define _MAIN_H
 
// Хидеры, необходимые для работы программы
# include <windows.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include <time.h>
# include <Mmsystem.h>
# include <WinUser.h>
# include "GL\GL.H"
# include "GL\GLU.H"
# include "GL\glut.h"
# include "GL\GLAux.h"
# include <dsound.h>

# include "StringPhysics.h"
# include "Control.h"

# pragma comment ( lib, "winmm.lib" )

// Звуковая библиотека
# pragma comment ( lib, "dsound.lib" )

// Обьявим глобальные переменные, ширину, высоту и глубину цвета экрана
# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 600
# define SCREEN_DEPTH 16

// Глобальные параметры окна; будут доступны из других файлов:
extern HWND  g_hWnd;
extern RECT  g_rRect;
extern HDC   g_hDC;
extern HGLRC g_hRC;
extern HINSTANCE g_hInstance;

// Функция - главный цикл программы
WPARAM MainLoop();

// Функция, устанавливающая формат пиксела
bool bSetupPixelFormat(HDC hdc);
 
// Прототип функции, устанавливающей размеры окна OpenGL
void SizeOpenGLScreen(int width, int height);
 
// Функция, инициализирующая OpenGL
void InitializeOpenGL(int width, int height);
 
// Общая инициализация
void InitOpenGL(HWND hWnd);

// Инициализация звука
int InitAudio(LPDIRECTSOUNDBUFFER *buffer, int secs, int samplerate, int bitspersample);

void FillBuffer(LPDIRECTSOUNDBUFFER buffer, float freq, int size, int samplerate, int bitsPerSample);

// Функция, которая собственно рисует сцену
void RenderScene();
 
// Де-инициализация
void DeInit();
 
# endif