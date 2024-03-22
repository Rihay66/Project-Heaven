#pragma once

#ifndef SOUND_MANAGER_HPP
#define SOUND_MANAGER_HPP

// include standard libraries
#include <map>
#include <string>

#include <soundComponents/sound_device.hpp>
#include <soundComponents/sound_buffer.hpp>
#include <soundComponents/sound_source.hpp>

/* Static Sound Manager class
*/
class SoundManager{
    private:
        // private static storage for sound device
        static SoundDevice* device;

        static SoundSource* source;

        // private static storage for sound buffers as a collection
        static std::map<std::string, SoundBuffer*> sounds;

        // constructor
        SoundManager() {};

    public:

        // initializes the sound device
        static void init();

        // closes and clear the sound device and all sound buffers
        static void close();

        //* helper functions

        static void playSound(std::string collectionName, std::string soundName, bool playOnce = false);

        static void stopSound();

        //* getter functions

        // get the buffer from the collection
        static SoundBuffer* getBufferFromCollection(std::string name);

        // get sound from the buffer that in the collection, returns -1 if collection is not found
        static unsigned int getSoundFromBufferInColleciton(std::string collectionName, std::string soundName);

        //* adder functions 

        // instantiates a new buffer that is empty 
        static SoundBuffer* createSoundCollection(std::string name);

        // create a new buffer and allow for loading of one sound into the buffer
        static SoundBuffer* createSoundCollection(std::string collectionName, std::string soundName, const char* filename);

        // add a new sound to the buffer, and if collection doesn't exist returns -1
        static unsigned int addSoundToBuffer(std::string collectionName, std::string soundName, const char* filename);

        //* remover functions

        static void removeSoundCollection(std::string name);

        static void removeSoundFromBuffer(std::string collectionName, std::string soundName);

};

#endif