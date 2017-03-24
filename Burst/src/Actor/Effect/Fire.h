#pragma once

#include "../Base/Actor.h"

class Fire : public Actor {
public:
	Fire(IWorld* world_, const Vector3& position_, const Vector3& velocity_);
	Fire(IWorld* world_, const Vector3& position_, const Vector3& velocity_, float power_);
	Fire(IWorld* world_, const Vector3& position_, const Vector3& velocity_, float lifetime_, float power_, float attenuation_, float scale_);
private:
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnDraw() const override;

private:
	//��]
	float rotation;
	//��s�@��������p�����A���ł����̈ړ���
	Vector3 flyVelocity;
	//�ړ���
	Vector3	velocity;
	//���Ń^�C�}�[
	float timer;
	//���Ŏ���
	float lifetime;
	//�����̋���
	float power;
	//������
	float attenuation;
	//�X�P�[��
	float scale;
};
