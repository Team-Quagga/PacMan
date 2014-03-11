#pragma once
#include "Engine\Camera.h"
#include <AL\al.h>
#include "AL\alc.h"
#include "AL\alext.h"

class AudioEngine
{
	Camera* mCamera;
	ALCdevice *mDevice;
    ALCcontext *mContext;
	ALuint buffers[15], sources[15];
	int usedBuffers;
public:
	AudioEngine(){};
	AudioEngine(Camera* camera);
	~AudioEngine(void);
	void Update();
	void Generate(int count, ALuint* buffers, ALuint* sources);
};

