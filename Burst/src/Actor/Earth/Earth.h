#pragma once

#include "../Base/Actor.h"

class Earth : public Actor
{
public:
	Earth(IWorld* world, const Vector3& position = Vector3::Zero);

	virtual void OnUpdate(float deltaTime) override;
	virtual void OnDraw() const override;
	virtual void OnCollide(Actor& other, const HitInfo& info) override;

private:
	float rotateY;
	float rotateZ;
};