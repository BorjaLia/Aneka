#pragma once
#include <cstdint>

namespace Engine
{
    // El tipo de ID ahora es simplemente un número
    using EventType = uint32_t;

    // 1. EL GENERADOR DE IDs AUTOMÁTICO
    class EventTypeGenerator
    {
    private:
        inline static EventType counter = 0;
    public:
        template <typename T>
        static EventType GetID()
        {
            // Esta variable estática se inicializa UNA SOLA VEZ por cada clase T distinta.
            // Le asigna un número único dinámicamente en tiempo de ejecución.
            static const EventType id = ++counter;
            return id;
        }
    };

    // 2. LA CLASE EVENTO PADRE
    class Event
    {
    public:
        virtual ~Event() = default;

        virtual EventType GetType() const = 0;
        virtual const char* GetName() const = 0;

        bool handled = false;
    };

    // 3. LA MAGIA: EL CRTP (Curiously Recurring Template Pattern)
    // Cualquier evento nuevo hereda de aquí pasándose a sí mismo como plantilla.
    // Esto inyecta automáticamente la función GetType() con un ID único.
    template <typename T>
    class EventBase : public Event
    {
    public:
        // Obtiene el ID estático (útil para el EventBus)
        static EventType GetStaticType()
        {
            return EventTypeGenerator::GetID<T>();
        }

        // Cumple el contrato virtual de la clase padre
        EventType GetType() const override
        {
            return GetStaticType();
        }
    };
}