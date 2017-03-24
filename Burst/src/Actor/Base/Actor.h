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
	//�R���X�g���N�^
	Actor(IWorld* world, const std::string& name, const Vector3& position, const BoundingSphere& body_, int hp_ = 1);
	//�R���X�g���N�^�@�������苅���g�p���������蔻�������ꍇ�͂�����
	Actor(IWorld* world, const std::string& name, const Vector3& position, int hp_ = 1);

	explicit Actor(const std::string& name = "none");
	//���z�f�X�g���N�^
	virtual ~Actor() {}
	//�X�V
	void Update(float deltaTime);
	//�`��
	void Draw() const;
	//�Փˏ���
	void Collide(Actor& other);
	//���S���Ă��邩�H
	bool IsDead() const;
	//���S����
	void Dead();
	//���O��Ԃ�
	const std::string& GetName() const;
	//���W��Ԃ�
	Vector3 GetPosition() const;
	//���W��Ԃ�
	Vector3* GetPositionPtr() const;
	//��]�s���Ԃ�
	Matrix4 GetRotate() const;
	//�ϊ��s���Ԃ�
	Matrix4 GetPose() const;
	//�̗͂�Ԃ�
	int GetHP() const;
	//�̗͂ɉ��Z����
	void AddHP(int value);
	//�q�̌���
	ActorPtr FindChildren(const std::string& name);
	//�q�̌���
	ActorPtr FindChildren(std::function<bool (const Actor&)> fn);
	//�q���m�̏Փ�
	void CollideChildren(Actor& other);
	//�Z�퓯�m�̏Փ˔���
	void CollideSibling();
	//�q�̒ǉ�
	void AddChild(const ActorPtr& child);
	//�q������
	void EachChildren(std::function<void(Actor&)> fn);
	//�q������(const��)
	void EachChildren(std::function<void(const Actor&)> fn) const;
	//���S���Ă���q���폜����
	void RemoveChildren(std::function <bool(Actor&)> fn);
	//���S���Ă���q���폜����
	void RemoveChildren();
	//�q������
	void ClearChildren();
	//�q���擾
	std::forward_list<ActorPtr> GetChildren() { return children_; };
	//���b�Z�[�W����
	void HandleMessage(EventMessage message, void* param);
	//���苅��`��
	void BodyDraw() const;
	//�������苅�ɋ���ǉ�
	void AddBodySphere(const BoundingSphere& body_);
	//�������苅�̕`��
	void BodySpheresDraw() const;
	//�������苅�̏���
	void BodySpheresClear();


	//�R�s�[�֎~
	Actor(const Actor& other) = delete;
	Actor& operator = (const Actor& other) = delete;


private:
	//���b�Z�[�W����
	virtual void OnMessage(EventMessage message, void* param);
	//�X�V
	virtual void OnUpdate(float deltaTime);
	//�`��
	virtual void OnDraw() const;
	//�Փ˂������̏���
	virtual void OnCollide(Actor& other,const HitInfo& info);
	//�Փ˔���
	HitInfo IsCollide(const Actor& other) const;

protected:
	//���[���h
	IWorld*				world;
	//���O
	std::string			name;
	//���W
	Vector3			position;
	//��]
	Matrix4			rotate;
	//�Փ˔���p���@��{�͂�������g�p����
	BoundingSphere		body;
	//�������苅�@���G�ȓ����蔻����s���ꍇ�͂�������g�p����
	std::vector<BoundingSphere> bodySpheres;
	//���S�t���O
	bool				isDead;
	//�����̋����g�p�����A���G�ȓ����蔻����s�����H
	bool isSpheresCollide;
	//�̗�
	int hp;

private:
	//�q�A�N�^�[
	std::forward_list<ActorPtr> children_;
};
