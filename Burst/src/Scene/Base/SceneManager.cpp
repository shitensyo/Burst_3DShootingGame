#include "SceneManager.h"
#include "SceneNull.h"

//�R���X�g���N�^
SceneManager::SceneManager() :
	currentScene_(std::make_shared<SceneNull>()) {
}

//������
void SceneManager::initialize() {
	End();
	scenes_.clear();
}

//�X�V
void SceneManager::Update(float deltaTime) {
	currentScene_->Update(deltaTime);
	if (currentScene_->IsEnd()) {
		change(currentScene_->Next());
	}
}

//�`��
void SceneManager::Draw() const {
	currentScene_->Draw();
}

//�I��
void SceneManager::End() {
	currentScene_->End();
	currentScene_ = std::make_shared<SceneNull>();
}

//�V�[���̒ǉ�
void SceneManager::add(Scene name, const IScenePtr& scene) {
	scenes_[name] = scene;
}

//�V�[���̍X�V
void SceneManager::change(Scene name) {
	End();
	currentScene_ = scenes_[name];
	currentScene_->Start();
}
