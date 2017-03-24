#include "Vector3.h"
#include "Math.h"
#include <cmath>
#include <sstream>

Vector3 Vector3::Zero = Vector3(0, 0, 0);
Vector3 Vector3::One = Vector3(1, 1, 1);
Vector3 Vector3::Up = Vector3(0, 1, 0);
Vector3 Vector3::Down = Vector3(0, -1, 0);
Vector3 Vector3::Right = Vector3(1, 0, 0);
Vector3 Vector3::Left = Vector3(-1, 0, 0);
Vector3 Vector3::Forward = Vector3(0, 0, 1);
Vector3 Vector3::Backward = Vector3(0, 0, -1);
Vector3 Vector3::White = Vector3(255,	255,	255);
Vector3 Vector3::Black = Vector3(0,		0,		0);
Vector3 Vector3::Blue  = Vector3(0,		0,		255);
Vector3 Vector3::Red   = Vector3(255,	0,		0);
Vector3 Vector3::Green = Vector3(0,		255,	0);

Vector3::Vector3()
: x(0), y(0), z(0)
{

}

Vector3::Vector3(float s)
: x(s), y(s), z(s)
{

}

Vector3::Vector3(float x, float y)
: x(x), y(y), z(0)
{

}

Vector3::Vector3(float x, float y, float z)
: x(x), y(y), z(z)
{

}

Vector3::Vector3(int s)
: x((float)s), y((float)s), z((float)s)
{

}

Vector3::Vector3(int x, int y)
: x((float)x), y((float)y), z((float)0)
{

}

Vector3::Vector3(int x, int y, int z)
: x((float)x), y((float)y), z((float)z)
{

}

Vector3::Vector3(const Vector3& vector)
: x(vector.x), y(vector.y), z(vector.z)
{

}

Vector3::Vector3(const GSvector3 & vector)
: x(vector.x), y(vector.y), z(vector.z)
{

}

float Vector3::Length() const
{
	return sqrt(x * x + y * y + z * z);
}

void Vector3::Normalize()
{
	float result = Length();
	if (result != 0.0f)
	{
		(*this) /= result;
	}
}

Vector3 Vector3::Normalized() const
{
	return Vector3::Normalize(Vector3(x, y, z));
}

void Vector3::Clamp(const Vector3 & min, const Vector3 & max)
{
	Vector3 result = Clamp(*this, min, max);
	(*this) = result;
}

