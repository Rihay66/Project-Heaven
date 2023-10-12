#include <gameObjs/soundListener.hpp>

//instantiate static resource
std::map<std::string, sf::Sound> SoundSource::Sounds;

static std::string checkName(std::string str){

    // Checking if string contains special character
    for(int i=0;i<str.length();i++)
    {
        if ((str[i]>=48 && str[i]<=57)||(str[i]>=65 && str[i]<=90)||(str[i]>=97 && str[i]<=122))
            continue;
        else
            std::cout << "ERROR: No special characters when setting or getting a sound! STR: \"" << str << "\""<< std::endl;
            exit(-1); //When a special character is found then stop the program
    }

    //Make all characters to lower case
    for(int j=0;j<str.length();j++){
        str[j]=tolower(str[j]);
    }
    
    return str;
}

//Constructor
SoundSource::SoundSource(float vol, glm::vec3 pos) : volume(vol), position(pos){}

//Destructor
SoundSource::~SoundSource(){
    //Grab all sound sources and stop playing their attached buffer
    for(auto sound : Sounds){
        sound.second.stop();
    }
}

void SoundSource::loadSound(sf::SoundBuffer& buffer, std::string name){
    //check the name
    name = checkName(name);
    
    //Instantiate  sound ojbect in resource
    Sounds[name];

    //Add the buffer to the sound
    Sounds[name].setBuffer(buffer);
    
}

void SoundSource::play(std::string name){
    //Check the name
    name = checkName(name);

    //Play the sound
    Sounds[name].play();
}

void SoundSource::pause(std::string name){
    //check the name
    name = checkName(name);

    //Pause the sound
    Sounds[name].pause();
}

void SoundSource::stop(std::string name){
    //check the name
    name = checkName(name);

    //*NOTE: Stopping the sound rewinds it back to it's start
    //Stop the sound
    Sounds[name].stop();
}

void SoundSource::setPos(glm::vec3 pos, std::string name){
    //Check the name
    name = checkName(name);

    //Set local pos 
    this->position = pos;

    //Set a sound's position
    Sounds[name].setPosition(pos.x, pos.y, pos.z);
}

void SoundSource::setRelativeToListener(bool flag, std::string name){
    //Check the name
    name = checkName(name);

    //Set a sound's relativity to the listener
    Sounds[name].setRelativeToListener(flag);
}

void SoundSource::setVolume(float amount, std::string name){
    //Check the name 
    name = checkName(name);

    //Set a sound's volume
    Sounds[name].setVolume(amount);
}

void SoundSource::setLoopFlag(bool flag, std::string name){
    //Check the name
    name = checkName(name);

    //Set a sound's loop flag
    Sounds[name].setLoop(flag);
}

void SoundSource::setPitch(float amount, std::string name){
    //Check the name
    name = checkName(name);

    //Set a sound's pitch 
    Sounds[name].setPitch(amount);
}

void SoundSource::setMinDistance(float amount, std::string name){
    //Check the name
    name = checkName(name);

    //Set distace from listener, must be above 1 to be 
    Sounds[name].setMinDistance(amount);
}

void SoundSource::setAttenuation(float amount, std::string name){
    //Check the name
    name = checkName(name);

    //Set attenuation of the sound
    Sounds[name].setAttenuation(amount);
}