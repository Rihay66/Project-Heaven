#pragma once

#ifndef SOUND_BUFFER_HPP
#define SOUND_BUFFER_HPP

// include OpenAL
#include <AL/al.h>

/* Sound Buffer Class for loading and storing sound.
Sounds are loading through file and returns a 
buffer can be retrieved. Sound files must be .wav file format
*/
class SoundBuffer{
    private:
        // define a buffer
        ALuint buffer;

    public: 
        //* getter functions

        // for retrieving the sound buffer 
        ALuint getSound();

        //* adder functions

        /* for loading a sound from file path, returns the sound as a buffer
        * @NOTE: The file format must be .wav
        */
        ALuint loadSound(const char* filename);

        //* remove functions

        // for removing a stored sound buffer, returns false for error and true for success
        bool removeSound();

};

#endif