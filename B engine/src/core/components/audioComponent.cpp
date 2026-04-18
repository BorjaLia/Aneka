#include "audioComponent.h"
#include "../node.h"
#include "../application.h"
#include "../IAudio.h"

namespace Engine
{
    AudioComponent::AudioComponent(AudioClip clip, bool playOnStart, bool positional, float maxDistance)
        : clip(clip), playOnStart(playOnStart), positional(positional), maxDistance(maxDistance)
    {}

    AudioComponent::~AudioComponent()
    {
        auto& bus = Application::Get().GetEventBus();
        bus.Unsubscribe(AudioPlayEvent::GetStaticType(),   playEventId);
        bus.Unsubscribe(AudioStopEvent::GetStaticType(),   stopEventId);
        bus.Unsubscribe(AudioMuteEvent::GetStaticType(),   muteEventId);
    }

    void AudioComponent::Start()
    {
        auto& bus = Application::Get().GetEventBus();

        // Listen for targeted play requests — only react if the event names this node.
        playEventId = bus.Subscribe<AudioPlayEvent>([this](AudioPlayEvent& e)
        {
            if (e.GetTargetNode() == owner->name)
            {
                params = e.GetParams();
                Play();
            }
        });

        stopEventId = bus.Subscribe<AudioStopEvent>([this](AudioStopEvent& e)
        {
            if (e.GetTargetNode() == owner->name)
                Stop();
        });

        // Global mute events are handled by the IAudio backend directly via Application,
        // but we subscribe here too in case a component wants to react (e.g. show a mute icon).
        muteEventId = bus.Subscribe<AudioMuteEvent>([](AudioMuteEvent&) {});

        if (playOnStart) Play();
    }

    void AudioComponent::Play()
    {
        IAudio* audio = Application::Get().GetAudio();
        if (!audio || clip.id == 0) return;

        if (positional)
        {
            // Find the listener position. If none exists, fall back to global playback.
            Vector2f listenerPos = owner->GetGlobalPosition(); // fallback = no attenuation
            Node* listenerNode = Application::Get().FindAudioListener();
            if (listenerNode) listenerPos = listenerNode->GetGlobalPosition();

            audio->PlayPositional(clip, params, listenerPos, owner->GetGlobalPosition(), maxDistance);
        }
        else
        {
            audio->Play(clip, params);
        }
    }

    void AudioComponent::Stop()
    {
        IAudio* audio = Application::Get().GetAudio();
        if (audio) audio->Stop(clip);
    }
}
