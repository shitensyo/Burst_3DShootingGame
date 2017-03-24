#pragma once

#include "../Base/Actor.h"
#include "../../World/IWorld.h"

//�󒆐�͂���o�Ă���Ԃ��퓬�@
class RedFighter : public Actor {
public:
	RedFighter(IWorld* world_, const Vector3& position_ , const Matrix4& rotate_ = Matrix4::Identity);
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnDraw() const override;
	virtual void OnCollide(Actor& other, const HitInfo& info) override;

	//��]�v�Z
	void PlayerLookingRotation(float deltaTime);
	//�U��
	void Attack(float deltaTime);

private:
	ActorPtr player;
	float timer;
	Matrix4 initRotate;

	//�ړ�����
	Vector3 velocity;
	//�ړ����x
	float speed;
	int bulletChange;

	Vector3 front;
	//�v���C���[�̕���
	Vector3 toPlayer;
	float dot;

	Matrix4 prevRotate;
	float boosterAngle;

	//���E�����H
	bool isBreakaway;
	float breakawayTimer;
};