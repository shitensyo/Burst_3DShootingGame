#include "Light.h"

//コンストラクタ
Light::Light(IWorld* world, const Vector3& position) :
	Actor(world, "Light", position, BoundingSphere()) {
}

//描画
void Light::OnDraw() const {
	static const float ambient[]  = { 0.2f, 0.2f, 0.2f, 1.0f };
	static const float diffuse[] = { 0.9f, 0.9f, 0.9f, 1.0f };
	static const float specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float pos[] = { position.x, position.y, position.z, 0.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
}