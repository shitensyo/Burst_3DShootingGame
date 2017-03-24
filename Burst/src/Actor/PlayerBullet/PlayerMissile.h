#pragma once

#include "../Base/Actor.h"
#include "../../World/IWorld.h"
#include <vector>

//�v���C���[�̃~�T�C��
class PlayerMissile : public Actor {
public:
	PlayerMissile(IWorld* world_, const Vector3& position_,const Matrix4& playerRotate_,const Vector3& direction_);
	PlayerMissile(IWorld* world_, const Vector3& position_, const Matrix4& playerRotate_, const Vector3& direction_,float modelScale);

	virtual void OnUpdate(float deltaTime) override;

	virtual void OnDraw() const override;

	virtual void OnCollide(Actor& other,const HitInfo& info) override;

private:
	float timer;
	Matrix4 scale;
	//���݂̈ړ�����
	Vector3 direction;
	//�^�[�Q�b�g�ւ̕���
	Vector3 targetDirection;
	float speed;
	float smokeTimer;
	//���ʂɂ���G�̍��W�������Ɋi�[
	std::vector<Vector3> enemyPositions;
};