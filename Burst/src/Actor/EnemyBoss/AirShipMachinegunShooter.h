#pragma once

#include "../Base/Actor.h"
#include "../../World/IWorld.h"

//空中戦艦マシンガン発射台
class AirShipMachinegunShooter : public Actor 
{
public:
	AirShipMachinegunShooter(IWorld* world_, const Vector3& position_, const Matrix4& initRotate_, bool isShot_ = true);
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnDraw() const override;
	virtual void OnCollide(Actor& other,const HitInfo& info) override;

private:
	//回転する
	void Rotation();
private:
	float timer;

	//初期回転行列
	Matrix4 initRotate;
	//発射方向
	Vector3 targetVec;
	//回転量
	float angleY;
	//発射方向、回転量切り替えタイマー
	float rotateTimer;

	bool isShot;
};