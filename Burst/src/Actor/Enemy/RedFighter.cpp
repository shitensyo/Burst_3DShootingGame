#include "RedFighter.h"
#include <gslib.h>
#include "../AssetID.h"
#include "../../../EventMessage.h"
#include "../Effect/Explosion.h"
#include "../Base/ActorGroup.h"
#include "../EnemyBullet/EnemyMachineGun.h"

static const Matrix4 MODEL_SCALE = Matrix4::Scale(Vector3(0.5f));
//弾を飛ばす方向
static const Vector3 BULLET_VELOCITY = Vector3(0.0f, -1.0f, -10.0f).Normalized();
//発射間隔
static const float BULLET_INTERVAL = 0.2f;
//弾速
static const float BULLET_SPEED = 800.0f;
//初期移動速度
static const float MOVE_SPEED_INIT = 200.0f;
//高速移動速度
static const float MOVE_SPEED_DASH = 400.0f;

//左方向を軸にした回転速度
static const float ANGLE_SPEED_PITCH = 180.0f;
//上方向を軸にした回転速度
static const float ANGLE_SPEED_YAW = 360.0f;

//マシンガン発射位置の幅
static const float MACHINEGUN_SHOT_WIDTH = 6.0f;
//マシンガン発射位置の前方距離 
static const float MACHINEGUN_SHOT_FRONT = 12.0f;

static const Matrix4 FIRE_SCALE = Matrix4::Scale(Vector3(0.3f, 0.3f, 0.6f));

RedFighter::RedFighter(IWorld * world_, const Vector3 & position_, const Matrix4 & rotate_):
	Actor(world_,"RedFighter", position_,BoundingSphere(10.0f),4),
	timer(0.0f),
	initRotate(rotate_),
	speed(MOVE_SPEED_INIT),
	bulletChange(1),
	front(Vector3::Zero),
	toPlayer(Vector3::Zero),
	dot(0.0f),
	boosterAngle(0.0f),
	prevRotate(rotate_),
	isBreakaway(false),
	breakawayTimer(0.0f)
{
	player = world->GetPlayer();
	rotate = rotate_;
}

void RedFighter::OnUpdate(float deltaTime)
{

	//移動
	front = rotate.GetFront();
	velocity = front * speed * deltaTime;
	position += velocity;
	boosterAngle += 200.0f * deltaTime;

	player = world->GetPlayer();
	if (player == nullptr) return;

	//プレイヤーの方向
	toPlayer = player->GetPosition() - position;
	toPlayer.Normalize();

	//前後判定
	dot = Vector3::Dot(front, toPlayer);

	//通常時はプレイヤーを追いかける
	if (!isBreakaway)
	{	
		//プレイヤーが背面にいて、かつ距離が近い場合は離脱モードへ移行
		if (dot <= 0.1f && Vector3::Length(player->GetPosition() - position) < 800)
			isBreakaway = true;
		//それ以外はプレイヤーに向かって突進
		else
		{
			speed = MOVE_SPEED_INIT;
			PlayerLookingRotation(deltaTime);
		}
	}
	//離脱時は高速移動してプレイヤーから距離を置く
	else
	{
		breakawayTimer += deltaTime;
		speed = MOVE_SPEED_DASH;
		if (breakawayTimer > 4.0f && Vector3::Length(player->GetPosition() - position) > 1000)
		{
			breakawayTimer = 0.0f;
			isBreakaway = false;
		}
	}



	Attack(deltaTime);
}

