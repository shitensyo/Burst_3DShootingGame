#pragma once

#include "../Base/Actor.h"
#include "../../World/IWorld.h"


//プレイヤーのマシンガン
class PlayerMachineGun : public Actor {
public:
	PlayerMachineGun(IWorld* world_, const Vector3& position_,const Vector3& direction_);
	PlayerMachineGun(IWorld* world_, const Vector3& position_, const Matrix4& playerRotate_, const Vector3& direction_);

	virtual void OnUpdate(float deltaTime) override;

	virtual void OnDraw() const override;

	virtual void OnCollide(Actor& other,const HitInfo& info) override;

private:
	float timer;
	Vector3 direction;

};