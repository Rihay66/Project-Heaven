#include <soundComponents/sound_source.hpp>

// include the sound manager for auto clear
#include <resourceSystems/managers/sound_manager.hpp>

void SoundSource::setPitch(float p){
    // check if parameter is within a range
    if(p > 0.0f && p < 1.0f){
        // then replace pitch to such value
        this->pitch = p;
        // change the source to have new pitch value
        alSourcef(source, AL_PITCH, pitch);
    }
}

void SoundSource::setGain(float g){
    // check if parameter is within a range
    if(g > 0.0f && g < 1.0f){
        // then replace pitch to such value
        this->gain = g;
        // change the source to have new gain value
        alSourcef(source, AL_GAIN, gain);
    }
}

void SoundSource::setBuffer(unsigned int buff){
    // check if given buffer is zero
    if(buff == 0){
        return; // stop function
    }
    this->buffer = buff;
    alSourcei(source, AL_BUFFER, buffer);
}

void SoundSource::setLoopSound(bool l){
    // set var of the parameter for looping sounds
    this->loopSound = l;

    // change source to allow auto looping of a sound
    alSourcei(source, AL_LOOPING, loopSound);
}

unsigned int SoundSource::getBuffer(){
    return this->buffer;
}

void SoundSource::play(const unsigned int sound, bool playAgainWhenFinished){
    // create a state variable
    ALint state;
    // check if it's a different buffer
    if(sound != buffer){
        setBuffer(sound);
    }

    if(playAgainWhenFinished){
        alGetSourcei(source, AL_SOURCE_STATE, &state);
        // check if the source is done playing a sound
        if(state != AL_PLAYING){
            // play sound
            alSourcePlay(source);
        }
    }else{
        // play sound
        alSourcePlay(source);
    }
}

void SoundSource::play(bool playAgainWhenFinished){
    // create a state variable
    ALint state;
    // check if sound buffer is not set to default value
    if(buffer != 0){
        if (playAgainWhenFinished){
            alGetSourcei(source, AL_SOURCE_STATE, &state);
            // check if the source is done playing a sound
            if (state != AL_PLAYING){
                // play sound
                alSourcePlay(source);
            }
        }
        else{
            alSourcePlay(source);
        }
    }
}

void SoundSource::stop(){
    alSourceStop(this->source);
}

void SoundSource::restartSound(){
    // pause the current sound
    alSourcePause(this->source);
    // restart the sound
    alSourceRewind(this->source);;
}


SoundSource::SoundSource(){
    // initialize OpenAL
    SoundManager::InitDevice();

    // generate OpenAL source
    alGenSources(1, &source);
    alSourcef(source, AL_PITCH, pitch);
    alSourcef(source, AL_GAIN, gain);
    alSource3f(source, AL_POSITION, position.x, position.y, position.z);
    alSource3f(source, AL_VELOCITY, velocity.x, velocity.y, velocity.z);
    alSourcei(source, AL_LOOPING, loopSound);
    alSourcei(source, AL_BUFFER, buffer);
    
    // add self to sound manager as reference
    SoundManager::AddSource(source);
}

SoundSource::~SoundSource(){}