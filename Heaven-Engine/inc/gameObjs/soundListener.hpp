#pragma once
#ifndef SOUNDLISTENER_HPP
#define SOUNDLISTENER_HPP

//include standard libs
#include <iostream>
#include <map>
#include <string>

//Include SFML lib
#include <SFML/Audio.hpp>

class SoundSource{
    private:
        //Contain resources of added sounds
        static std::map<std::string, sf::Sound> Sounds;

    public:
        //Constructor
        SoundSource();
        //Destructor
        ~SoundSource();
        
        //*NOTE: 
        //Load a sound buffer along with a name
        void loadSound(sf::SoundBuffer&, std::string name);

        //Get a sound from resource and play it
        void play(std::string name);
        //Get a sound from resource and pause it
        void pause(std::string name);
        //Get a sound from resource and stop it
        void stop(std::string name);

};

#endif