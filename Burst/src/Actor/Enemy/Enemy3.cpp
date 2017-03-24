#include "Enemy3.h"
#include <gslib.h>
#include "../AssetID.h"
#include "../../../EventMessage.h"
#include "../Effect/Explosion.h"
#include "../Base/ActorGroup.h"
#include "../EnemyBullet/EnemyMissile.h"

static const Matrix4 MODEL_SCALE = Matrix4::Scale(Vector3(0.8f));
//î≠éÀä‘äu
static const float BULLET_INTERVAL = 1.0f;
//íeèâë¨
static const float BULLET_SPEED = 150.0f;

Enemy3::Enemy3(IWorld * world_, const Vector3 & position_):
	Actor(world_, "Enemy3", position_, BoundingSphere(24.0f),10),
	timer(0.0f),
	target(nullptr),
	velocity(Vector3::Backward),
	speed(150.0f),
	angleX(0.0f),
	angleY(gsRandf(160.0f, 200.0f)),
	angleZ(gsRandf(0.0f,360.0f)),
	addAngleZ(260.0f),
	propellerAngle(0.0f)
{
	rotate.SetFront(Vector3::Backward);
	rotate.SetUp(Vector3::Up);
	rotate.SetLeft(Vector3::Left);

	player = world->FindActor("Player");
	if (player == nullptr) return;
	target = player->GetPositionPtr();
}

void Enemy3::OnUpdate(float deltaTime)
{	
	//à⁄ìÆ
	position += velocity * speed * deltaTime;
	if (position.z < -50.0f)
		Dead();

	//ÉvÉçÉyÉâäpìxâ¡éZ
	propellerAngle += 199.0f;

	//âÒì]
	player = world->FindActor("Player");
	if (player == nullptr) return;
	Vector3 toTarget = Vector3::Normalize(*target - position);
	rotate.SetFront(toTarget);
	rotate.SetLeft(Vector3::Normalize(Vector3::Cross(rotate.GetUp(), rotate.GetFront())));
	rotate.SetUp(Vector3::Normalize(Vector3::Cross(rotate.GetFront(), rotate.GetLeft())));

	//íeî≠éÀ
	timer += deltaTime;
	if (timer > BULLET_INTERVAL)
	{
		timer = 0.0f;
		//âÊñ âúÇÃï˚å¸ÇàÍíËó å¸Ç¢ÇƒÇΩÇÁî≠éÀÇµÇ»Ç¢
		if (rotate.GetFront().z > -0.5f) return;
		//î≠éÀà íuÇÃåvéZ
		Vector3 subPos = rotate.GetLeft() * 17.0f + rotate.GetUp() * -9.0f + rotate.GetFront() * 15.0f;
		//ÇQÇ©èäÇ©ÇÁî≠éÀ
		toTarget.x += gsRandf(-0.1f, 0.1f);
		world->AddActor(ActorGroup::EnemyBullet, std::make_shared<EnemyMissile>(world, position + subPos, toTarget * BULLET_SPEED));
		subPos.x *= -1;
		toTarget.x += gsRandf(-0.1f, 0.1f);
		world->AddActor(ActorGroup::EnemyBullet, std::make_shared<EnemyMissile>(world, position + subPos, toTarget * BULLET_SPEED));
	}
}

void Enemy3::OnDraw() const
{
	//ÉÇÉfÉãÇÃï`âÊ
	glPushMatrix();
	glMultMatrixf(MODEL_SCALE.ToGSmatrix4() * GetPose().ToGSmatrix4());
	gsDrawMesh(MODEL_ID::ENEMY_3_MODEL);
	glPopMatrix();

	//ÉvÉçÉyÉâÇÃï`âÊ
	glPushMatrix();
	Matrix4 mat = MODEL_SCALE * Matrix4::RotateY(propellerAngle) * GetPose();
	glMultMatrixf(mat.ToGSmatrix4());
	gsDrawMesh(MODEL_ID::ENEMY_3_PROPELLER_MODEL);
	glPopMatrix();

	//body.Translate(position).Draw();
}

void Enemy3::OnCollide(Actor& other,const HitInfo& info)
{
	hp--;
	if (hp <= 0)
	{
		//îöî≠ÇÃÉGÉtÉFÉNÉgÇê∂ê¨ÇµÇƒéÄñS
		world->AddActor(ActorGroup::Effect,std::make_shared<Explosion>(world, position + Vector3(0.0f, 2.0f, 0.0f),rotate.GetFront() * speed));
		Dead();
		static const int addscore = 1;
		world->SendMessage(EventMessage::AddScore, (void*)&addscore);
		gsPlaySE(SOUND_ID::BOMB_BIG_SE);
	}
}
