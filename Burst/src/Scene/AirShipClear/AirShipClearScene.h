#pragma once

#include "../Base/IScene.h"
#include "../../UI/Score/Score.h"
#include "../../UI/Base/FlashTexture.h"
#include "../../Actor/Base/ActorPtr.h"
#include <memory>
#include "../../UI/Base/NumberTexture.h"
#include "../../UI/Base/FlashTexture.h"
#include "../../ImageEffect/RenderTarget.h"
#include "../../ImageEffect/Effect.h"

class World;
enum class EventMessage;

class AirShipClearScene : public IScene {
public:
	//コンストラクタ
	AirShipClearScene();
	//デストラクタ
	virtual ~AirShipClearScene();
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
	//メッセージ処理
	void HandleMessage(EventMessage message, void* param);


private:
	using WorldPtr = std::shared_ptr<World>;
	//ワールド
	WorldPtr world;
	//終了フラグ
	bool isEnd;
	//タイマー
	float timer;
	float stageClearTimer;
};