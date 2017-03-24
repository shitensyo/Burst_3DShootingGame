#pragma once

#include "../Base/Actor.h"
#include "../../World/IWorld.h"

//�v���C���[�i��X�e�[�W�N���A���j
class AirClearPlayer : public Actor {
public:
	AirClearPlayer(IWorld* world);
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnDraw() const override;
	virtual void OnCollide(Actor& other, const HitInfo& info) override;

private:
	//�u�[�X�^�[�̉���]
	void BoosterRotate(float deltaTime);

private:
	float timer;

	//���݂̌���
	float angleX;
	float angleY;
	int angleZ;

	//�u�[�X�^�[�̉��̉�]
	float boosterAngle;
	Vector3 velocity;
};