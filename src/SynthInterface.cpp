// src/SynthInterface.cpp
#include "SynthInterface.h"
#include "FilterMode.h"
#include "LFOMode.h"
#include "EnvelopeMode"

using namespace daisy;

void SynthInterface::Init(DaisySeed*seed)
{
    seed_ = seed;

    for (int i = 0; i < kNumPots; i++)
        pots_[i].Init(seed_->GetPin(kPotPins[i]), seed_->AudioCallbackRate());

    mode_btn_.Init(seed_->GetPin(kModeBtnPin), AudioCallbackRate());
    reset_btn_.Init(seed_->GetPin(kResetBtnPin), AudioCallbackRate());

    for (int i = 0; i < kNumModeLeds; ++i)
    {
        mode_leds_[i].Init(seed_->GetPin(kModeLedPins[i]), GPIO::Mode::OUTPUT);
        mode_leds_[i].Write(false);
    }

    modes_.push_back(new FilterMode());
    modes_.push_back(new LFOMode());
    modes_.push_back(new EnvelopeMode());

    for (auto* mode : modes_) 
        mode->Init(seed_);

    EnterSnapMode();
    UpdateModeLeds();
}

void SynthInterface::Process()
{
    mode_btn_.Debounce();
    reset_btn_.Debounce();

    bool mode_pressed = mode_btn_.Pressed();

    if (mode_pressed && !last_mode_btn_state_)
        ToggleMode();

    last_mode_btn_state_=mode_pressed;

    for (int i = 0; i < kNumPots; i++)
    {
        pots_[i].Process();
        float val = pots_[i].Value();

        if (!snapped_[i])
        {
            float diff = fabsf(val - snap_targets_[i]);
            if (diff < kSnapThreshold)
            {
                snapped_[i] = true;
                pot_values_[i] = val;
            }
            else
                pot_values_[i] = val;
        }
    }

    modes_[current_mode_index_]->Process(_pot_values_);
}

void SynthInterface::ApplyToSynth(SynthEngine& synth)
{
    modes_[current_mode_index_]->ApplyToSynth(synth);
}

void SynthInterface::ToggleMode()
{
    current_mode_index_=++current_mode_index_ % modes_.size();
    UpdateModeLeds();
}

void SynthInterface::EnterSnapMode()
{
    for (int i = 0; i < kNumPots; i++)
    {
        snap_targets_[i] = pot_values_[i];
        snapped_[i] = false;
    }
}

void SynthInterface::UpdateModeLeds()
{
    for (int i = 0; i < kNumModeLeds; i++)
    {
        bool state = ((current_mode_index_ >> i) & 0x01);
        mode_leds_[i].Write(state);
    }
}