#pragma once

#include <gslib.h>
#include "../Math/MathsInclude.h"
class BoundingSphere;
class Ray;
class Line;

class Field {
public:
	//�R���X�g���N�^
	Field(GSuint skybox);
	//�R���X�g���N�^(�I�N�c���[�𗘗p����ꍇ�͂�����)
	Field(GSuint octree, GSuint skybox);
	//���C�Ƃ̏Փ˔���
	bool collision(
		const Ray& ray,
		GSvector3* intersect = nullptr,
		GSplane*   plane     = nullptr) const;
	//���C���Ƃ̏Փ˔���
	bool collision(
		const Line& line,
		GSvector3* intersect = nullptr,
		GSplane*   plane = nullptr) const;
	//���̂Ƃ̏Փ˔���
	bool collistion(
		const BoundingSphere& sphere,
		GSvector3* intersect = nullptr) const;
	//�`��
	void Draw() const;
	//�R�s�[�֎~
	Field(const Field& other);
	Field& operator = (const Field& other);
private:
	//�I�N�c���[���g�p���邩�H
	bool isOctree;
	//�I�N�c���[
	GSuint octree;
	//�X�J�C�{�b�N�X
	GSuint skybox;
};