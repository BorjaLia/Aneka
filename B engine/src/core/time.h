#pragma once

namespace Engine
{
    class Time
    {
    private:
        static float deltaTime;
        static float unscaledDeltaTime;
        static float timeScale;
        static float totalTime;

    public:
        // No queremos instancias de esta clase
        Time() = delete;

        // El que usarán los componentes para moverse (afectado por pausa/cámara lenta)
        static float GetDeltaTime() { return deltaTime * timeScale; }

        // El tiempo real (útil para el contador de FPS o UI que no se pausa)
        static float GetUnscaledDeltaTime() { return unscaledDeltaTime; }

        static float GetTime() { return totalTime; }

        static float GetTimeScale() { return timeScale; }
        static void SetTimeScale(float scale) { timeScale = scale; }

        // Esta función la llamará solo la Application una vez por frame
        static void Update(float rawDeltaTime)
        {
            unscaledDeltaTime = rawDeltaTime;
            deltaTime = rawDeltaTime; // Aquí podrías aplicar el cap de 0.25f si quieres
            totalTime += rawDeltaTime;
        }
    };
}