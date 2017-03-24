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

class AirShipStageScene : public IScene {
public:
	//コンストラクタ
	AirShipStageScene();
	//デストラクタ
	virtual ~AirShipStageScene();
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
	//リザルト中の処理
	void Result(float deltaTime);

private:
	using WorldPtr = std::shared_ptr<World>;
	//ワールド
	WorldPtr world;
	//スコア
	Score score;
	//終了フラグ
	bool isEnd;
	//プレイヤー
	ActorPtr player;
	//ボス
	ActorPtr boss;
	//クリア時のタイマー
	float stageClearTimer;

	//リザルトが開始したか？
	bool isResult;
	//プレイヤーが死亡してからの経過時間（リザルトが開始してからの秒数）
	float resultTimer;
	//リザルト用階級プレート移動用タイマー
	float plateTimer;
	////リザルト用撃破数描画用
	//NumberTexture resultNumberTex;
	////press space key描画
	//FlashTexture spaceTexture;

	bool isToTitleWaiting;
	bool isToTitle;

	bool isPause;
	float pauseTimer;

};