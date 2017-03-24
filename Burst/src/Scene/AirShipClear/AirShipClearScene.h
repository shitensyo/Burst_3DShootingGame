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

class AirShipClearScene : public IScene {
public:
	//�R���X�g���N�^
	AirShipClearScene();
	//�f�X�g���N�^
	virtual ~AirShipClearScene();
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
	using WorldPtr = std::shared_ptr<World>;
	//���[���h
	WorldPtr world;
	//�I���t���O
	bool isEnd;
	//�^�C�}�[
	float timer;
	float stageClearTimer;
};