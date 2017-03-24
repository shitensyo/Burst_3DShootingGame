#include "Communication.h"
#include "../AssetID.h"
#include "../../World/IWorld.h"
#include "../../../EventMessage.h"

//音が鳴ってテキストが出るまでの待ち時間
static const float WAIT_TIME = 0.4f;

Communication::Communication(IWorld * world, ActorPtr boss_, const Vector2 & position_, const Phase &phase_) :
	Actor(world, "Communication", Vector3::Zero, BoundingSphere()),
	timer(0.0f),
	textWaitTimer(0.0f),
	textNum(-1),
	isTextDraw(false),
	phase(phase_),
	initPosition(position_),
	textPosition(10, 2)
{
	texts.push_back("今回のミッションは、バリアに守られた敵空中戦艦の撃破だ。");
	texts.push_back("まずは機体の操縦に慣れてもらう。苦労して用意したんだ、大切に扱え。");
	texts.push_back("方向キーもしくはＷＡＳＤキーで、入力した方向に向かって機首が動く。");
	texts.push_back("ＳＨＩＦＴキーで高速移動ができる。急接近、離脱に利用しろ。");
	texts.push_back("ＳＰＡＣＥキーでホーミングミサイルが打てる。攻撃を当てづらい小型の敵機はこれで落とせ。");
	texts.push_back("それでは作戦に移る。");
	texts.push_back("まずは戦艦の両隣に浮かんでいる、バリアの発生装置の破壊だ。護衛の戦闘機に注意を払え。");
	texts.push_back("いいぞ。その調子だ。");
	texts.push_back("そのまま戦艦に攻撃を行え。画面上部のゲージは戦艦の耐久値だ。");
	texts.push_back("・・・ずいぶんと硬い戦艦だな。ラチがあかない。");
	texts.push_back("たった今友軍のスパイからの情報が入った。戦艦下部のコンテナを狙え。");
	texts.push_back("戦艦下部のコンテナは火薬庫として使われているようだ。誘爆させて戦艦にダメージを与えろ。");
	texts.push_back("上出来だ。そのまま攻撃を続行。戦艦を叩き落とせ。");

	texts.push_back("作戦終了。よくやった。");
	texts.push_back("通信が途絶えた・・・！！！　応答しろ！　応答しろ！！・・・");
}

void Communication::OnMessage(EventMessage event, void *)
{

}

void Communication::OnUpdate(float deltaTime)
{
	if (phase != Phase::DEAD && world->GetPlayer() == nullptr)
	{
		phase = Phase::DEAD;
		timer = 0.0f;
		textWaitTimer = 0.0f;
	}

	switch (phase)
	{
	case Phase::START:StartPhase(deltaTime);
		break;
	case Phase::TUTORIAL:TutorialPhase(deltaTime);
		break;
	case Phase::BARRIER:BarrierPhase(deltaTime);
		break;
	case Phase::CONTAINER:ContainerPhase(deltaTime);
		break;
	case Phase::SHIP:ShipPhase(deltaTime);
		break;
	case Phase::DEAD:DeadPhase(deltaTime);
		break;
	case Phase::CLEAR:ClearPhase(deltaTime);
		break;
	default:
		break;
	}
}

void Communication::OnDraw() const
{
	GSrect rect(0.0f, 0.0f, 800.0f, 36.0f);
	GSvector2 scale(1.0f, 0.8f);
	GScolor color(1.0f,1.0f,1.0f,0.6f);
	gsDrawSprite2D(TEXTURE_ID::BLACK_BAR_TEX, &initPosition.ToGSvector2(), &rect, NULL, &color, &scale, 0);

	if (isTextDraw)
	{
		Vector2 pos = initPosition + textPosition;
		gsTextPos(pos.x, pos.y);
		gsDrawText("");	//↓がgsTextPosに対応していないため　これを挟んで無理やり文字の位置を変える
		gsTextDraw(GS_FONT_NORMAL, 26, "メイリオ", texts.at(textNum).c_str());
	}
}

void Communication::StartPhase(float deltaTime)
{
	isTextDraw = false;
	timer += deltaTime;
	if (timer > 1.0f)
	{
		timer = 0.0f;
		phase = Phase::TUTORIAL;
	}
}

