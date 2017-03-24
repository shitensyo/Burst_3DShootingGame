#pragma once

#include "../Base/Actor.h"

class Camera : public Actor {
public:
	//�R���X�g���N�^
	explicit Camera(IWorld* world);
private:
	//�X�V
	virtual void OnUpdate(float deltaTime) override;
	//�`��
	virtual void OnDraw() const override;
};
