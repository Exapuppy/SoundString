
# include "stdafx.h"
# include "sound.h"

# ifdef _SOUND_H

int Sound :: InitAudio ( LPDIRECTSOUNDBUFFER *buffer, int secs, int samplerate, int bitspersample )
{
    ZeroMemory(&wfx, sizeof(WAVEFORMATEX));
    wfx.wFormatTag = WAVE_FORMAT_PCM;
    wfx.nChannels = 1;
    wfx.nSamplesPerSec = samplerate;
    wfx.wBitsPerSample = bitspersample;
    wfx.nBlockAlign = (WORD)(wfx.wBitsPerSample * wfx.nChannels / 8);
    wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;
 
    ZeroMemory(&dsbd, sizeof(DSBUFFERDESC));
    dsbd.dwSize = sizeof(DSBUFFERDESC);
    dsbd.dwFlags = DSBCAPS_GLOBALFOCUS;
    dsbd.dwBufferBytes = samplerate * secs;
    dsbd.lpwfxFormat = &wfx;
 
    DirectSoundCreate(NULL, &DS, NULL);
    DS->SetCooperativeLevel(GetForegroundWindow(), DSSCL_PRIORITY);
    DS->CreateSoundBuffer(&dsbd, buffer, NULL);
    //Возвращаем размер буфера
    return dsbd.dwBufferBytes;
}
void Sound :: FillBuffer ( LPDIRECTSOUNDBUFFER buffer, float freq, int size, int samplerate )
{    
    //Запираем буфер
    buffer->Lock(0, size, (void **)(&bufferBytes), &lockedSize, NULL, NULL, 0L);
 
    for ( q = 0; q < lockedSize / 2; q++)
    {
        //Определяем цикл, в котором находимся
        pos = freq / (float)samplerate * (float)q;
        //Берём остаток и переводим в радианы
        r = (pos - floor(pos)) * 2 * M_PI;
        value = sin(r);
 
        bufferBytes[q] = value * 32767 / 8;
    }
    //Отпираем буфер
    buffer->Unlock(bufferBytes, lockedSize, NULL, 0);
}

void Sound :: SoundString ( bool SoundFlag )
{	
	if ( flagi == 1 )
	{
		SoundCreate = InitAudio ( &DsBuffer, 1, SamplesPerSec, BitsPerSample);
		set_flagi ( 2 );
	}
		
    FillBuffer ( DsBuffer, frequency, SoundCreate, SamplesPerSec );
        //440 Гц - "Ля" первой октавы

	if ( SoundFlag )
		DsBuffer -> Play ( 0, 0, DSBPLAY_LOOPING );
	
	if ( !SoundFlag )
	{
		DsBuffer -> Stop ( );
		//DsBuffer -> Release ( );
		//DS -> Release ( );
	}
}

# endif