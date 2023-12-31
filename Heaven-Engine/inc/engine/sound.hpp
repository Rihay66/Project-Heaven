#pragma once
#ifndef SOUND_HPP
#define SOUND_HPP

//Include standard libraries
#include <iostream>
#include <exception>
#include <map>
#include <string>

//include SFML sound module
#include <SFML/Audio.hpp>

class SoundEngine{
    private:
        //resource containing each sound along with their names
        std::map<std::string, sf::SoundBuffer> SoundBuffers;

    public:
        //Constructor
        SoundEngine();
        //Destructor
        ~SoundEngine();

        //Loads a sound buffer and the buffer is stored in the static resources, can also return the buffer that is loaded
        sf::SoundBuffer& loadSoundBuffer(const std::string filename, std::string name);

        //Finds and returns a buffer from the static resources 
        sf::SoundBuffer& getSoundBuffer(std::string name);
};

#endif