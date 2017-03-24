#pragma once

#include "../Base/Actor.h"
#include "../../Def.h"

//フェードイン、アウトを行う(EventMessageを通して行う。最初のフェードインは勝手に行う。)
class Fade : public Actor
{
public:
	Fade(IWorld* world);
private:
	virtual void OnMessage(EventMessage event, void*) override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnDraw() const override;

private:
	//黒から白
	bool isFadeIn;
	bool isFadeOut;
	float alpha;
};
