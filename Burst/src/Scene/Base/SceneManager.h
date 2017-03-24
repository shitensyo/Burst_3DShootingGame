#pragma once

#include "IScenePtr.h"
#include <unordered_map>

enum class Scene;

//�V�[���Ǘ��N���X
class SceneManager {
public:
	//�R���X�g���N�^
	SceneManager();
	//������
	void initialize();
	//�X�V
	void Update(float deltaTime);
	//�`��
	void Draw() const;
	//�I��
	void End();
	//�V�[���̒ǉ�
	void add(Scene name, const IScenePtr& scene);
	//�V�[���̍X�V
	void change(Scene name);
	//�R�s�[�֎~
	SceneManager(const SceneManager& other) = delete;
	SceneManager& operator = (const SceneManager& other) = delete;
private:
	//�V�[��
	std::unordered_map<Scene, IScenePtr>	scenes_;
	//���݂̃V�[��
	IScenePtr currentScene_;
};
