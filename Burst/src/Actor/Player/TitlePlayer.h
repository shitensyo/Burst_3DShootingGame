#pragma once

#include "../Base/Actor.h"
#include "../../World/IWorld.h"

//�v���C���[�i�^�C�g����ʁj
class TitlePlayer : public Actor {
public:
	TitlePlayer(IWorld* world,const Vector3& position = Vector3::Zero);
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnDraw() const override;
	virtual void OnCollide(Actor& other, const HitInfo& info) override;

private:
	float timer;

	//���݂̌���
	float angleY;
	float addAngleY;
	float add;
	float sign;

	//�u�[�X�^�[�̉��̉�]
	float boosterAngle;

	Matrix4 initRotate;

};