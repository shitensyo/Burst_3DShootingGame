#pragma once

#include "../Base/Actor.h"
#include "../../Def.h"

class BossHPGauge : public Actor
{
public:
	BossHPGauge(IWorld* world, ActorPtr boss_,const Vector2& position_ = Vector2::Zero);
private:
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnDraw() const override;

private:
	ActorPtr boss;
	int bossHP;
	int maxHP;
	Vector2 spritePosition;
	float angle;
	Vector2 velocity;
	float alpha;
};
