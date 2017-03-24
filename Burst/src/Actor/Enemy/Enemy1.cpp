#include "Enemy1.h"
#include <gslib.h>
#include "../AssetID.h"
#include "../../../EventMessage.h"
#include "../Effect/Explosion.h"
#include "../Base/ActorGroup.h"
#include "../EnemyBullet/EnemyMachineGun.h"

static const Matrix4 MODEL_SCALE = Matrix4::Scale(Vector3(4.0f,8.0f,4.0f));
//’e‚ð”ò‚Î‚·•ûŒü
static const Vector3 BULLET_VELOCITY = Vector3(0.0f, -1.0f, -10.0f).Normalized();
//”­ŽËŠÔŠu
static const float BULLET_INTERVAL = 0.2f;
//’e‘¬
static const float BULLET_SPEED = 800.0f;

Enemy1::Enemy1(IWorld * world_, const Vector3 & position_):
	Actor(world_, "Enemy1", position_, BoundingSphere(18.0f),2),
	timer(0.0f),
	velocity(Vector3::Backward),
	speed(500.0f)
{
	rotate.SetFront(Vector3::Backward);
	rotate.SetUp(Vector3::Up);
	rotate.SetLeft(Vector3::Left);
}

void Enemy1::OnUpdate(float deltaTime)
{
	//’e”­ŽË
	timer += deltaTime;
	if (timer > BULLET_INTERVAL)
	{
		timer = 0.0f;
		//”­ŽËˆÊ’u‚ÌŒvŽZ
		Vector3 pos = position + rotate.GetFront() * 3.0f;
		world->AddActor(ActorGroup::EnemyBullet, std::make_shared<EnemyMachineGun>(world, pos, BULLET_VELOCITY * BULLET_SPEED,4.0f));
	}

	position += velocity * speed * deltaTime;
	if (position.z < -50.0f)
		Dead();
}

void Enemy1::OnDraw() const
{
	glPushMatrix();
	glMultMatrixf(MODEL_SCALE.ToGSmatrix4() * GetPose().ToGSmatrix4());
	gsDrawMesh(MODEL_ID::ENEMY_1_MODEL);
	glPopMatrix();

	//body.Translate(position).Draw();
}

void Enemy1::OnCollide(Actor& other,const HitInfo& info)
{
	hp--;
	if (hp <= 0)
	{
		//”š”­‚ÌƒGƒtƒFƒNƒg‚ð¶¬‚µ‚ÄŽ€–S
		world->AddActor(ActorGroup::Effect,std::make_shared<Explosion>(world, position + Vector3(0.0f, 2.0f, 0.0f),velocity * speed));
		Dead();
		static const int addscore = 1;
		world->SendMessage(EventMessage::AddScore, (void*)&addscore);
		gsPlaySE(SOUND_ID::BOMB_SMOLL_SE);
	}
}