void Communication::TutorialPhase(float deltaTime)
{
	//テキスト進行
	timer += deltaTime;
	
	//最初だけ早く
	if (textNum == -1)
		timer += deltaTime * 3.0f;
	if (timer < 6.0f) return;

	if (textWaitTimer <= 0.0f)
	{
		isTextDraw = false;
		gsPlaySE(SOUND_ID::RECEPTION_SE);
	}
	textWaitTimer += deltaTime;
	if (textWaitTimer > WAIT_TIME)
	{
		isTextDraw = true;
		timer = 0.0f;
		textWaitTimer = 0.0f;
		textNum++;

		//最後まで来たら段階変更
		if (textNum >= 6)
		{
			phase = Phase::BARRIER;
			world->SendMessageW(EventMessage::BarrierPhase);
		}
	}
}

void Communication::BarrierPhase(float deltaTime)
{
	//バリア発生装置が全滅したら次へ進む。
	if (world->FindActor("BarrierGenerator") == nullptr)
	{
		if (textWaitTimer <= 0.0f)
		{
			isTextDraw = false;
			gsPlaySE(SOUND_ID::RECEPTION_SE);
		}
		textWaitTimer += deltaTime;
		if (textWaitTimer > WAIT_TIME)
		{
			isTextDraw = true;
			textWaitTimer = 0.0f;
			textNum++;
			phase = Phase::CONTAINER;
		}
	}
}

void Communication::ContainerPhase(float deltaTime)
{	
	//コンテナを破壊したら次へ進む。
	if (world->FindActor("AirShipContainer") == nullptr)
	{
		isTextDraw = false;
		timer = 0.0f;
		textWaitTimer = 0.0f;
		phase = Phase::SHIP;
	}

	//最後まで進んでいるなら進行しない
	if (textNum >= 11) return;

	//テキスト進行
	//ここだけゆっくり
	if (textNum == 8)
		timer += deltaTime / 4;
	else
		timer += deltaTime;

	if (timer < 6.0f) return;

	if (textWaitTimer <= 0.0f)
	{
		isTextDraw = false;
		gsPlaySE(SOUND_ID::RECEPTION_SE);
	}
	textWaitTimer += deltaTime;
	if (textWaitTimer > WAIT_TIME)
	{
		isTextDraw = true;
		timer = 0.0f;
		textWaitTimer = 0.0f;
		textNum++;

		//ここまで進んだらコンテナにカーソルを表示する
		if (textNum >= 10)
		{
			world->SendMessageW(EventMessage::ContainerPhase);
		}
	}
}

void Communication::ShipPhase(float deltaTime)
{
	if (textNum == 12) return;

	if (textWaitTimer <= 0.0f)
	{
		isTextDraw = false;
		gsPlaySE(SOUND_ID::RECEPTION_SE);
	}
	textWaitTimer += deltaTime;
	if (textWaitTimer > WAIT_TIME)
	{
		isTextDraw = true;
		textWaitTimer = 0.0f;
		textNum = 12;
	}
}

void Communication::DeadPhase(float deltaTime)
{
	if (textNum == 14) return;

	timer += deltaTime;
	if (timer < 3.0f) return;
	if (textWaitTimer <= 0.0f)
	{
		isTextDraw = false;
		gsPlaySE(SOUND_ID::RECEPTION_SE);
	}
	textWaitTimer += deltaTime;
	if (textWaitTimer > WAIT_TIME)
	{
		isTextDraw = true;
		textWaitTimer = 0.0f;
		textNum = 14;
	}
}

void Communication::ClearPhase(float deltaTime)
{
	if (textNum == 13) return;

	timer += deltaTime;
	if (timer < 3.0f) return;
	if (textWaitTimer <= 0.0f)
	{
		isTextDraw = false;
		gsPlaySE(SOUND_ID::RECEPTION_SE);
	}
	textWaitTimer += deltaTime;
	if (textWaitTimer > WAIT_TIME)
	{
		isTextDraw = true;
		textWaitTimer = 0.0f;
		textNum = 13;
	}
}
