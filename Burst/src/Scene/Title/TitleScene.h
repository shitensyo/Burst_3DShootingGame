#pragma once

#include "../Base/IScene.h"
#include"../../UI/Base/FlashTexture.h"
#include <memory>

class World;
enum class EventMessage;

//�^�C�g���V�[��
class TitleScene : public IScene {
public:
	//�R���X�g���N�^
	TitleScene();
	//�f�X�g���N�^
	virtual ~TitleScene();
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
	bool isEnd;	//�I���t���O
	bool isToEnd;//�I�������邩�H

	float timer;

	//press space key�`��
	//FlashTexture spaceTexture;
	//GSvector2 titleLogoPos;
	//GSvector2 logoPos;
};


