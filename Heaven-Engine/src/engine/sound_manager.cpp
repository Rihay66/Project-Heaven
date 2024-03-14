#include <engine/sound_manager.hpp>
#include <utilities/convention_utils.hpp>

// instantiate static variables
SoundDevice* SoundManager::device;
std::map<std::string, SoundBuffer*> SoundManager::sounds;

void SoundManager::init(){
    // init sound device
    device = new SoundDevice();
}

void SoundManager::close(){
    // try and catch any errors
    try{
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