#pragma once

#include <gslib.h>
#include "../Math/MathsInclude.h"
class BoundingSphere;
class Ray;
class Line;

class Field {
public:
	//コンストラクタ
	Field(GSuint skybox);
	//コンストラクタ(オクツリーを利用する場合はこちら)
	Field(GSuint octree, GSuint skybox);
	//レイとの衝突判定
	bool collision(
		const Ray& ray,
		GSvector3* intersect = nullptr,
		GSplane*   plane     = nullptr) const;
	//ラインとの衝突判定
	bool collision(
		const Line& line,
		GSvector3* intersect = nullptr,
		GSplane*   plane = nullptr) const;
	//球体との衝突判定
	bool collistion(
		const BoundingSphere& sphere,
		GSvector3* intersect = nullptr) const;
	//描画
	void Draw() const;
	//コピー禁止
	Field(const Field& other);
	Field& operator = (const Field& other);
private:
	//オクツリーを使用するか？
	bool isOctree;
	//オクツリー
	GSuint octree;
	//スカイボックス
	GSuint skybox;
};