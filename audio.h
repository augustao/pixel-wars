#ifndef AUDIO_832729883928
#define AUDIO_832729883928

#include "main.h"

using namespace std;

void Init_Audio();
void Shutdown_Audio();
void ChannelEnded(int ch);
void PlaySFX(Mix_Chunk* chunkk);
void PlayMusic(Mix_Music *musicc);
void PlayMusicOnce(Mix_Music *musicc);

#endif