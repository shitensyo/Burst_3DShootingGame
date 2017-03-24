#pragma once

#include "../Base/Actor.h"
#include "../../World/IWorld.h"

//�G2�i�����Ă����������@�́j
class Enemy2 : public Actor {
public:
	Enemy2(IWorld* world_, const Vector3& position_);
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnDraw() const override;
	virtual void OnCollide(Actor& other,const HitInfo& info) override;

private:
	float timer;
	//�ړ����x
	float speed;
	//���݂̌���
	float angleX;
	float angleY;
	float angleZ;
	
	float addAngleZ;
};