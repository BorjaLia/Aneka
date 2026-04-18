#pragma once
#include <vector>
#include "Physics.h" // Necesitamos ver el OBB y el CollisionManifold

namespace Engine
{
    class Node;
    class ColliderComponent;
    class TriggerAreaComponent;

    class PhysicsSystem
    {
    public:
        PhysicsSystem();
        ~PhysicsSystem() = default;

        // El corazón físico del motor
        void Update(Node* rootScene, float fixedDeltaTime);

        // Control de Calidad (Quality of Life)
        // A mayor número, más sólidas las físicas, pero más costo de CPU. (Box2D usa 8 por defecto)
        void SetSolverIterations(int iterations) { solverIterations = iterations; }
        int GetSolverIterations() const { return solverIterations; }

    private:
        int solverIterations = 8;

        // ==========================================
        // CACHÉ DE MEMORIA (Data-Oriented Design)
        // ==========================================
        // Se mantienen vivos entre frames para reusar la capacidad de memoria reservada
        std::vector<ColliderComponent*> activeColliders;
        std::vector<TriggerAreaComponent*> activeTriggers;
        std::vector<Physics::OBB> obbCache;

        // ==========================================
        // PASOS DEL PIPELINE FÍSICO
        // ==========================================

        // Llena las listas y hornea los datos geométricos del usuario a OBBs puros
        void PrePass(Node* rootScene);

        // El doble bucle que evalúa colisiones y aplica el Solucionador Iterativo
        void SolveCollisions();

        // Evaluación separada para las zonas intangibles
        void DetectTriggers();
    };
}