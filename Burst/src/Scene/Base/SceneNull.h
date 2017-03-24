#pragma once

#include "IScene.h"

class SceneNull : public IScene {
public:
	//�J�n
	virtual void Start() override;
	//�X�V
	virtual void Update(float deltaTime) override;
	//�`��
	virtual void Draw() const override;
	//�I�����Ă��邩�H
	virtual bool IsEnd() const override;
	//���̃V�[����Ԃ�
	virtual Scene Next() const override;
	//�I��
	virtual void End() override;
};
