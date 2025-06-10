// src/ux/EnvelopeMode.cpp
#include "EnvelopeMode.h"

using namespace daisy;

void EnvelopeMode::Init(DaisySeed* seed)
{
    // nothing rn
}

void EnvelopeMode::Process(const float* pot_values)
{
    // store current pot values
    attack_ = pot_values[0];
    decay_ = pot_values[1];
    sustain_ = pot_values[2];
    release_ = pot_values[3];
    velocity_ = pot_values[4];
    shape_ = pot_values[5];
}

void EnvelopeMode::ApplyToSynth(SynthEngine& synth)
{
    synth.SetEnvelope(attack_, decay_, sustain_, release_);
    synth.SetVelocity(velocity_);
    synth.SetEnvelopeShape(shape_);
}
