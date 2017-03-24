#pragma once

#include "../Base/Actor.h"

//弾がバリアにはじかれたときのエフェクト
class Reflect : public Actor 
{
public:
	Reflect(IWorld* world_, const Vector3& position_,float finalScale_);
private:
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnDraw() const override;

private:
	//消滅タイマー
	float timer;
	float scale;
	//最終的なスケール
	float finalScale;
};