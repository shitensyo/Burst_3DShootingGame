#pragma once

#include "IScenePtr.h"
#include <unordered_map>

enum class Scene;

//シーン管理クラス
class SceneManager {
public:
	//コンストラクタ
	SceneManager();
	//初期化
	void initialize();
	//更新
	void Update(float deltaTime);
	//描画
	void Draw() const;
	//終了
	void End();
	//シーンの追加
	void add(Scene name, const IScenePtr& scene);
	//シーンの更新
	void change(Scene name);
	//コピー禁止
	SceneManager(const SceneManager& other) = delete;
	SceneManager& operator = (const SceneManager& other) = delete;
private:
	//シーン
	std::unordered_map<Scene, IScenePtr>	scenes_;
	//現在のシーン
	IScenePtr currentScene_;
};
