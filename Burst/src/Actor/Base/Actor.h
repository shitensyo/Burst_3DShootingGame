#pragma once

#include "ActorPtr.h"
#include "../../Math/BoundigSphere.h"
#include <gslib.h>
#include <string>
#include <memory>
#include <functional>
#include <forward_list>
#include "../../Math/MathsInclude.h"
#include <vector>

class IWorld;

enum class EventMessage;

class Actor {
public:
	//コンストラクタ
	Actor(IWorld* world, const std::string& name, const Vector3& position, const BoundingSphere& body_, int hp_ = 1);
	//コンストラクタ　複数判定球を使用した当たり判定をする場合はこちら
	Actor(IWorld* world, const std::string& name, const Vector3& position, int hp_ = 1);

	explicit Actor(const std::string& name = "none");
	//仮想デストラクタ
	virtual ~Actor() {}
	//更新
	void Update(float deltaTime);
	//描画
	void Draw() const;
	//衝突処理
	void Collide(Actor& other);
	//死亡しているか？
	bool IsDead() const;
	//死亡する
	void Dead();
	//名前を返す
	const std::string& GetName() const;
	//座標を返す
	Vector3 GetPosition() const;
	//座標を返す
	Vector3* GetPositionPtr() const;
	//回転行列を返す
	Matrix4 GetRotate() const;
	//変換行列を返す
	Matrix4 GetPose() const;
	//体力を返す
	int GetHP() const;
	//体力に加算する
	void AddHP(int value);
	//子の検索
	ActorPtr FindChildren(const std::string& name);
	//子の検索
	ActorPtr FindChildren(std::function<bool (const Actor&)> fn);
	//子同士の衝突
	void CollideChildren(Actor& other);
	//兄弟同士の衝突判定
	void CollideSibling();
	//子の追加
	void AddChild(const ActorPtr& child);
	//子を巡回
	void EachChildren(std::function<void(Actor&)> fn);
	//子を巡回(const版)
	void EachChildren(std::function<void(const Actor&)> fn) const;
	//死亡している子を削除する
	void RemoveChildren(std::function <bool(Actor&)> fn);
	//死亡している子を削除する
	void RemoveChildren();
	//子を消去
	void ClearChildren();
	//子を取得
	std::forward_list<ActorPtr> GetChildren() { return children_; };
	//メッセージ処理
	void HandleMessage(EventMessage message, void* param);
	//判定球を描画
	void BodyDraw() const;
	//複数判定球に球を追加
	void AddBodySphere(const BoundingSphere& body_);
	//複数判定球の描画
	void BodySpheresDraw() const;
	//複数判定球の消去
	void BodySpheresClear();


	//コピー禁止
	Actor(const Actor& other) = delete;
	Actor& operator = (const Actor& other) = delete;


private:
	//メッセージ処理
	virtual void OnMessage(EventMessage message, void* param);
	//更新
	virtual void OnUpdate(float deltaTime);
	//描画
	virtual void OnDraw() const;
	//衝突した時の処理
	virtual void OnCollide(Actor& other,const HitInfo& info);
	//衝突判定
	HitInfo IsCollide(const Actor& other) const;

protected:
	//ワールド
	IWorld*				world;
	//名前
	std::string			name;
	//座標
	Vector3			position;
	//回転
	Matrix4			rotate;
	//衝突判定用球　基本はこちらを使用する
	BoundingSphere		body;
	//複数判定球　複雑な当たり判定を行う場合はこちらを使用する
	std::vector<BoundingSphere> bodySpheres;
	//死亡フラグ
	bool				isDead;
	//複数の球を使用した、複雑な当たり判定を行うか？
	bool isSpheresCollide;
	//体力
	int hp;

private:
	//子アクター
	std::forward_list<ActorPtr> children_;
};
