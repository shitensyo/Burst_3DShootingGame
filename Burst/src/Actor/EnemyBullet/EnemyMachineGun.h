#pragma once

#include "../Base/Actor.h"
#include "../../World/IWorld.h"

//“G‚P‚Ì’e
class EnemyMachineGun : public Actor {
public:
	EnemyMachineGun(IWorld* world_, const Vector3& position_,const Vector3& velocity_);
	EnemyMachineGun(IWorld* world_, const Vector3& position_, const Vector3& velocity_, float lifeTime_);
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnDraw() const override;
	virtual void OnCollide(Actor& other,const HitInfo& info) override;

private:
	Vector3 velocity;
	float lifeTime;
	float lifeTimer;
};