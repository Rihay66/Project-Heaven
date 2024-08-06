#include <soundEngine/sound_device.hpp>
#include <utilities/convention_utils.hpp>

#include <AL/al.h>

//* Sound Device

SoundDevice::SoundDevice(const char* queriedDevice, const char debugMode){

    //TODO: create a query system to allow for a set device defined by a user

    //check if name exists

    // get specified name sound device
    ALCDevice = alcOpenDevice(queriedDevice);

    if(!ALCDevice){
        throw("ERROR: failed to get sound device");
    }

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

    // check for debug mode
    switch(debugMode){
        case 'd':
            // get device name
            std::cout << "Opened \""<< name << "\"\n";
            break;
        default:
            break;
    }

    // store sound device name
    deviceName = std::string(name);
}

SoundDevice::~SoundDevice(){
    // try to close sound device and report any errors
    try{
        // stop context from receiving updates
        alcSuspendContext(ALCContext);

        // try to close device
        alcMakeContextCurrent(nullptr);

        // destroy the context
        alcDestroyContext(ALCContext);

        // close the sound device
        alcCloseDevice(ALCDevice);

    }catch(std::exception& e){

        std::cout << "ERROR: OpenAL caused an Exception: " << e.what() << "\n";
        
        // check for any OpenAL errors
        ALenum err = alGetError();
        if(err != AL_NO_ERROR){
            fprintf(stderr, "ERROR: Sound Device OpenAL Error: %s\n", alGetString(err));
        }
    }

}

std::string SoundDevice::getSoundDeviceName(){
    return this->deviceName;
}