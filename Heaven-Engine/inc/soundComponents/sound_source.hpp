#pragma once

#ifndef SOUND_SOURCE_HPP
#define SOUND_SOURCE_HPP

#include <glm/glm.hpp>

#include <AL/al.h>

class SoundSource{
    private:
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

        void setBuffer(unsigned int buff);

        //* Getter functions

        unsigned int getBuffer();

        //* Helper functions

        // plays the given sound, also sets the given buffer to be current
        void play(const unsigned int sound, bool playOnce = false, bool waitForSound = false);
        
        // plays a pre-given sound
        void play(bool playOnce = false, bool waitForSound = false);

        // constructor
        SoundSource();
        // decontructor
        ~SoundSource();
};

#endif