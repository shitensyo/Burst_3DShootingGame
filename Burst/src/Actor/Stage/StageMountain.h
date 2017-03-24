#pragma once

#include "../Base/Actor.h"
#include <vector>

//�X�e�[�W�i�R�j
class StageMountain : public Actor {
public:
	//�R���X�g���N�^
	StageMountain(IWorld* world);
private:
	//�X�V
	virtual void OnUpdate(float deltaTime) override;
	//�`��
	virtual void OnDraw() const override;

private:
	//���W
	std::vector<Vector3> positions;
	//�X�P�[��
	std::vector<Vector3> scales;
	//�ړ���
	Vector3 velocity;
	//�ړ����x
	float speed;
};