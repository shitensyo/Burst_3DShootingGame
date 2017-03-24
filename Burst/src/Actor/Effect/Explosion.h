#pragma once

#include "../Base/Actor.h"
#include "../../World/IWorld.h"

//����
class Explosion : public Actor
{
public:
	//�R���X�g���N�^
	Explosion(IWorld* world_, const Vector3& position_, const Vector3& velocity_);
	//�R���X�g���N�^(�΂̑�����ύX�������ꍇ�͂�����)
	Explosion(IWorld* world_, const Vector3& position_, const Vector3& velocity_,int fireNum_);
	//�R���X�g���N�^(�ׂ����ݒ肵�����ꍇ�͂�����)
	Explosion(IWorld* world_, const Vector3& position_, const Vector3& velocity_, int fireNum_, float lifetime_, float power_, float attenuation_, float scale_);

private:
	virtual void OnUpdate(float deltaTime) override;

private:
	//�΂̐�����
	int fireNum;
	//�����̈ړ�����
	Vector3 velocity;
	//�΂̎���
	float lifetime;
	//�����̋����i�΂���ԋ����j
	float power;
	//������
	float attenuation;
	//�X�P�[��
	float scale;
};
