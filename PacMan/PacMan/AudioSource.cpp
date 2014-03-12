#include "AudioSource.h"
#include "AudioEngine.h"


AudioSource::AudioSource(AudioEngine* engine, AudioStream* stream, glm::vec3 position)
{
	//LoadAudioFile(path);
	mStream = *stream;
	mPosition = position;
}

AudioSource::~AudioSource(void)
{
	//Clean-up
    delete[] mStream.buf;                                                               //Delete the sound data buffer
    alDeleteSources(1, &mStream.source);                                                //Delete the OpenAL Source
    alDeleteBuffers(1, &mStream.buffer);                                                 //Delete the OpenAL Buffer
}

int AudioStream::LoadAudioFile(const char* file)
{
//Loading of the WAVE file
    FILE *fp = NULL;                                                            //Create FILE pointer for the WAVE file
    fp=fopen("WAVE/Sound.wav","rb");                                            //Open the WAVE file
    if (!fp) return printf("Failed to open file");                        //Could not open file
    
    //Check that the WAVE file is OK
    fread(type,sizeof(char),4,fp);                                              //Reads the first bytes in the file
    if(type[0]!='R' || type[1]!='I' || type[2]!='F' || type[3]!='F')            //Should be "RIFF"
    return printf ("No RIFF");                                            //Not RIFF

    fread(&size, sizeof(unsigned int),1,fp);                                           //Continue to read the file
    fread(type, sizeof(char),4,fp);                                             //Continue to read the file
    if (type[0]!='W' || type[1]!='A' || type[2]!='V' || type[3]!='E')           //This part should be "WAVE"
    return printf("not WAVE");                                            //Not WAVE
    
    fread(type,sizeof(char),4,fp);                                              //Continue to read the file
    if (type[0]!='f' || type[1]!='m' || type[2]!='t' || type[3]!=' ')           //This part should be "fmt "
    return printf("not fmt ");                                            //Not fmt 
    
    //Now we know that the file is a acceptable WAVE file
    //Info about the WAVE data is now read and stored
    fread(&chunkSize,sizeof(unsigned int),1,fp);
    fread(&formatType,sizeof(short),1,fp);
    fread(&channels,sizeof(short),1,fp);
    fread(&sampleRate,sizeof(unsigned int),1,fp);
    fread(&avgBytesPerSec,sizeof(unsigned int),1,fp);
    fread(&bytesPerSample,sizeof(short),1,fp);
    fread(&bitsPerSample,sizeof(short),1,fp);
    
    fread(type,sizeof(char),4,fp);
    if (type[0]!='d' || type[1]!='a' || type[2]!='t' || type[3]!='a')           //This part should be "data"
    return printf("Missing DATA");                                        //not data
    
    fread(&dataSize,sizeof(unsigned int),1,fp);                                        //The size of the sound data is read
    
    ////Display the info about the WAVE file
    //std::cout << "Chunk Size: " << chunkSize << "\n";
    //std::cout << "Format Type: " << formatType << "\n";
    //std::cout << "Channels: " << channels << "\n";
    //std::cout << "Sample Rate: " << sampleRate << "\n";
    //std::cout << "Average Bytes Per Second: " << avgBytesPerSec << "\n";
    //std::cout << "Bytes Per Sample: " << bytesPerSample << "\n";
    //std::cout << "Bits Per Sample: " << bitsPerSample << "\n";
    //std::cout << "Data Size: " << dataSize << "\n";
    //    
    buf= new unsigned char[dataSize];                            //Allocate memory for the sound data
	fread(buf,1,dataSize,fp);
    //std::cout << fread(buf,1,dataSize,fp) << " bytes loaded\n";           //Read the sound data and display the 
                                                                                //number of bytes loaded.
                                                                                //Should be the same as the Data Size if OK
	
    fclose(fp);                                                                 //Close the WAVE file

	frequency=sampleRate;;                                               //The Sample Rate of the WAVE file
    format=0;                                                            //The audio format (bits per sample, number of channels)


	//engine->Generate(1, &buffer,&source);                                                    //Generate one OpenAL Buffer and link to "buffer"
	alGenBuffers(1, &buffer);
	alGenSources(1, &source);
	
	//Generate one OpenAL Source and link to "source"
    if(alGetError() != AL_NO_ERROR) printf("Error GenSource");     //Error during buffer/source generation
    
    //Figure out the format of the WAVE file
    if(bitsPerSample == 8)
    {
        if(channels == 1)
            format = AL_FORMAT_MONO8;
        else if(channels == 2)
            format = AL_FORMAT_STEREO8;
    }
    else if(bitsPerSample == 16)
    {
        if(channels == 1)
            format = AL_FORMAT_MONO16;
        else if(channels == 2)
            format = AL_FORMAT_STEREO16;
    }
	if(!format) printf("Wrong BitPerSample");                      //Not valid format

    alBufferData(buffer, format, buf, dataSize, frequency);                    //Store the sound data in the OpenAL Buffer
    if(alGetError() != AL_NO_ERROR) 
    printf("Error loading ALBuffer");                              //Error during buffer loading
};

void AudioSource::Play()
{
    ALfloat SourceVel[] = { 0.0, 0.0, 0.0 };                                    //Velocity of the source sound

	//Source
    alSourcei (mStream.source, AL_BUFFER,   mStream.buffer);                                 //Link the buffer to the source
    alSourcef (mStream.source, AL_PITCH,    1.0f     );                                 //Set the pitch of the source
    alSourcef (mStream.source, AL_GAIN,     1.0f     );                                 //Set the gain of the source
	alSourcefv(mStream.source, AL_POSITION, &mPosition[0]);                                 //Set the position of the source
    alSourcefv(mStream.source, AL_VELOCITY, SourceVel);                                 //Set the velocity of the source
    alSourcei (mStream.source, AL_LOOPING,  AL_FALSE );                                 //Set if source is looping sound
    
    //PLAY
    alSourcePlay(mStream.source);                                                       //Play the sound buffer linked to the source
    	 if(alGetError() != AL_NO_ERROR) printf("Error playing sound"); //Error when playing sound
 	//system("PAUSE");
}