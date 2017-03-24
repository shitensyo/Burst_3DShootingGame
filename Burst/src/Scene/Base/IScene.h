#pragma once

enum class Scene;

//�V�[���C���^�[�t�F�[�X
class IScene {
public:
	//���z�f�X�g���N�^
	virtual ~IScene() {}
	//�J�n
	virtual void Start() = 0;
	//�X�V
	virtual void Update(float deltaTime) = 0;
	//�`��
	virtual void Draw() const = 0;
	//�I�����Ă��邩�H
	virtual bool IsEnd() const = 0;
	//���̃V�[����Ԃ�
	virtual Scene Next() const = 0;
	//�I��
	virtual void End() = 0;
};
