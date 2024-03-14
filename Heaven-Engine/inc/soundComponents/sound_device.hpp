#pragma once

#ifndef SOUND_DEVICE_HPP
#define SOUND_DEVICE_HPP

// include standard libraries
#include <string>

#include <AL/alc.h>

/* Sound Device class
*/
class SoundDevice{
    private:

        ALCdevice* ALCDevice;
        ALCcontext* ALCContext;

        // private storage of sound device name
        std::string deviceName;

    public:
        // constructor
        SoundDevice(const char* queriedDevice = nullptr, const char debugMode = NULL);
        // destructor
        ~SoundDevice();

        //* getter functions

        std::string getSoundDeviceName();
    
};


#endif