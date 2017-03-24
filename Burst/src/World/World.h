#pragma once

#include "IWorld.h"
#include "../Actor/Base/ActorManager.h"
#include "../Field/FieldPtr.h"
#include <functional>

enum class EventMessage;

class World : public IWorld {
public:
	//コンストラクタ
	World();
	//更新
	void Update(float deltaTime);
	//描画
	void Draw() const;
	//メッセージ処理
	void HandleMessage(EventMessage message, void* param);
	//フィールドの追加
	void AddField(const FieldPtr& field_);
	//カメラの追加
	void AddCamera(const ActorPtr& camera_);
	//ライトの追加
	void AddLight(const ActorPtr& light_);

	//アクターの追加
	virtual void AddActor(ActorGroup group, const ActorPtr& actor) override;
	//プレイヤーの追加
	virtual void AddPlayer(const ActorPtr& actor) override;
	//アクターの検索
	virtual ActorPtr FindActor(const std::string& name) override;
	//プレイヤーの取得
	virtual ActorPtr GetPlayer() override;
	//メッセージの送信
	virtual void SendMessage(EventMessage message, void* param = nullptr)  override;
	//イベントリスナーの追加
	void AddEventMessageListener(std::function<void(EventMessage, void*)> listener_);
	//フィールドの取得
	virtual FieldPtr GetField() const override;
	//ライトの取得
	virtual ActorPtr GetLight() const override;
	//カメラの取得
	virtual ActorPtr GetCamera() const override;
	//ビュー行列の更新
	virtual void SetLookAt(const Matrix4& lookat_) override;
	//ビュー行列の取得
	virtual Matrix4 GetLookAt() const override;
	//グループの親アクターを取得
	virtual ActorPtr GetGroup(const ActorGroup& group) override;

	//コピー禁止
	World(const World& other) = delete;
	World& operator = (const World& other) = delete;
private:
	//アクターマネージャー
	ActorManager	actors;
	//ライト
	ActorPtr		light;
	//カメラ
	ActorPtr		camera;
	//フィールド
	FieldPtr		field;
	//イベントリスナー
	std::function<void(EventMessage, void*)> listener;

	Matrix4 lookat;
};


