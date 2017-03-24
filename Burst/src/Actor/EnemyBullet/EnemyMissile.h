#pragma once

#include "../Base/Actor.h"
#include "../../World/IWorld.h"

//“G‚P‚Ì’e
class EnemyMissile : public Actor {
public:
	EnemyMissile(IWorld* world_, const Vector3& position_,const Vector3& velocity_);
	EnemyMissile(IWorld* world_, const Vector3& position_, const Vector3& velocity_, float modelScale);
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnDraw() const override;
	virtual void OnCollide(Actor& other,const HitInfo& info) override;

private:
	float timer;
	//ˆÚ“®•ûŒüi³‹K‰»j
	Vector3 velocityNormal;
	//’e‘¬
	float speed;
	float lifeTimer;
	Matrix4 scale;
};