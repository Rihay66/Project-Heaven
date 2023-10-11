#include <engine/sound.hpp>

//Instatiate static resources
std::map<std::string, sf::SoundBuffer> SoundEngine::Sounds;

static std::string checkFileName(std::string str){

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
SoundEngine::SoundEngine(){

}

//Destructor
SoundEngine::~SoundEngine(){

}

sf::SoundBuffer SoundEngine::loadSound(const std::string filename, std::string name){

    //Check if name doesn't have any special characters and set to be all lowercase
    name = checkFileName(name);

    //*load a sound and have it stored in the static resources

    //Instantiate sound buffer with it's name
    Sounds[name];

    //Load a sound and check for error
    if(!Sounds[name].loadFromFile(filename)){
        
        std::cout << "ERROR: Couldn't load sound file!\n";

        //Error exit
        exit(-1);
    }

    return Sounds[name];
}

sf::SoundBuffer SoundEngine::getSound(std::string name){

    //Check if name doesn't have any special characters and set to be all lowercase
    name = checkFileName(name);
    return Sounds[name];
}