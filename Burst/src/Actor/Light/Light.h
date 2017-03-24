#pragma once

#include "../Base/Actor.h"

class Light : public Actor {
public:
	Light(IWorld* world, const Vector3& position);
private:
	virtual void OnDraw() const override;
};
