#pragma once

#include "../Base/Actor.h"

class BarrierGenerator : public Actor
{
public:
	BarrierGenerator(IWorld* world, const Vector3& position, const Vector3& shipPos = Vector3::Zero);

	virtual void OnMessage(EventMessage event, void*) override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnDraw() const override;
	virtual void OnCollide(Actor& other, const HitInfo& info) override;

private:
	float timer;
	
	float angleY;
	float smokeTimer;

	Matrix4 poleMat;
	float cursorAngle;

	bool isCursorDraw;
};