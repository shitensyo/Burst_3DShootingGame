#pragma once

#include "../Base/Actor.h"
#include "../../World/IWorld.h"

//空中戦艦ミサイル発射台
class AirShipMissileShooter : public Actor 
{
public:
	AirShipMissileShooter(IWorld* world_, const Vector3& position_, const Matrix4& initRotate_, bool isShot_ = true);
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnDraw() const override;
	virtual void OnCollide(Actor& other,const HitInfo& info) override;

private:
	float timer;

	//初期回転行列
	Matrix4 initRotate;
	//攻撃目標
	ActorPtr player;
	//回転量
	float angleY;
	//1フレーム前の回転量
	Matrix4 prevRotate;
	//現在の回転量
	Matrix4 currentRotate;
	
	bool isShot;
};