#pragma once

#ifndef SOUND_BUFFER_HPP
#define SOUND_BUFFER_HPP

// include standard libraries
#include <map>
#include <string>

#include <AL/al.h>

/* Sound Buffer Class for loading and storing sounds.
Each given sound are stored with a identifier name and 
sound file as well using the identifier name the sound 
buffer can be returned. Sound files need to be in .wav
file format.
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

        // for retrieving the sound buffer by identifier name
        ALuint getSound(std::string name);

        //* Adder functions

        // for storing a sound along with their identifier name and file path, returns the sound as a buffer
        ALuint addSound(std::string name, const char* filename);

        //* Remove functions

        // for removing a stored sound buffer using the identifier name, returns false for error and true for success
        bool removeSound(std::string name);

};

#endif