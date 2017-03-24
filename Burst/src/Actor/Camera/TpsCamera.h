#pragma once

#include "../Base/Actor.h"

class TpsCamera : public Actor {
public:
	//�R���X�g���N�^
	explicit TpsCamera(IWorld* world, float targetLengthY_ = 10.0f, float targetLengthZ_ = 50.0f);
	TpsCamera(IWorld* world, const Vector3& position);
	//�X�V
	virtual void OnUpdate(float deltaTime) override;
	//�`��
	virtual void OnDraw() const override;

	//�r���[�s����擾����
	Matrix4 GetLookAt();

private:
	//�J�����̈ړ��v�Z
	void Move(
		const Vector3& restPosition,
		float stiffness,
		float friction,
		float mass
	);

private:
	ActorPtr player;
	//�ړ���
	Vector3 velocity;
	//�ڕW�ʒu
	Vector3 target;

	Matrix4 lookat;
	float targetLengthY, targetLengthZ;
};