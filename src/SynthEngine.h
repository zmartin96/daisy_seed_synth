// src/SynthEngine.h
#pragma once
#include "daisysp.h"

using namespace daisysp;

class SynthEngine
{
    public:
        void Init(float samplerate);
        void SetPitch(float pitch);
        void SetGain(float gain);
        void SetFilter(float cutoff, float resonance);
        void SetWaveMix(float blend);
        void SetFxMix(float mix);
        void SetLfoRate(float rate);
        void SetLfoDepth(float depth);
        void SetEnvelope(float attack, float decay);
        void SetModTarget(float target);
        void SetLfoShape(float shape);
        void SetEnvelope(float attack, float decay, float sustain, float release);
        void SetEnvelopeShape(float shape);
        void SetVelocity(float velocity);
        void Process();
        float Generate();

    private:
        Oscillator osc1_, osc2_;
        Svf filter_;
        AdEnv envelope_;
        Oscillator lfo_;

        float pitch_ = 0;
        float gain_ = 0;
        float cutoff_ = 0;
        float resonance_ = 0;
        float wave_mix_ = 0;
        float fx_mix_ = 0;
        float lfo_rate_ = 0;
        float lfo_depth_ = 0;
        float env_attack_ = 0;
        float env_decay_ = 0;
        float env_sustain_ = kEnvSustainLevel; // default sustain level
        float env_release_ = kEnvReleaseTime; // default release time
        float mod_target_ = 0;
        float lfo_shape_ = 0;
        float velocity_ = 0;

        // constants
        static constexpr float kPitchBaseFreq = 110.0f; // A2 pitch base frequency
        static constexpr float kPitchRange = 5.0f; // 5 octaves
        static constexpr float kFilterMinFreq = 100.0f; // minimum filter frequency
        static constexpr float kFilterMaxFreq = 10000.0f; // maximum filter frequency
        static constexpr float kLfoMaxRate = 20.0f; // maximum LFO rate in Hz (0-20Hz)
        static constexpr float kEnvelopeTimeScale = 2.0f; // scale for envelope (0-2 seconds)
        static constexpr float kEnvSustainLevel = 1.0f; // sustain level for envelope
        static constexpr float kEnvReleaseTime = 0.05f; // default release time for envelope (0-0.05 seconds)
        static constexpr float kNumWaveforms = 4.0f; // 4 waveforms for LFO shape (sine, triangle, square, sawtooth)
};