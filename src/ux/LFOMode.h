// src/ux/LFOMode.h
#pragma once
#include "UXMode.h"
#include "SynthEngine.h"

class LFOMode : public UXMode
{
public:
    // inherited functions
    void Init(daisy::DaisySeed *seed) override;
    void Process(const float *pot_values) override;
    void ApplyToSynth(SynthEngine &synth) override;
    const char *Name() override { return "LFO"; }

private:
    // parameters
    float rate_ = 0.0f;
    float depth_ = 0.0f;
    float attack_ = 0.0f;
    float decay_ = 0.0f;
    float modulation_ = 0.0f;
    float shape_ = 0.0f;
};