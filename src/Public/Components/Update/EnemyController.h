#pragma once

#include <Components/Update/IUpdateComponent.h>
#include <Components/Interfaces/ICollider.h>

#include <Objects/Object.h>
#include <Core/Logger.h>

class EnemyController : public IUpdateComponent, public ICollider {
private:
	void Update(float deltaTime) override {

	}

	virtual void OnCollisionEnter(ICollider* other) override {
		Logger::Log("Collision with " + other->GetOwner()->Name);
		if (other->GetOwner()->Name == "Bullet") {
			_owner->Enabled = false;
		}
	};

};

