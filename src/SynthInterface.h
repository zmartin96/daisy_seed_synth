// src/SynthInterface.h
#pragma once

#include <vector>
#include "daisy_seed.h"
#include "UXMode.h"
#include "dev/analog_control.h"
#include "dev/switch.h"
#include "dev/gpio.h"

class SynthInterface 
{
    public:
        void Init(daisy::DaisySeed* seed);
        void Process();
        void ApplyToSynth(SynthEngine& synth);

    private:
        static constexpr int kNumPots = 6;
        static constexpr int kNumModeLeds = 3;
        static constexpr float kSnapThreshold = 0.02f; // threshold for snap mode
        static constexpr dsy_gpio_pin kPotPins[kNumPots] = 
        {
            {daisy::DaisySeed::A0},
            {daisy::DaisySeed::A1},
            {daisy::DaisySeed::A2},
            {daisy::DaisySeed::A3}, 
            {daisy::DaisySeed::A4}, 
            {daisy::DaisySeed::A5}
        };
        static constexpr dsy_gpio_pin kModeBtnPin = {daisy::DaisySeed::D12};
        static constexpr dsy_gpio_pin kResetBtnPin = {daisy::DaisySeed::D13};
        static constexpr dsy_gpio_pin kModeLedPins[kNumModeLeds] = 
        {
            {daisy::DaisySeed::D21},
            {daisy::DaisySeed::D22},
            {daisy::DaisySeed::D23}
        };

        daisy::DaisySeed* seed_ = nullptr;
        daisy::AnalogControl pots_[kNumPots];
        daisy::Switch mode_btn_;
        daisy::Switch reset_btn_;
        daisy::GPIO mode_leds_[kNumModeLeds];

        std::vector<UXMode *> modes_;
        int current_mode_index_ = 0;

        float pot_values_[kNumPots] = {0};
        float snap_targets_[kNumPots]={0};
        bool snapped_[kNumPots] = {false};
        bool last_mode_btn_state_ = false;

        void ToggleMode();
        void EnterSnapMode();
        void UpdateModeLeds();
};