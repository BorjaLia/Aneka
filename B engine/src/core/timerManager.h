#pragma once
#include <vector>
#include <functional>

namespace Engine
{
    class TimerManager
    {
    private:
        struct TimerData
        {
            float timeRemaining;
            std::function<void()> callback;
        };

        std::vector<TimerData> activeTimers;
        std::vector<TimerData> pendingTimers; // Guarda los timers creados dentro de otros timers
        bool isUpdating = false;

    public:
        TimerManager() = default;
        ~TimerManager() = default;

        /// @brief Ejecuta una función después de X segundos
        void SetTimeout(float seconds, std::function<void()> callback)
        {
            if (isUpdating)
            {
                // Si estamos actualizando, lo dejamos en la sala de espera para no romper el bucle
                pendingTimers.push_back({ seconds, callback });
            }
            else
            {
                activeTimers.push_back({ seconds, callback });
            }
        }

        void Update(float dt)
        {
            isUpdating = true;

            // Recorremos y disparamos
            for (auto it = activeTimers.begin(); it != activeTimers.end(); )
            {
                it->timeRemaining -= dt;
                if (it->timeRemaining <= 0.0f)
                {
                    if (it->callback) it->callback();
                    it = activeTimers.erase(it); // Lo borramos y avanzamos al siguiente
                }
                else
                {
                    ++it;
                }
            }

            isUpdating = false;

            // Añadimos los que estaban en espera
            if (!pendingTimers.empty())
            {
                activeTimers.insert(activeTimers.end(), pendingTimers.begin(), pendingTimers.end());
                pendingTimers.clear();
            }
        }

        /// @brief Limpia todos los timers (ideal para cuando cambias de nivel)
        void ClearAll()
        {
            activeTimers.clear();
            pendingTimers.clear();
        }
    };
}