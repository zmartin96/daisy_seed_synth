// src/ux/LFOMode.cpp
#include "LFOMode.h"

void LFOMode::Init(daisy::DaisySeed *seed)
{
    // nothing rn
}

void LFOMode::Process(const float *pot_values)
{
    // store current pot values
    rate_ = pot_values[0];
    depth_ = pot_values[1];
    attack_ = pot_values[2];
    decay_ = pot_values[3];
    modulation_ = pot_values[4];
    shape_ = pot_values[5];
}

void LFOMode::ApplyToSynth(SynthEngine &synth)
{
    synth.SetLfoRate(rate_);
    synth.SetLfoDepth(depth_);
    synth.SetEnvelope(attack_,decay_);
    synth.SetModTarget(modulation_);
    synth.SetLfoShape(shape_);
}