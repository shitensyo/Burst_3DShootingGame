#pragma once

#include "../Base/Actor.h"
#include "../../World/IWorld.h"

//�v���C���[�i��X�e�[�W�Ŏg�p�j
class AirPlayer : public Actor {
public:
	AirPlayer(IWorld* world, const Vector3& position);

	virtual void OnUpdate(float deltaTime) override;

	virtual void OnDraw() const override;

	virtual void OnCollide(Actor& other,const HitInfo& info) override;

private:
	//�e�̔���
	void ShotBullet(float deltaTime);
	//�ړ�
	void Move(float deltaTime);

private:
	float timer;

	//�}�V���K�����ˊԊu�v���p
	float bulletTimer;
	//�}�V���K�����ˈʒu�̍��E�؂�ւ��p
	int bulletChange;

	//���݂̌���
	float angleX;
	float angleY;
	int angleZ;

	//��]���x���Z�p
	float addAngleZ;

	//�u�[�X�^�[�̉��̉�]
	float boosterAngle;
	//�u�[�X�^�[�̉��̊g�嗦
	Matrix4 boosterScale;
	//�u�[�X�^�[�̉��̈ʒu
	Vector3 boosterPos;
	
	//�����Ԃ��p�@�ŏI�I�Ȉړ��ʂ�ێ�
	Vector3 finalVelocity;

	//�_�b�V�������H
	bool isDash;
	//�_�b�V���o�ߎ���
	float dashTimer;
	//�_�b�V�����̔����������^�C�}�[
	float dashLineTimer;

	float missileTimer;
};