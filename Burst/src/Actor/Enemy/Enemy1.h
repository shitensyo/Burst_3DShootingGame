#pragma once

#include "../Base/Actor.h"
#include "../../World/IWorld.h"

//敵１（赤い機体）
class Enemy1 : public Actor {
public:
	Enemy1(IWorld* world_, const Vector3& position_);
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnDraw() const override;
	virtual void OnCollide(Actor& other,const HitInfo& info) override;

private:
	float timer;
	//移動方向
	Vector3 velocity;
	//移動速度
	float speed;
};