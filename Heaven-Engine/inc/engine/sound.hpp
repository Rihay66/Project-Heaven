#pragma once
#ifndef SOUND_HPP

//Include standard libraries
#include <iostream>
#include <vector>
#include <map>
#include <string>

//include SFML sound module
#include <SFML/Audio.hpp>

class SoundEngine{
    private:
        //Static resource containing each sound along with their names
        static std::map<std::string, sf::SoundBuffer> Sounds;

    public:
        //Constructor
        SoundEngine();
        //Destructor
        ~SoundEngine();

        //Loads a sound buffer and the buffer is stored in the static resources, can also return the buffer that is loaded
        sf::SoundBuffer loadSound(const std::string filename, std::string name);

        //Finds and returns a buffer from the static resources 
        sf::SoundBuffer getSound(std::string name);
};
//TODO: Make a sound listener a seperate class for game objects or manually use to be possible

#endif