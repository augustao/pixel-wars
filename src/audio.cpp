#include "audio.h"
using namespace std;

#define AUDIO_CHANNELS 64

// Audio Vars
int audio_rate = 22050;
Uint16 audio_format = AUDIO_S16; /* 16-bit stereo */
int audio_channels = 2;
int audio_buffers = 4096;

int channeltouse = 0;

void Init_Audio()
{
	// INITIALIZES SDL_MIXER AUDIO
	Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers);
	Mix_AllocateChannels(AUDIO_CHANNELS);
	Mix_ChannelFinished(ChannelEnded);
}

void Shutdown_Audio()
{
	Mix_CloseAudio();
}

void ChannelEnded(int ch)
{
	
}

void PlaySFX(Mix_Chunk* chunkk)
{
	Mix_PlayChannel(-1,chunkk,0);
}

void PlayMusic(Mix_Music *musicc)
{
	Mix_PlayMusic(musicc, -1);
	
}

void PlayMusicOnce(Mix_Music *musicc)
{
	Mix_PlayMusic(musicc, 0);
}
