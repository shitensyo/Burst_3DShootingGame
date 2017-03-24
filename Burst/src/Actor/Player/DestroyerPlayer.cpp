#include "DestroyerPlayer.h"
#include <gslib.h>
#include "../AssetID.h"
#include "../../../EventMessage.h"
#include "../Base/ActorGroup.h"
#include "../PlayerBullet/PlayerMachineGun.h"
#include "../Effect/Explosion.h"
#include "../Effect/HitSmoke.h"
#include <GSmusic.h>

//耐久値
static const int HP_MAX = 5;

//移動速度
static const float MOVE_SPEED_Z = 200.0f;
//回転速度
static const float ANGLE_SPEED_X = 60.0f;
static const float ANGLE_SPEED_Y = 60.0f;
static const float ANGLE_SPEED_Z = 30.0f;

//発射位置の幅
static const float MACHINEGUN_SHOT_WIDTH = 6.0f;
//発射位置の前方距離 
static const float MACHINEGUN_SHOT_FRONT = 12.0f;

static const Matrix4 PLAYER_MODEL_SCALE = Matrix4::Scale(Vector3(0.2f));

DestroyerPlayer::DestroyerPlayer(IWorld* world, const Vector3& position) :
	Actor(world, "Player", position, BoundingSphere(4.0f),HP_MAX),
	timer(0.0f),
	bulletTimer(0.0f),
	bulletChange(-1),
	angleX(0.0f),
	angleY(0.0f),
	angleZ(0.0f),
	addAngleZ(0.0f),
	boosterAngle(0.0f)
{
	
}

void DestroyerPlayer::OnUpdate(float deltaTime)
{
	timer += deltaTime;

	ShotBullet(deltaTime);
	Move(deltaTime);
	BoosterRotate(deltaTime);
}

void DestroyerPlayer::OnDraw() const
{
	//モデルの描画
	glPushMatrix();
	glMultMatrixf(PLAYER_MODEL_SCALE.ToGSmatrix4() * GetPose().ToGSmatrix4());
	gsDrawMesh(MODEL_ID::PLAYER_MODEL);
	glPopMatrix();

	//ブースターの炎の描画
	glPushMatrix();
	Matrix4 mat =
		PLAYER_MODEL_SCALE *
		Matrix4::RotateZ(boosterAngle) *Matrix4::Translate(Vector3(0.0f, 0.6f, -28.0f)) *
		GetPose();
	glMultMatrixf(mat.ToGSmatrix4());
	gsDrawMesh(MODEL_ID::PLAYER_BOOSTER_MODEL);
	glPopMatrix();

	//ロゴの描画
	gsDrawSprite2D(TEXTURE_ID::LOGO_TEX, &GSvector2(0,600-128), &GSrect(0,0,256,256), NULL, NULL, &GSvector2(0.5f,0.5f), 0);
	//HPバーの描画
	GSrect gaugeRect(0.0f, 0.0f, 96.0f * hp / HP_MAX, 32.0f);
	GSrect frameRect(0.0f, 0.0f, 96.0f,32.0f);
	GSvector2 pos(60, 556);
	GSvector2 scale(2, 2);
	gsDrawSprite2D(TEXTURE_ID::HP_GAUGE_FRAME_TEX, &pos, &frameRect, NULL, NULL, &scale, 0);
	gsDrawSprite2D(TEXTURE_ID::HP_GAUGE_TEX, &pos, &gaugeRect, NULL, NULL, &scale, 0);

	//判定球の描画
	//body.Translate(position).Draw();
//
//	//デバッグ文字描画
//	gsTextPos(0, 0);
//	gsDrawText("回転Z : %d", angleZ);
//	gsTextPos(0, 16);
//	gsDrawText("デバッグ : %f", timer);
}

void DestroyerPlayer::OnCollide(Actor& other,const HitInfo& info)
{
	gsPlaySE(SOUND_ID::DAMAGE_SE);
	hp--;
	//小爆発
	world->AddActor(ActorGroup::Effect, std::make_shared<Explosion>(world, position + Vector3(0.0f, 2.0f, 0.0f), Vector3::Zero, 5));
	//煙
	world->AddActor(ActorGroup::Effect, std::make_shared<HitSmoke>(world, position + Vector3(0.0f, 2.0f, 0.0f)));
	if (hp <= 0)
	{
		//爆発のエフェクトを生成して死亡
		world->AddActor(ActorGroup::Effect, std::make_shared<Explosion>(world, position + Vector3(0.0f, 2.0f, 0.0f), Vector3::Zero));
		Dead();
		gsPlaySE(SOUND_ID::BOMB_BIG_SE);
		//ＢＧＭも停止
		gsStopMusic();
	}
}

void DestroyerPlayer::ShotBullet(float deltaTime)
{	
	bulletTimer += deltaTime;
	if (bulletTimer > 0.05f)
	{
		bulletTimer = 0.0f;
		//発射位置の計算
		Vector3 pos =
			position +
			GetRotate().GetFront() * MACHINEGUN_SHOT_FRONT +
			GetRotate().GetLeft() * MACHINEGUN_SHOT_WIDTH * bulletChange;
		world->AddActor(ActorGroup::PlayerBullet, std::make_shared<PlayerMachineGun>(world, pos, GetRotate().GetFront()));
		//発射位置の左右切り替え
		bulletChange *= -1;
	}
}

void DestroyerPlayer::Move(float deltaTime)
{
	//上下を向く
	if (gsGetKeyState(GKEY_UP) == GS_TRUE) {
		angleX -= ANGLE_SPEED_X * deltaTime;
	}
	if (gsGetKeyState(GKEY_DOWN) == GS_TRUE) {
		angleX += ANGLE_SPEED_X * deltaTime;
	}
	//角度制限
	angleX = Math::Clamp(angleX, -89.0f, 89.0f);

	//左右を向きつつバレルロール
	if (gsGetKeyState(GKEY_LEFT) == GS_TRUE) {
		angleY += ANGLE_SPEED_Y * deltaTime;
		if (addAngleZ > 0)addAngleZ /= 2.0f;
		addAngleZ -= ANGLE_SPEED_Z * deltaTime;
		angleZ += (int)addAngleZ;
	}
	else if (gsGetKeyState(GKEY_RIGHT) == GS_TRUE) {
		angleY -= ANGLE_SPEED_Y * deltaTime;
		if (addAngleZ < 0)addAngleZ /= 2.0f;
		addAngleZ += ANGLE_SPEED_Z * deltaTime;
		angleZ += (int)addAngleZ;
	}
	else
	{
		//ロールしている状態なら向きを治す
		int abs = Math::Abs(angleZ);
		if (abs >= 5)
		{
			angleZ *= 0.95f;
		}
		addAngleZ *= 0.95f;
	}
	//角度制限
	//angleY = Math::Clamp(angleY, -50.0f, 50.0f);
	addAngleZ = Math::Clamp(addAngleZ, -10.0f, 10.0f);
	//360度超えたら一周
	angleZ %= 360;

	rotate = Matrix4::RotateZ(angleZ) * Matrix4::RotateX(angleX) * Matrix4::RotateY(angleY);
	position += rotate.GetFront() * MOVE_SPEED_Z * deltaTime;
	//移動制限
	//position.Clamp(Vector3(-100, -100, 0), Vector3(100, 100, 0));
}

void DestroyerPlayer::BoosterRotate(float deltaTime)
{
	boosterAngle += 2000.0f * deltaTime;
}