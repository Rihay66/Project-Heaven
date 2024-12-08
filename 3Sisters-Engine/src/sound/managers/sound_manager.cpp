#include <sound/managers/sound_manager.hpp>

// include standard output library
#include <iostream>
#include <algorithm>

// instantiate static variables
SoundDevice*                            SoundManager::device;
std::map<std::string, SoundBuffer>      SoundManager::sounds;
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
            if(!iter.second.removeSound()){
                std::cout << "ERROR: Failed to delete a sound buffer!\n";
            }
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

SoundBuffer& SoundManager::GetSoundBuffer(std::string name){
    return sounds[name];
}

unsigned int SoundManager::GetRawSoundBuffer(std::string name){
    return sounds[name].getSound();
}

SoundBuffer& SoundManager::LoadSound(std::string name, const char* filename){
    // set up automatic clear()
    SetUpAutoClear();

    // set up device
    InitDevice();

    // create the buffer
    SoundBuffer buffer;

    // load sound to the buffer
    if(buffer.loadSound(filename) == 0){
        std::cout << "ERROR: an error occured when loading the sound file: " << filename << "\n";
    }

    // add buffer to the list
    sounds[name] = buffer;

    return sounds[name];
}

void SoundManager::AddSoundSource(unsigned int source){
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

void SoundManager::RemoveSound(std::string name){
    // free buffer from memory
    sounds[name].removeSound();
    sounds.erase(name);
}

void SoundManager::RemoveSoundSource(unsigned int source){
    // check if source already exists
    for(auto& i : sources){
        // check for source and check that it is a valid source
        if(i == source && alIsSource(source)){
            // deletion of the source
            alDeleteSources(1, &source);
        }
    }

    // find object by index
    auto index = std::find(sources.begin(), sources.end(), source);

    // remove object from list
    if (index != sources.end()) { // ensure the object is found
        sources.erase(index);       // erase
    }
}

void SoundManager::SetUpAutoClear(){
    // set up on exit to call the Clear()
    if(!isAutoClearSet && std::atexit(Clear) == 0){
        isAutoClearSet = true; // disable calling this function again
    }
}