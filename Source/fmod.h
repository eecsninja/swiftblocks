// fmod.h
//
// Stub function in place of actual FMOD libraries.
//
// Author:    Simon Que


#ifndef _FMOD_H_
#define _FMOD_H_

enum {
    FSOUND_FREE,
    FSOUND_LOOP_NORMAL,
};

static struct FSOUND_SAMPLE {
    int foo;
} dummy_sample;

namespace {
int FSOUND_Init(int freq, int num_channels, int flags) {
    return 0;
}

FSOUND_SAMPLE* FSOUND_Sample_Load(int index, const char* path, int mode, int offset) {
    return &dummy_sample;
}

int FSOUND_PlaySound(int type, FSOUND_SAMPLE* sample) {
    return 0;
}

int FSOUND_StopSound(int channel) {
    return 0;
}

int FSOUND_SetLoopMode(int channel, int mode) {
    return 0;
}

int FSOUND_Sample_Free(FSOUND_SAMPLE* sample) {
    return 0;
}
}

#endif  // _FMOD_H_
