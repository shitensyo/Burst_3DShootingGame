#include "Actor.h"
#include <algorithm>

Actor::Actor(IWorld * world, const std::string & name, const Vector3 & position, const BoundingSphere & body_, int hp_) :
	world(world),
	name(name),
	position(position),
	rotate(Matrix4::Identity),
	body(body_),
	isDead(false),
	isSpheresCollide(false),
	hp(hp_)
{
	bodySpheres.clear();
}


Actor::Actor(IWorld * world, const std::string & name, const Vector3 & position, int hp_) :
	world(world),
	name(name),
	position(position),
	rotate(Matrix4::Identity),
	body(body),
	isDead(false),
	isSpheresCollide(true),
	hp(hp_)
{
}



//コンストラクタ
Actor::Actor(const std::string& name) :
	world(nullptr),
	name(name),
	position(0.0f, 0.0f, 0.0f),
	rotate(Matrix4::Identity),
	isDead(false) {
}


//更新
void Actor::Update(float deltaTime) {
	OnUpdate(deltaTime);
	EachChildren([&](Actor& child) {
		child.Update(deltaTime); 
	});
}

//描画
void Actor::Draw() const {
	OnDraw();
	EachChildren([&](const Actor& child) { child.Draw(); });
}


//衝突判定
void Actor::Collide(Actor& other) {
	HitInfo info = IsCollide(other);
	if (info.isHit) {
		OnCollide(other, info);
		other.OnCollide(*this, info);
	}
	EachChildren([&](Actor& child) { child.Collide(other); });
}


//死亡しているか？
bool Actor::IsDead() const {
	return isDead;
}

//死亡する
void Actor::Dead() {
	isDead = true;
}

//名前を返す
const std::string& Actor::GetName() const {
	return name;
}

//座標を返す
Vector3 Actor::GetPosition() const {
	return position;
}

Vector3 * Actor::GetPositionPtr() const
{
	return const_cast<Vector3*>(&position);
}

//回転行列を返す
Matrix4 Actor::GetRotate() const {
	return rotate;
}

//変換行列(回転と座標)を返す
Matrix4 Actor::GetPose() const {
	Matrix4 result(rotate);
	result.SetPosition(position);
	return result;
}

int Actor::GetHP() const
{
	return hp;
}

void Actor::AddHP(int value)
{
	hp += value;
}

//子の検索
ActorPtr Actor::FindChildren(const std::string& name) {
	return FindChildren(
		[&](const Actor& actor) { return actor.GetName() == name; });
}

//子の検索
ActorPtr Actor::FindChildren(std::function<bool (const Actor&)> fn) {
	const auto i = std::find_if(children_.begin(), children_.end(),
		[&](const ActorPtr& child) { return fn(*child); });
	if (i != children_.end()) {
		return *i;
	}
	for (const auto& child : children_) {
		const auto actor = child->FindChildren(fn);
		if (actor != nullptr) {
			return actor;
		}
	}
	return nullptr;
}

//子の衝突判定
void Actor::CollideChildren(Actor& other) {
	EachChildren(
	[&](Actor& my) {
		other.EachChildren([&](Actor& target) { my.Collide(target); });
	});
}

//子の衝突判定
void Actor::CollideSibling() {
	for (auto i = children_.begin(); i != children_.end(); ++i) {
		std::for_each(std::next(i), children_.end(),
			[&](const ActorPtr& actor) { (*i)->Collide(*actor); });
	}
}

//子の追加
void Actor::AddChild(const ActorPtr& child) {
	children_.push_front(child);
}

//子を巡回
void Actor::EachChildren(std::function<void (Actor&)>  fn) {
	std::for_each(
		children_.begin(), children_.end(),
		[&](const ActorPtr& child) { fn(*child); });
}

//子を巡回 (const版）
void Actor::EachChildren(std::function<void (const Actor&)> fn) const {
	std::for_each(
		children_.begin(), children_.end(),
		[&](const ActorPtr& child) { fn(*child); });
}

//子を削除
void Actor::RemoveChildren() {
	RemoveChildren([](Actor& child) { return child.IsDead(); });
	EachChildren([](Actor& child) { child.RemoveChildren(); });
}

//子を削除
void Actor::RemoveChildren(std::function<bool(Actor&)> fn) {
	children_.remove_if(
		[&](const ActorPtr& child) { return fn(*child); });
}

//子を消去
void Actor::ClearChildren() {
	children_.clear();
}

//メッセージ処理
void Actor::HandleMessage(EventMessage message, void* param) {
	OnMessage(message, param);
	EachChildren([&](Actor& child) { child.HandleMessage(message, param); });
}

void Actor::BodyDraw() const
{
	body.Translate(position).Draw();
}

//メッセージ処理
void Actor::OnMessage(EventMessage, void*) {}

void Actor::AddBodySphere(const BoundingSphere & body_)
{
	bodySpheres.push_back(body_);
}

void Actor::BodySpheresDraw() const
{
	int size = bodySpheres.size();
	for (int i = 0; i < size; i++)
	{
		bodySpheres.at(i).Transform(GetPose()).Draw();
	}
}

void Actor::BodySpheresClear()
{
	bodySpheres.clear();
}

void Actor::OnUpdate(float) {}

void Actor::OnDraw() const {
	BodyDraw(); //判定球のデバッグ表示
}

void Actor::OnCollide(Actor& other, const HitInfo& info){
}

HitInfo Actor::IsCollide(const Actor& other) const {
	//通常の当たり判定
	HitInfo info;

	//通常の当たり判定（球vs球）
	if (!isSpheresCollide)
	{
		info = body.Transform(GetPose()).Intersects(other.body.Transform(other.GetPose()));
		//球体同士の判定
		return info;
	}
	//複雑な当たり判定（複数球vs球）（球vs複数球は用意してない）
	else
	{
		//球体vs複数球体の当たり判定
		int size = bodySpheres.size();
		//ヒットするまでループ
		for (int i = 0; i < size; i++)
		{
			info = bodySpheres.at(i).Transform(GetPose()).Intersects(other.body.Transform(other.GetPose()));
			if (info.isHit)
				return info;
		}
		return info;
	}	
}


