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
            std::cout << "ERROR: No special characters when setting or getting of either Shader or Texture! STR: \"" << str << "\""<< std::endl;
            exit(-1); //When a special character is found then stop the program
    }

    //Make all characters to lower case
    for(int j=0;j<str.length();j++){
        str[j]=tolower(str[j]);
    }
    
    return str;
}

//Constructor
SoundSource::SoundSource(){}

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

}

void SoundSource::stop(std::string name){
    //check the name
    name = checkName(name);

    //Stop the sound
    Sounds[name].stop();
}