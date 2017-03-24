#pragma once

#include "../Base/Actor.h"

class MissileSmoke : public Actor {
public:
	MissileSmoke(IWorld* world_, const Vector3& position_, const Vector3& velocity_);
	MissileSmoke(IWorld* world_, const Vector3& position_, const Vector3& velocity_, float endTime_);
private:
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnDraw() const override;

private:
	float angle;
	//移動量
	Vector3	velocity;
	//消滅タイマー
	float timer;
	//消滅する時間
	float endTime;
};
