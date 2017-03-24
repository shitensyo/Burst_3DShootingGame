#pragma once

#include <GSgame.h>
#include "../Scene/Base/SceneManager.h"

class Game : public gslib::Game {
public:
	//コンストラクタ
	Game();
private:
	//開始
	virtual void start() override;
	//更新
	virtual void update(float deltaFrame)  override;
	//描画
	virtual void draw() override;
	//描画
	virtual void end() override;
private:
	//シーンマネージャ
	SceneManager	sceneManager;
};