void RedFighter::OnDraw() const
{
	//機体
	glPushMatrix();
	glMultMatrixf(MODEL_SCALE.ToGSmatrix4() * GetPose().ToGSmatrix4());
	gsDrawMesh(MODEL_ID::RED_FIGHTER_MODEL);
	glPopMatrix();

	//炎
	glPushMatrix();
	Matrix4 mat =
		FIRE_SCALE *
		Matrix4::RotateZ(boosterAngle) *Matrix4::Translate(Vector3(5.6f, 0.4f, -72.0f)) *
		GetPose();
	glMultMatrixf(mat.ToGSmatrix4());
	gsDrawMesh(MODEL_ID::PLAYER_BOOSTER_MODEL);
	glPopMatrix();
	glPushMatrix();
	mat =
		FIRE_SCALE *
		Matrix4::RotateZ(boosterAngle) *Matrix4::Translate(Vector3(-5.6f, 0.4f, -72.0f)) *
		GetPose();
	glMultMatrixf(mat.ToGSmatrix4());
	gsDrawMesh(MODEL_ID::PLAYER_BOOSTER_MODEL);
	glPopMatrix();

	//gsTextPos(0, 64);
	//gsDrawText("anglepitch : %f", anglePitch);
}

void RedFighter::OnCollide(Actor & other, const HitInfo & info)
{
	hp--;
	if (hp <= 0 && isDead == false)
	{
		//爆発のエフェクトを生成して死亡
		world->AddActor(ActorGroup::Effect, std::make_shared<Explosion>(world, position + Vector3(0.0f, 2.0f, 0.0f), velocity * speed));
		Dead();
		static const int addscore = 1;
		world->SendMessage(EventMessage::AddScore, (void*)&addscore);
		gsPlaySE(SOUND_ID::BOMB_SMOLL_SE);
	}
}


void RedFighter::PlayerLookingRotation(float deltaTime)
{
	////ピッチ方向のプレイヤーまでの角度
	//float anglePitch = Vector3::Inner(
	//	Vector3(0.0f, front.y, front.z).Normalized(),
	//	Vector3(0.0f, toPlayer.y, toPlayer.z).Normalized());
	////ヨー方向のプレイヤーまでの角度
	//float angleYaw = Vector3::Inner(
	//	Vector3(front.x, 0.0f, front.z).Normalized(),
	//	Vector3(toPlayer.x, 0.0f, toPlayer.z).Normalized());


	//プレイヤーのほうを向く
	//角度補正値
	float angleCorrection = Vector3::Inner(front, toPlayer) / 100.0f;

	float inputPitch = 1.0f * angleCorrection;
	//上下判定
	if (front.y < toPlayer.y)
		inputPitch = -inputPitch;

	float inputYaw = 1.0f * angleCorrection;
	//左右判定
	Vector3 cross = Vector3::Cross(front, toPlayer);
	//左右どちらに曲がるかを決定
	if (cross.y < 0)
		inputYaw = -inputYaw;

	inputPitch = Math::Clamp(inputPitch, -1.0f, 1.0f);
	inputYaw = Math::Clamp(inputYaw, -1.0f, 1.0f);


	//回転
	prevRotate = rotate;
	Matrix4 currentRotaet = rotate;
	currentRotaet *= Quaternion::RotateAxis(rotate.GetUp(), inputYaw * ANGLE_SPEED_YAW * deltaTime);
	currentRotaet *= Quaternion::RotateAxis(rotate.GetLeft(), inputPitch* ANGLE_SPEED_PITCH * deltaTime);
	rotate = Matrix4::Slerp(prevRotate, currentRotaet, 0.8f);
}

void RedFighter::Attack(float deltaTime)
{
	timer += deltaTime;
	if (timer > BULLET_INTERVAL)
	{
		//プレイヤーが正面にいない場合は打たない
		if (dot < 0) return;
		timer = 0.0f;
		//発射位置の計算
		Vector3 pos =
			position +
			GetRotate().GetFront() * MACHINEGUN_SHOT_FRONT +
			GetRotate().GetLeft() * MACHINEGUN_SHOT_WIDTH * bulletChange;
		world->AddActor(ActorGroup::EnemyBullet, std::make_shared<EnemyMachineGun>(world, pos, rotate.GetFront() * BULLET_SPEED, 2.0f));
		//発射位置の左右切り替え
		bulletChange *= -1;
	}
}