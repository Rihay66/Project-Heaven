#pragma once

#ifndef SOUND_MANAGER_HPP
#define SOUND_MANAGER_HPP

// include standard libraries
#include <map>

// include necessary components
#include <soundEngine/sound_device.hpp>
#include <soundEngine/sound_buffer.hpp>

/* A Static singleton Sound Manager class that hosts several
 function to load sounds and enables playing sounds. 
 Each loaded sound is also stored for future reference 
 by string handles as well stored within a collection 
 that contains a number of sounds. All functions and 
 resources are static and no public 
 constructor is defined.  
*/
class SoundManager{
    public:
        // initializes the sound device and OpenAL
        static void InitDevice();

        //* getter functions

        // get the buffer from the collection
        static SoundBuffer* GetBufferFromCollection(std::string name);

        // get sound from the buffer that in the collection, returns -1 if collection is not found
        static unsigned int GetSoundFromBufferInColleciton(std::string collectionName, std::string soundName);

        //* adder/setter functions 

        // instantiates a new buffer collection that is empty 
        static SoundBuffer* CreateSoundCollection(std::string name);

        // create a new buffer collection and allow for loading of one sound into the buffer collection
        static SoundBuffer* CreateSoundCollection(std::string collectionName, std::string soundName, const char* filename);

        // add a new sound buffer to a existing buffer collection, and if collection doesn't exist returns -1
        static unsigned int AddSoundToBuffer(std::string collectionName, std::string soundName, const char* filename);

        // store a sound source reference for automatic deletion
        static void AddSource(unsigned int source);

        //* remover functions

        // to remove a whole collection of sounds
        static void RemoveSoundCollection(std::string name);

        // to remove a single sound from a collection
        static void RemoveSoundFromBuffer(std::string collectionName, std::string soundName);
    private:
        // private static storage for sound device
        static SoundDevice* device;

        // private static storage for sound buffers as a collection
        static std::map<std::string, SoundBuffer*> sounds;
        
        // private static reference storage of sound sources
        static std::vector<unsigned int> sources;
    
        // closes and clear the sound device, sound buffers, and sound sources
        static void Clear();

        // constructor
        SoundManager() {};

        //! Currently EXPERIMENTAL, may cause exceptions or segfaults
        // private boolean to track automatic clear()
        static bool isAutoClearSet;
        // set up automatic de-allocation of loaded resources
        static void SetUpAutoClear();
};

#endif