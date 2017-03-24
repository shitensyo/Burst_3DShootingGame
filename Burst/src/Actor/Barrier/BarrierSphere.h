#pragma once

#include "../Base/Actor.h"

class BarrierSphere : public Actor
{
public:
	BarrierSphere(IWorld* world, const Vector3& position);


	virtual void OnUpdate(float deltaTime) override;
	virtual void OnDraw() const override;
	virtual void OnCollide(Actor& other, const HitInfo& info) override;
};