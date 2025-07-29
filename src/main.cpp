// src/main.cpp
#include "daisy_seed.h"
#include "daisysp.h"
#include "SynthEngine.h"
#include "SynthInterface.h"

using namespace daisy;
using namespace daisysp;

DaisySeed hw;
SynthEngine synth;
SynthInterface controls;

float audio_callback(float** in, float** out, size_t size)
{
    for(size_t i =0; i<size;i++)
    {
        controls.Process();
        synth.Process();
        controls.ApplyToSynth(synth);

        float signal = synth.Generate();

        // convert to stereo
        out[0][i]=signal; // L
        out[1][i]=signal; // R
    }

    return 0.0f;
}

int main(void)
{
    hw.Configure();
    hw.Init();
    hw.SetAudioBlockSize(4); // run callback every 4 samples
    float sample_rate=hw.AudioSampleRate();

    synth.Init(sample_rate);
    controls.Init(&hw);

    hw.StartAudio(audio_callback);

    while (1) {} // loop
}