	
# include "stdafx.h"
# include "glelements_and_texture.h"


# ifdef _GLELEMENTS_AND_TEXTURE_H

void CTexture :: InitTextures ( CTexture *Texture )
{	
	Texture -> LoadTexture ( IL_BMP, "01.bmp", &textures [ 1 ] );
	Texture -> LoadTexture ( IL_BMP, "02.bmp", &textures [ 2 ] );
	Texture -> LoadTexture ( IL_BMP, "03.bmp", &textures [ 3 ] );
	Texture -> LoadTexture ( IL_BMP, "04.bmp", &textures [ 4 ] );

	Texture -> LoadTexture ( IL_BMP, "05.bmp", &textures [ 5 ] );
	Texture -> LoadTexture ( IL_BMP, "06.bmp", &textures [ 6 ] );
	Texture -> LoadTexture ( IL_BMP, "07.bmp", &textures [ 7 ] );
	Texture -> LoadTexture ( IL_BMP, "08.bmp", &textures [ 8 ] );

	Texture -> LoadTexture ( IL_BMP, "09.bmp", &textures [ 9 ] );
	Texture -> LoadTexture ( IL_BMP, "10.bmp", &textures [ 10 ] );
	Texture -> LoadTexture ( IL_BMP, "11.bmp", &textures [ 11 ] );
	Texture -> LoadTexture ( IL_BMP, "12.bmp", &textures [ 12 ] );

	Texture -> LoadTexture ( IL_BMP, "13.bmp", &textures [ 13 ] );
	Texture -> LoadTexture ( IL_BMP, "14.bmp", &textures [ 14 ] );
	Texture -> LoadTexture ( IL_BMP, "15.bmp", &textures [ 15 ] );
	Texture -> LoadTexture ( IL_BMP, "16.bmp", &textures [ 16 ] );

	Texture -> LoadTexture ( IL_BMP, "17.bmp", &textures [ 17 ] );	
	Texture -> LoadTexture ( IL_BMP, "18.bmp", &textures [ 18 ] );
	Texture -> LoadTexture ( IL_BMP, "19.bmp", &textures [ 19 ] );
	Texture -> LoadTexture ( IL_BMP, "20.bmp", &textures [ 20 ] );

	Texture -> LoadTexture ( IL_BMP, "21.bmp", &textures [ 21 ] );
	Texture -> LoadTexture ( IL_BMP, "22.bmp", &textures [ 22 ] );
	Texture -> LoadTexture ( IL_BMP, "23.bmp", &textures [ 23 ] );
	Texture -> LoadTexture ( IL_BMP, "24.bmp", &textures [ 24 ] );
	
	Texture -> LoadTexture ( IL_BMP, "251.bmp", &textures [ 25 ] );
	Texture -> LoadTexture ( IL_BMP, "2521.bmp", &textures [ 26 ] );
	Texture -> LoadTexture ( IL_BMP, "2522.bmp", &textures [ 27 ] );
	Texture -> LoadTexture ( IL_BMP, "2523.bmp", &textures [ 28 ] );

	Texture -> LoadTexture ( IL_BMP, "2524.bmp", &textures [ 29 ] );
	Texture -> LoadTexture ( IL_BMP, "2525.bmp", &textures [ 30 ] );
	Texture -> LoadTexture ( IL_BMP, "2526.bmp", &textures [ 31 ] );
	Texture -> LoadTexture ( IL_BMP, "2527.bmp", &textures [ 32 ] );

	Texture -> LoadTexture ( IL_BMP, "2528.bmp", &textures [ 33 ] );
	Texture -> LoadTexture ( IL_BMP, "2529.bmp", &textures [ 34 ] );
	Texture -> LoadTexture ( IL_BMP, "25210.bmp", &textures [ 35 ] );
	Texture -> LoadTexture ( IL_BMP, "36.bmp", &textures [ 36 ] );

	Texture -> LoadTexture ( IL_BMP, "37.bmp", &textures [ 37 ] );
	Texture -> LoadTexture ( IL_BMP, "38.bmp", &textures [ 38 ] );
	Texture -> LoadTexture ( IL_BMP, "HOLDER01.bmp", &textures [ 39 ] );
	Texture -> LoadTexture ( IL_BMP, "HOLDER02.bmp", &textures [ 40 ] );
} 
void DrawQ ( CTexture *Texture, GLfloat *TCBlock, int TEXT_ID, GLfloat *CVBlock )
{
	static GLushort	QVBlock [ ] =	{	0,  1,  2,	3	};				//Номера вершин
	glBindTexture ( GL_TEXTURE_2D, Texture -> textures [ TEXT_ID ].texID );
		glPushName ( TEXT_ID );
			glTexCoordPointer ( 2, GL_FLOAT, 0, TCBlock );		
			glVertexPointer ( 3, GL_FLOAT, 0, CVBlock );
			glDrawElements ( GL_QUADS, 4, GL_UNSIGNED_SHORT, QVBlock );
		glPopName ( );
}
void CTexture :: LoadTexture ( ILenum FileType, char *filename, TextureImage *texture )
{	
	ilLoad ( FileType, ( LPCWSTR ) filename );
 	
	int err=ilGetError ( );
	if ( err != IL_NO_ERROR )
	{
		const wchar_t* strError = iluErrorString(err);
		MessageBox(NULL, (LPCWSTR)strError, L"Ошибка при загрузке!", MB_OK);
		exit(1);
	} 
	
	texture->width = ilGetInteger(IL_IMAGE_WIDTH);			// Ширина
	texture->height = ilGetInteger(IL_IMAGE_HEIGHT);		// Высота
	texture->bpp = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);	// Байт на пиксель
 
	// Загружаем данные в нашу текстуру
	texture->imageData = ilGetData();
 
	ilEnable(IL_CONV_PAL);
 
	// Тип данных изображения
	unsigned int type = ilGetInteger(IL_IMAGE_FORMAT);
 
	// Генерируем текстуру
	glGenTextures(1, &texture->texID);
 
	// Привязываем данные текстуры к ID
	glBindTexture(GL_TEXTURE_2D,texture->texID);
 
	// биндим мип-мапы
	gluBuild2DMipmaps(GL_TEXTURE_2D, texture->bpp, texture->width,
		texture->height, type, GL_UNSIGNED_BYTE, texture->imageData);
 
	// Устанавливаем качество текстур
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
}
void GLelements :: CreateTimeNumElement ( GLfloat HEIGHT, GLfloat RADIUS, int R, int G, int B )
{	
# pragma region Координаты вершин 6-угольника
	GLfloat CVertex3TineElem [ ] =
	{						 
		 0.0f, -HEIGHT, 0.0f,	
		 RADIUS, -HEIGHT / 1.35f, 0.0f,
		 RADIUS, HEIGHT / 1.35f, 0.0f,
		 0.0f, HEIGHT, 0.0f,
		 -RADIUS, HEIGHT / 1.35f, 0.0f,
		 -RADIUS, -HEIGHT / 1.35f, 0.0f
	};
# pragma endregion
# pragma region Номера вершин 6-угольника
	static GLushort QVertex3 [ ] =
	{
		 0, 1, 2, 3, 4, 5
	};
# pragma endregion
# pragma region Отрисовка OpenGL
	glPushMatrix();
		glEnable ( GL_LINE );
		//glEnable ( GL_LINE_SMOOTH );	
		glEnableClientState ( GL_VERTEX_ARRAY );
			glLineWidth ( 1.0f );
			glColor3ub ( R, G, B );
					glVertexPointer ( 3, GL_FLOAT, 0, CVertex3TineElem );		
					glDrawElements ( GL_LINE_STRIP, 7, GL_UNSIGNED_SHORT, QVertex3 );
					glColor3ub ( 255, 255, 255 );
			//glPopName ( );
			glLineWidth ( 1.0f );
		glDisableClientState ( GL_VERTEX_ARRAY );
		//glDisable ( GL_LINE_SMOOTH );
	glPopMatrix ( );
# pragma endregion
}
void GLelements :: CreateOctagon ( float X, float Y, float Z, GLfloat LENGHT, GLfloat RADIUS )
{		
	glTranslatef ( X, Y, Z );	
# pragma region Координаты вершин 8-угольника
	GLfloat CVertex3String01 [ ] =
	{							 
		 0.0f, 0.0f, 0.0f,				//1//
		 0.0f, -RADIUS, RADIUS,
		 LENGHT, -RADIUS, RADIUS,
		 LENGHT, 0.0f, 0.0f
	};
	GLfloat CVertex3String02 [ ] =
	{							 
		 0.0f, -RADIUS, RADIUS,			//2//
		 0.0f, -RADIUS, RADIUS * 2, 
		 LENGHT, -RADIUS, RADIUS * 2,
		 LENGHT, -RADIUS, RADIUS
	};
	GLfloat CVertex3String03 [ ] =
	{							 
		 0.0f, -RADIUS, RADIUS * 2,		//3//
		 0.0f, 0.0f, RADIUS * 3,
		 LENGHT, 0.0f, RADIUS * 3,
		 LENGHT, -RADIUS, RADIUS * 2
	};
	GLfloat CVertex3String04 [ ] =
	{
		 0.0f, 0.0f, RADIUS * 3,		//4//
		 0.0f, RADIUS, RADIUS * 3,
		 LENGHT, RADIUS, RADIUS * 3,
		 LENGHT, 0.0f, RADIUS * 3
	};
	GLfloat CVertex3String05 [ ] =
	{	 
		 0.0f, RADIUS, RADIUS * 3,		//5//
		 0.0f, RADIUS * 2, RADIUS * 2,
		 LENGHT, RADIUS * 2, RADIUS * 2,
		 LENGHT, RADIUS, RADIUS * 3
	};
	GLfloat CVertex3String06 [ ] =
	{	 
		 0.0f, RADIUS * 2, RADIUS * 2,	//6//
		 0.0f, RADIUS * 2, RADIUS,
		 LENGHT, RADIUS * 2, RADIUS,
		 LENGHT, RADIUS * 2, RADIUS * 2
	};
	GLfloat CVertex3String07 [ ] =
	{	 
		 0.0f, RADIUS * 2, RADIUS,		//7//
		 0.0f, RADIUS, 0.0f,
		 LENGHT, RADIUS, 0.0f,
		 LENGHT, RADIUS * 2, RADIUS
	};
	GLfloat CVertex3String08 [ ] =
	{	 
		 0.0f, RADIUS, 0.0f,			//8//
		 0.0f, 0.0f, 0.0f, 
		 LENGHT, 0.0f, 0.0f,
		 LENGHT, RADIUS, 0.0f
	 };
# pragma endregion
# pragma region Номера вершин 8-угольника
	static GLushort	QVertex3 [ ] =
	{
		 0,  1,  2,	 3
	};
# pragma endregion
# pragma region Отрисовка OpenGL
	glPushMatrix();		
		glEnableClientState ( GL_VERTEX_ARRAY );		
		glEnable ( GL_SMOOTH );
			glColor3ub ( 50, 50, 50 );
			glVertexPointer ( 3, GL_FLOAT, 0, CVertex3String01 );		
			glDrawElements ( GL_QUADS, 4, GL_UNSIGNED_SHORT, QVertex3 );
			glColor3ub ( 150, 150, 150 );
			glVertexPointer ( 3, GL_FLOAT, 0, CVertex3String02 );		
			glDrawElements ( GL_QUADS, 4, GL_UNSIGNED_SHORT, QVertex3 );			
			glVertexPointer ( 3, GL_FLOAT, 0, CVertex3String03 );		
			glDrawElements ( GL_QUADS, 4, GL_UNSIGNED_SHORT, QVertex3 );			
			glVertexPointer ( 3, GL_FLOAT, 0, CVertex3String04 );		
			glDrawElements ( GL_QUADS, 4, GL_UNSIGNED_SHORT, QVertex3 );
			glColor3ub ( 50, 50, 50 );
			glVertexPointer ( 3, GL_FLOAT, 0, CVertex3String05 );		
			glDrawElements ( GL_QUADS, 4, GL_UNSIGNED_SHORT, QVertex3 );
			glColor3ub ( 150, 150, 150 );
			glVertexPointer ( 3, GL_FLOAT, 0, CVertex3String06 );		
			glDrawElements ( GL_QUADS, 4, GL_UNSIGNED_SHORT, QVertex3 );			
			glVertexPointer ( 3, GL_FLOAT, 0, CVertex3String07 );		
			glDrawElements ( GL_QUADS, 4, GL_UNSIGNED_SHORT, QVertex3 );
			glColor3ub ( 50, 50, 50 );
			glVertexPointer ( 3, GL_FLOAT, 0, CVertex3String08 );		
			glDrawElements ( GL_QUADS, 4, GL_UNSIGNED_SHORT, QVertex3 );
			glColor3ub ( 255, 255, 255 );
		glDisable ( GL_SMOOTH );
		glDisableClientState ( GL_VERTEX_ARRAY );		
	glPopMatrix();
# pragma endregion	
	glTranslatef ( -X, -Y, -Z );
}
void GLelements :: CreateHolderStrings ( CTexture *Texture, float X, float Y, float Z )
{
	glTranslatef ( X, Y, Z );
# pragma region Координаты вершин стоек
	GLfloat CVBlock01 [ ] =
	{	
		0.0f, -1.49999f, 0.55f,
		0.0f, -1.49999f, 0.0f,
		0.0f, 1.99999f, 0.0f,
		0.0f, 1.99999f, 0.55f
	};
	GLfloat CVBlock02 [ ] =
	{	
		0.2f, -1.49999f, 0.55f,
		0.2f, -1.49999f, 0.0f,
		0.2f, 1.99999f, 0.0f,
		0.2f, 1.99999f, 0.55f
	};
	GLfloat CVBlock03 [ ] =
	{
		0.2f, -1.49999f, 0.55f,
		0.2f, -1.49999f, 0.0f,
		0.0f, -1.49999f, 0.0f,
		0.0f, -1.49999f, 0.55f
	};
	GLfloat CVBlock04 [ ] =
	{
		0.2f, -1.49999f, 0.0f,
		0.2f, 1.99999f, 0.0f,
		0.0f, 1.99999f, 0.0f,
		0.0f, -1.49999f, 0.0f
	};
	GLfloat CVBlock05 [ ] =
	{
		0.2f, 1.99999f, 0.1f,
		0.2f, 1.99999f, 0.0f,
		0.0f, 1.99999f, 0.0f,
		0.0f, 1.99999f, 0.1f
	};
	GLfloat CVBlock06 [ ] =
	{
		0.2f, -1.49999f, 0.55f,
		0.2f, 1.99999f, 0.55f,
		0.0f, 1.99999f, 0.55f,
		0.0f, -1.49999f, 0.55f
	};
# pragma endregion
# pragma region Верщины текстурных координат
	static GLfloat TCBlock01 [ ] =
	{		
		0, 1,	1, 1,	1, 0,	0, 0
	};
	static GLfloat TCBlock02 [ ] =
	{		 
		 1, 1,	1, 0,	0, 0,	0, 1
	};
# pragma endregion
# pragma region Отрисовка OpenGL		
	glPushMatrix();
		glEnableClientState ( GL_VERTEX_ARRAY );
		glEnableClientState ( GL_TEXTURE_COORD_ARRAY );
			glEnable ( GL_SMOOTH );
			DrawQ ( Texture, TCBlock01, 40, CVBlock01 );		DrawQ ( Texture, TCBlock01, 40, CVBlock02 );
			DrawQ ( Texture, TCBlock02, 39, CVBlock03 );		DrawQ ( Texture, TCBlock02, 40, CVBlock04 );
			DrawQ ( Texture, TCBlock02, 39, CVBlock05 );		DrawQ ( Texture, TCBlock02, 40, CVBlock06 );
			glDisable ( GL_SMOOTH );
		glDisableClientState ( GL_TEXTURE_COORD_ARRAY );
		glDisableClientState ( GL_VERTEX_ARRAY );
	glPopMatrix();
# pragma endregion
	glTranslatef ( -X, -Y, -Z );
}
void GLelements :: CreateBigStend ( CTexture *Texture, int NOT )
{	
# pragma region Координаты вершин
	GLfloat CVBlock01 [ ] =
	{								
		0.5f, -1.5f, 0.6f,			//  ______________ 
		19.5f, -1.5f, 0.6f,			// |\____________/|
		19.5f, -1.5f, 0.0f,			// ||            ||
		0.5f, -1.5f, 0.0f			// |/____________\|
	};
	GLfloat CVBlock02 [ ] =
	{
		19.5f, -1.5f, 0.6f,			//  ______________ 
		19.5f, 2.0f, 0.6f,			// |\____________/|
		19.5f, 2.0f, 0.0f,			// ||____________ |
		19.5f, -1.5f, 0.0f			// |/____________\|
	};
	GLfloat CVBlock03 [ ] =
	{	
		19.5f, 2.0f, 0.6f,			//  ______________
		0.5f, 2.0f, 0.6f,			// |\            /|
		0.5f, 2.0f, 0.0f,			// ||____________||
		19.5f, 2.0f, 0.0f			// |/____________\|
	};
	GLfloat CVBlock04 [ ] =
	{	
		0.5f, 2.0f, 0.6f,			//  ______________ 
		0.5f, -1.5f, 0.6f,			// |\____________/|
		0.5f, -1.5f, 0.0f,			// | ____________||
		0.5f, 2.0f, 0.0f			// |/____________\|
	};
	//--------------------------------------------------------------//
	GLfloat CVBlock05 [ ] =	
	{
		0.0f, -4.5f, 0.6f,			//  ______________ 
		25.0f, -4.5f, 0.6f,			// |\____________/|
		25.0f, -4.5f, 0.0f,			// ||____________||
		0.0f, -4.5f, 0.0f			// |/            \|
	};
	GLfloat CVBlock06 [ ] =
	{
		25.0f, -4.5f, 0.0f,			//  ______________ 
		25.0f, -4.5f, 0.6f,			// |\____________/
		25.0f, 2.5f, 0.6f,			// ||____________|
		25.0f, 2.5f, 0.0f			// |/____________\ 
	};
	GLfloat CVBlock07 [ ] =
	{
		25, 2.5, 0.6f,				// |\____________/|
		0, 2.5, 0.6f,				// ||____________||
		0, 2.5, 0.0f,				// |/____________\|
		25, 2.5, 0.0f
	};
	GLfloat CVBlock08 [ ] =
	{
		0.0f, -4.5f, 0.6f,			//  ______________ 
		0.0f, -4.5f, 0.0f,			//  \____________/|
		0.0f, 2.5f, 0.0f,			//  |____________||
		0.0f, 2.5f, 0.6f			//  /____________\|
	};
	//--------------------Передняя панель--------------------------//
	GLfloat CVBlock09 [ ] =
	{
		0.0f, -2.5f, 0.6f,
		20.0f, -2.5f, 0.6f,			//   ____________
		20.0f, -1.5f, 0.6f,			//  /____________\ 
		0.0f, -1.5f, 0.6f
	};
	GLfloat CVBlock10 [ ] =
	{
		20.0f, -1.5f, 0.6f,			// /| 
		20.0f, 2.0f, 0.6f,			// || 
		19.5f, 2.0f, 0.6f,			// \|
		19.5f, -1.5f, 0.6f			
	};
	GLfloat CVBlock11 [ ] =
	{
		20.0f, 2.5f, 0.6f,			
		0.0f, 2.5f, 0.6f,			//  ______________ 
		0.0f, 2.0f, 0.6f,			//  \____________/
		20.0f, 2.0f, 0.6f
	};
	GLfloat CVBlock12 [ ] =
	{
		0.0f, 2.0f, 0.6f,			// |\ 
		0.0f, -1.5f, 0.6f,			// ||
		0.5f, -1.5f, 0.6f,			// |/
		0.5f, 2.0f, 0.6f
	};
	//----------------------Задняя панель--------------------------//
	GLfloat CVBlock13 [ ] =
	{
		0.0f, -2.5f, 0.0f,
		20.0f, -2.5f, 0.0f,			//   ____________
		20.0f, -1.5f, 0.0f,			//  /____________\ 
		0.0f, -1.5f, 0.0f
	};
	GLfloat CVBlock14 [ ] =
	{
		20.0f, -1.5f, 0.0f,			// /|
		20.0f, 2.0f, 0.0f,			// ||
		19.5f, 2.0f, 0.0f,			// \|
		19.5f, -1.5f, 0.0f
	};
	GLfloat CVBlock15 [ ] =
	{
		20.0f, 2.5f, 0.0f,
		0.0f, 2.5f, 0.0f,			//  ______________ 
		0.0f, 2.0f, 0.0f,			//  \____________/
		20.0f, 2.0f, 0.0f
	};
	GLfloat CVBlock16 [ ] =
	{
		0.0f, 2.0f, 0.0f,			// |\ 
		0.0f, -1.5f, 0.0f,			// ||
		0.5f, -1.5f, 0.0f,			// |/
		0.5f, 2.0f, 0.0f
	};
	//-------------Нижняя панель (передняя сторона)-------------//
	GLfloat CVBlock17 [ ] =
	{
		0.25f, -4.5f, 0.6f,			//  ________________ 
		19.75f, -4.5f, 0.6f,		// | |____________| |
		19.75f, -4.25f, 0.6f,		// | |____________| |
		0.25f, -4.25f, 0.6f			// |_|            |_|
	};
	GLfloat CVBlock18 [ ] =
	{
		20.0f, -4.5f, 0.6f,			//  ______________
		20.0f, -2.5f, 0.6f,			// | |____________| 
		19.75f, -2.5f, 0.6f,		// | |____________| 
		19.75f, -4.5f, 0.6f			// |_|____________|
	};
	GLfloat CVBlock19 [ ] =
	{
		19.75f, -2.5f, 0.6f,		//  _              _ 
		0.25f, -2.5f, 0.6f,			// | |____________| |		
		0.25f, -2.75f, 0.6f,		// | |____________| |	
		19.75f, -2.75f, 0.6f		// |_|____________|_|
	};
	GLfloat CVBlock20 [ ] =
	{
		0.0f, -2.5f, 0.6f,			//    ______________ 
		0.0f, -4.5f, 0.6f,			//   |____________| |		
		0.25f, -4.5f, 0.6f,			//   |____________| |
		0.25f, -2.5f, 0.6f			//   |____________|_|
	};
	GLfloat CVBlock21 [ ] =
	{								
		0.25f, -4.25f, 0.6f,		//  ______________ 
		19.75f, -4.25f, 0.6f,		// | ____________ |
		19.75f, -4.25f, 0.35f,		// ||            ||
		0.25f, -4.25f, 0.35f		// |______________|
	};
	GLfloat CVBlock22 [ ] =
	{
		19.75f, -4.25f, 0.6f,		//  ______________ 
		19.75f, -2.75f, 0.6f,		// | ____________ |
		19.75f, -2.75f, 0.35f,		// ||____________ |
		19.75f, -4.25f, 0.35f		// |______________|
	};
	GLfloat CVBlock23 [ ] =
	{	
		19.75f, -2.75f, 0.6f,		//  ______________
		0.25f, -2.75f, 0.6f,		// |              |
		0.25f, -2.75f, 0.35f,		// ||____________||
		19.75f, -2.75f, 0.35f		// |______________|
	};
	GLfloat CVBlock24 [ ] =
	{	
		0.25f, -2.75f, 0.6f,		//  ______________ 
		0.25f, -4.25f, 0.6f,		// | ____________ |
		0.25f, -4.25f, 0.35f,		// | ____________||
		0.25f, -2.75f, 0.35f		// |______________|
	};
	//------------Нижняя панель (задняя маленькая №1)-------------//
	GLfloat CVBlock25_1 [ ] =
	{
		0.25f, -3.75f, 0.35f,		//  ______________
		19.75f, -3.75f, 0.35f,		// |			  |
		19.75f, -2.75f, 0.35f,		// |______________|
		0.25f, -2.75f, 0.35f		
	};
	//------------Нижняя панель (задняя маленькая №1)-------------//
	GLfloat CVBlock25_2 [ ] =
	{
		0.25f, -4.25f, 0.35f,		//  ______________
		19.75f, -4.25f, 0.35f,		// |			  |
		19.75f, -3.75f, 0.35f,		// |______________|
		0.25f, -3.75f, 0.35f		
	};
	//-------------Нижняя панель (задняя большая)--------------//
	GLfloat CVBlock26 [ ] =
	{
		0.0f, -4.5f, 0.0f,			//  ______________
		20.0f, -4.5f, 0.0f,			// |			  |
		20.0f, -2.5f, 0.0f,			// |			  |
		0.0f, -2.5f, 0.0f			// |______________|
	};
	//------------Правая панель (передняя сторона)-------------//
	GLfloat CVBlock27 [ ] =
	{
		20.5f, 2.0f, 0.6f,			//  ______________	1 верхняя
		24.5f, 2.0f, 0.6f,			// |			  |
		24.5f, 2.5f, 0.6f,			// |			  |
		20.5f, 2.5f, 0.6f			// |______________|
	};
	GLfloat CVBlock28 [ ] =
	{
		20.5f, 0.5f, 0.6f,			//  ______________	2 верхняя
		24.5f, 0.5f, 0.6f,			// |			  |
		24.5f, 1.0f, 0.6f,			// |			  |
		20.5f, 1.0f, 0.6f			// |______________|
	};
	GLfloat CVBlock29 [ ] =
	{
		20.5f, -1.0f, 0.6f,			//  ______________	3 верхняя
		24.5f, -1.0f, 0.6f,			// |			  |
		24.5f, -0.5f, 0.6f,			// |			  |
		20.5f, -0.5f, 0.6f			// |______________|
	};
	GLfloat CVBlock30 [ ] =
	{
		20.5f, -2.5f, 0.6f,			//  ______________	4 верхняя
		24.5f, -2.5f, 0.6f,			// |			  |
		24.5f, -2.0f, 0.6f,			// |			  |
		20.5f, -2.0f, 0.6f			// |______________|
	};
	GLfloat CVBlock54 [ ] =
	{
		20.5f, -4.5f, 0.6f,			//  ______________	5 верхняя
		24.5f, -4.5f, 0.6f,			// |			  |
		24.5f, -3.5f, 0.6f,			// |			  |
		20.5f, -3.5f, 0.6f			// |______________|
	};
	GLfloat CVBlock31 [ ] =
	{
		20.0f, -4.5f, 0.6f,			//  ___	 левая
		20.5f, -4.5f, 0.6f,			// |   |
		20.5f, 2.5f, 0.6f,			// |   |
		20.0f, 2.5f, 0.6f			// |___|
	};
	GLfloat CVBlock32 [ ] =
	{
		24.5f, -4.5f, 0.6f,			//  ___	 правая
		25.0f, -4.5f, 0.6f,			// |   |
		25.0f, 2.5f, 0.6f,			// |   |
		24.5f, 2.5f, 0.6f			// |___|
	};
	//----------Правая панель (внутренний контур №1)-----------//
	GLfloat CVBlock33 [ ] =
	{								
		20.5f, 1.0f, 0.6f,			//  ______________ 
		24.5f, 1.0f, 0.6f,			// | ____________ |
		24.5f, 1.0f, 0.55f,			// ||            ||
		20.5f, 1.0f, 0.55f			// |______________|
	};
	GLfloat CVBlock34 [ ] =
	{
		24.5f, 1.0f, 0.6f,			//  ______________ 
		24.5f, 2.0f, 0.6f,			// | ____________ |
		24.5f, 2.0f, 0.55f,			// ||____________ |
		24.5f, 1.0f, 0.55f			// |______________|
	};
	GLfloat CVBlock35 [ ] =
	{	
		24.5f, 2.0f, 0.6f,			//  ______________
		20.5f, 2.0f, 0.6f,			// |              |
		20.5f, 2.0f, 0.55f,			// ||____________||
		24.5f, 2.0f, 0.55f			// |______________|
	};
	GLfloat CVBlock36 [ ] =
	{	
		20.5f, 2.0f, 0.6f,			//  ______________ 
		20.5f, 1.0f, 0.6f,			// | ____________ |
		20.5f, 1.0f, 0.55f,			// | ____________||
		20.5f, 2.0f, 0.55f			// |______________|
	};
	//----------Правая панель (внутренний контур №2)-----------//
	GLfloat CVBlock37 [ ] =
	{								
		20.5f, -0.5f, 0.6f,			//  ______________ 
		24.5f, -0.5f, 0.6f,			// | ____________ |
		24.5f, -0.5f, 0.55f,		// ||            ||
		20.5f, -0.5f, 0.55f			// |______________|
	};
	GLfloat CVBlock38 [ ] =
	{
		24.5f, -0.5f, 0.6f,			//  ______________ 
		24.5f, 0.5f, 0.6f,			// | ____________ |
		24.5f, 0.5f, 0.55f,			// ||____________ |
		24.5f, -0.5f, 0.55f			// |______________|
	};
	GLfloat CVBlock39 [ ] =
	{	
		24.5f, 0.5f, 0.6f,			//  ______________
		20.5f, 0.5f, 0.6f,			// |              |
		20.5f, 0.5f, 0.55f,			// ||____________||
		24.5f, 0.5f, 0.55f			// |______________|
	};
	GLfloat CVBlock40 [ ] =
	{	
		20.5f, 0.5f, 0.6f,			//  ______________ 
		20.5f, -0.5f, 0.6f,			// | ____________ |
		20.5f, -0.5f, 0.55f,		// | ____________||
		20.5f, 0.5f, 0.55f			// |______________|
	};
	//----------Правая панель (внутренний контур №3)-----------//
	GLfloat CVBlock41 [ ] =
	{								
		20.5f, -2.0f, 0.6f,			//  ______________ 
		24.5f, -2.0f, 0.6f,			// | ____________ |
		24.5f, -2.0f, 0.55f,		// ||            ||
		20.5f, -2.0f, 0.55f			// |______________|
	};
	GLfloat CVBlock42 [ ] =
	{
		24.5f, -2.0f, 0.6f,			//  ______________ 
		24.5f, -1.0f, 0.6f,			// | ____________ |
		24.5f, -1.0f, 0.55f,		// ||____________ |
		24.5f, -2.0f, 0.55f			// |______________|
	};
	GLfloat CVBlock43 [ ] =
	{	
		24.5f, -1.0f, 0.6f,			//  ______________
		20.5f, -1.0f, 0.6f,			// |              |
		20.5f, -1.0f, 0.55f,		// ||____________||
		24.5f, -1.0f, 0.55f			// |______________|
	};
	GLfloat CVBlock44 [ ] =
	{	
		20.5f, -1.0f, 0.6f,			//  ______________ 
		20.5f, -2.0f, 0.6f,			// | ____________ |
		20.5f, -2.0f, 0.55f,		// | ____________||
		20.5f, -1.0f, 0.55f			// |______________|
	};
	//----------Правая панель (внутренний контур №4)-----------//
	GLfloat CVBlock49 [ ] =
	{								
		20.5f, -3.5f, 0.6f,			//  ______________ 
		24.5f, -3.5f, 0.6f,			// | ____________ |
		24.5f, -3.5f, 0.55f,		// ||            ||
		20.5f, -3.5f, 0.55f			// |______________|
	};
	GLfloat CVBlock50 [ ] =
	{
		24.5f, -3.5f, 0.6f,			//  ______________ 
		24.5f, -2.0f, 0.6f,			// | ____________ |
		24.5f, -2.0f, 0.55f,		// ||____________ |
		24.5f, -3.5f, 0.55f			// |______________|
	};
	GLfloat CVBlock51 [ ] =
	{	
		24.5f, -2.0f, 0.6f,			//  ______________
		20.5f, -2.0f, 0.6f,			// |              |
		20.5f, -2.0f, 0.55f,		// ||____________||
		24.5f, -2.0f, 0.55f			// |______________|
	};
	GLfloat CVBlock52 [ ] =
	{	
		20.5f, -2.0f, 0.6f,			//  ______________ 
		20.5f, -3.5f, 0.6f,			// | ____________ |
		20.5f, -3.5f, 0.55f,		// | ____________||
		20.5f, -2.0f, 0.55f			// |______________|
	};
	//----------Правая панель (задняя маленькая №1)-----------//
	GLfloat CVBlock45 [ ] =
	{
		20.5f, 1.0f, 0.55f,			//  ______________
		24.5f, 1.0f, 0.55f,			// |			  |
		24.5f, 2.0f, 0.55f,			// |______________|
		20.5f, 2.0f, 0.55f		
	};
	//----------Правая панель (задняя маленькая №2)-----------//
	GLfloat CVBlock46 [ ] =
	{
		20.5f, -0.5f, 0.55f,		//  ______________
		24.5f, -0.5f, 0.55f,		// |			  |
		24.5f, 0.5f, 0.55f,			// |______________|
		20.5f, 0.5f, 0.55f		
	};
	//----------Правая панель (задняя маленькая №3)-----------//
	GLfloat CVBlock47 [ ] =
	{
		20.5f, -2.0f, 0.55f,		//  ______________
		24.5f, -2.0f, 0.55f,		// |			  |
		24.5f, -1.0f, 0.55f,		// |______________|
		20.5f, -1.0f, 0.55f		
	};
	//----------Правая панель (задняя маленькая №4)-----------//
	GLfloat CVBlock53 [ ] =
	{
		20.5f, -3.5f, 0.55f,		//  ______________
		24.5f, -3.5f, 0.55f,		// |			  |
		24.5f, -2.0f, 0.55f,		// |______________|
		20.5f, -2.0f, 0.55f		
	};
	//-------------Правая панель (задняя большая)--------------//
	GLfloat CVBlock48 [ ] =
	{
		20.0f, -4.5f, 0.0f,			//  ______________
		25.0f, -4.5f, 0.0f,			// |			  |
		25.0f, 2.5f, 0.0f,			// |			  |
		20.0f, 2.5f, 0.0f			// |______________|
	};
	//-------------BG--------------//
	GLfloat CVBlock55 [ ] =
	{
		-50.0f, -50.0f, -0.0f,			//  ______________
		50.0f, -50.0f, -0.0f,			// |			  |
		50.0f, 50.0f, -0.0f,			// |			  |
		-50.0f, 50.0f, -0.0f			// |______________|
	};
# pragma endregion
# pragma region Верщины текстурных координат
	static GLfloat TCBlock01 [ ] =
	{		
		 0, 1,	1, 1,	1, 0,	0, 0		 
	};
	static GLfloat TCBlock02 [ ] =
	{		
		 0, 0,	1, 0,	1, 1,	0, 1		 
	};
	static GLfloat TCBlock03 [ ] =
	{		 
		 1, 1,	1, 0,	0, 0,	0, 1
	};
	static GLfloat TCBlock04 [ ] =
	{		 
		 1, 1,	0, 1,	0, 0,	1, 0	
	};
	static GLfloat TCBlock05 [ ] =
	{		 
		 0, 0,	0, 1,	1, 1,	1, 0	
	};
	static GLfloat TCBlock06 [ ] =
	{		
		 1, 0,	0, 0,	0, 1,	1, 1
	};	
# pragma endregion
# pragma region Отрисовка OpenGL		
	glPushMatrix();
		glEnableClientState ( GL_VERTEX_ARRAY );
		glEnableClientState ( GL_TEXTURE_COORD_ARRAY );		
			DrawQ ( Texture, TCBlock02, 1, CVBlock01 );			DrawQ ( Texture, TCBlock03, 2, CVBlock02 );
			DrawQ ( Texture, TCBlock01, 3, CVBlock03 );			DrawQ ( Texture, TCBlock03, 4, CVBlock04 );
			DrawQ ( Texture, TCBlock02, 7, CVBlock05 );			DrawQ ( Texture, TCBlock02, 8, CVBlock06 );
			DrawQ ( Texture, TCBlock02, 7, CVBlock07 );			DrawQ ( Texture, TCBlock06, 8, CVBlock08 );

			DrawQ ( Texture, TCBlock02, 9, CVBlock09 );			DrawQ ( Texture, TCBlock05, 10, CVBlock10 );
			DrawQ ( Texture, TCBlock04, 11, CVBlock11 );		DrawQ ( Texture, TCBlock05, 12, CVBlock12 );
			DrawQ ( Texture, TCBlock06, 9, CVBlock13 );			DrawQ ( Texture, TCBlock05, 10, CVBlock14 );
			DrawQ ( Texture, TCBlock04, 11, CVBlock15 );		DrawQ ( Texture, TCBlock03, 12, CVBlock16 );
			
			DrawQ ( Texture, TCBlock02, 14, CVBlock17 );		DrawQ ( Texture, TCBlock05, 15, CVBlock18 );
			DrawQ ( Texture, TCBlock04, 16, CVBlock19 );		DrawQ ( Texture, TCBlock03, 17, CVBlock20 );
			DrawQ ( Texture, TCBlock02, 1, CVBlock21 );			DrawQ ( Texture, TCBlock03, 2, CVBlock22 );
			DrawQ ( Texture, TCBlock01, 3, CVBlock23 );			DrawQ ( Texture, TCBlock01, 4, CVBlock24 );

			DrawQ ( Texture, TCBlock02, 25, CVBlock25_1 );		DrawQ ( Texture, TCBlock02, NOT, CVBlock25_2 );
			
			DrawQ ( Texture, TCBlock06, 18, CVBlock26 );
			DrawQ ( Texture, TCBlock02, 19, CVBlock27 );		DrawQ ( Texture, TCBlock02, 20, CVBlock28 );
			DrawQ ( Texture, TCBlock02, 21, CVBlock29 );		DrawQ ( Texture, TCBlock02, 22, CVBlock30 );
			DrawQ ( Texture, TCBlock02, 23, CVBlock31 );		DrawQ ( Texture, TCBlock02, 24, CVBlock32 );

			DrawQ ( Texture, TCBlock02, 1, CVBlock33 );			DrawQ ( Texture, TCBlock03, 2, CVBlock34 );
			DrawQ ( Texture, TCBlock01, 3, CVBlock35 );			DrawQ ( Texture, TCBlock01, 4, CVBlock36 );
			DrawQ ( Texture, TCBlock02, 1, CVBlock37 );			DrawQ ( Texture, TCBlock03, 2, CVBlock38 );
			DrawQ ( Texture, TCBlock01, 3, CVBlock39 );			DrawQ ( Texture, TCBlock01, 4, CVBlock40 );

			DrawQ ( Texture, TCBlock02, 1, CVBlock41 );			DrawQ ( Texture, TCBlock03, 2, CVBlock42 );
			DrawQ ( Texture, TCBlock01, 3, CVBlock43 );			DrawQ ( Texture, TCBlock01, 4, CVBlock44 );
			DrawQ ( Texture, TCBlock01, 36, CVBlock45 );		DrawQ ( Texture, TCBlock01, 36, CVBlock46 );
			DrawQ ( Texture, TCBlock01, 36, CVBlock47 );		DrawQ ( Texture, TCBlock06, 37, CVBlock48 );

			DrawQ ( Texture, TCBlock02, 1, CVBlock49 );			DrawQ ( Texture, TCBlock03, 2, CVBlock50 );
			DrawQ ( Texture, TCBlock01, 3, CVBlock51 );			DrawQ ( Texture, TCBlock01, 4, CVBlock52 );
			DrawQ ( Texture, TCBlock01, 36, CVBlock53 );		DrawQ ( Texture, TCBlock02, 38, CVBlock54 );			
		glDisableClientState ( GL_TEXTURE_COORD_ARRAY );
		glDisableClientState ( GL_VERTEX_ARRAY );
	glPopMatrix();
# pragma endregion
}
void GLelements :: CreateQuadNoteLine ( float X, float Y, float Z, int R, int G, int B )
{	
	glTranslatef ( X, Y, Z );
# pragma region Координаты вершин 4-угольника
	GLfloat CVertex3OktElem01 [ ] =
	{						 
		 0.0f, -4.25f, 0.38f,	
		 0.0f, -2.75f, 0.38f,
		 0.025f, -2.75f, 0.38f,
		 0.025f, -4.25f, 0.38f	 
	};
	GLfloat CVertex3OktElem02 [ ] =
	{						 
		 0.025f, -4.25f, 0.38f,	
		 0.025f, -4.25f, 0.35f,
		 0.025f, -2.75f, 0.35f,
		 0.025f, -2.75f, 0.38f	 
	};
	GLfloat CVertex3OktElem03 [ ] =
	{						 
		 0.0f, -4.25f, 0.35f,	
		 0.0f, -4.25f, 0.38f,
		 0.0f, -2.75f, 0.38f,
		 0.0f, -2.75f, 0.35f	 
	};
# pragma endregion
# pragma region Номера вершин 4-угольника
	static GLushort QVertex3 [ ] =
	{
		 0, 1, 2, 3
	};
# pragma endregion
# pragma region Отрисовка OpenGL
	glPushMatrix();
		glEnable ( GL_LINE );
		glEnable ( GL_LINE_SMOOTH );		
		glEnableClientState ( GL_VERTEX_ARRAY );		
			glLineWidth ( 1.0f );
					glColor3ub ( R, G, B );
						glVertexPointer ( 3, GL_FLOAT, 0, CVertex3OktElem01 );		
						glDrawElements ( GL_QUADS, 4, GL_UNSIGNED_SHORT, QVertex3 );
						glVertexPointer ( 3, GL_FLOAT, 0, CVertex3OktElem02 );		
						glDrawElements ( GL_QUADS, 4, GL_UNSIGNED_SHORT, QVertex3 );
						glVertexPointer ( 3, GL_FLOAT, 0, CVertex3OktElem03 );		
						glDrawElements ( GL_QUADS, 4, GL_UNSIGNED_SHORT, QVertex3 );
					glColor3ub ( 255, 255, 255 );
			glPopName ( );
			glLineWidth ( 1.0f );
		glDisableClientState ( GL_VERTEX_ARRAY );
		glDisable ( GL_LINE_SMOOTH );
	glPopMatrix ( );
# pragma endregion
	glTranslatef ( -X, -Y, -Z );
}
void GLelements :: CreateTimeNum_0 ( float X, float Y, float Z, GLfloat HEIGHT, GLfloat RADIUS, GLfloat size, int R, int G, int B )
{
	glTranslatef ( X, Y, Z );
		glTranslatef ( 0.0f, 0.8f * size, 0.0f );			
		glRotatef ( 90.0f, 0.0f, 0.0f, 1.0f );						//	
			CreateTimeNumElement ( HEIGHT * size, RADIUS * size, R, G, B );	//	|_|
		glRotatef ( -90.0f, 0.0f, 0.0f, 1.0f );						//	|_|
		glTranslatef ( 0.0f, -0.8f * size, 0.0f );

		glTranslatef ( 0.0f, -0.8f * size, 0.0f );					//	 _
		glRotatef ( 90.0f, 0.0f, 0.0f, 1.0f );						//	|_|
			CreateTimeNumElement ( HEIGHT * size, RADIUS * size, R, G, B );	//	| |
		glRotatef ( -90.0f, 0.0f, 0.0f, 1.0f );
		glTranslatef ( 0.0f, 0.8f * size, 0.0f );					//

		glTranslatef ( -0.4f * size, 0.4f * size, 0.0f );			//	 _
			CreateTimeNumElement ( HEIGHT * size, RADIUS * size, R, G, B );	//   _|
		glTranslatef ( 0.4f * size, -0.4f * size, 0.0f );			//	|_|																	

		glTranslatef ( 0.4f * size, 0.4f * size, 0.0f );			//	 _
			CreateTimeNumElement ( HEIGHT * size, RADIUS * size, R, G, B );	//	|_
		glTranslatef ( -0.4f * size, -0.4f * size, 0.0f );			//	|_|

		glTranslatef ( -0.4f * size, -0.4f * size, 0.0f );			//   _	
			CreateTimeNumElement ( HEIGHT * size, RADIUS * size, R, G, B );	//  |_|
		glTranslatef ( 0.4f * size, 0.4f * size, 0.0f );			//   _|

		glTranslatef ( 0.4f * size, -0.4f * size, 0.0f );			//	 _
			CreateTimeNumElement ( HEIGHT * size, RADIUS * size, R, G, B );	//	|_|
		glTranslatef ( -0.4f * size, 0.4f * size, 0.0f );			//	|_
	glTranslatef ( -X,- Y, -Z );
}
void GLelements :: CreateTimeNum_1 ( float X, float Y, float Z, GLfloat HEIGHT, GLfloat RADIUS, GLfloat size, int R, int G, int B )
{
	glTranslatef ( X, Y, Z );				
		glTranslatef ( 0.4f * size, 0.4f * size, 0.0f );			//	 _
			CreateTimeNumElement ( HEIGHT * size, RADIUS * size, R, G, B );	//	|_
		glTranslatef ( -0.4f * size, -0.4f * size, 0.0f );			//	|_|

		glTranslatef ( 0.4f * size, -0.4f * size, 0.0f );			//	 _
			CreateTimeNumElement ( HEIGHT * size, RADIUS * size, R, G, B );	//	|_|
		glTranslatef ( -0.4f * size, 0.4f * size, 0.0f );			//	|_
	glTranslatef ( -X,- Y, -Z );
}
void GLelements :: CreateTimeNum_2 ( float X, float Y, float Z, GLfloat HEIGHT, GLfloat RADIUS, GLfloat size, int R, int G, int B )
{
	glTranslatef ( X, Y, Z );
		glTranslatef ( 0.0f, 0.8f * size, 0.0f );						// 
		glRotatef ( 90.0f, 0.0f, 0.0f, 1.0f );							//	
			CreateTimeNumElement ( HEIGHT * size, RADIUS * size, R, G, B );		//	|_|
		glRotatef ( -90.0f, 0.0f, 0.0f, 1.0f );							//	|_|
		glTranslatef ( 0.0f, -0.8f * size, 0.0f );

		glRotatef ( 90.0f, 0.0f, 0.0f, 1.0f );							//	 _
			CreateTimeNumElement ( HEIGHT * size, RADIUS * size, R, G, B );		//	| |
		glRotatef ( -90.0f, 0.0f, 0.0f, 1.0f );							//	|_|

		glTranslatef ( 0.0f, -0.8f * size, 0.0f );						//	 _
		glRotatef ( 90.0f, 0.0f, 0.0f, 1.0f );							//	|_|
			CreateTimeNumElement ( HEIGHT * size, RADIUS * size, R, G, B );		//	| |
		glRotatef ( -90.0f, 0.0f, 0.0f, 1.0f );
		glTranslatef ( 0.0f, 0.8f * size, 0.0f );							

		glTranslatef ( 0.4f * size, 0.4f * size, 0.0f );				//	 _
			CreateTimeNumElement ( HEIGHT * size, RADIUS * size, R, G, B );		//	|_
		glTranslatef ( -0.4f * size, -0.4f * size, 0.0f );				//	|_|

		glTranslatef ( -0.4f * size, -0.4f * size, 0.0f );				//   _	
			CreateTimeNumElement ( HEIGHT * size, RADIUS * size, R, G, B );		//  |_|
		glTranslatef ( 0.4f * size, 0.4f * size, 0.0f );				//   _|
	glTranslatef ( -X,- Y, -Z );
}
void GLelements :: CreateTimeNum_3 ( float X, float Y, float Z, GLfloat HEIGHT, GLfloat RADIUS, GLfloat size, int R, int G, int B )
{
	glTranslatef ( X, Y, Z );
		glTranslatef ( 0.0f, 0.8f * size, 0.0f );					
		glRotatef ( 90.0f, 0.0f, 0.0f, 1.0f );							//	
			CreateTimeNumElement ( HEIGHT * size, RADIUS * size, R, G, B );		//	|_|
		glRotatef ( -90.0f, 0.0f, 0.0f, 1.0f );							//	|_|
		glTranslatef ( 0.0f, -0.8f * size, 0.0f );

		glRotatef ( 90.0f, 0.0f, 0.0f, 1.0f );							//	 _
			CreateTimeNumElement ( HEIGHT * size, RADIUS * size, R, G, B );		//	| |
		glRotatef ( -90.0f, 0.0f, 0.0f, 1.0f );							//	|_|

		glTranslatef ( 0.0f, -0.8f * size, 0.0f );						//	 _
		glRotatef ( 90.0f, 0.0f, 0.0f, 1.0f );							//	|_|
			CreateTimeNumElement ( HEIGHT * size, RADIUS * size, R, G, B );		//	| |
		glRotatef ( -90.0f, 0.0f, 0.0f, 1.0f );
		glTranslatef ( 0.0f, 0.8f * size, 0.0f );			

		glTranslatef ( 0.4f * size, 0.4f * size, 0.0f );				//	 _
			CreateTimeNumElement ( HEIGHT * size, RADIUS * size, R, G, B );		//	|_
		glTranslatef ( -0.4f * size, -0.4f * size, 0.0f );				//	|_|
		
		glTranslatef ( 0.4f * size, -0.4f * size, 0.0f );				//	 _
			CreateTimeNumElement ( HEIGHT * size, RADIUS * size, R, G, B );		//	|_|
		glTranslatef ( -0.4f * size, 0.4f * size, 0.0f );				//	|_
	glTranslatef ( -X,- Y, -Z );
}
void GLelements :: CreateTimeNum_4 ( float X, float Y, float Z, GLfloat HEIGHT, GLfloat RADIUS, GLfloat size, int R, int G, int B )
{
	glTranslatef ( X, Y, Z );
		glRotatef ( 90.0f, 0.0f, 0.0f, 1.0f );							//	 _
			CreateTimeNumElement ( HEIGHT * size, RADIUS * size, R, G, B );		//	| |
		glRotatef ( -90.0f, 0.0f, 0.0f, 1.0f );							//	|_|
		
		glTranslatef ( -0.4f * size, 0.4f * size, 0.0f );				//	 _
			CreateTimeNumElement ( HEIGHT * size, RADIUS * size, R, G, B );		//   _|
		glTranslatef ( 0.4f * size, -0.4f * size, 0.0f );				//	|_|
																		

		glTranslatef ( 0.4f * size, 0.4f * size, 0.0f );				//	 _
			CreateTimeNumElement ( HEIGHT * size, RADIUS * size, R, G, B );		//	|_
		glTranslatef ( -0.4f * size, -0.4f * size, 0.0f );				//	|_|

		glTranslatef ( 0.4f * size, -0.4f * size, 0.0f );				//	 _
			CreateTimeNumElement ( HEIGHT * size, RADIUS * size, R, G, B );		//	|_|
		glTranslatef ( -0.4f * size, 0.4f * size, 0.0f );				//	|_
	glTranslatef ( -X,- Y, -Z );
}
void GLelements :: CreateTimeNum_5 ( float X, float Y, float Z, GLfloat HEIGHT, GLfloat RADIUS, GLfloat size, int R, int G, int B )
{
	glTranslatef ( X, Y, Z );
		glTranslatef ( 0.0f, 0.8f * size, 0.0f );			
		glRotatef ( 90.0f, 0.0f, 0.0f, 1.0f );		
			CreateTimeNumElement ( HEIGHT * size, RADIUS * size, R, G, B );		//	|_|
		glRotatef ( -90.0f, 0.0f, 0.0f, 1.0f );							//	|_|
		glTranslatef ( 0.0f, -0.8f * size, 0.0f );

		glRotatef ( 90.0f, 0.0f, 0.0f, 1.0f );							//	 _
			CreateTimeNumElement ( HEIGHT * size, RADIUS * size, R, G, B );		//	| |
		glRotatef ( -90.0f, 0.0f, 0.0f, 1.0f );							//	|_|

		glTranslatef ( 0.0f, -0.8f * size, 0.0f );						//	 _
		glRotatef ( 90.0f, 0.0f, 0.0f, 1.0f );							//	|_|
			CreateTimeNumElement ( HEIGHT * size, RADIUS * size, R, G, B );		//	| |
		glRotatef ( -90.0f, 0.0f, 0.0f, 1.0f );
		glTranslatef ( 0.0f, 0.8f * size, 0.0f );			

		glTranslatef ( -0.4f * size, 0.4f * size, 0.0f );				//	 _
			CreateTimeNumElement ( HEIGHT * size, RADIUS * size, R, G, B );		//   _|
		glTranslatef ( 0.4f * size, -0.4f * size, 0.0f );				//	|_|
																		

		glTranslatef ( 0.4f * size, -0.4f * size, 0.0f );				//	 _
			CreateTimeNumElement ( HEIGHT * size, RADIUS * size, R, G, B );		//	|_|
		glTranslatef ( -0.4f * size, 0.4f * size, 0.0f );				//	|_
	glTranslatef ( -X,- Y, -Z );
}
void GLelements :: CreateTimeNum_6 ( float X, float Y, float Z, GLfloat HEIGHT, GLfloat RADIUS, GLfloat size, int R, int G, int B )
{
	glTranslatef ( X, Y, Z );
		glTranslatef ( 0.0f, 0.8f * size, 0.0f );						
		glRotatef ( 90.0f, 0.0f, 0.0f, 1.0f );						
			CreateTimeNumElement ( HEIGHT * size, RADIUS * size, R, G, B );		//	|_|
		glRotatef ( -90.0f, 0.0f, 0.0f, 1.0f );							//	|_|
		glTranslatef ( 0.0f, -0.8f * size, 0.0f );

		glRotatef ( 90.0f, 0.0f, 0.0f, 1.0f );							//	 _
			CreateTimeNumElement ( HEIGHT * size, RADIUS * size, R, G, B );		//	| |
		glRotatef ( -90.0f, 0.0f, 0.0f, 1.0f );							//	|_|

		glTranslatef ( 0.0f, -0.8f * size, 0.0f );						//	 _
		glRotatef ( 90.0f, 0.0f, 0.0f, 1.0f );							//	|_|
			CreateTimeNumElement ( HEIGHT * size, RADIUS * size, R, G, B );		//	| |
		glRotatef ( -90.0f, 0.0f, 0.0f, 1.0f );
		glTranslatef ( 0.0f, 0.8f * size, 0.0f );			

		glTranslatef ( -0.4f * size, 0.4f * size, 0.0f );				//   _
			CreateTimeNumElement ( HEIGHT * size, RADIUS * size, R, G, B );		//	 _| 
		glTranslatef ( 0.4f * size, -0.4f * size, 0.0f );				//  |_|

		glTranslatef ( -0.4f * size, -0.4f * size, 0.0f );				//   _	
			CreateTimeNumElement ( HEIGHT * size, RADIUS * size, R, G, B );		//  |_|
		glTranslatef ( 0.4f * size, 0.4f * size, 0.0f );				//   _|

		glTranslatef ( 0.4f * size, -0.4f * size, 0.0f );				//	 _
			CreateTimeNumElement ( HEIGHT * size, RADIUS * size, R, G, B );		//	|_|
		glTranslatef ( -0.4f * size, 0.4f * size, 0.0f );				//	|_
	glTranslatef ( -X,- Y, -Z );
}
void GLelements :: CreateTimeNum_7 ( float X, float Y, float Z, GLfloat HEIGHT, GLfloat RADIUS, GLfloat size, int R, int G, int B )
{
	glTranslatef ( X, Y, Z );
		glTranslatef ( 0.0f, 0.8f * size, 0.0f );			
		glRotatef ( 90.0f, 0.0f, 0.0f, 1.0f );		
			CreateTimeNumElement ( HEIGHT * size, RADIUS * size, R, G, B );		//	|_|
		glRotatef ( -90.0f, 0.0f, 0.0f, 1.0f );							//	|_|
		glTranslatef ( 0.0f, -0.8f * size, 0.0f );
				
		glTranslatef ( 0.4f * size, 0.4f * size, 0.0f );				//	 _
			CreateTimeNumElement ( HEIGHT * size, RADIUS * size, R, G, B );		//	|_
		glTranslatef ( -0.4f * size, -0.4f * size, 0.0f );				//	|_|		

		glTranslatef ( 0.4f * size, -0.4f * size, 0.0f );				//	 _
			CreateTimeNumElement ( HEIGHT * size, RADIUS * size, R, G, B );		//	|_|
		glTranslatef ( -0.4f * size, 0.4f * size, 0.0f );				//	|_
	glTranslatef ( -X,- Y, -Z );
}
void GLelements :: CreateTimeNum_8 ( float X, float Y, float Z, GLfloat HEIGHT, GLfloat RADIUS, GLfloat size, int R, int G, int B )
{
	glTranslatef ( X, Y, Z );
		glTranslatef ( 0.0f, 0.8f * size, 0.0f );			
		glRotatef ( 90.0f, 0.0f, 0.0f, 1.0f );		
			CreateTimeNumElement ( HEIGHT * size, RADIUS * size, R, G, B );		//	|_|
		glRotatef ( -90.0f, 0.0f, 0.0f, 1.0f );							//	|_|
		glTranslatef ( 0.0f, -0.8f * size, 0.0f );

		glRotatef ( 90.0f, 0.0f, 0.0f, 1.0f );							//	 _
			CreateTimeNumElement ( HEIGHT * size, RADIUS * size, R, G, B );		//	| |
		glRotatef ( -90.0f, 0.0f, 0.0f, 1.0f );							//	|_|

		glTranslatef ( 0.0f, -0.8f * size, 0.0f );						//	 _
		glRotatef ( 90.0f, 0.0f, 0.0f, 1.0f );							//	|_|
			CreateTimeNumElement ( HEIGHT * size, RADIUS * size, R, G, B );		//	| |
		glRotatef ( -90.0f, 0.0f, 0.0f, 1.0f );
		glTranslatef ( 0.0f, 0.8f * size, 0.0f );			

		glTranslatef ( -0.4f * size, 0.4f * size, 0.0f );				//	 _
			CreateTimeNumElement ( HEIGHT * size, RADIUS * size, R, G, B );		//   _|
		glTranslatef ( 0.4f * size, -0.4f * size, 0.0f );				//	|_|																		

		glTranslatef ( 0.4f * size, 0.4f * size, 0.0f );				//	 _
			CreateTimeNumElement ( HEIGHT * size, RADIUS * size, R, G, B );		//	|_
		glTranslatef ( -0.4f * size, -0.4f * size, 0.0f );				//	|_|

		glTranslatef ( -0.4f * size, -0.4f * size, 0.0f );				//   _	
			CreateTimeNumElement ( HEIGHT * size, RADIUS * size, R, G, B );		//  |_|
		glTranslatef ( 0.4f * size, 0.4f * size, 0.0f );				//   _|

		glTranslatef ( 0.4f * size, -0.4f * size, 0.0f );				//	 _
			CreateTimeNumElement ( HEIGHT * size, RADIUS * size, R, G, B );		//	|_|
		glTranslatef ( -0.4f * size, 0.4f * size, 0.0f );				//	|_
	glTranslatef ( -X,- Y, -Z );
}
void GLelements :: CreateTimeNum_9 ( float X, float Y, float Z, GLfloat HEIGHT, GLfloat RADIUS, GLfloat size, int R, int G, int B )
{
	glTranslatef ( X, Y, Z );
		glTranslatef ( 0.0f, 0.8f * size, 0.0f );			
		glRotatef ( 90.0f, 0.0f, 0.0f, 1.0f );		
			CreateTimeNumElement ( HEIGHT * size, RADIUS * size, R, G, B );		//	|_|
		glRotatef ( -90.0f, 0.0f, 0.0f, 1.0f );							//	|_|
		glTranslatef ( 0.0f, -0.8f * size, 0.0f );

		glRotatef ( 90.0f, 0.0f, 0.0f, 1.0f );							//	 _
			CreateTimeNumElement ( HEIGHT * size, RADIUS * size, R, G, B );		//	| |
		glRotatef ( -90.0f, 0.0f, 0.0f, 1.0f );							//	|_|

		glTranslatef ( 0.0f, -0.8f * size, 0.0f );						//	 _
		glRotatef ( 90.0f, 0.0f, 0.0f, 1.0f );							//	|_|
			CreateTimeNumElement ( HEIGHT * size, RADIUS * size, R, G, B );		//	| |
		glRotatef ( -90.0f, 0.0f, 0.0f, 1.0f );
		glTranslatef ( 0.0f, 0.8f * size, 0.0f );			

		glTranslatef ( -0.4f * size, 0.4f * size, 0.0f );				//	 _
			CreateTimeNumElement ( HEIGHT * size, RADIUS * size, R, G, B );		//   _|
		glTranslatef ( 0.4f * size, -0.4f * size, 0.0f );				//	|_|																		

		glTranslatef ( 0.4f * size, 0.4f * size, 0.0f );				//	 _
			CreateTimeNumElement ( HEIGHT * size, RADIUS * size, R, G, B );		//	|_
		glTranslatef ( -0.4f * size, -0.4f * size, 0.0f );				//	|_|

		glTranslatef ( 0.4f * size, -0.4f * size, 0.0f );				//	 _
			CreateTimeNumElement ( HEIGHT * size, RADIUS * size, R, G, B );		//	|_|
		glTranslatef ( -0.4f * size, 0.4f * size, 0.0f );				//	|_
	glTranslatef ( -X,- Y, -Z );
}

# endif