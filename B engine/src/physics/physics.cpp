#include "Physics.h"
#include <cmath>
#include <algorithm>
#include <limits>

namespace Engine::Physics
{
    // =========================================================================
    // UTILIDADES GEOMÉTRICAS (Fábricas)
    // =========================================================================

    AABB GetAABB(const Vector2f& center, const Vector2f& size)
    {
        Vector2f halfSize = size * 0.5f;
        return { center - halfSize, center + halfSize };
    }

    OBB GetOBB(const Vector2f& center, const Vector2f& size, float rotationRadians)
    {
        OBB obb;

        // 1. Ejes direccionales locales
        float c = std::cos(rotationRadians);
        float s = std::sin(rotationRadians);
        obb.axisX = { c, s };
        obb.axisY = { -s, c };

        // 2. Vértices (Calculados desde el centro usando los ejes)
        float hw = size.x * 0.5f;
        float hh = size.y * 0.5f;

        Vector2f local[4] = {
            { -hw, -hh }, // Abajo-Izquierda
            {  hw, -hh }, // Abajo-Derecha
            {  hw,  hh }, // Arriba-Derecha
            { -hw,  hh }  // Arriba-Izquierda
        };

        for (int i = 0; i < 4; ++i)
        {
            obb.vertices[i] = center + (obb.axisX * local[i].x) + (obb.axisY * local[i].y);
        }

        return obb;
    }

    // Estructura interna para el Teorema de Ejes Separadores (SAT)
    struct Projection { float min, max; };

    static Projection GetProjection(const OBB& obb, const Vector2f& axis)
    {
        float min = axis.Dot(obb.vertices[0]);
        float max = min;
        for (int i = 1; i < 4; ++i)
        {
            float proj = axis.Dot(obb.vertices[i]);
            if (proj < min) min = proj;
            if (proj > max) max = proj;
        }
        return { min, max };
    }

    // =========================================================================
    // FUNCIONES NÚCLEO DE COLISIÓN (El Radar)
    // =========================================================================

    CollisionManifold CheckCollision(const Vector2f& posA, float radiusA, const Vector2f& posB, float radiusB)
    {
        CollisionManifold manifold;
        Vector2f dir = posA - posB;
        float distSq = dir.MagnitudeSquared();
        float radiusSum = radiusA + radiusB;

        if (distSq < (radiusSum * radiusSum))
        {
            manifold.isColliding = true;
            manifold.contactCount = 1;

            float dist = std::sqrt(distSq);
            if (dist != 0.0f)
            {
                manifold.depth = radiusSum - dist;
                manifold.normal = dir * (1.0f / dist); // Normalizada
                manifold.contactPoints[0] = posB + (manifold.normal * radiusB);
            }
            else
            {
                // Centros idénticos
                manifold.depth = radiusSum;
                manifold.normal = { 1.0f, 0.0f };
                manifold.contactPoints[0] = posA;
            }
        }
        return manifold;
    }

    CollisionManifold CheckCollision(const Vector2f& circlePos, float radius, const OBB& obb)
    {
        CollisionManifold manifold;

        // Promedio de los 4 vértices para el centro del OBB
        Vector2f obbCenter = (obb.vertices[0] + obb.vertices[1] + obb.vertices[2] + obb.vertices[3]) * 0.25f;
        Vector2f dir = circlePos - obbCenter;

        // Distancia del centro a los bordes usando los ejes proyectados
        float halfWidth = std::abs((obb.vertices[0] - obbCenter).Dot(obb.axisX));
        float halfHeight = std::abs((obb.vertices[0] - obbCenter).Dot(obb.axisY));

        float distX = std::max(-halfWidth, std::min(dir.Dot(obb.axisX), halfWidth));
        float distY = std::max(-halfHeight, std::min(dir.Dot(obb.axisY), halfHeight));

        Vector2f closestPoint = obbCenter + (obb.axisX * distX) + (obb.axisY * distY);
        Vector2f diff = circlePos - closestPoint;
        float distSq = diff.MagnitudeSquared();

        if (distSq < (radius * radius))
        {
            manifold.isColliding = true;
            manifold.contactCount = 1;
            manifold.contactPoints[0] = closestPoint;

            float dist = std::sqrt(distSq);
            if (dist != 0.0f)
            {
                manifold.depth = radius - dist;
                manifold.normal = diff * (1.0f / dist); // Apunta de B (Caja) hacia A (Círculo)
            }
            else
            {
                manifold.depth = radius;
                manifold.normal = obb.axisY; // Empuje por defecto
            }
        }
        return manifold;
    }

