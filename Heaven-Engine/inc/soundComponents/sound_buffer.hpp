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

        //* Getter functions

        ALuint getSound(std::string name);

        //* Adder functions

        ALuint addSound(std::string name, const char* filename);

        //* Remove functions

        bool removeSound(std::string name);

};

#endif