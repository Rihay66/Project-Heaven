#include <engine/sound.hpp>

// include standard libraries
#include <iostream>
#include <exception>

#include <AL/alext.h>
#include <sndfile.h>
#include <inttypes.h>
#include <limits.h>

static std::string checkName(std::string str){

    // checking if string contains special character
    for(int i=0;i<str.length();i++)
    {
        if ((str[i]>=48 && str[i]<=57)||(str[i]>=65 && str[i]<=90)||(str[i]>=97 && str[i]<=122))
            continue;
        else
            std::cout << "ERROR: No special characters when setting or getting a sound buffer! STR: \"" << str << "\""<< std::endl;
            exit(-1); // when a special character is found then stop the program
    }

    // make all characters to lower case
    for(int j=0;j<str.length();j++){
        str[j]=tolower(str[j]);
    }
    
    return str;
}

ALuint* grabSoundBuffers(std::map<std::string, ALuint> &buffers){
    // allocate memory for an array of ALuint to store all the buffer values
    ALuint* bufferArray = new ALuint[buffers.size()];

    // iterator for traversing the map
    auto it = buffers.begin();

    // index to keep track of the position in the bufferArray
    size_t index = 0;

    // iterate over the map and copy buffer values to bufferArray
    while (it != buffers.end()) {
        bufferArray[index++] = it->second;
        ++it;
    }

    return bufferArray;
}

//* Sound Device

SoundDevice* SoundDevice::get(){
    static SoundDevice* snd_device = new SoundDevice();
    return snd_device;
}

SoundDevice::SoundDevice(){
    //TODO: create a query system to allow for a set device defined by a user

    // get default sound device
    ALCDevice = alcOpenDevice(nullptr);

    if(!ALCDevice)
        throw("ERROR: failed to get sound device");

    // create context 
    ALCContext = alcCreateContext(ALCDevice, nullptr);

    if(!ALCContext){
        throw("ERROR: failed to set sound context");
    }

    if(!alcMakeContextCurrent(ALCContext)){ // make context current
        throw("ERROR: to make context current");
    }

    const ALCchar* name = nullptr;
    if(alcIsExtensionPresent(ALCDevice, "ALC_ENUMERATE_ALL_EXT")){
        name = alcGetString(ALCDevice, ALC_ALL_DEVICES_SPECIFIER);
    }

    if(!name || alcGetError(ALCDevice) != AL_NO_ERROR){
        name = alcGetString(ALCDevice, ALC_DEVICE_SPECIFIER);
    }

    std::cout << "Opened \""<< name << "\"\n";
}

SoundDevice::~SoundDevice(){
    // try to close device
    try{
        if(!alcMakeContextCurrent(nullptr)){
            throw("ERROR: failed to set context to nullptr");
        }

        alcDestroyContext(ALCContext);
        if(ALCContext){
            throw("ERROR: failed to unset context during close");
        }

        if(!alcCloseDevice(ALCDevice)){
            throw("ERROR: failed to close sound device");
        }
    }catch(std::exception& e){
        std::cout << "ERROR: " << e.what() << "\n";
    }
}

//* Sound Buffer

SoundBuffer* SoundBuffer::get(){
    static SoundBuffer* buffer = new SoundBuffer();
    return buffer;
}

ALuint SoundBuffer::addSound(const char* filename, std::string name){

    // create local vars
    ALenum err, format;
    ALuint buffer;
    SNDFILE* sndfile;
    SF_INFO sfinfo;
    short* membuf;
    sf_count_t num_frames;
    ALsizei num_bytes;

    // open the audio file and check if it's usable
    sndfile = sf_open(filename, SFM_READ, &sfinfo);
    if(!sndfile){
        fprintf(stderr, "ERROR: could not open audio in %s: %s\n", filename, sf_strerror(sndfile));
        return 0;
    }

    if(sfinfo.frames < 1 || sfinfo.frames > (sf_count_t)(INT_MAX / sizeof(short)) / sfinfo.channels){
        fprintf(stderr, "ERROR: bas sample count in %s (%" PRId64 ")\n", filename, sfinfo.frames);
        sf_close(sndfile);
        return 0;
    }

    // get the sound format, and figure out the OpenAL format
    format = AL_NONE;
    if(sfinfo.channels == 1){
        format = AL_FORMAT_MONO16;
    }else if(sfinfo.channels == 2){
        format = AL_FORMAT_STEREO16;
    }else if(sfinfo.channels == 3){
        if(sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT){
            format = AL_FORMAT_BFORMAT2D_16;
        }
    }else if(sfinfo.channels == 4){
        if(sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT){
            format = AL_FORMAT_BFORMAT3D_16;
        }
    }

    // check if format has been set
    if(!format){
        fprintf(stderr, "ERROR: unsupported channel count: %d\n", sfinfo.channels);
        sf_close(sndfile);
        return 0;
    }

    // decode the whole file into a buffer
    membuf = static_cast<short*>(malloc((size_t)(sfinfo.frames * sfinfo.channels) * sizeof(short)));

    num_frames = sf_readf_short(sndfile, membuf, sfinfo.frames);
    if(num_frames < 1){
        free(membuf);
        sf_close(sndfile);
        fprintf(stderr, "ERROR: failed to read samples in %s (%" PRId64 ")\n", filename, num_frames);
        return 0;
    }

    num_bytes = (ALsizei)(num_frames * sfinfo.channels) * (ALsizei)sizeof(short);

    // buffer the audio data into a new buffer object, then free the data and close the file

    buffer = 0;
    alGenBuffers(1, &buffer);
    alBufferData(buffer, format, membuf, num_bytes, sfinfo.samplerate);

    free(membuf);
    sf_close(sndfile);

    // check for any OpenAL errors
    err = alGetError();
    if(err != AL_NO_ERROR){
        fprintf(stderr, "ERROR: OpenAL Error: %s\n", alGetString(err));
        if(buffer && alIsBuffer(buffer)){
            alDeleteBuffers(1, &buffer);
        }
        return 0;
    }
    
    // check name convention
    name = checkName(name);

    // add name to resources
    soundBuffers[name] = buffer;
    
    return buffer;
} 

bool SoundBuffer::removeSound(std::string name){

    if(soundBuffers[name]){
        // remove sound buffer
        alDeleteBuffers(1, &soundBuffers[name]);
        soundBuffers.erase(name);
    }else{
        // couldn't find the buffer in resources
        return false;
    }

    // check for any OpenAL errors
    ALenum err = alGetError();
    if(err != AL_NO_ERROR){
        fprintf(stderr, "ERROR: OpenAL Error: %s\n", alGetString(err));

        return false;
    }

    return true;
}

SoundBuffer::SoundBuffer(){

}

SoundBuffer::~SoundBuffer(){
    // delete all sound buffers
    alDeleteBuffers(soundBuffers.size(), grabSoundBuffers(soundBuffers));

    // check for any OpenAL errors
    ALenum err = alGetError();
    if(err != AL_NO_ERROR){
        fprintf(stderr, "ERROR: OpenAL Error: %s\n", alGetString(err));
    }

    soundBuffers.clear();
}
