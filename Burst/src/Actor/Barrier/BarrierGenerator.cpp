#include "BarrierGenerator.h"
#include "../AssetID.h"
#include "../../World/IWorld.h"
#include "../Base/ActorGroup.h"
#include "../Effect/Explosion.h"
#include "../Effect/BasicParticle.h"
#include "../AssetID.h"
#include "../../Def.h"
#include "../Camera/TpsCamera.h"
#include "../../../EventMessage.h"

static const Matrix4 MODEL_SCALE = Matrix4::Scale(Vector3(0.8f));
//体力初期値
static const int INIT_HP = 100;

//回転速度
static const float SPIN_SPEED = 60.0f;

//上下にふわふわ動く速さ
static const float UP_DOWN_SPEED = 90.0f;
//上下移動量
static const float UP_DOWN_LENGTH = 2.0f;

//煙放出間隔
static const float SMOKE_INTERVAL = 0.1f;
//煙基本速度
static const float SMOKE_SPEED = 60.0f;
//煙を放出する高さ
static const float SMOKE_POSITION_HEIGHT = 50.0f;

//バリア球体のスケール最小、最大値
static const float SPHERE_MODEL_SCALE_MIN = 0.60f;
static const float SPHERE_MODEL_SCALE_MAX = 0.70f;
//バリア球体の高さ
static const float SPHERE_HEIGHT = 160.0f;

//円柱のスケール
static const Vector3 POLE_MODEL_SCALE = Vector3(0.9f,0.9f,0.6f);

//カーソルスケール
static const float CURSOR_SCALE = 0.2f;
//カーソル回転量
static const float CURSOR_ANGLE_ADD = 30.0f;

BarrierGenerator::BarrierGenerator(IWorld * world, const Vector3 & position, const Vector3& shipPos) :
	Actor(world, "BarrierGenerator", position, BoundingSphere(110.0f), INIT_HP),
	timer(0.0f),
	angleY(0.0f),
	smokeTimer(0.0f),
	cursorAngle(0.0f),
	isCursorDraw(false)
{
	//円柱のモデルのマトリックス計算
	Vector3 shipPosXZ = shipPos;
	shipPosXZ.y = 0.0f;
	Vector3 posXZ = position;
	posXZ.y = 0.0f;
	Vector3 toShip = shipPosXZ - posXZ;
	toShip.Normalize();
	Matrix4 polerot;
	polerot.SetFront(toShip);
	polerot.SetUp(Vector3::Up);
	polerot.SetLeft(Vector3::Cross(Vector3::Up, toShip));
	polerot.SetPosition(position + rotate.GetUp() * SPHERE_HEIGHT);

	poleMat = Matrix4::Scale(POLE_MODEL_SCALE) * polerot;
}

void BarrierGenerator::OnMessage(EventMessage event, void *)
{
	if (event == EventMessage::BarrierPhase)
	{
		isCursorDraw = true;
	}
}

void BarrierGenerator::OnUpdate(float deltaTime)
{
	//body.radius = 120.0f;
	//回転
	rotate = Matrix4::RotateY(angleY);
	angleY += SPIN_SPEED * deltaTime;

	//上下にふわふわする
	timer += UP_DOWN_SPEED * deltaTime;
	position.y += UP_DOWN_LENGTH * Math::Sin(timer);

	//耐久値に応じて煙を吹く
	if (hp < 50)
	{
		smokeTimer += deltaTime;
		if (smokeTimer > SMOKE_INTERVAL)
		{
			smokeTimer = gsRandf(-0.1f,0.0f);
			Vector3 pos = position + rotate.GetUp() * SMOKE_POSITION_HEIGHT;
			Vector3 dir = Vector3(gsRandf(0.0f, 1.0f), gsRandf(0.6f, 1.0f), gsRandf(0.0f, 1.0f));
			dir.Normalize();
			float speed = SMOKE_SPEED * gsRandf(0.9f, 3.1f);
			world->AddActor(ActorGroup::Effect, std::make_shared<BasicParticle>(world, TEXTURE_ID::BLACK_SMOKE_TEX, pos, dir * speed, 12.0f, 4.0f));
		}
	}


	poleMat.SetPosition(position + rotate.GetUp() * SPHERE_HEIGHT);

	//カーソルを回転
	cursorAngle += CURSOR_ANGLE_ADD * deltaTime;
}

