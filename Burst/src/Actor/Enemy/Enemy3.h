#pragma once

#include "../Base/Actor.h"
#include "../../World/IWorld.h"

//�G3�i�w���j
class Enemy3 : public Actor {
public:
	Enemy3(IWorld* world_, const Vector3& position_);
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnDraw() const override;
	virtual void OnCollide(Actor& other,const HitInfo& info) override;

private:
	float timer;

	//�U���ڕW
	ActorPtr player;
	Vector3* target;
	//�ړ�����
	Vector3 velocity;
	//�ړ����x
	float speed;
	//���݂̌���
	float angleX;
	float angleY;
	float angleZ;
	
	float addAngleZ;

	//�v���y����]�p
	float propellerAngle;
};