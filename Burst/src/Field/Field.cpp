#include "Field.h"
#include "../Math/Ray.h"
#include "../Math/Line.h"
#include "../Math/BoundigSphere.h"

Field::Field(GSuint skybox):
	isOctree(false),skybox(skybox){
}

//�R���X�g���N�^
Field::Field(GSuint octree, GSuint skybox) :
	isOctree(true), octree(octree), skybox(skybox) {
}

//���C�Ƃ̏Փ˔���
bool Field::collision(
	const Ray& ray,
	GSvector3* intersect,
	GSplane*   plane) const {
	return gsOctreeCollisionRay(
		gsGetOctree(octree),
		&ray.position.ToGSvector3(), &ray.direction.ToGSvector3(), intersect, plane) == GS_TRUE;
}

//���C���Ƃ̏Փ˔���
bool Field::collision(
	const Line& line,
	GSvector3* intersect,
	GSplane*   plane) const {
	return gsOctreeCollisionLine(
		gsGetOctree(octree),
		&line.start.ToGSvector3(), &line.end.ToGSvector3(), intersect, plane) == GS_TRUE;
}

//���̂Ƃ̏Փ˔���
bool Field::collistion(
	const BoundingSphere& sphere,
	GSvector3* intersect) const {
	return gsOctreeCollisionSphere(
		gsGetOctree(octree),
		&sphere.center.ToGSvector3(), sphere.radius, intersect) == GS_TRUE;

}

//�`��
void Field::Draw() const {
	gsDrawSkyBox(skybox);

	if(isOctree)
		gsDrawOctree(octree);
}
