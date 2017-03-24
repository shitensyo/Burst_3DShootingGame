#pragma once

#include "../Base/Actor.h"
#include "../../World/IWorld.h"

//�G�P�i�Ԃ��@�́j
class Enemy1 : public Actor {
public:
	Enemy1(IWorld* world_, const Vector3& position_);
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnDraw() const override;
	virtual void OnCollide(Actor& other,const HitInfo& info) override;

private:
	float timer;
	//�ړ�����
	Vector3 velocity;
	//�ړ����x
	float speed;
};