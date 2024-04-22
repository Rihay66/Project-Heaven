#pragma once

#ifndef SOUND_SOURCE_HPP
#define SOUND_SOURCE_HPP

#include <glm/glm.hpp>

#include <AL/al.h>

//TODO: Add documentation about the class

class SoundSource{
    protected:
        // TODO: Add documentation for each variable
        // variables
        unsigned int source;
        float pitch = 1.0f;
        float gain = 1.0f;
        glm::vec3 position = glm::vec3(0.0f);
        glm::vec3 velocity = glm::vec3(0.0f);
        bool loopSound = false;
        unsigned int buffer = 0;

    public:

        //* Setter functions

        // sets the pitch of the source, takes in a vlaue within 0.0f to 1.0f
        void setPitch(float p);

        // sets the gain of the source, takes in a vlaue within 0.0f to 1.0f
        void setGain(float g);

        // adds and sets the sound buffer of the source
        void setBuffer(unsigned int buff);

        //* Getter functions
        // returns the sound buffer that is set to this sound source
        unsigned int getBuffer();

        //* Helper functions

        // plays the given sound, also sets the given buffer to be current
        void play(const unsigned int sound, bool playOnce = false);
        
        // plays a pre-given sound
        void play(bool playOnce = false);

        // stops current sound
        void stop();

        // pauses current sound and restarts the sound to the beggining
        void restartSound();

        // constructor
        SoundSource();
        // decontructor
        ~SoundSource();
};

#endif