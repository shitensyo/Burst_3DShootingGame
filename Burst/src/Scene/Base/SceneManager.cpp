#include "SceneManager.h"
#include "SceneNull.h"

//コンストラクタ
SceneManager::SceneManager() :
	currentScene_(std::make_shared<SceneNull>()) {
}

//初期化
void SceneManager::initialize() {
	End();
	scenes_.clear();
}

//更新
void SceneManager::Update(float deltaTime) {
	currentScene_->Update(deltaTime);
	if (currentScene_->IsEnd()) {
		change(currentScene_->Next());
	}
}

//描画
void SceneManager::Draw() const {
	currentScene_->Draw();
}

//終了
void SceneManager::End() {
	currentScene_->End();
	currentScene_ = std::make_shared<SceneNull>();
}

//シーンの追加
void SceneManager::add(Scene name, const IScenePtr& scene) {
	scenes_[name] = scene;
}

//シーンの更新
void SceneManager::change(Scene name) {
	End();
	currentScene_ = scenes_[name];
	currentScene_->Start();
}
