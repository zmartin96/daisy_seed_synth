// src/ux/SequencerMode.h
#pragma once
#include "UXMode.h"
#include "SynthEngine.h"

class SequencerMode : public UXMode
{
    public:
        void Init(daisy::DaisySeed* seed) override;
        void Process(const float* pot_values) override;
        void ApplyToSynth(SynthEngine& synth) override;
        const char* Name() override { return "Sequencer"; }

    private:
        static constexpr int kNumSteps = 16; // number of steps in sequencer
        float steps_[kNumSteps] = {0}; // step values
        int step_count_ =8; 
        int current_step_ = 0; // current step index

        float tempo_ = 120.0f; // tempo bpm
        float note_length_ = 0.5f // length of note in seconds
        float mod_depth_ = 1.0f; // modulation depth
        float mod_target_ = 0.0f; // modulation target (0-1)
        float pattern_shape_ = 0.0f; // pattern shape (0-1)

        float last_time_ = 0.0f;
        float interval_ = 0.5f;

        void UpdateInterval();
        void GeneratePattern();
};