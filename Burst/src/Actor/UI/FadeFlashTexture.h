#pragma once

#include "../Base/Actor.h"
#include "../../Def.h"

//フェードしながら点滅するテクスチャの描画を行う 現状press space key表示専用
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
