#pragma once
#include <glm\glm.hpp>
#include <AL\al.h>
#include "AL\alc.h"
#include "AL\alext.h"

class AudioEngine;
struct AudioStream
{
	//Variables to store info about the WAVE file (all of them is not needed for OpenAL)
    char type[4];
    unsigned int size,chunkSize;
    short formatType,channels;
    unsigned int sampleRate,avgBytesPerSec;
    short bytesPerSample,bitsPerSample;
    unsigned int dataSize;
	unsigned char* buf;
	ALuint buffer;                                                           //Stores the sound data
    ALuint frequency;                                               //The Sample Rate of the WAVE file
	ALuint source;                                                              //Is the name of source (where the sound come from)
    ALenum format;                                                            //The audio format (bits per sample, number of channels)
	int LoadAudioFile(const char* path);
};

class AudioSource
{
	glm::vec3 mPosition;
public:
	AudioStream mStream;
	AudioSource(){};
	AudioSource(AudioEngine* engine, AudioStream* stream, glm::vec3 position);
	~AudioSource(void);
	void Play();
	void Set(AudioEngine* engine);
};

