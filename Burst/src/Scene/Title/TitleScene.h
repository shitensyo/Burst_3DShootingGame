#pragma once

#include "../Base/IScene.h"
#include"../../UI/Base/FlashTexture.h"
#include <memory>

class World;
enum class EventMessage;

//タイトルシーン
class TitleScene : public IScene {
public:
	//コンストラクタ
	TitleScene();
	//デストラクタ
	virtual ~TitleScene();
	//開始
	virtual void Start() override;
	//更新
	virtual void Update(float deltaTime) override;
	//描画
	virtual void Draw() const override;
	//終了しているか？
	virtual bool IsEnd() const override;
	//次のシーンを返す
	virtual Scene Next() const override;
	//終了
	virtual void End() override;
	//メッセージ処理
	void HandleMessage(EventMessage message, void* param);

private:
	using WorldPtr = std::shared_ptr<World>;
	//ワールド
	WorldPtr world;
	bool isEnd;	//終了フラグ
	bool isToEnd;//終了させるか？

	float timer;

	//press space key描画
	//FlashTexture spaceTexture;
	//GSvector2 titleLogoPos;
	//GSvector2 logoPos;
};


