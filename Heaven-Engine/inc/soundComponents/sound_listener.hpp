#pragma once
#ifndef SOUND_LISTENER_HPP
#define SOUND_LISTENER_HPP

// include standard libs
#include <map>
#include <string>

#include <glm/glm.hpp>

/* Sound Source Class contains a collection of loaded sounds.
 Sounds that can be played, stopped, and looped and adjusted to meet a specific need.
*/
class SoundSource{
    private:
        // contain resources of added sounds
        //static std::map<std::string, sf::Sound> Sounds;

        // contain reference to the volume
        float volume;
        // contain reference to min distance from listener
        float minDistance;
        // contain reference to attenuation from listener
        float attenuation;
        // contain reference to distance between the sound source position and another position
        float distance;

        // contain reference to this sound source current position
        glm::vec3 position;

    public:

        // constructor
        SoundSource(float volume = 0.0f, glm::vec3 position = glm::vec3(0.0f));
        // destructor
        ~SoundSource();
        
        // load a sound buffer along with a name
        //void loadSound(sf::SoundBuffer&, std::string name, bool loop = false);

        //*NOTE: For these functions to be used, be sure to load the sound along with it's set name
        
        // get a sound from resource and play it
        void play(std::string name);
        // get a sound from resource and pause it
        void pause(std::string name);
        // get a sound from resource and stop it
        void stop(std::string name);

        // set position
        void setPos(glm::vec3 pos, std::string name);

        // set listener relation, i.e relation to the speakers
        void setRelativeToListener(bool flag, std::string name);

        // set volume
        void setVolume(float amount, std::string name);

        // set loop flag to a sound
        void setLoopFlag(bool flag, std::string name);

        // set pitch
        void setPitch(float amount, std::string name);

        // set distance from this sound source and another position
        void setMinDistance(float amount, std::string name);

        // set attenuation
        void setAttenuation(float amount, std::string name);
};

#endif