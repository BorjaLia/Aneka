#pragma once
#include "../../core/IAudio.h"
#include <unordered_map>

namespace Engine
{
    /// Raylib-backed audio implementation.
    /// This is the ONLY file in the audio system that may include raylib headers.
    class RaylibAudio : public IAudio
    {
    public:
        bool Initialize() override;
        void Shutdown()   override;

        AudioClip LoadClip(const char* filepath)  override;
        void      UnloadClip(AudioClip clip)       override;

        void Play(AudioClip clip, const AudioPlayParams& params = {}) override;
        void Stop(AudioClip clip)                                      override;

        void SetMasterMuted(bool muted)      override;
        void SetMasterVolume(float volume)   override;

        void PlayPositional(AudioClip clip, const AudioPlayParams& params,
                            const Vector2f& listenerPos,
                            const Vector2f& sourcePos,
                            float           maxDistance) override;

    private:
        // Maps our opaque AudioClip id → the raw Raylib Sound struct (stored by id)
        // We store only the id and reconstruct the Sound when needed.
        struct SoundEntry { unsigned int raylibId = 0; };
        std::unordered_map<unsigned int, SoundEntry> loadedSounds;
        unsigned int nextId = 1;

        bool masterMuted  = false;
        float masterVolume = 1.0f;
    };
}
