#include "AirShipMissileShooter.h"
#include "../AssetID.h"
#include "../../Math/Math.h"
#include "../Base/ActorGroup.h"
#include "../EnemyBullet/EnemyMissile.h"
#include "../Effect/Explosion.h"

//モデル追加乗算スケール
static const float MODEL_MUL_SCALE = 3.0f;
//モデル基本スケール
static const Matrix4 MODEL_SCALE = Matrix4::Scale(Vector3(15.0f * MODEL_MUL_SCALE));
//発射間隔
static const float BULLET_INTERVAL = 3.0f;
//弾初速
static const float BULLET_SPEED = 250.0f;
//回転限界量
static const float ANGLE_Y_LIMIT = 100.0f;

//ミサイルスケール
static const float MISSILE_SCALE = 4.0f;

AirShipMissileShooter::AirShipMissileShooter(IWorld * world_, const Vector3 & position_, const Matrix4& initRotate_, bool isShot_) :
	Actor(world_, "AirShipMissileShooter", position_, BoundingSphere()),
	timer(gsRandf(0.0f, 2.0f)),
	initRotate(initRotate_),
	angleY(0.0f),
	prevRotate(initRotate_),
	currentRotate(initRotate_),
	isShot(isShot_)
{
	rotate = initRotate;
	player = world->GetPlayer();
}

void AirShipMissileShooter::OnUpdate(float deltaTime)
{
	if (!isShot) return;

	player = world->GetPlayer();
	//プレイヤーがいない場合は実行しない
	if (player == nullptr) return;

	//プレイヤーが遠い場合は実行しない
	if (Vector3::Length(player->GetPosition() - position) > 8000.0f) return;


	//プレイヤーのほうを向く
	Vector3 toPlayer = player->GetPosition() - position;
	toPlayer.Normalize();

	//プレイヤーまでの角度をＸＺ平面上で計算
	Vector3 f = initRotate.GetFront();
	f = Vector3(f.x, 0.0f, f.z);
	f.Normalize();
	Vector3 toP = Vector3(toPlayer.x, 0.0f, toPlayer.z);
	toP.Normalize();
	angleY = Vector3::Inner(f, toP);
	angleY = Math::Clamp(angleY, -ANGLE_Y_LIMIT, ANGLE_Y_LIMIT);

	//左右判定
	Vector3 cross = Vector3::Cross(initRotate.GetFront(), toPlayer);
	if (cross.y < 0)
		angleY = -angleY;

	//回転
	prevRotate = currentRotate;
	currentRotate = Quaternion::RotateAxis(rotate.GetUp(), angleY);
	//補完してなめらかに
	currentRotate = Matrix4::Slerp(prevRotate, currentRotate, 0.1f);
	rotate = initRotate * currentRotate;

	//攻撃
	timer += deltaTime;
	if (timer > BULLET_INTERVAL)
	{
		timer = gsRandf(0.0f, 5.5f);
		//回転量が限界なら発射しない
		if (Math::Abs(angleY) >= ANGLE_Y_LIMIT) return;
		//発射位置の計算
		int x = gsRand(-1, 1);
		Vector3 shotPos = rotate.GetLeft() * 30.0f * x + rotate.GetUp() * 30.0f + rotate.GetFront() * 200.0f;
		//発射方向の計算（ランダムで多少ばらつかせる）
		Vector3 toTarget = toPlayer;
		toTarget.x += gsRandf(-0.3f, 0.3f);
		toTarget.y += gsRandf(-0.3f, 0.3f);
		toTarget.z += gsRandf(-0.1f, 0.1f);
		//発射
		world->AddActor(ActorGroup::EnemyBullet, std::make_shared<EnemyMissile>(world, position + shotPos, toTarget * BULLET_SPEED, MISSILE_SCALE));
		//エフェクト
		world->AddActor(ActorGroup::Effect, std::make_shared<Explosion>(world, position + shotPos, Vector3::Zero,2));
	}
}

void AirShipMissileShooter::OnDraw() const
{	
	//モデルの描画
	glPushMatrix();
	glMultMatrixf(MODEL_SCALE.ToGSmatrix4() * GetPose().ToGSmatrix4());
	gsDrawMesh(MODEL_ID::BOSS_AIR_SHIP_MISSILE_SHOOTER);
	glPopMatrix();
}

void AirShipMissileShooter::OnCollide(Actor& other,const HitInfo& info)
{
}
