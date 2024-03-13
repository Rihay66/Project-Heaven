#pragma once

#ifndef SOUND_HPP
#define SOUND_HPP

// include standard libraries
#include <map>
#include <string>

#include <AL/alc.h>
#include <AL/al.h>

/* Sound Device class
*/
class SoundDevice{
    public:

        // Sound device getter
        static SoundDevice* get();

    private:
        ALCdevice* ALCDevice;
        ALCcontext* ALCContext;

        // private constructor
        SoundDevice();
        // private destructor
        ~SoundDevice();
    
};

/* Sound Buffer Class
*/
class SoundBuffer{
    public: 
        // Sound buffer getter
        static SoundBuffer* get();

        //* Adder functions

        ALuint addSound(const char* filename, std::string name);

        //* Remove functions

        bool removeSound(std::string name);

    private:
        // private constructor
        SoundBuffer();
        // private descontructor
        ~SoundBuffer();

        // private storage of sounds
        std::map<std::string, ALuint> soundBuffers;
};

#endif