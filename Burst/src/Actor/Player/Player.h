#pragma once

#include "../Base/Actor.h"
#include "../../World/IWorld.h"

//�v���C���[�i�ŏ��ɍ�����v���C���[�̂ЂȌ`�j
class Player : public Actor {
public:
	Player(IWorld* world, const Vector3& position);

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

	
};