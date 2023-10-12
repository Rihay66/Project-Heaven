#include <engine/sound.hpp>

static std::string checkName(std::string str){

    // Checking if string contains special character
    for(int i=0;i<str.length();i++)
    {
        if ((str[i]>=48 && str[i]<=57)||(str[i]>=65 && str[i]<=90)||(str[i]>=97 && str[i]<=122))
            continue;
        else
            std::cout << "ERROR: No special characters when setting or getting a sound buffer! STR: \"" << str << "\""<< std::endl;
            exit(-1); //When a special character is found then stop the program
    }

    //Make all characters to lower case
    for(int j=0;j<str.length();j++){
        str[j]=tolower(str[j]);
    }
    
    return str;
}

SoundEngine::SoundEngine(){

}

SoundEngine::~SoundEngine(){
    //Manually delete the buffers
    try{
        for(auto iter : SoundBuffers){
            iter.second.~SoundBuffer();
        }
    }
    catch(std::exception& e){
        std::cout << "ERROR: " << e.what() << "\n";
    }
}

sf::SoundBuffer& SoundEngine::loadSoundBuffer(const std::string filename, std::string name){

    //Check if name doesn't have any special characters and set to be all lowercase
    name = checkName(name);

    //*load a sound and have it stored in the static resources

    //Instantiate sound buffer with it's name
    SoundBuffers[name];

    //Load a sound and check for error
    if(!SoundBuffers[name].loadFromFile(filename)){
        
        std::cout << "ERROR: Couldn't load sound file!\n";

        //Error exit
        exit(-1);
    }

    return SoundBuffers[name];
}

sf::SoundBuffer& SoundEngine::getSoundBuffer(std::string name){

    //Check if name doesn't have any special characters and set to be all lowercase
    name = checkName(name);
    return SoundBuffers[name];
}