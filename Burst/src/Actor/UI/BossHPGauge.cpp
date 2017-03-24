#include "BossHPGauge.h"
#include "../AssetID.h"
#include "../../Def.h"

BossHPGauge::BossHPGauge(IWorld* world, ActorPtr boss_, const Vector2& position_) :
	Actor(world, "DashLine", Vector3::Zero, BoundingSphere()),
	bossHP(0),
	maxHP(100),
	boss(boss_),
	spritePosition(position_),
	alpha(0.0f)
{
	//‰ŠúHP‚ðE‚Á‚Ä‚­‚é
	maxHP = boss->GetHP();
}

void BossHPGauge::OnUpdate(float deltaTime)
{
	bossHP = boss->GetHP();
}

void BossHPGauge::OnDraw() const
{
	GSrect gaugeRect(0.0f, 0.0f, 796 * bossHP / maxHP, 32.0f);
	GSrect frameRect(0.0f, 0.0f, 816.0f, 48.0f);
	GSvector2 scale(1, 0.2);
	gsDrawSprite2D(TEXTURE_ID::BOSS_GAUGE_FRAME_TEX, &spritePosition.ToGSvector2() , &frameRect, NULL, NULL, &scale, 0);
	gsDrawSprite2D(TEXTURE_ID::BOSS_GAUGE_TEX, &(spritePosition.ToGSvector2() + GSvector2(2, 2)), &gaugeRect, NULL, NULL, &scale, 0);
}
