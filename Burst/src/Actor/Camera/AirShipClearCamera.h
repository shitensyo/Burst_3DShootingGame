#pragma once

#include "../Base/Actor.h"
#include <vector>

class AirShipClearCamera : public Actor {
public:
	explicit AirShipClearCamera(IWorld* world);
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnDraw() const override;

private:
	float timer;
	//移動量
	Vector3 velocity;
	//目標位置
	Vector3 target;

	Matrix4 lookat;
	std::vector<Vector3> positions;
	int positionNum;
	
};