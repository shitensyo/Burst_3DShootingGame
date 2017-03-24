#include "Field.h"
#include "../Math/Ray.h"
#include "../Math/Line.h"
#include "../Math/BoundigSphere.h"

Field::Field(GSuint skybox):
	isOctree(false),skybox(skybox){
}

//コンストラクタ
Field::Field(GSuint octree, GSuint skybox) :
	isOctree(true), octree(octree), skybox(skybox) {
}

//レイとの衝突判定
bool Field::collision(
	const Ray& ray,
	GSvector3* intersect,
	GSplane*   plane) const {
	return gsOctreeCollisionRay(
		gsGetOctree(octree),
		&ray.position.ToGSvector3(), &ray.direction.ToGSvector3(), intersect, plane) == GS_TRUE;
}

//ラインとの衝突判定
bool Field::collision(
	const Line& line,
	GSvector3* intersect,
	GSplane*   plane) const {
	return gsOctreeCollisionLine(
		gsGetOctree(octree),
		&line.start.ToGSvector3(), &line.end.ToGSvector3(), intersect, plane) == GS_TRUE;
}

//球体との衝突判定
bool Field::collistion(
	const BoundingSphere& sphere,
	GSvector3* intersect) const {
	return gsOctreeCollisionSphere(
		gsGetOctree(octree),
		&sphere.center.ToGSvector3(), sphere.radius, intersect) == GS_TRUE;

}

//描画
void Field::Draw() const {
	gsDrawSkyBox(skybox);

	if(isOctree)
		gsDrawOctree(octree);
}
