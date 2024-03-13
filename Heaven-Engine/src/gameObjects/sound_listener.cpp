#include <gameObjects/sound_listener.hpp>

#include <iostream>

// instantiate static resource
//std::map<std::string, sf::Sound> SoundSource::Sounds;

static std::string checkName(std::string str){

    // checking if string contains special character
    for(int i=0;i<str.length();i++)
    {
        if ((str[i]>=48 && str[i]<=57)||(str[i]>=65 && str[i]<=90)||(str[i]>=97 && str[i]<=122))
            continue;
        else
            std::cout << "ERROR: No special characters when setting or getting a sound! STR: \"" << str << "\""<< std::endl;
            exit(-1); // when a special character is found then stop the program
    }

    // make all characters to lower case
    for(int j=0;j<str.length();j++){
        str[j]=tolower(str[j]);
    }
    
    return str;
}

// constructor
SoundSource::SoundSource(float vol, glm::vec3 pos) : volume(vol), position(pos){}

// destructor
SoundSource::~SoundSource(){
    // grab all sound sources and stop playing their attached buffer
    /*
    for(auto sound : Sounds){
        sound.second.stop();
    }
    // clear all element of static resource
    Sounds.clear();
    */
}
/*
void SoundSource::loadSound(sf::SoundBuffer& buffer, std::string name, bool loop){
    // check the name
    name = checkName(name);
    
    // instantiate  sound ojbect in resource
    Sounds[name];

    // add the buffer to the sound
    Sounds[name].setBuffer(buffer);

    // set loop flag, Default is falsse
    Sounds[name].setLoop(loop);
}

void SoundSource::play(std::string name){
    // check the name
    name = checkName(name);

    // play the sound
    Sounds[name].play();
}

void SoundSource::pause(std::string name){
    // check the name
    name = checkName(name);

    // pause the sound
    Sounds[name].pause();
}

void SoundSource::stop(std::string name){
    // check the name
    name = checkName(name);

    //*NOTE: Stopping the sound rewinds it back to it's start
    // stop the sound
    Sounds[name].stop();
}

void SoundSource::setPos(glm::vec3 pos, std::string name){
    // check the name
    name = checkName(name);

    // set local pos 
    this->position = pos;

    // set a sound's position
    Sounds[name].setPosition(pos.x, pos.y, pos.z);
}

void SoundSource::setRelativeToListener(bool flag, std::string name){
    // check the name
    name = checkName(name);

    // set a sound's relativity to the listener
    Sounds[name].setRelativeToListener(flag);
}

void SoundSource::setVolume(float amount, std::string name){
    // check the name 
    name = checkName(name);

    // set a sound's volume
    Sounds[name].setVolume(amount);
}

void SoundSource::setLoopFlag(bool flag, std::string name){
    // check the name
    name = checkName(name);

    // set a sound's loop flag
    Sounds[name].setLoop(flag);
}

void SoundSource::setPitch(float amount, std::string name){
    // check the name
    name = checkName(name);

    // set a sound's pitch 
    Sounds[name].setPitch(amount);
}

void SoundSource::setMinDistance(float amount, std::string name){
    // check the name
    name = checkName(name);

    // set distace from listener, must be above 1 to be 
    Sounds[name].setMinDistance(amount);
}

void SoundSource::setAttenuation(float amount, std::string name){
    // check the name
    name = checkName(name);

    // set attenuation of the sound
    Sounds[name].setAttenuation(amount);
}
*/