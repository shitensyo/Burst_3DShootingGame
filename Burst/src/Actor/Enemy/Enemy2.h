#pragma once

#include "../Base/Actor.h"
#include "../../World/IWorld.h"

//敵2（白くてかっこいい機体）
class Enemy2 : public Actor {
public:
	Enemy2(IWorld* world_, const Vector3& position_);
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnDraw() const override;
	virtual void OnCollide(Actor& other,const HitInfo& info) override;

private:
	float timer;
	//移動速度
	float speed;
	//現在の向き
	float angleX;
	float angleY;
	float angleZ;
	
	float addAngleZ;
};