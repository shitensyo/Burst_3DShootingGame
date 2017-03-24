#pragma once

#include "../Base/Actor.h"
#include "../../Def.h"

//�t�F�[�h���Ȃ���_�ł���e�N�X�`���̕`����s�� ����press space key�\����p
class FadeFlashTexture : public Actor
{
public:
	FadeFlashTexture(IWorld* world, int texID_,const Vector2& position_);
private:
	virtual void OnMessage(EventMessage event, void*) override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnDraw() const override;

private:
	int texID;
	float alpha;
	float timer;
};