    CollisionManifold CheckCollision(const OBB& a, const OBB& b)
    {
        CollisionManifold manifold;
        float minDepth = std::numeric_limits<float>::max();
        Vector2f bestNormal;

        // === STEP 1: SAT — find the axis of minimum penetration ===
        // We test all 4 separating axes (2 from each box).
        // If any axis shows a gap, they're not colliding.
        Vector2f axes[4] = { a.axisX, a.axisY, b.axisX, b.axisY };

        for (int i = 0; i < 4; ++i)
        {
            Projection pA = GetProjection(a, axes[i]);
            Projection pB = GetProjection(b, axes[i]);

            if (pA.max < pB.min || pB.max < pA.min) return manifold; // Gap found — no collision

            float depth = std::min(pA.max, pB.max) - std::max(pA.min, pB.min);
            if (depth < minDepth)
            {
                minDepth = depth;
                bestNormal = axes[i];
            }
        }

        // === STEP 2: Orient the normal from B toward A ===
        Vector2f centerA = (a.vertices[0] + a.vertices[1] + a.vertices[2] + a.vertices[3]) * 0.25f;
        Vector2f centerB = (b.vertices[0] + b.vertices[1] + b.vertices[2] + b.vertices[3]) * 0.25f;

        if (bestNormal.Dot(centerA - centerB) < 0.0f)
            bestNormal = -bestNormal;

        manifold.isColliding = true;
        manifold.depth = minDepth;
        manifold.normal = bestNormal;

        // === STEP 3: Reference Face Clipping (Sutherland-Hodgman style) ===
        // Goal: find the 1 or 2 world-space points where the boxes actually touch.
        //
        // "Reference face" = the face on box A most aligned with the collision normal.
        // "Incident face"  = the face on box B most aligned with -normal (the one penetrating).
        //
        // We find the incident face's two vertices, then clip them against the
        // side planes of the reference face. What survives clipping and is below
        // the reference face's front plane becomes our contact points.

        // --- Find the reference face on A (most aligned with bestNormal) ---
        // Each box has 2 face pairs (axisX faces and axisY faces).
        // We pick whichever axis is most parallel to the normal.
        Vector2f refFaceNormal;
        Vector2f refFaceV0, refFaceV1; // The two vertices of the reference face

        float dotX = std::abs(bestNormal.Dot(a.axisX));
        float dotY = std::abs(bestNormal.Dot(a.axisY));

        if (dotX >= dotY)
        {
            // The reference face is perpendicular to axisX
            if (bestNormal.Dot(a.axisX) > 0)
            {
                // +X face: vertices 1 and 2
                refFaceV0 = a.vertices[1];
                refFaceV1 = a.vertices[2];
            }
            else
            {
                // -X face: vertices 0 and 3
                refFaceV0 = a.vertices[0];
                refFaceV1 = a.vertices[3];
            }
            refFaceNormal = a.axisX;
        }
        else
        {
            // The reference face is perpendicular to axisY
            if (bestNormal.Dot(a.axisY) > 0)
            {
                // +Y face: vertices 2 and 3
                refFaceV0 = a.vertices[2];
                refFaceV1 = a.vertices[3];
            }
            else
            {
                // -Y face: vertices 0 and 1
                refFaceV0 = a.vertices[0];
                refFaceV1 = a.vertices[1];
            }
            refFaceNormal = a.axisY;
        }

        // --- Find the incident face on B (most opposed to bestNormal) ---
        Vector2f incFaceV0, incFaceV1;

        float dotBX = std::abs(bestNormal.Dot(b.axisX));
        float dotBY = std::abs(bestNormal.Dot(b.axisY));

        if (dotBX >= dotBY)
        {
            if (bestNormal.Dot(b.axisX) > 0)
            {
                incFaceV0 = b.vertices[0];
                incFaceV1 = b.vertices[3];
            }
            else
            {
                incFaceV0 = b.vertices[1];
                incFaceV1 = b.vertices[2];
            }
        }
        else
        {
            if (bestNormal.Dot(b.axisY) > 0)
            {
                incFaceV0 = b.vertices[0];
                incFaceV1 = b.vertices[1];
            }
            else
            {
                incFaceV0 = b.vertices[2];
                incFaceV1 = b.vertices[3];
            }
        }

        // --- Clip the incident edge against the side planes of the reference face ---
        // The reference face has two side planes, perpendicular to its edge direction.
        Vector2f refEdge = refFaceV1 - refFaceV0;
        refEdge.Normalize();

        // Lambda to clip a segment against a half-plane defined by a point and direction
        auto Clip = [](Vector2f v0, Vector2f v1, Vector2f planeNormal, float planeOffset,
            Vector2f& out0, Vector2f& out1) -> int
            {
                float d0 = planeNormal.Dot(v0) - planeOffset;
                float d1 = planeNormal.Dot(v1) - planeOffset;

                int count = 0;
                if (d0 >= 0.0f) { if (count == 0) out0 = v0; else out1 = v0; count++; }
                if (d1 >= 0.0f) { if (count == 0) out0 = v1; else out1 = v1; count++; }

                // One vertex inside, one outside: compute the intersection point
                if (d0 * d1 < 0.0f)
                {
                    float t = d0 / (d0 - d1);
                    Vector2f intersection = v0 + (v1 - v0) * t;
                    if (count == 0) out0 = intersection; else out1 = intersection;
                    count++;
                }
                return count;
            };

        // Clip against side plane 1 (at refFaceV0, normal = -refEdge)
        Vector2f cp0, cp1;
        int count = Clip(incFaceV0, incFaceV1, -refEdge, -refEdge.Dot(refFaceV0), cp0, cp1);
        if (count < 2) { manifold.contactPoints[0] = centerA - (bestNormal * (minDepth * 0.5f)); manifold.contactCount = 1; return manifold; }

        // Clip against side plane 2 (at refFaceV1, normal = +refEdge)
        Vector2f cp2, cp3;
        count = Clip(cp0, cp1, refEdge, refEdge.Dot(refFaceV1), cp2, cp3);
        if (count < 2) { manifold.contactPoints[0] = centerA - (bestNormal * (minDepth * 0.5f)); manifold.contactCount = 1; return manifold; }

        // --- Keep only points that are on or behind the reference face ---
        // (They must have penetrated past the face to be real contact points)
        float refFaceDot = bestNormal.Dot(refFaceV0);
        manifold.contactCount = 0;

        auto TryAddContact = [&](const Vector2f& pt)
            {
                if (manifold.contactCount >= MAX_CONTACT_POINTS) return;
                if (bestNormal.Dot(pt) <= refFaceDot)
                {
                    manifold.contactPoints[manifold.contactCount++] = pt;
                }
            };

        TryAddContact(cp2);
        TryAddContact(cp3);

        // Fallback: if clipping produced nothing, use the center-based estimate
        if (manifold.contactCount == 0)
        {
            manifold.contactPoints[0] = centerA - (bestNormal * (minDepth * 0.5f));
            manifold.contactCount = 1;
        }

        return manifold;
    }

