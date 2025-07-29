// src/SynthEngine.cpp
#include "SynthEngine.h"

void SynthEngine::Init(float samplerate)
{
    osc1_.Init(samplerate);
    osc2_.Init(samplerate);
    osc1_.SetWaveform(Oscillator::WAVE_SINE);
    osc2_.SetWaveform(Oscillator::WAVE_SAW);

    lfo_.Init(samplerate);
    filter_.Init(samplerate);
    envelope_.Init(samplerate);

    envelope_.SetSustainLevel(1.0f);
    envelope_.SetReleaseTime(0.05f);
}

void SynthEngine::SetPitch(float pitch) 
{ 
    pitch_ = pitch; 
    float freq = 110.0f * powf(2.0f, pitch_ *5.0f);
    osc1_.SetFreq(freq);
    osc2_.SetFreq(freq);
}

void SynthEngine::SetGain(float gain) 
{ 
    gain_ = gain; 
}

void SynthEngine::SetFilter(float cutoff, float resonance)
{
    cutoff_ = cutoff;
    resonance_ = resonance;

    filter_.SetFreq(100.0f + cutoff_ * 10000.0f);
    filter_.SetRes(resonance_);
}

void SynthEngine::SetWaveMix(float blend) 
{ 
    wave_mix_ = blend; 
}

void SynthEngine::SetFxMix(float mix) 
{
    fx_mix_ = mix; 
}

void SynthEngine::SetLfoRate(float rate) 
{ 
    lfo_rate_ = rate; 
    lfo_.SetFreq(rate*kLfoMaxRate) // 0-20Hz
}

void SynthEngine::SetLfoDepth(float depth) 
{ 
    lfo_depth_ = depth; 
}

void SynthEngine::SetEnvelope(float attack, float decay)
{
    env_attack_ = attack;
    env_decay_ = decay;
    envelope_.SetAttackTime(env_attack_ * kEnvelopeTimeScale);
    envelope_.SetDecayTime(env_decay_ * kEnvelopeTimeScale);
}

void SynthEngine::SetEnvelope(float attack, float decay, float sustain, float release)
{
    env_attack_ = attack * kEnvelopeTimeScale;
    env_decay_ = decay * kEnvelopeTimeScale;
    env_sustain_ = sustain* kEnvelopeTimeScale;
    env_release_ = release * kEnvelopeTimeScale;
    envelope_.SetAttackTime(env_attack_);
    envelope_.SetDecayTime(env_decay_);
    envelope_.SetSustainLevel(env_sustain_);
    envelope_.SetReleaseTime(env_release_);
}

void SynthEngine::SetModTarget(float target) 
{ 
    mod_target_ = target; 
}

void SynthEngine::SetLfoShape(float shape) 
{ 
    lfo_shape_ = shape; 
    int idx = (int)(shape * kNumWaveforms); // convert float to int index
    switch (idx) {
        case 0: lfo_.SetWaveform(Oscillator::WAVE_SINE); break;
        case 1: lfo_.SetWaveform(Oscillator::WAVE_TRIANGLE); break;
        case 2: lfo_.SetWaveform(Oscillator::WAVE_SQUARE); break;
        case 3: lfo_.SetWaveform(Oscillator::WAVE_SAW); break;
        default: lfo_.SetWaveform(Oscillator::WAVE_SINE); break; // default to sine
    }
}

void SynthEngine::Process()
{
    lfo_.Process();
    envelope_.Process();
}

float SynthEngine::Generate()
{
    float lfo_value = lfo_.Process();
    float mod = lfo_value * lfo_depth_;
    float osc_val = osc1_.Process() * (1.0f - wave_mix_) + osc2_.Process() * wave_mix_; // blend oscillators
    float filtered = filter_.Process(osc_val + mod);
    float enveloped = envelope_.Process() * filtered;

    switch ((int)mod_target_) {
        case 0: return enveloped * gain_; // no modulation
        case 1: return enveloped * gain_ * (1.0f + mod); // direct
        case 2: return enveloped * gain_ * (1.0f - mod); // inverse
        default: return enveloped * gain_; // default to no modulation
    }

}

void SynthEngine::SetVelocity(float velocity)
{
    velocity_ = velocity;
}

void SynthEngine::SetEnvelopeShape(float shape)
{
    lfo_shape_=shape; // crossfade
}