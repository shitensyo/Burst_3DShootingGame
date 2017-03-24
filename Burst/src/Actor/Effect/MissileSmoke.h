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
	//�ړ���
	Vector3	velocity;
	//���Ń^�C�}�[
	float timer;
	//���ł��鎞��
	float endTime;
};
