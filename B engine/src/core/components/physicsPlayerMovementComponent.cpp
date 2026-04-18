#include "physicsPlayerMovementComponent.h"
#include "../Node.h"
#include "RigidBodyComponent.h"
#include "AnimatedSpriteComponent.h"
#include "../Application.h" // Para Input y EventBus global
#include <cmath>

namespace Engine
{
	PhysicsPlayerController::PhysicsPlayerController(float walkSpd, float runSpd, float jumpFrc, PlatformerKeys customKeys)
		: walkSpeed(walkSpd), runSpeed(runSpd), jumpForce(jumpFrc), keys(customKeys)
	{
	}

	void PhysicsPlayerController::Start()
	{
		if (owner)
		{
			rigidBody = owner->GetComponent<RigidBodyComponent>();
			animator = owner->GetComponent<AnimatedSpriteComponent>(); // Lo buscamos (es opcional)
		}
	}

	void PhysicsPlayerController::FixedUpdate(float /*fixedDeltaTime*/)
	{
		auto* input = Application::Get().GetInput();

		if (!input || !rigidBody) return;

		float speed = isRunning ? runSpeed : walkSpeed;
		Vector2f vel = rigidBody->GetVelocity();

		if (input->IsKeyDown(keys.right) && !touchingRightWall) vel.x = speed;
		else if (input->IsKeyDown(keys.left) && !touchingLeftWall) vel.x = -speed;
		else vel.x = 0.0f;

		if (input->IsKeyDown(keys.rotLeft))  rigidBody->AddTorque(-torqueForce);
		else if (input->IsKeyDown(keys.rotRight)) rigidBody->AddTorque(torqueForce);

		if (jumpRequested)
		{
			if (isGrounded)
			{
				ENGINE_LOG("JUMP");
				vel.y = jumpForce;
			}
			jumpRequested = false;
		}

		rigidBody->SetVelocity(vel);

		isGrounded = false;
		touchingLeftWall = false;
		touchingRightWall = false;
	}

	void PhysicsPlayerController::Update(float /*deltaTime*/)
	{
		auto* input = Application::Get().GetInput();

		if (!input) return;

		isRunning = input->IsKeyDown(keys.run);
		if (input->IsKeyPressed(keys.jump)) jumpRequested = true;
	}

	void PhysicsPlayerController::OnCollision(const Physics::CollisionManifold& hit)
	{
		if (hit.normal.y > 0.5f)isGrounded = true;
		if (hit.normal.x > 0.1f)touchingLeftWall = true;
		if (hit.normal.x < -0.1f)touchingRightWall = true;
	}
}