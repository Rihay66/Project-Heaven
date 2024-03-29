#include <soundComponents/sound_source.hpp>

void SoundSource::setBuffer(unsigned int buff){
    // check if given buffer is zero
    if(buff == 0){
        return; // stop function
    }
    this->buffer = buff;
}

unsigned int SoundSource::getBuffer(){
    return this->buffer;
}

void SoundSource::play(const unsigned int sound, bool playOnce, bool waitForSound){
    // create a state variable
    ALint state;
    // check if it's a different buffer
    if(sound != buffer){
        setBuffer(sound);
        alSourcei(source, AL_BUFFER, buffer);
    }

    if(playOnce){
        alGetSourcei(source, AL_SOURCE_STATE, &state);
        // check if the source is done playing the sound
        if(state != AL_PLAYING){
            // play sound
            alSourcePlay(source);
        }
    }else{
        // play sound
        alSourcePlay(source);
    }

    if(waitForSound){
        // set state variable
        state = AL_PLAYING;

        // wait for sound to finish playing
        while(state == AL_PLAYING && alGetError() == AL_NO_ERROR){
            alGetSourcei(source, AL_SOURCE_STATE, &state);
        }
    }
}

void SoundSource::play(bool playOnce, bool waitForSound){
    // create a state variable
    ALint state;
    // check if sound buffer is not set to default value
    if(buffer != 0){
        if (playOnce){
            alGetSourcei(source, AL_SOURCE_STATE, &state);
            // check if the source is done playing the sound
            if (state != AL_PLAYING){
                // play sound
                alSourcePlay(source);
            }
        }
        else{
            alSourcePlay(source);
        }

        if(waitForSound){
            // set state variable
            state = AL_PLAYING;

            // wait for sound to finish playing
            while(state == AL_PLAYING && alGetError() == AL_NO_ERROR){
                alGetSourcei(source, AL_SOURCE_STATE, &state);
            }
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
    // genretate OpenAL source
    alGenSources(1, &source);
    alSourcef(source, AL_PITCH, pitch);
    alSourcef(source, AL_GAIN, gain);
    alSource3f(source, AL_POSITION, position.x, position.y, position.z);
    alSource3f(source, AL_VELOCITY, velocity.x, velocity.y, velocity.z);
    alSourcei(source, AL_LOOPING, loopSound);
    alSourcei(source, AL_BUFFER, buffer);
}

SoundSource::~SoundSource(){
    // remove source
    alDeleteSources(1, &source);
}

