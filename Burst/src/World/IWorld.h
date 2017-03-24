#pragma once

#include "../Actor/Base/Actor.h"
#include "../Field/FieldPtr.h"
#include <string>

enum class ActorGroup;
enum class EventMessage;

//���[���h���ۃC���^�[�t�F�[�X
class IWorld {
public:
	//���z�f�X�g���N�^
	virtual ~IWorld() {}
	//�A�N�^�[�̒ǉ�
	virtual void AddActor(ActorGroup group, const ActorPtr& actor) = 0;
	//�v���C���[�̒ǉ�
	virtual void AddPlayer(const ActorPtr& actor) = 0;
	//�A�N�^�[�̌���
	virtual ActorPtr FindActor(const std::string& name) = 0;
	//�t�B�[���h�̎擾
	virtual FieldPtr GetField() const = 0;
	//���C�g�̎擾
	virtual ActorPtr GetLight() const = 0;
	//�J�����̎擾
	virtual ActorPtr GetCamera() const = 0;
	//�r���[�s��̍X�V
	virtual void SetLookAt(const Matrix4& lookat_) = 0;
	//�r���[�s��̎擾
	virtual Matrix4 GetLookAt() const = 0;
	//�O���[�v�̐e�A�N�^�[���擾
	virtual ActorPtr GetGroup(const ActorGroup& group) = 0;
	//���b�Z�[�W�̑��M
	virtual void SendMessage(EventMessage message, void* param = nullptr) = 0;
	//�v���C���[�̎擾
	virtual ActorPtr GetPlayer() = 0;
};
