#include <soundComponents/sound_buffer.hpp>
#include <utilities/convention_utils.hpp>

#include <AL/alext.h>
#include <sndfile.h>
#include <inttypes.h>
#include <limits.h>

ALuint SoundBuffer::getSound(std::string name){
    return this->soundBuffers[name];
}

ALuint SoundBuffer::addSound(std::string name, const char* filename){

    // create local vars
    ALenum err, format;
    ALuint buffer;
    SNDFILE* sndfile;
    SF_INFO sfinfo;
    short* membuf;
    sf_count_t num_frames;
    ALsizei num_bytes;

    // open the audio file and check if it's usable
    sndfile = sf_open(filename, SFM_READ, &sfinfo);
    if(!sndfile){
        fprintf(stderr, "ERROR: could not open audio in %s: %s\n", filename, sf_strerror(sndfile));
        return 0;
    }

    if(sfinfo.frames < 1 || sfinfo.frames > (sf_count_t)(INT_MAX / sizeof(short)) / sfinfo.channels){
        fprintf(stderr, "ERROR: bas sample count in %s (%" PRId64 ")\n", filename, sfinfo.frames);
        sf_close(sndfile);
        return 0;
    }

    // get the sound format, and figure out the OpenAL format
    format = AL_NONE;
    if(sfinfo.channels == 1){
        format = AL_FORMAT_MONO16;
    }else if(sfinfo.channels == 2){
        format = AL_FORMAT_STEREO16;
    }else if(sfinfo.channels == 3){
        if(sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT){
            format = AL_FORMAT_BFORMAT2D_16;
        }
    }else if(sfinfo.channels == 4){
        if(sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT){
            format = AL_FORMAT_BFORMAT3D_16;
        }
    }

    // check if format has been set
    if(!format){
        fprintf(stderr, "ERROR: unsupported channel count: %d\n", sfinfo.channels);
        sf_close(sndfile);
        return 0;
    }

    // decode the whole file into a buffer
    membuf = static_cast<short*>(malloc((size_t)(sfinfo.frames * sfinfo.channels) * sizeof(short)));

    num_frames = sf_readf_short(sndfile, membuf, sfinfo.frames);
    if(num_frames < 1){
        free(membuf);
        sf_close(sndfile);
        fprintf(stderr, "ERROR: failed to read samples in %s (%" PRId64 ")\n", filename, num_frames);
        return 0;
    }

    num_bytes = (ALsizei)(num_frames * sfinfo.channels) * (ALsizei)sizeof(short);

    // buffer the audio data into a new buffer object, then free the data and close the file

    buffer = 0;
    alGenBuffers(1, &buffer);
    alBufferData(buffer, format, membuf, num_bytes, sfinfo.samplerate);

    free(membuf);
    sf_close(sndfile);

    // check for any OpenAL errors
    err = alGetError();
    if(err != AL_NO_ERROR){
        fprintf(stderr, "ERROR: Sound Buffer Sound Loading OpenAL Error: %s\n", alGetString(err));
        if(buffer && alIsBuffer(buffer)){
            alDeleteBuffers(1, &buffer);
        }
        return 0;
    }
    
    // check name convention
    name = checkName(name);

    // add name to resources
    soundBuffers[name] = buffer;
    
    return buffer;
} 

bool SoundBuffer::removeSound(std::string name){

    if(soundBuffers[name]){
        // remove sound buffer
        alDeleteBuffers(1, &soundBuffers[name]);
        soundBuffers.erase(name);
    }else{
        // couldn't find the buffer in resources
        return false;
    }

    // check for any OpenAL errors
    ALenum err = alGetError();
    if(err != AL_NO_ERROR){
        fprintf(stderr, "ERROR: Sound Buffer Sound Removal OpenAL Error: %s\n", alGetString(err));

        return false;
    }

    return true;
}

SoundBuffer::SoundBuffer(){}

SoundBuffer::~SoundBuffer(){
    // delete all sound buffers
    for(auto const& i : this->soundBuffers){
        if(!removeSound(i.first)){
            fprintf(stderr, "ERROR: Failed to remove buffer | %s, %i\n", i.first.c_str(), i.second);
        }
    }
    
    // check for any OpenAL errors
    ALenum err = alGetError();
    if(err != AL_NO_ERROR){
        fprintf(stderr, "ERROR: Sound Buffer Deconstructor OpenAL Error: %s\n", alGetString(err));
    }

    soundBuffers.clear();
}