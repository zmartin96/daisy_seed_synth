// src/ux/FilterMode.cpp
#include "FilterMode.h"

void FilterMode::Init(daisy::DaisySeed* seed)
{
    // nothing rn
}

void FilterMode::Process(const float* pot_values)
{
    // store current pot values
    pitch_ = pot_values[0];
    gain_ = pot_values[1];
    cutoff_ = pot_values[2];
    resonance_ = pot_values[3];
    wave_mix_ = pot_values[4];
    fx_mix_ = pot_values[5];
}

void FilterMode::ApplyToSynth(SynthEngine& synth)
{
    synth.SetPitch(pitch_);
    synth.SetGain(gain_);
    synth.SetFilter(cutoff_,resonance_);
    synth.SetWaveMix(wave_mix_);
    synth.SetFxMix(fx_mix_);
}