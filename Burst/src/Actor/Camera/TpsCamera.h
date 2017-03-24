#pragma once

#include "../Base/Actor.h"

class TpsCamera : public Actor {
public:
	//コンストラクタ
	explicit TpsCamera(IWorld* world, float targetLengthY_ = 10.0f, float targetLengthZ_ = 50.0f);
	TpsCamera(IWorld* world, const Vector3& position);
	//更新
	virtual void OnUpdate(float deltaTime) override;
	//描画
	virtual void OnDraw() const override;

	//ビュー行列を取得する
	Matrix4 GetLookAt();

private:
	//カメラの移動計算
	void Move(
		const Vector3& restPosition,
		float stiffness,
		float friction,
		float mass
	);

private:
	ActorPtr player;
	//移動量
	Vector3 velocity;
	//目標位置
	Vector3 target;

	Matrix4 lookat;
	float targetLengthY, targetLengthZ;
};