void BarrierGenerator::OnDraw() const
{
	//発生装置本体の描画
	glPushMatrix();
	glMultMatrixf(MODEL_SCALE.ToGSmatrix4() * GetPose().ToGSmatrix4());
	gsDrawMesh(MODEL_ID::BARRIER_GENERATOR);
	glPopMatrix();

	//バリア球体の描画
	glPushMatrix();
	Matrix4 sphere = Matrix4::Scale(Vector3(gsRandf(SPHERE_MODEL_SCALE_MIN, SPHERE_MODEL_SCALE_MAX)));
	sphere.SetPosition(position + rotate.GetUp() * SPHERE_HEIGHT);
	glMultMatrixf(sphere.ToGSmatrix4());
	gsDrawMesh(MODEL_ID::BARRIER_SPHERE);
	glPopMatrix();

	//バリア円柱の描画
	glPushMatrix();
	glMultMatrixf(poleMat.ToGSmatrix4());
	gsDrawMesh(MODEL_ID::BARRIER_POLE);
	glPopMatrix();


	//ロックオンカーソルの描画 
	if (!isCursorDraw) return;
	GSvector3 cameraPos = world->GetCamera()->GetPosition().ToGSvector3();
	GSvector3 playerPos = world->GetPlayer()->GetPosition().ToGSvector3();
	GSvector3 cameraToPlayer = playerPos - cameraPos;
	cameraToPlayer.normalize();
	GSvector3 cameraToGenerator = position.ToGSvector3() - cameraPos;
	cameraToGenerator.normalize();
	//カメラの背面にある場合は計算および描画をしない
	if (cameraToPlayer.dot(cameraToGenerator) < 0.0f) return;
	GSmatrix4 wmat,vmat,pmat,smat;
	wmat.identity();//ワールド変換行列
	vmat.identity();//ビュー（透視）変換行列
	pmat.identity();//射影変換行列
	smat.identity();//スクリーン変換行列

	wmat.setPosition(position.ToGSvector3());	
	vmat.setLookAtRH(cameraPos, playerPos, GSvector3(0, 1, 0));
	pmat.setPerspectiveRH(FOV, ASPECT, PERSPECTIVE_NEAR, PERSPECTIVE_FAR);
	smat = Matrix4::Screen(0.0f, 0.0f, WINDOW_WIDTH, WINDOW_HEIGHT).ToGSmatrix4();
	GSmatrix4 wvp = wmat * vmat * pmat;
	float w = wvp.m[3][3];
	GSvector3 projpos = wvp.getPosition() / w;
	GSmatrix4 drawmat;
	drawmat.identity();
	drawmat.setPosition(projpos);
	drawmat *= smat;
	//描画座標を取り出す
	GSvector2 drowPos = GSvector2(drawmat.getPosition().x, drawmat.getPosition().y);
	drowPos += GSvector2(0, 2);
	//カーソルの大きさ
	GSvector2 s;
	gsDrawSprite2D(TEXTURE_ID::LOCKON_CURSOR_TEX, &drowPos, &GSrect(0, 0, 256, 256), &(GSvector2(320, 320) * CURSOR_SCALE * 2), NULL, &GSvector2(CURSOR_SCALE, CURSOR_SCALE), cursorAngle);
}


void BarrierGenerator::OnCollide(Actor & other, const HitInfo & info)
{
	if (other.GetName() == "Player") return;

	hp--;
	if (hp <= 0)
	{
		world->AddActor(ActorGroup::Effect, std::make_shared<Explosion>(world, position, Vector3::Zero, 40, 1.5f, 800.0f, 0.84f, 12.0f));
		gsPlaySE(SOUND_ID::BOMB_MIDDLE_SE);
		Dead();
	}
}
