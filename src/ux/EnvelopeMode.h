// src/ux/EnvelopeMode.h
#pragma once
#include "UXMode.h"
#include "SynthEngine.h"

class EnvelopeMode : public UXMode
{
    public:
        // inherited functions
        void Init(daisy::DaisySeed* seed) override;
        void Process(const float* pot_values) override;
        void ApplyToSynth(SynthEngine& synth) override;
        const char* Name() override { return "Envelope"; }

    private:
        // parameters
        float attack_ = 0.0f;   // Attack time
        float decay_ = 0.0f;    // Decay time
        float sustain_ = 1.0f;  // Sustain level (0-1)
        float release_ = 0.05f; // Release time
        float velocity_ = 1.0f; // Velocity sensitivity (0-1)
        float shape_ = 0.0f;   // Envelope shape (0-1, linear to exponential)
};