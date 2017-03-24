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
	//ˆÚ“®—Ê
	Vector3 velocity;
	//–Ú•WˆÊ’u
	Vector3 target;

	Matrix4 lookat;
	std::vector<Vector3> positions;
	int positionNum;
	
};