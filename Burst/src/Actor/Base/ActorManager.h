#pragma once

#include "Actor.h"
#include <unordered_map>
#include "../../ImageEffect/RenderTarget.h"
#include "../../ImageEffect/Effect.h"
#include "../../World/IWorld.h"

enum class ActorGroup;

//�A�N�^�[�ꊇ�Ǘ��N���X
class ActorManager {
public:
	//�R���X�g���N�^
	ActorManager();
	//������
	void Initialize();
	//�X�V
	void Update(float deltaTime);
	//�`��
	void Draw() const;
	//���[���h���Z�b�g����
	void SetWorld(IWorld* world_);
	//�A�N�^�[�̒ǉ�
	void AddActor(ActorGroup group, const ActorPtr& actor);
	//�v���C���[�̒ǉ�
	void AddPlayer(const ActorPtr& actor);
	//�A�N�^�[�̌���
	ActorPtr FindActor(const std::string& name);
	//�A�N�^�[�̌���
	ActorPtr FindNormalActor(const std::string& name);
	//�A�N�^�[�̌���
	ActorPtr FindBloomActor(const std::string& name);
	//�v���C���[�̎擾
	ActorPtr GetPlayer();
	//���b�Z�[�W����
	void HandleMessage(EventMessage message, void* param);
	//�e�ł���O���[�v�A�N�^�[�̎擾
	ActorPtr GetGroupActor(const ActorGroup& group);
	//�R�s�[�֎~
	ActorManager(const ActorManager& other) = delete;
	ActorManager& operator = (const ActorManager& other) = delete;
private:
	//�Փ˔���
	void Collide();
private:
	//���[���h
	IWorld*	world;
	//���[�g�m�[�h
	//�ʏ�`��
	Actor normalActor;
	//�u���[�����������`��
	Actor bloomActor;
	//�t�h�`��
	Actor uiActor;

	//�A�N�^�[�O���[�v
	std::unordered_map<ActorGroup, ActorPtr> actors;

	RenderTarget*	normalDraw = nullptr;	//�������񂱂��ɂ��ׂĂ�`�悵�A��Ńu���[��������

	Effect*			bloomEffect = nullptr;
	RenderTarget*	bloomBase = nullptr;	//bloom����������̂͂����ł��ׂĕ`��
	RenderTarget*	extract = nullptr;		//base����P�x�̍����Ƃ���𒊏o����
	RenderTarget*	blurV = nullptr;		//�摜���c�ɂڂ���
	RenderTarget*	blurH = nullptr;		//�摜�����ɂڂ���
	RenderTarget*	conbine = nullptr;		//�ŏI�I�ȕ`�挋��

	//�v���C���[�����͎Q�Ƃ����񐔂������̂ŕێ�
	ActorPtr player;
};