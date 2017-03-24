#pragma once

#include "../Base/Actor.h"
#include "../../World/IWorld.h"

//プレイヤー（タイトル画面）
class TitlePlayer : public Actor {
public:
	TitlePlayer(IWorld* world,const Vector3& position = Vector3::Zero);
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnDraw() const override;
	virtual void OnCollide(Actor& other, const HitInfo& info) override;

private:
	float timer;

	//現在の向き
	float angleY;
	float addAngleY;
	float add;
	float sign;

	//ブースターの炎の回転
	float boosterAngle;

	Matrix4 initRotate;

};