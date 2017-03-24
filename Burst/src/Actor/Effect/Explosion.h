#pragma once

#include "../Base/Actor.h"
#include "../../World/IWorld.h"

//爆発
class Explosion : public Actor
{
public:
	//コンストラクタ
	Explosion(IWorld* world_, const Vector3& position_, const Vector3& velocity_);
	//コンストラクタ(火の多さを変更したい場合はこちら)
	Explosion(IWorld* world_, const Vector3& position_, const Vector3& velocity_,int fireNum_);
	//コンストラクタ(細かく設定したい場合はこちら)
	Explosion(IWorld* world_, const Vector3& position_, const Vector3& velocity_, int fireNum_, float lifetime_, float power_, float attenuation_, float scale_);

private:
	virtual void OnUpdate(float deltaTime) override;

private:
	//火の生成個数
	int fireNum;
	//爆発の移動方向
	Vector3 velocity;
	//火の寿命
	float lifetime;
	//爆発の強さ（火が飛ぶ距離）
	float power;
	//減衰率
	float attenuation;
	//スケール
	float scale;
};
