#pragma once

#include "Actor.h"
#include <unordered_map>
#include "../../ImageEffect/RenderTarget.h"
#include "../../ImageEffect/Effect.h"
#include "../../World/IWorld.h"

enum class ActorGroup;

//アクター一括管理クラス
class ActorManager {
public:
	//コンストラクタ
	ActorManager();
	//初期化
	void Initialize();
	//更新
	void Update(float deltaTime);
	//描画
	void Draw() const;
	//ワールドをセットする
	void SetWorld(IWorld* world_);
	//アクターの追加
	void AddActor(ActorGroup group, const ActorPtr& actor);
	//プレイヤーの追加
	void AddPlayer(const ActorPtr& actor);
	//アクターの検索
	ActorPtr FindActor(const std::string& name);
	//アクターの検索
	ActorPtr FindNormalActor(const std::string& name);
	//アクターの検索
	ActorPtr FindBloomActor(const std::string& name);
	//プレイヤーの取得
	ActorPtr GetPlayer();
	//メッセージ処理
	void HandleMessage(EventMessage message, void* param);
	//親であるグループアクターの取得
	ActorPtr GetGroupActor(const ActorGroup& group);
	//コピー禁止
	ActorManager(const ActorManager& other) = delete;
	ActorManager& operator = (const ActorManager& other) = delete;
private:
	//衝突判定
	void Collide();
private:
	//ワールド
	IWorld*	world;
	//ルートノード
	//通常描画
	Actor normalActor;
	//ブルームをかけた描画
	Actor bloomActor;
	//ＵＩ描画
	Actor uiActor;

	//アクターグループ
	std::unordered_map<ActorGroup, ActorPtr> actors;

	RenderTarget*	normalDraw = nullptr;	//いったんここにすべてを描画し、後でブルームを合成

	Effect*			bloomEffect = nullptr;
	RenderTarget*	bloomBase = nullptr;	//bloomをかけるものはここですべて描画
	RenderTarget*	extract = nullptr;		//baseから輝度の高いところを抽出する
	RenderTarget*	blurV = nullptr;		//画像を縦にぼかす
	RenderTarget*	blurH = nullptr;		//画像を横にぼかす
	RenderTarget*	conbine = nullptr;		//最終的な描画結果

	//プレイヤーだけは参照される回数が多いので保持
	ActorPtr player;
};