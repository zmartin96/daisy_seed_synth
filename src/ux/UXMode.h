// src/ux/UXMode.h
#pragma once
#include "DaisySeed.h"

class SynthEngine;

// base class for UX modes
class UXMode 
{
    public:
        virtual ~UXMode() {}

        // call at start
        virtual void Init(daisy::DaisySeed* seed)=0;

        // process current values of all potentiometers
        virtual void Process(const float* pot_values)=0;

        // apply the results to synth engine
        virtual void ApplyToSynth(SynthEngine& synth)=0;

        // name of mode
        virtual const char* Name() = 0;

};