float Vector3::Length(const Vector3& v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

float Vector3::Distance(const Vector3& v1, const Vector3& v2)
{
	return (v2 - v1).Length();
}

Vector3 Vector3::Normalize(const Vector3& v)
{
	Vector3 result = v;
	result.Normalize();
	return result;
}

float Vector3::Dot(const Vector3& v1, const Vector3& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector3 Vector3::Cross(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}

float Vector3::Inner(const Vector3& v1, const Vector3& v2)
{
	return Math::Degree(acosf(Dot(Normalize(v1), Normalize(v2))));
}

Vector3 Vector3::FrontVec(Vector3& position, Vector3& rotate)
{
	// 原点を設定
	Vector3 origin = position;

	// オブジェクトの位置を設定
	Vector3 point = position + Forward;

	// 中心を原点に移動
	Vector3 center = point - origin;

	// キャラクターの回転量からcossinを割り出す
	float rotatecos = cos(-Math::Radian(rotate.y));
	float rotatesin = sin(-Math::Radian(rotate.y));

	// 原点を中心に回転
	Vector3 front = Vector3(
		center.x * rotatecos - center.z * rotatesin,
		0.0f,
		center.x * rotatesin + center.z * rotatecos
		);

	// 原点から戻す
	front += origin;

	return front - position;
}

// 二つのベクトル間の線形補間をする
Vector3 Vector3::Lerp(const Vector3& start, const Vector3& end, float amount)
{
	if (amount < 0.0f) {
		amount = 0.0f;
	}
	else if (amount > 1.0f) {
		amount = 1.0f;
	}
	return start * (1.0f - amount) + end * amount;
}

// バネの力を加える
void Vector3::Spring(
	Vector3& position,
	Vector3& velocity,
	const Vector3& restPosition,
	float stiffness,
	float friction,
	float mass
	)
{
	// バネの伸び具合を計算
	Vector3 stretch = (position - restPosition);
	// バネの力を計算
	Vector3 force = -stiffness * stretch;
	// 加速度を追加
	Vector3 acceleration = force / mass;
	// 移動速度を計算
	velocity = friction * (velocity + acceleration);
	// 座標の更新
	position += velocity;
}

float Vector3::Pitch(const Vector3& front)
{
	float l = Length(front);
	if (l == 0)
		return 0.0f;

	float y = front.y / l;
	return Math::Asin(Math::Degree(-y));
}

float Vector3::Yaw(const Vector3& front)
{
	if (Length(front) == 0){
		return 0.0f;
	}
	return Math::Atan(front.x, front.z);
}

Vector3 Vector3::Direction(const Vector3& start, const Vector3& end)
{
	return Normalize(end - start);
}

Vector3 Vector3::Clamp(const Vector3 & value, const Vector3 & min, const Vector3 & max)
{
	Vector3 result;
	result = Vector3(
		Math::Clamp(value.x, min.x, max.x),
		Math::Clamp(value.y, min.y, max.y),
		Math::Clamp(value.z, min.z, max.z));
	return result;
}

Vector3 Vector3::CreateFromEleDir(float elavation, float direction)
{
	Vector3 result;
	result.x = Math::Cos(elavation) * Math::Sin(direction);
	result.y = -Math::Sin(elavation);
	result.z = Math::Cos(elavation) * Math::Cos(direction);

	return	result;
}

Vector3 Vector3::CreateFromPitchYaw(float pitch, float yaw)
{
	return CreateFromEleDir(pitch, yaw);
}

GSvector3 Vector3::ToGSvector3(const Vector3 & v)
{
	GSvector3 result;
	result.x = v.x;
	result.y = v.y;
	result.z = v.z;
	return result;
}

GSvector3 Vector3::ToGSvector3() const
{
	return ToGSvector3(*this);
}

Vector3& Vector3::operator = (const GSvector3& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
 	return *this;
}

Vector3::operator std::string() const
{
	std::stringstream ss;
	ss << "(" << x << " , " << y << " , " << z << ")";
	return ss.str();
}

Vector3::operator GSvector3() const
{
	return GSvector3((float)x, (float)y, (float)z);
}

Vector3 operator + (const Vector3& v1, const Vector3& v2)
{
	Vector3 result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
}

Vector3& operator += (Vector3& v1, const Vector3& v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	return v1;
}

Vector3 operator - (const Vector3& v1, const Vector3& v2)
{
	Vector3 result;
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;
}

Vector3& operator -= (Vector3& v1, const Vector3& v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	return v1;
}

Vector3 operator * (const Vector3& v, const float f)
{
	Vector3 result;
	result.x = v.x * f;
	result.y = v.y * f;
	result.z = v.z * f;
	return result;
}

Vector3 operator * (const float f, const Vector3& v)
{
	Vector3 result;
	result.x = v.x * f;
	result.y = v.y * f;
	result.z = v.z * f;
	return result;
}

Vector3 operator * (const Vector3& v1, const Vector3& v2)
{
	Vector3 result;
	result.x = v1.x * v2.x;
	result.y = v1.y * v2.y;
	result.z = v1.z * v2.z;
	return result;
}

Vector3& operator *= (Vector3& v, const float f)
{
	v.x = v.x * f;
	v.y = v.y * f;
	v.z = v.z * f;
	return v;
}

Vector3& operator *= (const float f, Vector3& v)
{
	v.x = v.x * f;
	v.y = v.y * f;
	v.z = v.z * f;
	return v;
}

Vector3 operator / (const Vector3& v, const float f)
{
	Vector3 result;
	result.x = v.x / f;
	result.y = v.y / f;
	result.z = v.z / f;
	return result;
}

Vector3 operator / (const float f, const Vector3& v)
{
	Vector3 result;
	result.x = v.x / f;
	result.y = v.y / f;
	result.z = v.z / f;
	return result;
}

Vector3 operator / (const Vector3& v1, const  Vector3& v2)
{
	Vector3 result;
	result.x = v1.x / v2.x;
	result.y = v1.y / v2.y;
	result.z = v1.z / v2.z;
	return result;
}

Vector3& operator /= (Vector3& v, const float f)
{
	v.x = v.x / f;
	v.y = v.y / f;
	v.z = v.z / f;
	return v;
}

Vector3 operator - (const Vector3& v)
{
	Vector3 result = v;
	result.x = -v.x;
	result.y = -v.y;
	result.z = -v.z;
	return result;
}

bool operator != (const Vector3& v1, const Vector3& v2)
{
	return ((int)v1.x == (int)v2.x) && ((int)v1.y == (int)v2.y) && ((int)v1.z == (int)v2.z);
}