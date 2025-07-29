# Daisy Seed Drum Synth

A multi-mode synthesizer and drum machine built for the Daisy Seed platform.

## Features
- Four UX modes: Filter, LFO, Envelope and Drum Machine
- Six potentiometers (A0-A5) used contextually by each mode
- Drum machine mode with four voices (kick, snare, hi-hat, crash)
- Voice select button to edit each drum voice individually
- Trigger buttons to play each drum sound
- Mode button cycles between modes with three LEDs indicating the current mode

## Hardware Connections
| Item | Pin(s) | Purpose |
|------|-------|---------|
| Potentiometers | A0-A5 | Mode-specific parameter control |
| Mode Button | D12 | Cycle active UX mode |
| Reset Button | D13 | Reserved (currently unused) |
| Voice Button | D14 | Select drum voice in Drum Machine mode |
| Trigger Buttons | D15-D18 | Fire Kick, Snare, Hi-hat and Crash |
| Mode LEDs | D21-D23 | Binary display of current mode |

Connect the audio output to the Seed's line out or headphone jack.

## UX Modes
**Filter Mode**
- Pot0: Pitch
- Pot1: Gain
- Pot2: Filter cutoff
- Pot3: Filter resonance
- Pot4: Waveform blend
- Pot5: FX mix

**LFO Mode**
- Pot0: Rate
- Pot1: Depth
- Pot2: Attack
- Pot3: Decay
- Pot4: Modulation target
- Pot5: LFO waveform shape

**Envelope Mode**
- Pot0: Attack
- Pot1: Decay
- Pot2: Sustain
- Pot3: Release
- Pot4: Velocity
- Pot5: Curve

**Drum Machine Mode**
- Pot0: Attack for selected voice
- Pot1: Decay for selected voice
- Pot2: Sustain for selected voice
- Pot3: Release for selected voice
- Pot4: Unused
- Pot5: Unused
- Use the voice button to cycle through the four drum sounds
- Trigger buttons play each voice

## Building
...

## License
MIT