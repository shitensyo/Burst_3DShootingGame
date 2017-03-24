#pragma once

#include "IWorld.h"
#include "../Actor/Base/ActorManager.h"
#include "../Field/FieldPtr.h"
#include <functional>

enum class EventMessage;

class World : public IWorld {
public:
	//�R���X�g���N�^
	World();
	//�X�V
	void Update(float deltaTime);
	//�`��
	void Draw() const;
	//���b�Z�[�W����
	void HandleMessage(EventMessage message, void* param);
	//�t�B�[���h�̒ǉ�
	void AddField(const FieldPtr& field_);
	//�J�����̒ǉ�
	void AddCamera(const ActorPtr& camera_);
	//���C�g�̒ǉ�
	void AddLight(const ActorPtr& light_);

	//�A�N�^�[�̒ǉ�
	virtual void AddActor(ActorGroup group, const ActorPtr& actor) override;
	//�v���C���[�̒ǉ�
	virtual void AddPlayer(const ActorPtr& actor) override;
	//�A�N�^�[�̌���
	virtual ActorPtr FindActor(const std::string& name) override;
	//�v���C���[�̎擾
	virtual ActorPtr GetPlayer() override;
	//���b�Z�[�W�̑��M
	virtual void SendMessage(EventMessage message, void* param = nullptr)  override;
	//�C�x���g���X�i�[�̒ǉ�
	void AddEventMessageListener(std::function<void(EventMessage, void*)> listener_);
	//�t�B�[���h�̎擾
	virtual FieldPtr GetField() const override;
	//���C�g�̎擾
	virtual ActorPtr GetLight() const override;
	//�J�����̎擾
	virtual ActorPtr GetCamera() const override;
	//�r���[�s��̍X�V
	virtual void SetLookAt(const Matrix4& lookat_) override;
	//�r���[�s��̎擾
	virtual Matrix4 GetLookAt() const override;
	//�O���[�v�̐e�A�N�^�[���擾
	virtual ActorPtr GetGroup(const ActorGroup& group) override;

	//�R�s�[�֎~
	World(const World& other) = delete;
	World& operator = (const World& other) = delete;
private:
	//�A�N�^�[�}�l�[�W���[
	ActorManager	actors;
	//���C�g
	ActorPtr		light;
	//�J����
	ActorPtr		camera;
	//�t�B�[���h
	FieldPtr		field;
	//�C�x���g���X�i�[
	std::function<void(EventMessage, void*)> listener;

	Matrix4 lookat;
};


