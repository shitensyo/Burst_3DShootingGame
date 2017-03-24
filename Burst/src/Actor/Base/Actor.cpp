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



//�R���X�g���N�^
Actor::Actor(const std::string& name) :
	world(nullptr),
	name(name),
	position(0.0f, 0.0f, 0.0f),
	rotate(Matrix4::Identity),
	isDead(false) {
}


//�X�V
void Actor::Update(float deltaTime) {
	OnUpdate(deltaTime);
	EachChildren([&](Actor& child) {
		child.Update(deltaTime); 
	});
}

//�`��
void Actor::Draw() const {
	OnDraw();
	EachChildren([&](const Actor& child) { child.Draw(); });
}


//�Փ˔���
void Actor::Collide(Actor& other) {
	HitInfo info = IsCollide(other);
	if (info.isHit) {
		OnCollide(other, info);
		other.OnCollide(*this, info);
	}
	EachChildren([&](Actor& child) { child.Collide(other); });
}


//���S���Ă��邩�H
bool Actor::IsDead() const {
	return isDead;
}

//���S����
void Actor::Dead() {
	isDead = true;
}

//���O��Ԃ�
const std::string& Actor::GetName() const {
	return name;
}

//���W��Ԃ�
Vector3 Actor::GetPosition() const {
	return position;
}

Vector3 * Actor::GetPositionPtr() const
{
	return const_cast<Vector3*>(&position);
}

//��]�s���Ԃ�
Matrix4 Actor::GetRotate() const {
	return rotate;
}

//�ϊ��s��(��]�ƍ��W)��Ԃ�
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

//�q�̌���
ActorPtr Actor::FindChildren(const std::string& name) {
	return FindChildren(
		[&](const Actor& actor) { return actor.GetName() == name; });
}

//�q�̌���
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

//�q�̏Փ˔���
void Actor::CollideChildren(Actor& other) {
	EachChildren(
	[&](Actor& my) {
		other.EachChildren([&](Actor& target) { my.Collide(target); });
	});
}

//�q�̏Փ˔���
void Actor::CollideSibling() {
	for (auto i = children_.begin(); i != children_.end(); ++i) {
		std::for_each(std::next(i), children_.end(),
			[&](const ActorPtr& actor) { (*i)->Collide(*actor); });
	}
}

//�q�̒ǉ�
void Actor::AddChild(const ActorPtr& child) {
	children_.push_front(child);
}

//�q������
void Actor::EachChildren(std::function<void (Actor&)>  fn) {
	std::for_each(
		children_.begin(), children_.end(),
		[&](const ActorPtr& child) { fn(*child); });
}

//�q������ (const�Łj
void Actor::EachChildren(std::function<void (const Actor&)> fn) const {
	std::for_each(
		children_.begin(), children_.end(),
		[&](const ActorPtr& child) { fn(*child); });
}

//�q���폜
void Actor::RemoveChildren() {
	RemoveChildren([](Actor& child) { return child.IsDead(); });
	EachChildren([](Actor& child) { child.RemoveChildren(); });
}

//�q���폜
void Actor::RemoveChildren(std::function<bool(Actor&)> fn) {
	children_.remove_if(
		[&](const ActorPtr& child) { return fn(*child); });
}

//�q������
void Actor::ClearChildren() {
	children_.clear();
}

//���b�Z�[�W����
void Actor::HandleMessage(EventMessage message, void* param) {
	OnMessage(message, param);
	EachChildren([&](Actor& child) { child.HandleMessage(message, param); });
}

void Actor::BodyDraw() const
{
	body.Translate(position).Draw();
}

//���b�Z�[�W����
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
	BodyDraw(); //���苅�̃f�o�b�O�\��
}

void Actor::OnCollide(Actor& other, const HitInfo& info){
}

HitInfo Actor::IsCollide(const Actor& other) const {
	//�ʏ�̓����蔻��
	HitInfo info;

	//�ʏ�̓����蔻��i��vs���j
	if (!isSpheresCollide)
	{
		info = body.Transform(GetPose()).Intersects(other.body.Transform(other.GetPose()));
		//���̓��m�̔���
		return info;
	}
	//���G�ȓ����蔻��i������vs���j�i��vs�������͗p�ӂ��ĂȂ��j
	else
	{
		//����vs�������̂̓����蔻��
		int size = bodySpheres.size();
		//�q�b�g����܂Ń��[�v
		for (int i = 0; i < size; i++)
		{
			info = bodySpheres.at(i).Transform(GetPose()).Intersects(other.body.Transform(other.GetPose()));
			if (info.isHit)
				return info;
		}
		return info;
	}	
}


