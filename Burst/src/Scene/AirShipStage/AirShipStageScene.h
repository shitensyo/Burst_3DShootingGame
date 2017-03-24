#pragma once

#include "../Base/IScene.h"
#include "../../UI/Score/Score.h"
#include "../../UI/Base/FlashTexture.h"
#include "../../Actor/Base/ActorPtr.h"
#include <memory>
#include "../../UI/Base/NumberTexture.h"
#include "../../UI/Base/FlashTexture.h"
#include "../../ImageEffect/RenderTarget.h"
#include "../../ImageEffect/Effect.h"

class World;
enum class EventMessage;

class AirShipStageScene : public IScene {
public:
	//�R���X�g���N�^
	AirShipStageScene();
	//�f�X�g���N�^
	virtual ~AirShipStageScene();
	//�J�n
	virtual void Start() override;
	//�X�V
	virtual void Update(float deltaTime) override;
	//�`��
	virtual void Draw() const override;
	//�I�����Ă��邩�H
	virtual bool IsEnd() const override;
	//���̃V�[����Ԃ�
	virtual Scene Next() const override;
	//�I��
	virtual void End() override;
	//���b�Z�[�W����
	void HandleMessage(EventMessage message, void* param);

private:
	//���U���g���̏���
	void Result(float deltaTime);

private:
	using WorldPtr = std::shared_ptr<World>;
	//���[���h
	WorldPtr world;
	//�X�R�A
	Score score;
	//�I���t���O
	bool isEnd;
	//�v���C���[
	ActorPtr player;
	//�{�X
	ActorPtr boss;
	//�N���A���̃^�C�}�[
	float stageClearTimer;

	//���U���g���J�n�������H
	bool isResult;
	//�v���C���[�����S���Ă���̌o�ߎ��ԁi���U���g���J�n���Ă���̕b���j
	float resultTimer;
	//���U���g�p�K���v���[�g�ړ��p�^�C�}�[
	float plateTimer;
	////���U���g�p���j���`��p
	//NumberTexture resultNumberTex;
	////press space key�`��
	//FlashTexture spaceTexture;

	bool isToTitleWaiting;
	bool isToTitle;

	bool isPause;
	float pauseTimer;

};