#pragma once

#include "../Base/Actor.h"
#include "../../World/IWorld.h"

//‹ó’†íŠÍ‰Î–òƒRƒ“ƒeƒi
class AirShipContainer : public Actor
{
public:
	AirShipContainer(IWorld* world_,ActorPtr boss_, const Vector3& position_);
	virtual void OnMessage(EventMessage event, void*) override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnDraw() const override;
	virtual void OnCollide(Actor& other, const HitInfo& info) override;

private:
	ActorPtr boss;
	float cursorAngle;
	bool isCursorDraw;
};