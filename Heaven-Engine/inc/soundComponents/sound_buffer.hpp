#pragma once

#ifndef SOUND_BUFFER_HPP
#define SOUND_BUFFER_HPP

// include standard libraries
#include <map>
#include <string>

#include <AL/al.h>

/* Sound Buffer Class
*/
class SoundBuffer{
    private:
        // private storage of sounds
        std::map<std::string, ALuint> soundBuffers;

    public: 
        // constructor
        SoundBuffer();
        // descontructor
        ~SoundBuffer();

        //* Adder functions

        ALuint addSound(const char* filename, std::string name);

        //* Remove functions

        bool removeSound(std::string name);

};

#endif