
# include "Main.h"
# include "glelements.h"

# define TEX_BIG_STEND01_02	12

void GLelements :: CreateTimeNumElement ( GLfloat HEIGHT, GLfloat RADIUS )
{	
# pragma region Координаты вершин 6-угольника
	static GLfloat CVertex3TineElem [ ] =
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
	static GLushort	QVertex3 [ ] =
	{
		 0,  1,  2,	 3,  4,  5
	};
# pragma endregion
# pragma region Вершины тексурных координат
	static GLfloat TexCoordString [ ] =
	{
		1, 1,	1, 0,	0, 0,	0, 1,	//1..8//
	};
# pragma endregion
# pragma region Отрисовка OpenGL
	glPushMatrix();
	glEnable(GL_LINE);
	glEnable(GL_LINE_SMOOTH);	
	glEnableClientState ( GL_VERTEX_ARRAY );
	glEnableClientState ( GL_TEXTURE_COORD_ARRAY );
		glLineWidth ( 2.0f );
		glColor3ub ( 255, 0, 0);
		glBindTexture ( GL_TEXTURE_2D, textures [ 12 ].texID );
		glPushName ( TEX_BIG_STEND01_02 );
				glTexCoordPointer ( 2, GL_FLOAT, 0, TexCoordString );
				glVertexPointer ( 3, GL_FLOAT, 0, CVertex3TineElem );		
			    glDrawElements ( GL_LINE_STRIP, 7, GL_UNSIGNED_SHORT, QVertex3 );
		glPopName();
		glLineWidth ( 1.0f );
	glDisableClientState ( GL_VERTEX_ARRAY );
	glDisableClientState ( GL_TEXTURE_COORD_ARRAY );
	glDisable(GL_LINE_SMOOTH);
	glPopMatrix();
# pragma endregion
}
void GLelements :: CreateTimeNum_0 ( float X, float Y, float Z )
{
	glTranslatef ( X, Y, Z );
		glTranslatef ( 0.0f, 0.8f, 0.0f );			// Горизонтальный блок
		glRotatef ( 90.0f, 0.0f, 0.0f, 1.0f );		//	
			CreateTimeNumElement ( 0.38, 0.1 );		//	|_|
		glRotatef ( -90.0f, 0.0f, 0.0f, 1.0f );		//	|_|
		glTranslatef ( 0.0f, -0.8f, 0.0f );

		glTranslatef ( 0.0f, -0.8f, 0.0f );			//	 _
		glRotatef ( 90.0f, 0.0f, 0.0f, 1.0f );		//	|_|
			CreateTimeNumElement ( 0.38, 0.1 );		//	| |
		glRotatef ( -90.0f, 0.0f, 0.0f, 1.0f );
		glTranslatef ( 0.0f, 0.8f, 0.0f );			//

		glTranslatef ( -0.4f, 0.4f, 0.0f );			// Вертикальный блок
			CreateTimeNumElement ( 0.38, 0.1 );		//	 _
		glTranslatef ( 0.4f, -0.4f, 0.0f );			//   _|
													//	|_|

		glTranslatef ( 0.4f, 0.4f, 0.0f );			//	 _
			CreateTimeNumElement ( 0.38, 0.1 );		//	|_
		glTranslatef ( -0.4f, -0.4f, 0.0f );		//	|_|

		glTranslatef ( -0.4f, -0.4f, 0.0f );		//   _	
			CreateTimeNumElement ( 0.38, 0.1 );		//  |_|
		glTranslatef ( 0.4f, 0.4f, 0.0f );			//   _|

		glTranslatef ( 0.4f, -0.4f, 0.0f );			//	 _
			CreateTimeNumElement ( 0.38, 0.1 );		//	|_|
		glTranslatef ( -0.4f, 0.4f, 0.0f );			//	|_
	glTranslatef ( -X,- Y, -Z );
}
void GLelements :: CreateTimeNum_1 ( float X, float Y, float Z )
{
	glTranslatef ( X, Y, Z );				
		glTranslatef ( 0.4f, 0.4f, 0.0f );			//	 _
			CreateTimeNumElement ( 0.38, 0.1 );		//	|_
		glTranslatef ( -0.4f, -0.4f, 0.0f );		//	|_|

		glTranslatef ( 0.4f, -0.4f, 0.0f );			//	 _
			CreateTimeNumElement ( 0.38, 0.1 );		//	|_|
		glTranslatef ( -0.4f, 0.4f, 0.0f );			//	|_
	glTranslatef ( -X,- Y, -Z );
}
void GLelements :: CreateTimeNum_2 ( float X, float Y, float Z )
{
	glTranslatef ( X, Y, Z );
		glTranslatef ( 0.0f, 0.8f, 0.0f );			// 
		glRotatef ( 90.0f, 0.0f, 0.0f, 1.0f );		//	
			CreateTimeNumElement ( 0.38, 0.1 );		//	|_|
		glRotatef ( -90.0f, 0.0f, 0.0f, 1.0f );		//	|_|
		glTranslatef ( 0.0f, -0.8f, 0.0f );

		glRotatef ( 90.0f, 0.0f, 0.0f, 1.0f );		//	 _
			CreateTimeNumElement ( 0.38, 0.1 );		//	| |
		glRotatef ( -90.0f, 0.0f, 0.0f, 1.0f );		//	|_|

		glTranslatef ( 0.0f, -0.8f, 0.0f );			//	 _
		glRotatef ( 90.0f, 0.0f, 0.0f, 1.0f );		//	|_|
			CreateTimeNumElement ( 0.38, 0.1 );		//	| |
		glRotatef ( -90.0f, 0.0f, 0.0f, 1.0f );
		glTranslatef ( 0.0f, 0.8f, 0.0f );			//		

		glTranslatef ( 0.4f, 0.4f, 0.0f );			//	 _
			CreateTimeNumElement ( 0.38, 0.1 );		//	|_
		glTranslatef ( -0.4f, -0.4f, 0.0f );		//	|_|

		glTranslatef ( -0.4f, -0.4f, 0.0f );		//   _	
			CreateTimeNumElement ( 0.38, 0.1 );		//  |_|
		glTranslatef ( 0.4f, 0.4f, 0.0f );			//   _|
	glTranslatef ( -X,- Y, -Z );
}
void GLelements :: CreateTimeNum_3 ( float X, float Y, float Z )
{
	glTranslatef ( X, Y, Z );
		glTranslatef ( 0.0f, 0.8f, 0.0f );			// 
		glRotatef ( 90.0f, 0.0f, 0.0f, 1.0f );		//	
			CreateTimeNumElement ( 0.38, 0.1 );		//	|_|
		glRotatef ( -90.0f, 0.0f, 0.0f, 1.0f );		//	|_|
		glTranslatef ( 0.0f, -0.8f, 0.0f );

		glRotatef ( 90.0f, 0.0f, 0.0f, 1.0f );		//	 _
			CreateTimeNumElement ( 0.38, 0.1 );		//	| |
		glRotatef ( -90.0f, 0.0f, 0.0f, 1.0f );		//	|_|

		glTranslatef ( 0.0f, -0.8f, 0.0f );			//	 _
		glRotatef ( 90.0f, 0.0f, 0.0f, 1.0f );		//	|_|
			CreateTimeNumElement ( 0.38, 0.1 );		//	| |
		glRotatef ( -90.0f, 0.0f, 0.0f, 1.0f );
		glTranslatef ( 0.0f, 0.8f, 0.0f );			//

		glTranslatef ( 0.4f, 0.4f, 0.0f );			//	 _
			CreateTimeNumElement ( 0.38, 0.1 );		//	|_
		glTranslatef ( -0.4f, -0.4f, 0.0f );		//	|_|
		
		glTranslatef ( 0.4f, -0.4f, 0.0f );			//	 _
			CreateTimeNumElement ( 0.38, 0.1 );		//	|_|
		glTranslatef ( -0.4f, 0.4f, 0.0f );			//	|_
	glTranslatef ( -X,- Y, -Z );
}
void GLelements :: CreateTimeNum_4 ( float X, float Y, float Z )
{
	glTranslatef ( X, Y, Z );
		glRotatef ( 90.0f, 0.0f, 0.0f, 1.0f );		//	 _
			CreateTimeNumElement ( 0.38, 0.1 );		//	| |
		glRotatef ( -90.0f, 0.0f, 0.0f, 1.0f );		//	|_|
		
		glTranslatef ( -0.4f, 0.4f, 0.0f );			// 
			CreateTimeNumElement ( 0.38, 0.1 );		//	 _
		glTranslatef ( 0.4f, -0.4f, 0.0f );			//   _|
													//	|_|

		glTranslatef ( 0.4f, 0.4f, 0.0f );			//	 _
			CreateTimeNumElement ( 0.38, 0.1 );		//	|_
		glTranslatef ( -0.4f, -0.4f, 0.0f );		//	|_|

		glTranslatef ( 0.4f, -0.4f, 0.0f );			//	 _
			CreateTimeNumElement ( 0.38, 0.1 );		//	|_|
		glTranslatef ( -0.4f, 0.4f, 0.0f );			//	|_
	glTranslatef ( -X,- Y, -Z );
}
void GLelements :: CreateTimeNum_5 ( float X, float Y, float Z )
{
	glTranslatef ( X, Y, Z );
		glTranslatef ( 0.0f, 0.8f, 0.0f );			// 
		glRotatef ( 90.0f, 0.0f, 0.0f, 1.0f );		//	
			CreateTimeNumElement ( 0.38, 0.1 );		//	|_|
		glRotatef ( -90.0f, 0.0f, 0.0f, 1.0f );		//	|_|
		glTranslatef ( 0.0f, -0.8f, 0.0f );

		glRotatef ( 90.0f, 0.0f, 0.0f, 1.0f );		//	 _
			CreateTimeNumElement ( 0.38, 0.1 );		//	| |
		glRotatef ( -90.0f, 0.0f, 0.0f, 1.0f );		//	|_|

		glTranslatef ( 0.0f, -0.8f, 0.0f );			//	 _
		glRotatef ( 90.0f, 0.0f, 0.0f, 1.0f );		//	|_|
			CreateTimeNumElement ( 0.38, 0.1 );		//	| |
		glRotatef ( -90.0f, 0.0f, 0.0f, 1.0f );
		glTranslatef ( 0.0f, 0.8f, 0.0f );			//

		glTranslatef ( -0.4f, 0.4f, 0.0f );			// 
			CreateTimeNumElement ( 0.38, 0.1 );		//	 _
		glTranslatef ( 0.4f, -0.4f, 0.0f );			//   _|
													//	|_|

		glTranslatef ( 0.4f, -0.4f, 0.0f );			//	 _
			CreateTimeNumElement ( 0.38, 0.1 );		//	|_|
		glTranslatef ( -0.4f, 0.4f, 0.0f );			//	|_
	glTranslatef ( -X,- Y, -Z );
}
void GLelements :: CreateTimeNum_6 ( float X, float Y, float Z )
{
	glTranslatef ( X, Y, Z );
		glTranslatef ( 0.0f, 0.8f, 0.0f );			// 
		glRotatef ( 90.0f, 0.0f, 0.0f, 1.0f );		//	
			CreateTimeNumElement ( 0.38, 0.1 );		//	|_|
		glRotatef ( -90.0f, 0.0f, 0.0f, 1.0f );		//	|_|
		glTranslatef ( 0.0f, -0.8f, 0.0f );

		glRotatef ( 90.0f, 0.0f, 0.0f, 1.0f );		//	 _
			CreateTimeNumElement ( 0.38, 0.1 );		//	| |
		glRotatef ( -90.0f, 0.0f, 0.0f, 1.0f );		//	|_|

		glTranslatef ( 0.0f, -0.8f, 0.0f );			//	 _
		glRotatef ( 90.0f, 0.0f, 0.0f, 1.0f );		//	|_|
			CreateTimeNumElement ( 0.38, 0.1 );		//	| |
		glRotatef ( -90.0f, 0.0f, 0.0f, 1.0f );
		glTranslatef ( 0.0f, 0.8f, 0.0f );			//

		glTranslatef ( -0.4f, 0.4f, 0.0f );			//   _
			CreateTimeNumElement ( 0.38, 0.1 );		//	 _| 
		glTranslatef ( 0.4f, -0.4f, 0.0f );			//  |_|

		glTranslatef ( -0.4f, -0.4f, 0.0f );		//   _	
			CreateTimeNumElement ( 0.38, 0.1 );		//  |_|
		glTranslatef ( 0.4f, 0.4f, 0.0f );			//   _|

		glTranslatef ( 0.4f, -0.4f, 0.0f );			//	 _
			CreateTimeNumElement ( 0.38, 0.1 );		//	|_|
		glTranslatef ( -0.4f, 0.4f, 0.0f );			//	|_
	glTranslatef ( -X,- Y, -Z );
}
void GLelements :: CreateTimeNum_7 ( float X, float Y, float Z )
{
	glTranslatef ( X, Y, Z );
		glTranslatef ( 0.0f, 0.8f, 0.0f );			//
		glRotatef ( 90.0f, 0.0f, 0.0f, 1.0f );		//	
			CreateTimeNumElement ( 0.38, 0.1 );		//	|_|
		glRotatef ( -90.0f, 0.0f, 0.0f, 1.0f );		//	|_|
		glTranslatef ( 0.0f, -0.8f, 0.0f );
				
		glTranslatef ( 0.4f, 0.4f, 0.0f );			//	 _
			CreateTimeNumElement ( 0.38, 0.1 );		//	|_
		glTranslatef ( -0.4f, -0.4f, 0.0f );		//	|_|		

		glTranslatef ( 0.4f, -0.4f, 0.0f );			//	 _
			CreateTimeNumElement ( 0.38, 0.1 );		//	|_|
		glTranslatef ( -0.4f, 0.4f, 0.0f );			//	|_
	glTranslatef ( -X,- Y, -Z );
}
void GLelements :: CreateTimeNum_8 ( float X, float Y, float Z )
{
	glTranslatef ( X, Y, Z );
		glTranslatef ( 0.0f, 0.8f, 0.0f );			// Горизонтальный блок
		glRotatef ( 90.0f, 0.0f, 0.0f, 1.0f );		//	
			CreateTimeNumElement ( 0.38, 0.1 );		//	|_|
		glRotatef ( -90.0f, 0.0f, 0.0f, 1.0f );		//	|_|
		glTranslatef ( 0.0f, -0.8f, 0.0f );

		glRotatef ( 90.0f, 0.0f, 0.0f, 1.0f );		//	 _
			CreateTimeNumElement ( 0.38, 0.1 );		//	| |
		glRotatef ( -90.0f, 0.0f, 0.0f, 1.0f );		//	|_|

		glTranslatef ( 0.0f, -0.8f, 0.0f );			//	 _
		glRotatef ( 90.0f, 0.0f, 0.0f, 1.0f );		//	|_|
			CreateTimeNumElement ( 0.38, 0.1 );		//	| |
		glRotatef ( -90.0f, 0.0f, 0.0f, 1.0f );
		glTranslatef ( 0.0f, 0.8f, 0.0f );			//

		glTranslatef ( -0.4f, 0.4f, 0.0f );			// Вертикальный блок
			CreateTimeNumElement ( 0.38, 0.1 );		//	 _
		glTranslatef ( 0.4f, -0.4f, 0.0f );			//   _|
													//	|_|

		glTranslatef ( 0.4f, 0.4f, 0.0f );			//	 _
			CreateTimeNumElement ( 0.38, 0.1 );		//	|_
		glTranslatef ( -0.4f, -0.4f, 0.0f );		//	|_|

		glTranslatef ( -0.4f, -0.4f, 0.0f );		//   _	
			CreateTimeNumElement ( 0.38, 0.1 );		//  |_|
		glTranslatef ( 0.4f, 0.4f, 0.0f );			//   _|

		glTranslatef ( 0.4f, -0.4f, 0.0f );			//	 _
			CreateTimeNumElement ( 0.38, 0.1 );		//	|_|
		glTranslatef ( -0.4f, 0.4f, 0.0f );			//	|_
	glTranslatef ( -X,- Y, -Z );
}
void GLelements :: CreateTimeNum_9 ( float X, float Y, float Z )
{
	glTranslatef ( X, Y, Z );
		glTranslatef ( 0.0f, 0.8f, 0.0f );			// 
		glRotatef ( 90.0f, 0.0f, 0.0f, 1.0f );		//	
			CreateTimeNumElement ( 0.38, 0.1 );		//	|_|
		glRotatef ( -90.0f, 0.0f, 0.0f, 1.0f );		//	|_|
		glTranslatef ( 0.0f, -0.8f, 0.0f );

		glRotatef ( 90.0f, 0.0f, 0.0f, 1.0f );		//	 _
			CreateTimeNumElement ( 0.38, 0.1 );		//	| |
		glRotatef ( -90.0f, 0.0f, 0.0f, 1.0f );		//	|_|

		glTranslatef ( 0.0f, -0.8f, 0.0f );			//	 _
		glRotatef ( 90.0f, 0.0f, 0.0f, 1.0f );		//	|_|
			CreateTimeNumElement ( 0.38, 0.1 );		//	| |
		glRotatef ( -90.0f, 0.0f, 0.0f, 1.0f );
		glTranslatef ( 0.0f, 0.8f, 0.0f );			//

		glTranslatef ( -0.4f, 0.4f, 0.0f );			// 
			CreateTimeNumElement ( 0.38, 0.1 );		//	 _
		glTranslatef ( 0.4f, -0.4f, 0.0f );			//   _|
													//	|_|

		glTranslatef ( 0.4f, 0.4f, 0.0f );			//	 _
			CreateTimeNumElement ( 0.38, 0.1 );		//	|_
		glTranslatef ( -0.4f, -0.4f, 0.0f );		//	|_|

		glTranslatef ( 0.4f, -0.4f, 0.0f );			//	 _
			CreateTimeNumElement ( 0.38, 0.1 );		//	|_|
		glTranslatef ( -0.4f, 0.4f, 0.0f );			//	|_
	glTranslatef ( -X,- Y, -Z );
}
void GLelements :: CreateOctagon ( float X, float Y, float Z, GLfloat LENGHT, GLfloat RADIUS )
{		
	glTranslatef ( X, Y, Z );	
# pragma region Координаты вершин 8-угольника
	static GLfloat CVertex3String01 [ ] =
	{							 
		 0.0f, 0.0f, 0.0f,		//1//
		 0.0f, -RADIUS, RADIUS,
		 -LENGHT, -RADIUS, RADIUS,
		 -LENGHT, 0.0f, 0.0f
	};
	static GLfloat CVertex3String02 [ ] =
	{							 
		 0.0f, -RADIUS, RADIUS,	//2//
		 0.0f, -RADIUS, RADIUS * 2, 
		 -LENGHT, -RADIUS, RADIUS * 2,
		 -LENGHT, -RADIUS, RADIUS
	};
	static GLfloat CVertex3String03 [ ] =
	{							 
		 0.0f, -RADIUS, RADIUS * 2,	//3//
		 0.0f, 0.0f, RADIUS * 3,
		 -LENGHT, 0.0f, RADIUS * 3,
		 -LENGHT, -RADIUS, RADIUS * 2
	};
	static GLfloat CVertex3String04 [ ] =
	{
		 0.0f, 0.0f, RADIUS * 3,		//4//
		 0.0f, RADIUS, RADIUS * 3,
		 -LENGHT, RADIUS, RADIUS * 3,
		 -LENGHT, 0.0f, RADIUS * 3
	};
	static GLfloat CVertex3String05 [ ] =
	{	 
		 0.0f, RADIUS, RADIUS * 3,	//5//
		 0.0f, RADIUS * 2, RADIUS * 2,
		-LENGHT, RADIUS * 2, RADIUS * 2,
		 -LENGHT, RADIUS, RADIUS * 3
	};
	static GLfloat CVertex3String06 [ ] =
	{	 
		 0.0f, RADIUS * 2, RADIUS * 2,		//6//
		 0.0f, RADIUS * 2, RADIUS,
		 -LENGHT, RADIUS * 2, RADIUS,
		 -LENGHT, RADIUS * 2, RADIUS * 2
	};
	static GLfloat CVertex3String07 [ ] =
	{	 
		 0.0f, RADIUS * 2, RADIUS,		//7//
		 0.0f, RADIUS, 0.0f,
		 -LENGHT, RADIUS, 0.0f,
		 -LENGHT, RADIUS * 2, RADIUS
	};
	static GLfloat CVertex3String08 [ ] =
	{	 
		 0.0f, RADIUS, 0.0f,		//8//
		 0.0f, 0.0f, 0.0f, 
		 -LENGHT, 0.0f, 0.0f,
		 -LENGHT, RADIUS, 0.0f
	 };
# pragma endregion
# pragma region Номера вершин 8-угольника
	static GLushort	QVertex3 [ ] =
	{
		 0,  1,  2,	 3		//1//
		// 1,  5,  6,		 1,  2,  6,		//2//
		// 5,  9, 10,		 5,  6, 10,		//3//
		// 9, 13, 14,		 9, 10, 14,		//4//

		//13, 17, 18,		13, 14, 18,		//5//
		//17, 21, 22,		17, 18, 22,		//6// 
		//21, 25, 26,		21, 22, 26,		//7//
		//25,  0,  3,		25, 26,  3		//8//
	};
# pragma endregion
# pragma region Вершины тексурных координат
	static GLfloat TexCoordString [ ] =
	{
		1, 1,	1, 0,	0, 0,	0, 1,	//1..8//
	};
# pragma endregion
# pragma region Отрисовка OpenGL
	glPushMatrix();
	glEnable(GL_LINE);
	glEnable(GL_LINE_SMOOTH);	
	glLineWidth ( 2.0f );
		glEnableClientState ( GL_VERTEX_ARRAY );
		glEnableClientState ( GL_TEXTURE_COORD_ARRAY );			
				glTexCoordPointer ( 2, GL_FLOAT, 0, TexCoordString );
				glVertexPointer ( 3, GL_FLOAT, 0, CVertex3String01 );		
			    glDrawElements ( GL_LINE_STRIP, 4, GL_UNSIGNED_SHORT, QVertex3 );			
				glVertexPointer ( 3, GL_FLOAT, 0, CVertex3String02 );		
			    glDrawElements ( GL_LINE_STRIP, 4, GL_UNSIGNED_SHORT, QVertex3 );			
				glVertexPointer ( 3, GL_FLOAT, 0, CVertex3String03 );		
			    glDrawElements ( GL_LINE_STRIP, 4, GL_UNSIGNED_SHORT, QVertex3 );			
				glVertexPointer ( 3, GL_FLOAT, 0, CVertex3String04 );		
			    glDrawElements ( GL_LINE_STRIP, 4, GL_UNSIGNED_SHORT, QVertex3 );			
				glVertexPointer ( 3, GL_FLOAT, 0, CVertex3String05 );		
			    glDrawElements ( GL_LINE_STRIP, 4, GL_UNSIGNED_SHORT, QVertex3 );			
				glVertexPointer ( 3, GL_FLOAT, 0, CVertex3String06 );		
			    glDrawElements ( GL_LINE_STRIP, 4, GL_UNSIGNED_SHORT, QVertex3 );			
				glVertexPointer ( 3, GL_FLOAT, 0, CVertex3String07 );		
			    glDrawElements ( GL_LINE_STRIP, 4, GL_UNSIGNED_SHORT, QVertex3 );			
				glVertexPointer ( 3, GL_FLOAT, 0, CVertex3String08 );		
			    glDrawElements ( GL_LINE_STRIP, 4, GL_UNSIGNED_SHORT, QVertex3 );		
		glDisableClientState ( GL_VERTEX_ARRAY );
		glDisableClientState ( GL_TEXTURE_COORD_ARRAY );
	glLineWidth ( 1.0f );
	glDisable(GL_LINE_SMOOTH);
	glPopMatrix();
# pragma endregion	
	glTranslatef ( -X, -Y, -Z );
}
void GLelements :: CreateHolderStrings ( float X, float Y, float Z )
{
	glTranslatef ( X, Y, Z );
# pragma region Координаты вершин стоек
	static GLfloat CVBlockEl01 [ ] =
	{	
		0.0f, -1.49999f, 0.5991f,
		0.0f, -1.49999f, 0.49f,
		0.0f, 1.99999f, 0.49f,
		0.0f, 1.99999f, 0.5991f
	};
	static GLfloat CVBlockEl02 [ ] =
	{	
		0.2f, -1.49999f, 0.5991f,
		0.2f, -1.49999f, 0.49f,
		0.2f, 1.99999f, 0.49f,
		0.2f, 1.99999f, 0.5991f
	};
	static GLfloat CVBlockEl03 [ ] =
	{
		0.2f, -1.49999f, 0.5991f,
		0.2f, -1.49999f, 0.49f,
		0.0f, -1.49999f, 0.49f,
		0.0f, -1.49999f, 0.5991f
	};
	static GLfloat CVBlockEl04 [ ] =
	{
		0.2f, -1.49999f, 0.49f,
		0.2f, 1.99999f, 0.49f,
		0.0f, 1.99999f, 0.49f,
		0.0f, -1.49999f, 0.49f
	};
	static GLfloat CVBlockEl05 [ ] =
	{
		0.2f, 1.99999f, 0.5991f,
		0.2f, 1.99999f, 0.49f,
		0.0f, 1.99999f, 0.49f,
		0.0f, 1.99999f, 0.5991f
	};
	static GLfloat CVBlockEl06 [ ] =
	{
		0.2f, -1.49999f, 0.5991f,
		0.2f, 1.99999f, 0.5991f,
		0.0f, 1.99999f, 0.5991f,
		0.0f, -1.49999f, 0.5991f
	};
# pragma endregion
# pragma region Номера вершин стоек
	static GLushort	QVBlockEl [ ] =
	{
		 0,  1,  2,  3
	};
# pragma endregion
# pragma region Вершины тексурных координат для стоек
	static GLfloat TexCoordBlock [ ] =
	{
		1, 1,	1, 0,	0, 0,	0, 1	//1\2//
	};
# pragma endregion	
# pragma region Отрисовка OpenGL		
	glPushMatrix();
		glEnableClientState ( GL_VERTEX_ARRAY );
		glEnableClientState ( GL_TEXTURE_COORD_ARRAY );			
				glTexCoordPointer ( 2, GL_FLOAT, 0, TexCoordBlock );
				glVertexPointer ( 3, GL_FLOAT, 0, CVBlockEl01 );			       
				glDrawElements ( GL_LINE_STRIP, 5, GL_UNSIGNED_SHORT, QVBlockEl );

				glVertexPointer ( 3, GL_FLOAT, 0, CVBlockEl02 );
				glDrawElements ( GL_LINE_STRIP, 5, GL_UNSIGNED_SHORT, QVBlockEl );			
				
				glVertexPointer ( 3, GL_FLOAT, 0, CVBlockEl03 );
				glDrawElements ( GL_LINE_STRIP, 5, GL_UNSIGNED_SHORT, QVBlockEl );

				glVertexPointer ( 3, GL_FLOAT, 0, CVBlockEl04 );
				glDrawElements ( GL_LINE_STRIP, 5, GL_UNSIGNED_SHORT, QVBlockEl );

				glVertexPointer ( 3, GL_FLOAT, 0, CVBlockEl05 );
				glDrawElements ( GL_LINE_STRIP, 5, GL_UNSIGNED_SHORT, QVBlockEl );

				glVertexPointer ( 3, GL_FLOAT, 0, CVBlockEl06 );
				glDrawElements ( GL_LINE_STRIP, 5, GL_UNSIGNED_SHORT, QVBlockEl );
			glPopName();
		glDisableClientState ( GL_VERTEX_ARRAY );
		glDisableClientState ( GL_TEXTURE_COORD_ARRAY );
	glPopMatrix();
# pragma endregion
	glTranslatef ( -X, -Y, -Z );
}
void GLelements :: CreateBigStend ( float X, float Y, float Z, int ID_NUM )
{	
# pragma region Координаты вершин
	static GLfloat CVBlockEl01 [ ] =
	{	
		0.0f, -2.5f, 0.6f,
		20.0f, -2.5f, 0.6f,
		20.0f, 2.5f, 0.6f,
		0.0f, 2.5f, 0.6f
	};	
	static GLfloat CVBlockEl02 [ ] =
	{	
		0.5f, -1.5f, 0.6f,
		19.5f, -1.5f, 0.6f,
		19.5f, -1.5f, 0.49f,
		0.5f, -1.5f, 0.49f
	};
	static GLfloat CVBlockEl03 [ ] =
	{
		19.5f, -1.5f, 0.6f,
		19.5f, 2.0f, 0.6f,
		19.5f, 2.0f, 0.49f,
		19.5f, -1.5f, 0.49f
	};
	static GLfloat CVBlockEl04 [ ] =
	{	
		19.5f, 2.0f, 0.6f,
		0.5f, 2.0f, 0.6f,
		0.5f, 2.0f, 0.49f,
		19.5f, 2.0f, 0.49f
	};
	static GLfloat CVBlockEl05 [ ] =
	{	
		0.5f, -1.5f, 0.6f,
		0.5f, 2.0f, 0.6f,
		0.5f, 2.0f, 0.49f,
		0.5f, -1.5f, 0.49f
	};
	static GLfloat CVBlockEl06 [ ] =
	{	
		0.0f, -2.5f, 0.0f,
		20.0f, -2.5f, 0.0f,
		20.0f, 2.5f, 0.0f,
		0.0f, 2.5f, 0.0f
	};
	static GLfloat CVBlockEl07 [ ] =
	{
		0.0f, -2.5f, 0.6f,
		20.0f, -2.5f, 0.6f,
		20.0f, -2.5f, 0.0f,
		0.0f, -2.5f, 0.0f
	};
	static GLfloat CVBlockEl08 [ ] =
	{
		20.0f, -2.5f, 0.6f,
		20.0f, 2.5f, 0.6f,
		20.0f, 2.5f, 0.0f,
		20.0f, -2.5f, 0.0f
	};
	static GLfloat CVBlockEl09 [ ] =
	{
		20, 2.5, 0.6f,
		0, 2.5, 0.6f,
		0, 2.5, 0.0f,
		20, 2.5, 0.0f
	};
	static GLfloat CVBlockEl10 [ ] =
	{
		0.0f, 2.5f, 0.6f,
		0.0f, -2.5f, 0.6f,
		0.0f, -2.5f, 0.0f,
		0.0f, 2.5f, 0.0f
	};
# pragma endregion
# pragma region Номера вершин
	static GLushort	QVBlockEl [ ] =
	{		
		 0,  1,  2,	 3
	};
# pragma endregion
# pragma region Вершины тексурных координат
	static GLfloat TexCoordBlock [ ] =
	{
		0, 0,	1, 0,	1, 1,	0, 1	//All//
	};
# pragma endregion	
# pragma region Отрисовка OpenGL		
	glPushMatrix();
		glEnableClientState ( GL_VERTEX_ARRAY );
		glEnableClientState ( GL_TEXTURE_COORD_ARRAY );		
		//glDisable(GL_DEPTH_TEST);
		//glBlendFunc(GL_DST_COLOR,GL_ZERO);
		//glEnable(GL_BLEND);
		glColor3ub ( 128, 212, 255);			
				//glTexCoordPointer ( 2, GL_FLOAT, 0, TexCoordBlock );
				glVertexPointer ( 3, GL_FLOAT, 0, CVBlockEl01 );			       
				glDrawElements ( GL_LINE_STRIP, 5, GL_UNSIGNED_SHORT, QVBlockEl );			
		/*glBlendFunc(GL_ONE,GL_ONE);
			glBindTexture ( GL_TEXTURE_2D, textures [ 17 ].texID );
			glPushName ( TEX_NUM_01 );
					glTexCoordPointer ( 2, GL_FLOAT, 0, TexCoordBlock );
					glVertexPointer ( 3, GL_FLOAT, 0, CVBlockEl01_01 );			       
					glDrawElements ( GL_LINE_STRIP, 4, GL_UNSIGNED_SHORT, QVBlockEl );
			glPopName ( );
		glDisable(GL_BLEND);*/			
				glVertexPointer ( 3, GL_FLOAT, 0, CVBlockEl02 );
				glDrawElements ( GL_LINE_STRIP, 5, GL_UNSIGNED_SHORT, QVBlockEl );
				glVertexPointer ( 3, GL_FLOAT, 0, CVBlockEl03 );
				glDrawElements ( GL_LINE_STRIP, 5, GL_UNSIGNED_SHORT, QVBlockEl );
				glVertexPointer ( 3, GL_FLOAT, 0, CVBlockEl04 );
				glDrawElements ( GL_LINE_STRIP, 5, GL_UNSIGNED_SHORT, QVBlockEl );
				glVertexPointer ( 3, GL_FLOAT, 0, CVBlockEl05 );
				glDrawElements ( GL_LINE_STRIP, 5, GL_UNSIGNED_SHORT, QVBlockEl );				
				glVertexPointer ( 3, GL_FLOAT, 0, CVBlockEl06 );
				glDrawElements ( GL_LINE_STRIP, 5, GL_UNSIGNED_SHORT, QVBlockEl );				
				glVertexPointer ( 3, GL_FLOAT, 0, CVBlockEl07 );
				glDrawElements ( GL_LINE_STRIP, 5, GL_UNSIGNED_SHORT, QVBlockEl );
				glVertexPointer ( 3, GL_FLOAT, 0, CVBlockEl08 );
				glDrawElements ( GL_LINE_STRIP, 5, GL_UNSIGNED_SHORT, QVBlockEl );
				glVertexPointer ( 3, GL_FLOAT, 0, CVBlockEl09 );
				glDrawElements ( GL_LINE_STRIP, 5, GL_UNSIGNED_SHORT, QVBlockEl );
				glVertexPointer ( 3, GL_FLOAT, 0, CVBlockEl10 );
				glDrawElements ( GL_LINE_STRIP, 5, GL_UNSIGNED_SHORT, QVBlockEl );			
		glDisableClientState ( GL_VERTEX_ARRAY );
		glDisableClientState ( GL_TEXTURE_COORD_ARRAY );
	glPopMatrix();
# pragma endregion
}