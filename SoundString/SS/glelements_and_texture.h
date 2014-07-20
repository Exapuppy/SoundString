
# ifndef _GLELEMENTS_AND_TEXTURE_H
# define _GLELEMENTS_AND_TEXTURE_H

# include "main.h"

# ifdef _MAIN_H

# include "devil\include\IL\il.h"
# include "devil\include\IL\ilu.h"

struct TextureImage
{
	GLubyte		*imageData;		// Данные текстуры
	GLuint		bpp;			// Байт на пиксел
	GLuint		width,height;	// Высота и ширина
	GLuint		texID;			// ID текстуры
};

class CTexture
{
	public:
		TextureImage textures [ 41 ];
		void InitTextures ( CTexture *Texture );
		CTexture ( )
		{	
			ilInit ( );
			iluInit ( );
		}
		~CTexture ( ) { }
		void LoadTexture ( ILenum FileType, char *filename, TextureImage *texture );
		void FreeTexture ( TextureImage *texture ) { }
};

class GLelements
{
	public:
		void CreateTimeNumElement ( GLfloat HEIGHT, GLfloat RADIUS, int R, int G, int B );		
		void CreateOctagon ( float X, float Y, float Z, GLfloat LENGHT, GLfloat RADIUS );		
		void CreateHolderStrings ( CTexture *Texture, float X, float Y, float Z );
		void CreateBigStend ( CTexture *Texture, int NOT );
		void CreateQuadNoteLine ( float X, float Y, float Z, int R, int G, int B );
		void CreateTimeNum_0 ( float X, float Y, float Z, GLfloat HEIGHT, GLfloat RADIUS, GLfloat size, int R, int G, int B );
		void CreateTimeNum_1 ( float X, float Y, float Z, GLfloat HEIGHT, GLfloat RADIUS, GLfloat size, int R, int G, int B );
		void CreateTimeNum_2 ( float X, float Y, float Z, GLfloat HEIGHT, GLfloat RADIUS, GLfloat size, int R, int G, int B );
		void CreateTimeNum_3 ( float X, float Y, float Z, GLfloat HEIGHT, GLfloat RADIUS, GLfloat size, int R, int G, int B );
		void CreateTimeNum_4 ( float X, float Y, float Z, GLfloat HEIGHT, GLfloat RADIUS, GLfloat size, int R, int G, int B );
		void CreateTimeNum_5 ( float X, float Y, float Z, GLfloat HEIGHT, GLfloat RADIUS, GLfloat size, int R, int G, int B );
		void CreateTimeNum_6 ( float X, float Y, float Z, GLfloat HEIGHT, GLfloat RADIUS, GLfloat size, int R, int G, int B );
		void CreateTimeNum_7 ( float X, float Y, float Z, GLfloat HEIGHT, GLfloat RADIUS, GLfloat size, int R, int G, int B );
		void CreateTimeNum_8 ( float X, float Y, float Z, GLfloat HEIGHT, GLfloat RADIUS, GLfloat size, int R, int G, int B );
		void CreateTimeNum_9 ( float X, float Y, float Z, GLfloat HEIGHT, GLfloat RADIUS, GLfloat size, int R, int G, int B );
};

# endif
# endif