#pragma once
#include "../core/types.h"
#include <string>

namespace Engine
{
    /// Pure interface for the audio backend.
    /// Mirrors the pattern used by IRenderer: one interface, one Raylib implementation.
    /// No knowledge of Raylib or any other backend lives here.
    class IAudio
    {
    public:
        virtual ~IAudio() = default;

        /// Initialise the audio device. Called once at startup.
        virtual bool Initialize() = 0;

        /// Release the audio device and all loaded sounds.
        virtual void Shutdown() = 0;

        // ------------------------------------------------------------------
        // Resource lifetime (called by ResourceManager — not by game code)
        // ------------------------------------------------------------------

        /// Load a sound file from disk and return an opaque handle.
        virtual AudioClip LoadClip(const char* filepath) = 0;

        /// Release a previously loaded clip from memory.
        virtual void UnloadClip(AudioClip clip) = 0;

        // ------------------------------------------------------------------
        // Global playback
        // ------------------------------------------------------------------

        /// Play a sound with the given parameters. Returns immediately.
        virtual void Play(AudioClip clip, const AudioPlayParams& params = {}) = 0;

        /// Stop all currently playing instances of this clip.
        virtual void Stop(AudioClip clip) = 0;

        virtual bool IsPlaying(AudioClip clip) = 0;

        /// Pause / resume all audio.
        virtual void SetMasterMuted(bool muted) = 0;

        /// Set master volume 0.0 – 1.0.
        virtual void SetMasterVolume(float volume) = 0;

        // ------------------------------------------------------------------
        // Positional audio
        // ------------------------------------------------------------------

        /// Play a sound attenuated by world-space distance.
        /// @param listenerPos  Position of the AudioListenerComponent.
        /// @param sourcePos    Position of the AudioComponent in the world.
        /// @param maxDistance  Distance at which the sound becomes inaudible.
        virtual void PlayPositional(AudioClip clip, const AudioPlayParams& params,
                                    const Vector2f& listenerPos,
                                    const Vector2f& sourcePos,
                                    float           maxDistance) = 0;
    };
}
