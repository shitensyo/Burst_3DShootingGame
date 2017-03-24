#pragma once

#include "../Base/Actor.h"
#include "../../Def.h"

//基本的な2Dテクスチャ（スプライト）の描画を行う
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
