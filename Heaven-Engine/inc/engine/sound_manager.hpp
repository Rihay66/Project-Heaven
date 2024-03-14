#pragma once

#ifndef SOUND_MANAGER_HPP
#define SOUND_MANAGER_HPP

// include standard libraries
#include <map>
#include <string>

#include <soundComponents/sound_device.hpp>
#include <soundComponents/sound_buffer.hpp>

/* Static Sound Manager class
*/
class SoundManager{
    private:
        // private static storage for sound device
        static SoundDevice* device;

        // private static storage for sound buffers as a collection
        static std::map<std::string, SoundBuffer*> sounds;

        // constructor
        SoundManager() {};

    public:

        // initializes the sound device
        static void init();

        // closes and clear the sound device and all sound buffers
        static void close();

        //* adder functions

        //* remover functions

};

#endif