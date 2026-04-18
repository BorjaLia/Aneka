#pragma once
#include "../src/core/types.h"

namespace Engine::Physics
{
    // =========================================================================
    // CONSTANTES FÍSICAS
    // =========================================================================
    constexpr int MAX_CONTACT_POINTS = 2;

    // =========================================================================
    // ESTRUCTURAS DE DATOS (Caché y Resolución)
    // =========================================================================

    // La estructura AAA para resolver físicas dinámicas
    struct CollisionManifold
    {
        bool isColliding = false;

        Vector2f normal = { 0.0f, 0.0f }; // Dirección del impacto (apunta de B hacia A)
        float depth = 0.0f;               // Profundidad de la penetración (Escalar)

        // Puntos exactos del choque en el mundo (1 para Círculos, 1 o 2 para Cajas)
        Vector2f contactPoints[MAX_CONTACT_POINTS];
        int contactCount = 0;
    };

    // Caja delimitadora simple (Ultra rápida, no rota)
    struct AABB
    {
        Vector2f min;
        Vector2f max;
    };

    // Caja delimitadora orientada (Precisa, rota con el Transform)
    struct OBB
    {
        Vector2f vertices[4];
        Vector2f axisX; // Vector "Adelante/Derecha" local
        Vector2f axisY; // Vector "Arriba" local
    };

    // =========================================================================
    // UTILIDADES (Fábricas de Geometría)
    // =========================================================================

    AABB GetAABB(const Vector2f& center, const Vector2f& size);
    OBB GetOBB(const Vector2f& center, const Vector2f& size, float rotationRadians);

    // =========================================================================
    // EL RADAR (Sistemas de Detección Pura)
    // =========================================================================

    // Sobrecargas específicas y optimizadas (Usadas internamente por el motor)
    CollisionManifold CheckCollision(const Vector2f& posA, float radiusA, const Vector2f& posB, float radiusB);
    CollisionManifold CheckCollision(const Vector2f& circlePos, float radius, const OBB& obb);
    CollisionManifold CheckCollision(const OBB& a, const OBB& b);

    // Despachador Universal (Usado para Triggers, UI, o consultas del usuario)
    // ¡Ojo! Ahora requiere recibir la rotación para construir los OBB dinámicamente.
    CollisionManifold CheckCollision(const Shape& shapeA, const Vector2f& posA, float rotA,
        const Shape& shapeB, const Vector2f& posB, float rotB);
}