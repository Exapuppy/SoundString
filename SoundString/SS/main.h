
# ifndef _MAIN_H
# define _MAIN_H
 
// ������, ����������� ��� ������ ���������
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

// �������� ����������
# pragma comment ( lib, "dsound.lib" )

// ������� ���������� ����������, ������, ������ � ������� ����� ������
# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 600
# define SCREEN_DEPTH 16

// ���������� ��������� ����; ����� �������� �� ������ ������:
extern HWND  g_hWnd;
extern RECT  g_rRect;
extern HDC   g_hDC;
extern HGLRC g_hRC;
extern HINSTANCE g_hInstance;

// ������� - ������� ���� ���������
WPARAM MainLoop();

// �������, ��������������� ������ �������
bool bSetupPixelFormat(HDC hdc);
 
// �������� �������, ��������������� ������� ���� OpenGL
void SizeOpenGLScreen(int width, int height);
 
// �������, ���������������� OpenGL
void InitializeOpenGL(int width, int height);
 
// ����� �������������
void InitOpenGL(HWND hWnd);

// ������������� �����
int InitAudio(LPDIRECTSOUNDBUFFER *buffer, int secs, int samplerate, int bitspersample);

void FillBuffer(LPDIRECTSOUNDBUFFER buffer, float freq, int size, int samplerate, int bitsPerSample);

// �������, ������� ���������� ������ �����
void RenderScene();
 
// ��-�������������
void DeInit();
 
# endif