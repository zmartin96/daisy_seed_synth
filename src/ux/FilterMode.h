// src/ux/FilterMode.h
#pragma once
#include "UXMode.h"
#include "SynthEngine.h"

class FilterMode : public UXMode
{
    public:
        // inherited functions
        void Init(daisy::DaisySeed* seed) override;
        void Process(const float* pot_values) override;
        void ApplyToSynth(SynthEngine& synth) override;
        const char* Name() override { return "Filter"; }

    private:
        // parameters
        float pitch_ = 0.0f;
        float gain_ = 0.0f;
        float cutoff_ = 0.0f;
        float resonance_ = 0.0f;
        float wave_mix_ = 0.0f;
        float fx_mix_ = 0.0f;
};