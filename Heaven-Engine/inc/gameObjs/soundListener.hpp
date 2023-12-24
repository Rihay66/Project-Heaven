#pragma once
#ifndef SOUNDLISTENER_HPP
#define SOUNDLISTENER_HPP

//include standard libs
#include <iostream>
#include <map>
#include <string>

//Include SFML lib
#include <SFML/Audio.hpp>
#include <glm/glm.hpp>

class SoundSource{
    private:
        //Contain resources of added sounds
        static std::map<std::string, sf::Sound> Sounds;

    public:
        //Contain reference to the volume
        float volume;
        //Contain reference to min distance from listener
        float minDistance;
        //Contain reference to attenuation from listener
        float attenuation;
        //Contain reference to distance between the sound source position and another position
        float distance;

        //Contain reference to this sound source current position
        glm::vec3 position;

        //Constructor
        SoundSource(float volume = 0.0f, glm::vec3 position = glm::vec3(0.0f));
        //Destructor
        ~SoundSource();
        
        //Load a sound buffer along with a name
        void loadSound(sf::SoundBuffer&, std::string name, bool loop = false);

        //*NOTE: For these functions to be used, be sure to load the sound along with it's set name
        //Get a sound from resource and play it
        void play(std::string name);
        //Get a sound from resource and pause it
        void pause(std::string name);
        //Get a sound from resource and stop it
        void stop(std::string name);

        //Set position
        void setPos(glm::vec3 pos, std::string name);

        //Set listener relation, i.e relation to the speakers
        void setRelativeToListener(bool flag, std::string name);

        //Set volume
        void setVolume(float amount, std::string name);

        //Set loop flag to a sound
        void setLoopFlag(bool flag, std::string name);

        //Set pitch
        void setPitch(float amount, std::string name);

        //Set distance from this sound source and another position
        void setMinDistance(float amount, std::string name);

        //Set attenuation
        void setAttenuation(float amount, std::string name);
};

#endif