    // =========================================================================
    // DESPACHADOR MAESTRO (La "Sala de Enrutamiento" para el Sistema ECS)
    // =========================================================================

    CollisionManifold CheckCollision(const Shape& shapeA, const Vector2f& posA, float rotA,
        const Shape& shapeB, const Vector2f& posB, float rotB)
    {
        // CASO: Círculo vs Círculo
        if (std::holds_alternative<CircleShape>(shapeA) && std::holds_alternative<CircleShape>(shapeB))
        {
            return CheckCollision(posA, std::get<CircleShape>(shapeA).radius,
                posB, std::get<CircleShape>(shapeB).radius);
        }

        // CASO: Rectángulo vs Rectángulo (Convertimos ambos a OBB)
        if (std::holds_alternative<RectangleShape>(shapeA) && std::holds_alternative<RectangleShape>(shapeB))
        {
            OBB obbA = GetOBB(posA, std::get<RectangleShape>(shapeA).size, rotA);
            OBB obbB = GetOBB(posB, std::get<RectangleShape>(shapeB).size, rotB);
            return CheckCollision(obbA, obbB);
        }

        // CASO: Círculo (A) vs Rectángulo (B)
        if (std::holds_alternative<CircleShape>(shapeA) && std::holds_alternative<RectangleShape>(shapeB))
        {
            OBB obbB = GetOBB(posB, std::get<RectangleShape>(shapeB).size, rotB);
            return CheckCollision(posA, std::get<CircleShape>(shapeA).radius, obbB);
        }

        // CASO: Rectángulo (A) vs Círculo (B)
        if (std::holds_alternative<RectangleShape>(shapeA) && std::holds_alternative<CircleShape>(shapeB))
        {
            OBB obbA = GetOBB(posA, std::get<RectangleShape>(shapeA).size, rotA);

            // Evaluamos invertido (Círculo vs OBB)
            CollisionManifold m = CheckCollision(posB, std::get<CircleShape>(shapeB).radius, obbA);

            // Invertimos la normal para mantener la regla "apunta desde B hacia A"
            if (m.isColliding) m.normal = -m.normal;

            return m;
        }

        // Retorno vacío de seguridad
        return CollisionManifold{};
    }
}