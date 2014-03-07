#include "AudioSource.h"
#include "AudioEngine.h"


AudioSource::AudioSource(AudioEngine* engine, const char* path, glm::vec3 position)
{
	LoadAudioFile(path);


	frequency=mStream.sampleRate;;                                               //The Sample Rate of the WAVE file
    format=0;                                                            //The audio format (bits per sample, number of channels)


	engine->Generate(1, &buffer,&source);                                                    //Generate one OpenAL Buffer and link to "buffer"
											                                                  //Generate one OpenAL Source and link to "source"
    if(alGetError() != AL_NO_ERROR) printf("Error GenSource");     //Error during buffer/source generation
    
    //Figure out the format of the WAVE file
    if(mStream.bitsPerSample == 8)
    {
        if(mStream.channels == 1)
            format = AL_FORMAT_MONO8;
        else if(mStream.channels == 2)
            format = AL_FORMAT_STEREO8;
    }
    else if(mStream.bitsPerSample == 16)
    {
        if(mStream.channels == 1)
            format = AL_FORMAT_MONO16;
        else if(mStream.channels == 2)
            format = AL_FORMAT_STEREO16;
    }
	if(!format) printf("Wrong BitPerSample");                      //Not valid format

    alBufferData(buffer, format, mStream.buf, mStream.dataSize, frequency);                    //Store the sound data in the OpenAL Buffer
    if(alGetError() != AL_NO_ERROR) 
    printf("Error loading ALBuffer");                              //Error during buffer loading
}

AudioSource::~AudioSource(void)
{
	//Clean-up
    delete[] mStream.buf;                                                               //Delete the sound data buffer
    alDeleteSources(1, &source);                                                //Delete the OpenAL Source
    alDeleteBuffers(1, &buffer);                                                 //Delete the OpenAL Buffer
}

int AudioSource::LoadAudioFile(const char* file)
{
//Loading of the WAVE file
    FILE *fp = NULL;                                                            //Create FILE pointer for the WAVE file
    fp=fopen("WAVE/Sound.wav","rb");                                            //Open the WAVE file
    if (!fp) return printf("Failed to open file");                        //Could not open file
    
    //Check that the WAVE file is OK
    fread(mStream.type,sizeof(char),4,fp);                                              //Reads the first bytes in the file
    if(mStream.type[0]!='R' || mStream.type[1]!='I' || mStream.type[2]!='F' || mStream.type[3]!='F')            //Should be "RIFF"
    return printf ("No RIFF");                                            //Not RIFF

    fread(&mStream.size, sizeof(unsigned int),1,fp);                                           //Continue to read the file
    fread(mStream.type, sizeof(char),4,fp);                                             //Continue to read the file
    if (mStream.type[0]!='W' || mStream.type[1]!='A' || mStream.type[2]!='V' || mStream.type[3]!='E')           //This part should be "WAVE"
    return printf("not WAVE");                                            //Not WAVE
    
    fread(mStream.type,sizeof(char),4,fp);                                              //Continue to read the file
    if (mStream.type[0]!='f' || mStream.type[1]!='m' || mStream.type[2]!='t' || mStream.type[3]!=' ')           //This part should be "fmt "
    return printf("not fmt ");                                            //Not fmt 
    
    //Now we know that the file is a acceptable WAVE file
    //Info about the WAVE data is now read and stored
    fread(&mStream.chunkSize,sizeof(unsigned int),1,fp);
    fread(&mStream.formatType,sizeof(short),1,fp);
    fread(&mStream.channels,sizeof(short),1,fp);
    fread(&mStream.sampleRate,sizeof(unsigned int),1,fp);
    fread(&mStream.avgBytesPerSec,sizeof(unsigned int),1,fp);
    fread(&mStream.bytesPerSample,sizeof(short),1,fp);
    fread(&mStream.bitsPerSample,sizeof(short),1,fp);
    
    fread(mStream.type,sizeof(char),4,fp);
    if (mStream.type[0]!='d' || mStream.type[1]!='a' || mStream.type[2]!='t' || mStream.type[3]!='a')           //This part should be "data"
    return printf("Missing DATA");                                        //not data
    
    fread(&mStream.dataSize,sizeof(unsigned int),1,fp);                                        //The size of the sound data is read
    
    ////Display the info about the WAVE file
    //std::cout << "Chunk Size: " << mStream.chunkSize << "\n";
    //std::cout << "Format Type: " << mStream.formatType << "\n";
    //std::cout << "Channels: " << mStream.channels << "\n";
    //std::cout << "Sample Rate: " << mStream.sampleRate << "\n";
    //std::cout << "Average Bytes Per Second: " << mStream.avgBytesPerSec << "\n";
    //std::cout << "Bytes Per Sample: " << mStream.bytesPerSample << "\n";
    //std::cout << "Bits Per Sample: " << mStream.bitsPerSample << "\n";
    //std::cout << "Data Size: " << mStream.dataSize << "\n";
    //    
    mStream.buf= new unsigned char[mStream.dataSize];                            //Allocate memory for the sound data
	fread(mStream.buf,1,mStream.dataSize,fp);
    //std::cout << fread(mStream.buf,1,mStream.dataSize,fp) << " bytes loaded\n";           //Read the sound data and display the 
                                                                                //number of bytes loaded.
                                                                                //Should be the same as the Data Size if OK
	
    fclose(fp);                                                                 //Close the WAVE file
};

void AudioSource::Play()
{
    ALfloat SourceVel[] = { 0.0, 0.0, 0.0 };                                    //Velocity of the source sound
	//Source
    alSourcei (source, AL_BUFFER,   buffer);                                 //Link the buffer to the source
    alSourcef (source, AL_PITCH,    1.0f     );                                 //Set the pitch of the source
    alSourcef (source, AL_GAIN,     1.0f     );                                 //Set the gain of the source
	alSourcefv(source, AL_POSITION, &mPosition[0]);                                 //Set the position of the source
    alSourcefv(source, AL_VELOCITY, SourceVel);                                 //Set the velocity of the source
    alSourcei (source, AL_LOOPING,  AL_FALSE );                                 //Set if source is looping sound
    
    //PLAY
    alSourcePlay(source);                                                       //Play the sound buffer linked to the source
    	 if(alGetError() != AL_NO_ERROR) printf("Error playing sound"); //Error when playing sound
 	//system("PAUSE");
}