#pragma once

#include "../Base/Actor.h"
#include <vector>

class TitleCamera : public Actor {
public:
	explicit TitleCamera(IWorld* world, const Vector3& position = Vector3::One, const Vector3& target_ = Vector3::Zero);
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnDraw() const override;

private:
	//–Ú•WˆÊ’u
	Vector3 target;

};