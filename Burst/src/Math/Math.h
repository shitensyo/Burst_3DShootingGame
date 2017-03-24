#pragma once

const static float PI = 3.14159265358979f;

class Math
{
public:
	Math() = default;
	~Math() = default;

	///<summary>
	//�p�x��n���A������Ԃ�
	///</summary>
	static float Sin(float angle);
	///<summary>
	//�p�x��n���A������Ԃ�
	///</summary>
	static float Sin(double angle);
	///<summary>
	//�p�x��n���A������Ԃ�
	///</summary>
	static float Sin(int angle);
	///<summary>
	//�p�x��n���A�]����Ԃ�
	///</summary>
	static float Cos(float angle);
	///<summary>
	//�p�x��n���A�]����Ԃ�
	///</summary>
	static float Cos(double angle);
	///<summary>
	//�p�x��n���A�]����Ԃ�
	///</summary>
	static float Cos(int angle);
	///<summary>
	//�p�x��n���A���ڂ�Ԃ�
	///</summary>
	static float Tan(float angle);
	///<summary>
	//�p�x��n���A���ڂ�Ԃ�
	///</summary>
	static float Tan(double angle);
	///<summary>
	//�p�x��n���A���ڂ�Ԃ�
	///</summary>
	static float Tan(int angle);
	///<summary>
	//�p�x��n���A�t���������W�A���ŕԂ�
	///</summary>
	static float Asin(float angle);
	///<summary>
	//�p�x��n���A�t���������W�A���ŕԂ�
	///</summary>
	static float Asin(double angle);
	///<summary>
	//�p�x��n���A�t���������W�A���ŕԂ�
	///</summary>
	static float Asin(int angle);
	///<summary>
	//�p�x��n���A�t�]�������W�A���ŕԂ�
	///</summary>
	static float Acos(float angle);
	///<summary>
	//�p�x��n���A�t�]�������W�A���ŕԂ�
	///</summary>
	static float Acos(double angle);
	///<summary>
	//�p�x��n���A�t�]�������W�A���ŕԂ�
	///</summary>
	static float Acos(int angle);
	///<summary>
	//�p�x��n���A�t���ڂ����W�A���ŕԂ�
	///</summary>
	static float Atan(float angle);
	///<summary>
	//�p�x��n���A�t���ڂ����W�A���ŕԂ�
	///</summary>
	static float Atan(double angle);
	///<summary>
	//�p�x��n���A�t���ڂ����W�A���ŕԂ�
	///</summary>
	static float Atan(int angle);
	static float Atan(float y, float x);
	///<summary>
	//y / x �̋t���ڂ�Ԃ�
	///</summary>
	static float Atan2(float y, float x);
	///<summary>
	//y / x �̋t���ڂ�Ԃ�
	///</summary>
	static float Atan2(double y, double x);
	///<summary>
	//y / x �̋t���ڂ�Ԃ�
	///</summary>
	static float Atan2(int y, int x);
	///<summary>
	//���W�A����n���A�p�x��Ԃ�
	///</summary>
	static float Degree(float radian);
	///<summary>
	//�p�x��n���A���W�A����Ԃ�
	///</summary>
	static float Radian(float degree);
	///<summary>
	//��̎�����n���A�傫������Ԃ�
	///</summary>
	static float Max(float value1, float value2);
	///<summary>
	//��̕��������_����n���A�傫������Ԃ�
	///</summary>
	static float Max(double value1, double value2);
	///<summary>
	//��̐�����n���A�傫������Ԃ�
	///</summary>
	static float Max(int value1, int value2);
	///<summary>
	//��̎�����n���A����������Ԃ�
	///</summary>
	static float Min(float value1, float value2);
	///<summary>
	//��̕��������_����n���A����������Ԃ�
	///</summary>
	static float Min(double value1, double value2);
	///<summary>
	//��̐�����n���A����������Ԃ�
	///</summary>
	static float Min(int value1, int value2);
	///<summary>
	//������n���A�ׂ����Ԃ�
	///</summary>
	static float Pow(float value, float power = 2.0f);
	///<summary>
	//���������_����n���A�ׂ����Ԃ�
	///</summary>
	static float Pow(double value, float power = 2.0f);
	///<summary>
	//������n���A�ׂ����Ԃ�
	///</summary>
	static float Pow(int value, float power = 2.0f);
	///<summary>
	//������n���A��Βl��Ԃ�
	///</summary>
	static float Abs(float value);
	///<summary>
	//���������_����n���A��Βl��Ԃ�
	///</summary>
	static float Abs(double value);
	///<summary>
	//������n���A��Βl��Ԃ�
	///</summary>
	static int Abs(int value);

	template <class Type>
	static Type Abstemp(Type value)
	{
		return static_cast<Type>(0) > value ? -value : value;
	}

	///<summary>
	//���`���
	///</summary>
	template <typename T> static T Lerp(const T& start, const T& end, float amount)
	{
		if (amount < 0.0f) {
			amount = 0.0f;
		}
		else if (amount > 1.0f) {
			amount = 1.0f;
		}
		return start * (1.0f - amount) + end * amount;
	}

	/**********
	* @brief �x�W�F���`���
	* @param[in] start : �J�n�l
	* @param[in] center : ���Ԓl
	* @param[in] end : �I���l
	* @param[in] t : ���Ԕ䗦
	* @note t = 0.0 ~ 1.0
	*
	* @return 3�_�Ԃŕ⊮���ꂽ�l��Ԃ�
	**********/
	template <typename T> inline
		static T Bezier(const T& start, const T& center, const T& end, float t)
	{
			return (((1.0f - t) * (1.0f - t) * start) + (2.0f * (1.0f - t) * (t * center)) + (t * t) * end);
		}

	///<summary>
	//������n���A��������Ԃ�
	///</summary>
	static float Sqrt(float value);
	///<summary>
	//���������_����n���A��������Ԃ�
	///</summary>
	static float Sqrt(double value);
	///<summary>
	//������n���A��������Ԃ�
	///</summary>
	static float Sqrt(int value);
	///<summary>
	//�l���w�肳�ꂽ�͈͓��ɐ������܂�
	///</summary>
	static float Clamp(float value, float min, float max);
	///<summary>
	//�l���w�肳�ꂽ�͈͓��ɐ������܂�
	///</summary>
	static int Clamp(int value, int min, int max);

	//�l���w�肳�ꂽ�͈͓��Ŗ������[�v�����܂�
	static float InfinityClamp(float value, float min, float max);
	//�l���w�肳�ꂽ�͈͓��Ŗ������[�v�����܂�

	static int InfinityClamp(int value, int min, int max);
};