#pragma once

#include "../Base/Actor.h"
#include <vector>

//�X�e�[�W�i�R�j
class StageDestroyBase : public Actor {
public:
	//�R���X�g���N�^
	StageDestroyBase(IWorld* world);
private:
	//�X�V
	virtual void OnUpdate(float deltaTime) override;
	//�`��
	virtual void OnDraw() const override;

private:
	//�X�P�[��
	float scale;
};