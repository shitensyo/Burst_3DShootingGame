#pragma once

#include "../Base/Actor.h"
#include "../../World/IWorld.h"
#include <vector>

//�G�{�X�󒆐�͌��j���o
class DeadAirShip : public Actor
{
public:
	DeadAirShip(IWorld* world_, const Vector3& position_);
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnDraw() const override;
	virtual void OnCollide(Actor& other, const HitInfo& info) override;

private:
	float timer;
	float bombTime;
	//�ړ�����
	Vector3 velocity;
	//�ړ����x
	float speed;
	//���݂̌���
	float angleX;
	float angleY;
	float angleZ;

	float smokeTimer;
	//�����o�n�_
	std::vector<Vector3> smokePositions;

	float lifeTimer;
};