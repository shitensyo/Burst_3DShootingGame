#pragma once

#include "../Base/Actor.h"

class Fire : public Actor {
public:
	Fire(IWorld* world_, const Vector3& position_, const Vector3& velocity_);
	Fire(IWorld* world_, const Vector3& position_, const Vector3& velocity_, float power_);
	Fire(IWorld* world_, const Vector3& position_, const Vector3& velocity_, float lifetime_, float power_, float attenuation_, float scale_);
private:
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnDraw() const override;

private:
	//回転
	float rotation;
	//飛行機から引き継いだ、飛んでた時の移動量
	Vector3 flyVelocity;
	//移動量
	Vector3	velocity;
	//消滅タイマー
	float timer;
	//消滅時間
	float lifetime;
	//爆発の強さ
	float power;
	//減衰率
	float attenuation;
	//スケール
	float scale;
};
