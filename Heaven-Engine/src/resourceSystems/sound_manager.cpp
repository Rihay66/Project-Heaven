#include <resourceSystems/sound_manager.hpp>

// include standard output library
#include <iostream>

// instantiate static variables
SoundDevice*                            SoundManager::device;
std::map<std::string, SoundBuffer*>     SoundManager::sounds;
std::vector<unsigned int>               SoundManager::sources;
bool                                    SoundManager::isAutoClearSet = false;

void SoundManager::InitDevice(){
    // set up automatic clear()
    SetUpAutoClear();

    // init sound device
    
    // check if sound device is already initialized
    if(device != nullptr)
        return; // don't do anything

    // init sound device
    device = new SoundDevice();
}

void SoundManager::Clear(){
    // try and catch any errors
    try{
        // clear all sound sources
        for(auto& source : sources){
            // check if it's a valid source
            if(alIsSource(source)){
                // remove source
                alDeleteSources(1, &source);
            }
        }

        // clear all sound buffers
        for(auto& iter : sounds){
            delete iter.second;
        }

        // shutdown the sound device
        delete device;
        
    }catch(std::exception& e){
        // print out error
        std::cout << "ERROR: OpenAL caused an Exception: " << e.what() << "\n";

        // check for any OpenAL errors
        ALenum err = alGetError();
        if(err != AL_NO_ERROR){
            fprintf(stderr, "ERROR: OpenAL Error: %s\n", alGetString(err));
        }
    }
}

SoundBuffer* SoundManager::GetBufferFromCollection(std::string name){
    return sounds[name];
}

unsigned int SoundManager::GetSoundFromBufferInColleciton(std::string collectionName, std::string soundName){
    if(!GetBufferFromCollection(collectionName))
        return -1;

    return sounds[collectionName]->getSound(soundName);
}

SoundBuffer* SoundManager::CreateSoundCollection(std::string name){
    // set up automatic clear()
    SetUpAutoClear();

    // set up device
    InitDevice();

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

SoundBuffer* SoundManager::CreateSoundCollection(std::string collectionName, std::string soundName, const char* filename){
    // set up automatic clear()
    SetUpAutoClear();

    // set up device
    InitDevice();

    // create the buffer
    CreateSoundCollection(collectionName);

    // add sound to the buffer
    if(sounds[collectionName]->addSound(soundName, filename) == 0){
        std::cout << "ERROR: an error occured when loading the sound file: " << filename << "\n";
    }

    return sounds[collectionName];
}

unsigned int SoundManager::AddSoundToBuffer(std::string collectionName, std::string soundName, const char* filename){
    // set up automatic clear()
    SetUpAutoClear();

    // set up device
    InitDevice();
    
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

void SoundManager::AddSource(unsigned int source){
    // check if source is valid
    if(!alIsSource(source)){
        std::cout << "ERROR: invalid sound source added to sound manager!\n";
        return; // stop function
    }

    // set up automatic clear()
    SetUpAutoClear();

    // set up device
    InitDevice();

    // check if source already exists
    for(auto& i : sources){
        if(i == source){
            return; // stop function
        }
    }

    // if it doesn't exist then add
    sources.push_back(source);
}

void SoundManager::RemoveSoundCollection(std::string name){
    // check if buffer is not already null
    if(sounds[name] == nullptr){
        return; // stop function
    }

    // free buffer from memory
    delete sounds[name];
    sounds.erase(name);
}

void SoundManager::RemoveSoundFromBuffer(std::string collectionName, std::string soundName){
    // check if buffer is not already null
    if(sounds[collectionName] == nullptr){
        return; // stop function
    }

    // remove sound
    sounds[collectionName]->removeSound(soundName);
}

void SoundManager::SetUpAutoClear(){
    // set up on exit to call the Clear()
    if(!isAutoClearSet && std::atexit(Clear) == 0){
        isAutoClearSet = true; // disable calling this function again
    }
}