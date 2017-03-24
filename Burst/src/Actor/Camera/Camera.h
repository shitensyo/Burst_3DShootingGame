#pragma once

#include "../Base/Actor.h"

class Camera : public Actor {
public:
	//コンストラクタ
	explicit Camera(IWorld* world);
private:
	//更新
	virtual void OnUpdate(float deltaTime) override;
	//描画
	virtual void OnDraw() const override;
};
