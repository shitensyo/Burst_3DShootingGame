#pragma once

#include "../Base/Actor.h"
#include "../../Def.h"

class DashLine : public Actor
{
public:
	DashLine(IWorld* world, const Vector2& position_ = Vector2::WindowCenter, float speed_ = 1000.0f);
private:
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnDraw() const override;

private:
	float timer;
	Vector2 spritePosition;
	float angle;
	Vector2 velocity;
	float alpha;
};
