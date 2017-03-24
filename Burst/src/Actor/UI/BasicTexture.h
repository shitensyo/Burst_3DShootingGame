#pragma once

#include "../Base/Actor.h"
#include "../../Def.h"

//��{�I��2D�e�N�X�`���i�X�v���C�g�j�̕`����s��
class BasicTexture : public Actor
{
public:
	BasicTexture(IWorld* world, int texID_,const Vector2& position_, float alpha_ = 1.0f);
private:
	virtual void OnMessage(EventMessage event, void*) override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnDraw() const override;

private:
	int texID;
	float alpha;
};
