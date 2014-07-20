
# ifndef _SOUND_H
# define _SOUND_H

# include "main.h"

# ifdef _MAIN_H

# define M_PI 3.14159265358979323846

class Sound 
{	
	private:
		int SoundCreate;
		LPDIRECTSOUNDBUFFER DsBuffer;
		int BitsPerSample;
		int SamplesPerSec;
		int frequency;
		short *bufferBytes;
		DWORD lockedSize;
		WAVEFORMATEX wfx;
		DSBUFFERDESC dsbd;
		LPDIRECTSOUND DS;

		float pos;
		float r;
		float value;
		DWORD q;

		int flagi;
	public:		
		Sound ( )
		{ 
			SoundCreate = 0;
			DsBuffer = NULL;
			BitsPerSample = 16;
			SamplesPerSec = 96000;
			frequency = 440;
			DS = NULL;
			
			flagi = 1;
		}
		int get_frequency ( ) 
		{
			return frequency;
		}
		void set_frequency ( int set )
		{	
			int ch = 0;
			ch = fmod ( (float) set, 2 );
			if ( ch == 1 )
				frequency = set + 1;
			else
				frequency = set;
		}
		int get_flagi ( ) { return flagi; }
		void set_flagi ( int f ) {  flagi = f; }
		int InitAudio ( LPDIRECTSOUNDBUFFER *buffer, int secs, int samplerate, int bitspersample );
		void FillBuffer ( LPDIRECTSOUNDBUFFER buffer, float freq, int size, int samplerate );
		void SoundString ( bool SoundFlag );
};

# endif
# endif