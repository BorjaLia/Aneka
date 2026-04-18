#pragma once
#include "Event.h"
#include <functional>
#include <map>
#include <cstdint>

namespace Engine
{
    using EventCallback = std::function<void(Event&)>;
    using EventListenerID = uint32_t;

    class EventBus
    {
    private:
        std::map<EventType, std::map<EventListenerID, EventCallback>> subscribers;
        EventListenerID nextId = 0;

    public:
        // ------------------------------------------------------------------
        // MÉTODO 1: El original (Bajo nivel)
        // ------------------------------------------------------------------
        EventListenerID Subscribe(EventType type, EventCallback callback)
        {
            EventListenerID id = nextId++;
            subscribers[type][id] = callback;
            return id;
        }

        // ------------------------------------------------------------------
        // MÉTODO 2: ¡LA NUEVA SOBRECARGA MÁGICA! (Alto nivel)
        // ------------------------------------------------------------------
        // Ya no le pasas el ID. Automáticamente deduce qué evento quieres 
        // escuchar en base al tipo de la función lambda que le pases.
        template <typename T>
        EventListenerID Subscribe(std::function<void(T&)> callback)
        {
            // Envolvemos tu callback tipado en un callback genérico del motor
            auto wrapper = [callback](Event& e)
                {
                    // Aquí el motor hace el cast por ti de forma segura
                    callback(static_cast<T&>(e));
                };

            // Nos suscribimos usando el ID automático de este evento
            return Subscribe(T::GetStaticType(), wrapper);
        }

        void Unsubscribe(EventType type, EventListenerID id)
        {
            auto it = subscribers.find(type);
            if (it != subscribers.end())
            {
                it->second.erase(id);
            }
        }

        void Publish(Event& event)
        {
            EventType type = event.GetType();
            auto it = subscribers.find(type);
            if (it != subscribers.end())
            {
                for (auto& pair : it->second)
                {
                    if (event.handled) break;
                    pair.second(event);
                }
            }
        }
    };
}