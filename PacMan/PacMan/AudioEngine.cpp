#include "AudioEngine.h"


AudioEngine::AudioEngine(Camera* camera)
{
	mCamera = camera;
	mDevice = alcOpenDevice(NULL);                                               //Open the device
    if(!mDevice) printf("no sound device");                         //Error during device oening
    mContext = alcCreateContext(mDevice, NULL);                                   //Give the device a context
    alcMakeContextCurrent(mContext);                                             //Make the context the current
    if(!mContext) printf("no sound context");                       //Error during context handeling

	// Clear Error Code (so we can catch any new errors)
	alGetError();

	usedBuffers = 0;

	alGenBuffers(15, buffers);
	alGenSources(15, sources);
}

void AudioEngine::Generate(int count, ALuint* buffers, ALuint* sources)
{
	*buffers = this->buffers[usedBuffers];
	*sources = this->sources[usedBuffers];
	usedBuffers += count;
}

AudioEngine::~AudioEngine(void)
{
	alcMakeContextCurrent(NULL);                                                //Make no context current
	alcDestroyContext(mContext);                                                 //Destroy the OpenAL Context
    alcCloseDevice(mDevice);                                                     //Close the OpenAL Device
}

void AudioEngine::Update()
{
	const static float v[3] = {0,0,0};
	glm::vec3 a = mCamera->orientation * glm::vec3(0,0,1);
	float dir[6] = 	{a.x,a.y,a.z,0,	1,0	};
	 //Listener                                                                               
	alListenerfv(AL_POSITION,    &mCamera->position[0]);                                  //Set position of the listener
	alListenerfv(AL_VELOCITY,    v);                                  //Set velocity of the listener
	alListenerfv(AL_ORIENTATION, dir);                                  //Set orientation of the listener
}