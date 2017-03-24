#pragma once

#include "IScene.h"

class SceneNull : public IScene {
public:
	//開始
	virtual void Start() override;
	//更新
	virtual void Update(float deltaTime) override;
	//描画
	virtual void Draw() const override;
	//終了しているか？
	virtual bool IsEnd() const override;
	//次のシーンを返す
	virtual Scene Next() const override;
	//終了
	virtual void End() override;
};
