#include "SceneNull.h"
#include "Scene.h"

//�J�n
void SceneNull::Start() {}

//�X�V
void SceneNull::Update(float) {}

//�`��
void SceneNull::Draw() const {}

//�I�����Ă��邩�H
bool SceneNull::IsEnd() const {
	return false;
}

//���̃V�[����Ԃ�
Scene SceneNull::Next() const {
	return Scene::None;
}

//�I��
void SceneNull::End() {}
