#pragma once

enum class Scene;

//シーンインターフェース
class IScene {
public:
	//仮想デストラクタ
	virtual ~IScene() {}
	//開始
	virtual void Start() = 0;
	//更新
	virtual void Update(float deltaTime) = 0;
	//描画
	virtual void Draw() const = 0;
	//終了しているか？
	virtual bool IsEnd() const = 0;
	//次のシーンを返す
	virtual Scene Next() const = 0;
	//終了
	virtual void End() = 0;
};
