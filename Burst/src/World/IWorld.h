#pragma once

#include "../Actor/Base/Actor.h"
#include "../Field/FieldPtr.h"
#include <string>

enum class ActorGroup;
enum class EventMessage;

//ワールド抽象インターフェース
class IWorld {
public:
	//仮想デストラクタ
	virtual ~IWorld() {}
	//アクターの追加
	virtual void AddActor(ActorGroup group, const ActorPtr& actor) = 0;
	//プレイヤーの追加
	virtual void AddPlayer(const ActorPtr& actor) = 0;
	//アクターの検索
	virtual ActorPtr FindActor(const std::string& name) = 0;
	//フィールドの取得
	virtual FieldPtr GetField() const = 0;
	//ライトの取得
	virtual ActorPtr GetLight() const = 0;
	//カメラの取得
	virtual ActorPtr GetCamera() const = 0;
	//ビュー行列の更新
	virtual void SetLookAt(const Matrix4& lookat_) = 0;
	//ビュー行列の取得
	virtual Matrix4 GetLookAt() const = 0;
	//グループの親アクターを取得
	virtual ActorPtr GetGroup(const ActorGroup& group) = 0;
	//メッセージの送信
	virtual void SendMessage(EventMessage message, void* param = nullptr) = 0;
	//プレイヤーの取得
	virtual ActorPtr GetPlayer() = 0;
};
