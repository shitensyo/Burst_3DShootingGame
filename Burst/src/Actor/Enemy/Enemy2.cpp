#include "Enemy2.h"
#include <gslib.h>
#include "../AssetID.h"
#include "../../../EventMessage.h"
#include "../Effect/Explosion.h"
#include "../Base/ActorGroup.h"
#include "../EnemyBullet/EnemyMachineGun.h"

static const Matrix4 MODEL_SCALE = Matrix4::Scale(Vector3(0.05f));
//”­ŽËŠÔŠu
static const float BULLET_INTERVAL = 0.1f;
//’e‘¬
static const float BULLET_SPEED = 700.0f;

Enemy2::Enemy2(IWorld * world_, const Vector3 & position_):
	Actor(world_, "Enemy2", position_, BoundingSphere(18.0f),2),
	timer(0.0f),
	speed(400.0f),
	angleX(0.0f),
	angleY(gsRandf(160.0f, 200.0f)),
	angleZ(gsRandf(0.0f,360.0f)),
	addAngleZ(260.0f)
{
	//rotate.SetFront(Vector3::Backward);
	//rotate.SetUp(Vector3::Up);
	//rotate.SetLeft(Vector3::Left);
	if (gsRand(0, 1) == 0)
		addAngleZ *= -1;
}

void Enemy2::OnUpdate(float deltaTime)
{
	//’e”­ŽË
	timer += deltaTime;
	if (timer > BULLET_INTERVAL)
	{
		timer = 0.0f;
		//”­ŽËˆÊ’u‚ÌŒvŽZ
		Vector3 pos = position + GetRotate().GetFront() * 3.0f;
		//”­ŽË•ûŒü‚ÌŒvŽZ
		Vector3 vec = GetRotate().GetFront();
		vec.x += gsRandf(-0.1f, 0.1f);
		vec.y += gsRandf(-0.1f, 0.1f);
		vec.Normalize();
		world->AddActor(ActorGroup::EnemyBullet, std::make_shared<EnemyMachineGun>(world, pos, vec * BULLET_SPEED,4.0f));
	}

	//‰ñ“]ŒvŽZ
	angleZ -= addAngleZ * deltaTime;
	rotate = Matrix4::RotateZ(angleZ) * Matrix4::RotateX(angleX) * Matrix4::RotateY(angleY);
	
	//ˆÚ“®
	position += 
		rotate.GetFront() * speed * deltaTime +
		-rotate.GetUp() * 150.0f * deltaTime;
	speed *= 1.001f;
	if (position.z < -50.0f)
		Dead();
}

void Enemy2::OnDraw() const
{
	glPushMatrix();
	glMultMatrixf(MODEL_SCALE.ToGSmatrix4() * GetPose().ToGSmatrix4());
	gsDrawMesh(MODEL_ID::ENEMY_2_MODEL);
	glPopMatrix();

	//body.Translate(position).Draw();
}

void Enemy2::OnCollide(Actor& other,const HitInfo& info)
{
	hp--;
	if (hp <= 0)
	{
		//”š”­‚ÌƒGƒtƒFƒNƒg‚ð¶¬‚µ‚ÄŽ€–S
		world->AddActor(ActorGroup::Effect,std::make_shared<Explosion>(world, position + Vector3(0.0f, 2.0f, 0.0f),rotate.GetFront() * speed));
		Dead();
		static const int addscore = 1;
		world->SendMessage(EventMessage::AddScore, (void*)&addscore);
		gsPlaySE(SOUND_ID::BOMB_MIDDLE_SE);
	}
}
