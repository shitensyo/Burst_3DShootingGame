#include "Math.h"
#include <math.h>
#include <cassert>

// �p�x��n���ASin��Ԃ�
float Math::Sin(float angle)
{
	return sinf(Radian(angle));
}

// �p�x��n���ASin��Ԃ�
float Math::Sin(double angle)
{
	return sinf(Radian((float)angle));
}

// �p�x��n���ASin��Ԃ�
float Math::Sin(int angle)
{
	return sinf(Radian((float)angle));
}

// �p�x��n���ACos��Ԃ�
float Math::Cos(float angle)
{
	return cosf(Radian(angle));
}

// �p�x��n���ACos��Ԃ�
float Math::Cos(double angle)
{
	return cosf(Radian((float)angle));
}

// �p�x��n���ACos��Ԃ�
float Math::Cos(int angle)
{
	return cosf(Radian((float)angle));
}

// �p�x��n���ATan��Ԃ�
float Math::Tan(float angle)
{
	return tanf(Radian(angle));
}

// �p�x��n���ATan��Ԃ�
float Math::Tan(double angle)
{
	return tanf(Radian((float)angle));
}

// �p�x��n���ATan��Ԃ�
float Math::Tan(int angle)
{
	return tanf(Radian((float)angle));
}

// �p�x��n���A�t������Ԃ�
float Math::Asin(float angle)
{
	return asinf(Radian(angle));
}

// �p�x��n���A�t������Ԃ�
float Math::Asin(double angle)
{
	return asinf(Radian((float)angle));
}

// �p�x��n���A�t������Ԃ�
float Math::Asin(int angle)
{
	return asinf(Radian((float)angle));
}

// �p�x��n���A�t�]����Ԃ�
float Math::Acos(float angle)
{
	return acosf(Radian(angle));
}

// �p�x��n���A�t�]����Ԃ�
float Math::Acos(double angle)
{
	return acosf(Radian((float)angle));
}

// �p�x��n���A�t�]����Ԃ�
float Math::Acos(int angle)
{
	return acosf(Radian((float)angle));
}

// �p�x��n���A�t���ڂ�Ԃ�
float Math::Atan(float angle)
{
	return atanf(Radian(angle));
}

// �p�x��n���A�t���ڂ�Ԃ�
float Math::Atan(double angle)
{
	return atanf(Radian((float)angle));
}

// �p�x��n���A�t���ڂ�Ԃ�
float Math::Atan(int angle)
{
	return atanf(Radian((float)angle));
}

float Math::Atan(float y, float x)
{
	return atan2(y, x);
}

// y / x �̋t���ڂ�Ԃ�
float Math::Atan2(float y, float x)
{
	return atan2f(Radian(y), Radian(x));
}

// y / x �̋t���ڂ�Ԃ�
float Math::Atan2(double y, double x)
{
	return atan2f(Radian((float)y), Radian((float)x));
}

// y / x �̋t���ڂ�Ԃ�
float Math::Atan2(int y, int x)
{
	return atan2f(Radian((float)y), Radian((float)x));
}

// ���W�A����n���A�p�x��Ԃ�
float Math::Degree(float radian)
{
	return radian / PI * 180.0f;
}

// �p�x��n���A���W�A����Ԃ�
float Math::Radian(float degree)
{
	return degree * PI / 180.0f;
}

// ��̎�����n���A�傫������Ԃ�
float Math::Max(float value1, float value2)
{
	return fmaxf(value1, value2);
}

// ��̕��������_����n���A�傫������Ԃ�
float Math::Max(double value1, double value2)
{
	return fmaxf((float)value1, (float)value2);
}

// ��̐�����n���A�傫������Ԃ�
float Math::Max(int value1, int value2)
{
	return fmaxf((float)value1, (float)value2);
}

// ��̎�����n���A����������Ԃ�
float Math::Min(float value1, float value2)
{
	return fminf(value1, value2);
}

// ��̕��������_����n���A����������Ԃ�
float Math::Min(double value1, double value2)
{
	return fminf((float)value1, (float)value2);
}

// ��̐�����n���A����������Ԃ�
float Math::Min(int value1, int value2)
{
	return fminf((float)value1, (float)value2);
}

// ������n���A�ׂ����Ԃ�
float Math::Pow(float value, float power)
{
	return powf(value, power);
}

// ���������_����n���A�ׂ����Ԃ�
float Math::Pow(double value, float power)
{
	return powf((float)value, power);
}

// ������n���A�ׂ����Ԃ�
float Math::Pow(int value, float power)
{
	return powf((float)value, power);
}

// ������n���A��Βl��Ԃ�
float Math::Abs(float value)
{
	return fabsf(value);
}

// ���������_����n���A��Βl��Ԃ�
float Math::Abs(double value)
{
	return fabsf((float)value);
}

// ������n���A��Βl��Ԃ�
int Math::Abs(int value)
{
	return abs(value);
}

// ������n���A��������Ԃ�
float Math::Sqrt(float value)
{
	return sqrtf(value);
}

// ���������_����n���A��������Ԃ�
float Math::Sqrt(double value)
{
	return sqrtf((float)value);
}

// ������n���A��������Ԃ�
float Math::Sqrt(int value)
{
	return sqrtf((float)value);
}

// �l���w�肳�ꂽ�͈͓��ɐ������܂�
float Math::Clamp(float value, float min, float max)
{
	if (min == max)
		return min;
	
	if (value < min)
		return min;
	if (value > max)
		return max;
	return value;
}

// �l���w�肳�ꂽ�͈͓��ɐ������܂�
int Math::Clamp(int value, int min, int max)
{
	if (min == max)
		return min;

	if (value < min)
		return min;
	if (value > max)
		return max;
	return value;
}

//�l���w�肳�ꂽ�͈͓��Ŗ������[�v�����܂�
float Math::InfinityClamp(float value, float min, float max){
	if (value < min)
		return max;
	if (value > max)
		return min;
	return value;
}

//�l���w�肳�ꂽ�͈͓��Ŗ������[�v�����܂�
int Math::InfinityClamp(int value, int min, int max){
	if (value < min)
		return max;
	if (value > max)
		return min;
	return value;
}