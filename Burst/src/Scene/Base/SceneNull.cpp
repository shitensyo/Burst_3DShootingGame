#include "SceneNull.h"
#include "Scene.h"

//開始
void SceneNull::Start() {}

//更新
void SceneNull::Update(float) {}

//描画
void SceneNull::Draw() const {}

//終了しているか？
bool SceneNull::IsEnd() const {
	return false;
}

//次のシーンを返す
Scene SceneNull::Next() const {
	return Scene::None;
}

//終了
void SceneNull::End() {}
