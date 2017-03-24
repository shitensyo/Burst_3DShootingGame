#include "AirShipMachinegunShooter.h"
#include "../AssetID.h"
#include "../../Math/Math.h"
#include "../Base/ActorGroup.h"
#include "../EnemyBullet/EnemyMachineGun.h"

//モデル追加乗算スケール
static const float MODEL_MUL_SCALE = 3.0f;
//モデル基本スケール
static const Matrix4 MODEL_SCALE = Matrix4::Scale(Vector3(15.0f * MODEL_MUL_SCALE));
//発射間隔
static const float BULLET_INTERVAL = 0.15f;
//弾初速
static const float BULLET_SPEED = 1200.0f;
//弾寿命
static const float BULLET_LIFE_TIME = 1.6f;
//回転限界量
static const float ANGLE_Y_LIMIT = 100.0f;
//発射方向、回転量を変える間隔
static const float ANGLE_CHANGE_INTERVAL = 5.0f;

//正面と判定するときの内積値　これを超えたら正面にいるとする
static const float DOT_LIMIT = 0.2f;

AirShipMachinegunShooter::AirShipMachinegunShooter(IWorld * world_, const Vector3 & position_, const Matrix4& initRotate_, bool isShot_) :
	Actor(world_, "AirShipMachinegunShooter", position_, BoundingSphere()),
	timer(gsRandf(0.0f, 2.0f)),
	initRotate(initRotate_),
	targetVec(initRotate_.GetFront()),
	angleY(0.0f),
	rotateTimer(0.0f),
	isShot(isShot_)
{
	rotate = initRotate;
}

void AirShipMachinegunShooter::OnUpdate(float deltaTime)
{
	if (!isShot) return;

	//プレイヤーと前後判定
	ActorPtr player = world->GetPlayer();
	if (player == nullptr) return;

	Vector3 toPlayer = player->GetPosition() - position;
	toPlayer.Normalize();
	float dot = Vector3::Dot(initRotate.GetFront(), toPlayer);
	//プレイヤーが正面にいるなら
	if (dot > DOT_LIMIT)
	{
		targetVec = toPlayer;
		Rotation();
	}
	else
	{
		//発射方向を変える
		rotateTimer += deltaTime;
		if (rotateTimer > ANGLE_CHANGE_INTERVAL)
		{
			rotateTimer = 0.0f;
			//適当に決めたベクトルのほうを向く
			targetVec = initRotate.GetLeft() * gsRandf(-1.0f, 1.0f) + initRotate.GetFront() * gsRandf(1.0f, 1.5f) + initRotate.GetUp() * gsRandf(0.0f, 1.0f);
			targetVec.Normalize();
			Rotation();
		}
	}
	
	//攻撃
	timer += deltaTime;
	if (timer > BULLET_INTERVAL)
	{
		timer = 0.0f;
		//発射位置の計算
		Vector3 shotPos = rotate.GetUp() * 10.0f + rotate.GetFront() * 40.0f;
		//発射方向の計算（ランダムで多少ばらつかせる）
		Vector3 toTarget = targetVec;
		toTarget.x += gsRandf(-0.06f, 0.06f);
		toTarget.y += gsRandf(-0.06f, 0.06f);
		toTarget.z += gsRandf(-0.06f, 0.06f);
		//発射
		world->AddActor(ActorGroup::EnemyBullet, std::make_shared<EnemyMachineGun>(world, position + shotPos, toTarget * BULLET_SPEED, BULLET_LIFE_TIME));
	}
}

void AirShipMachinegunShooter::OnDraw() const
{
	//モデルの描画
	glPushMatrix();
	glMultMatrixf(MODEL_SCALE.ToGSmatrix4() * GetPose().ToGSmatrix4());
	gsDrawMesh(MODEL_ID::BOSS_AIR_SHIP_MACHINEGUN_SHOOTER);
	glPopMatrix();
}

void AirShipMachinegunShooter::OnCollide(Actor& other,const HitInfo& info)
{
}


void AirShipMachinegunShooter::Rotation()
{
	//砲身が向くべき角度をＸＺ平面上で計算
	Vector3 f = initRotate.GetFront();
	f = Vector3(f.x, 0.0f, f.z);
	f.Normalize();
	Vector3 to = Vector3(targetVec.x, 0.0f, targetVec.z);
	to.Normalize();
	angleY = Vector3::Inner(f, to);

	//左右判定
	Vector3 cross = Vector3::Cross(initRotate.GetFront(), to);
	if (cross.y < 0)
		angleY = -angleY;

	//逆さに付いている砲台は向き反転
	if (initRotate.GetUp().y < 0)
		angleY = -angleY;

	//回転
	Matrix4 rot = Quaternion::RotateAxis(rotate.GetUp(), angleY);
	rotate = initRotate * rot;

}