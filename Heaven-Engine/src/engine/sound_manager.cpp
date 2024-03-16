#include <engine/sound_manager.hpp>
#include <utilities/convention_utils.hpp>

// include standard output library
#include <ostream>

// instantiate static variables
SoundDevice* SoundManager::device;
SoundSource* SoundManager::source;
std::map<std::string, SoundBuffer*> SoundManager::sounds;

void SoundManager::init(){
    // init sound device
    device = new SoundDevice();

    // init sound source
    source = new SoundSource();
}

void SoundManager::close(){
    // try and catch any errors
    try{
        // delete the source
        delete source;

        // clear all sound buffers
        for(auto& iter : sounds){
            delete iter.second;
        }

        // shutdown the sound device
        delete device;
        
    }catch(std::exception& e){

        std::cout << "ERROR: OpenAL caused an Exception: " << e.what() << "\n";

        // check for any OpenAL errors
        ALenum err = alGetError();
        if(err != AL_NO_ERROR){
            fprintf(stderr, "ERROR: OpenAL Error: %s\n", alGetString(err));
        }
    }
}

void SoundManager::playSound(std::string collectionName, std::string soundName, bool playOnce){
    // check that collection nor source are not null
    if(sounds[collectionName] != nullptr && source != nullptr){
        source->play(sounds[collectionName]->getSound(soundName), playOnce);
    }
}

SoundBuffer* SoundManager::getBufferFromCollection(std::string name){
    return sounds[name];
}

unsigned int SoundManager::getSoundFromBufferInColleciton(std::string collectionName, std::string soundName){
    if(!getBufferFromCollection(collectionName))
        return -1;

    return sounds[collectionName]->getSound(soundName);
}

SoundBuffer* SoundManager::createSoundCollection(std::string name){
    // check if buffer is not already initialized 
    if(sounds[name] != nullptr){
        // give a warning
        std::cout << "Warning: " << name << 
        " already exists, if creation with the same name was intentional then remove collection and try again\n";

        // return already existing buffer
        return sounds[name];
    }else{
        // init the buffer
        sounds[name] = new SoundBuffer();
    }

    // return new or already existing buffer
    return sounds[name];
}

SoundBuffer* SoundManager::createSoundCollection(std::string collectionName, std::string soundName, const char* filename){
    // create the buffer
    createSoundCollection(collectionName);

    // add sound to the buffer
    if(sounds[collectionName]->addSound(soundName, filename) == 0){
        std::cout << "ERROR: an error occured when loading the sound file: " << filename << "\n";
    }

    return sounds[collectionName];
}

unsigned int SoundManager::addSoundToBuffer(std::string collectionName, std::string soundName, const char* filename){
    // check if buffer exists
    if(sounds[collectionName] != nullptr){
        if(sounds[collectionName]->addSound(soundName, filename) == 0){
            std::cout << "ERROR: an error occured when loading the sound file: " << filename << "\n";
        }
        return sounds[collectionName]->getSound(soundName);
    }else{
        return -1;
    }
}

void SoundManager::removeSoundCollection(std::string name){
    // check if buffer is not already null
    if(sounds[name] == nullptr){
        return; // stop function
    }

    // free buffer from memory
    delete sounds[name];
    sounds.erase(name);
}

void SoundManager::removeSoundFromBuffer(std::string collectionName, std::string soundName){
    // check if buffer is not already null
    if(sounds[collectionName] == nullptr){
        return; // stop function
    }

    // remove sound
    sounds[collectionName]->removeSound(soundName);
}