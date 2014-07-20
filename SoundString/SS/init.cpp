
# include "stdafx.h"
# include "main.h"

# ifdef _MAIN_H

bool bSetupPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;	// ���������� ������� �������
	int pixelformat;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);	// ������������� ������ ���������
	pfd.nVersion = 1;				// ������ ������ = 1
			// ������� ������ ����� OpenGL
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.dwLayerMask = PFD_MAIN_PLANE;		// ����������� ����� (���� ���� ������������)
    pfd.iPixelType = PFD_TYPE_RGBA;		// ��� ����� RGB and Alpha ���� ��������
    pfd.cColorBits = SCREEN_DEPTH;		// ���������� ���� #define ��� �������� �������
    pfd.cDepthBits = SCREEN_DEPTH;	// ��� ������������ ��� RGBA, �� ��� ����� ���������
    pfd.cAccumBits = 0;
    pfd.cStencilBits = 0;
 
    // �-� ���� ������ �������, �������� ���������� �������� �����������, ����� ��� �������
    if ( (pixelformat = ChoosePixelFormat(hdc, &pfd)) == FALSE )
    {
        MessageBox(NULL, L"ChoosePixelFormat failed", L"Error", MB_OK);
        return FALSE;
    }
 
    // ������������� ��������� ������ �������
    if (SetPixelFormat(hdc, pixelformat, &pfd) == FALSE)
    {
        MessageBox(NULL, L"SetPixelFormat failed", L"Error", MB_OK);
        return FALSE;
    }
 
    return TRUE;
}
 
void SizeOpenGLScreen(int width, int height)
{
	if (height==0)		// ������������ ������� �� 0
		height=1;
 
	glViewport(0,0,width,height);
 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
 
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height, .5f ,1000.0f);
 
	glMatrixMode(GL_MODELVIEW);  // ������� ������� �������
	glLoadIdentity();            // � ������� �
}
 
void InitializeOpenGL(int width, int height)
{
    g_hDC = GetDC(g_hWnd);	// ������������� ���������� ���������� ����
 
    if (!bSetupPixelFormat(g_hDC))		// ������������� ������ �������
        PostQuitMessage (0);			// � ������� ��� ������
 
    g_hRC = wglCreateContext(g_hDC);		// �������� ���������� ��� hdc
    wglMakeCurrent(g_hDC, g_hRC);		// ������ �������� �������
    glEnable(GL_TEXTURE_2D);			// �������� ��������
    glEnable(GL_DEPTH_TEST);			// � ���� �������
 
    // � ������������� ������ ��������:
    SizeOpenGLScreen(width, height);
}
 
void DeInit()
{
	if (g_hRC)
	{
		wglMakeCurrent(NULL, NULL);	// ����������� ������, ������� ��� �������
		wglDeleteContext(g_hRC);	// ������� �������� ���������� OpenGL
	}
 
	if (g_hDC)
		ReleaseDC(g_hWnd, g_hDC);	// ������� HDC �� ������
 
	UnregisterClass(L" ", g_hInstance);	// ����������� ����� ����
	PostQuitMessage (0);					// �������
}

# endif