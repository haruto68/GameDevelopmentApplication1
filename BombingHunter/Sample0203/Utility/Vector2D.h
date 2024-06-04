#pragma once

//�N���X��`
class Vector2D
{
public:
	float x;	//X���W
	float y;	//Y���W

public:
	Vector2D();						//�R���X�g���N�^
	Vector2D(float scalar);			//�R���X�g���N�^
	Vector2D(float mx, float my);	//�R���X�g���N�^
	~Vector2D();					//�f�X�g���N�^

public:
	//���Z�q�I�[�o�[���[�h
	
	//������Z
	Vector2D& operator = (const Vector2D& location);
	
	//���Z
	const Vector2D& operator + (const Vector2D& location) const;
	Vector2D& operator += (const Vector2D& location);

	//���Z
	const Vector2D& operator - (const Vector2D& location) const;
	Vector2D& operator -= (const Vector2D& location);

	//��Z
	const Vector2D& operator * (const float& scalar) const;
	const Vector2D& operator * (const Vector2D& location) const;
	Vector2D& operator *= (const float& scalar);
	Vector2D& operator *= (const Vector2D& location);

	//���Z
	const Vector2D& operator / (const float& scalar) const;
	const Vector2D& operator / (const Vector2D& location) const;
	Vector2D& operator /= (const float& scalar);
	Vector2D& operator /= (const Vector2D& location);

	//�����l�ɃL���X�g����
	void ToInt(int* x, int* y) const;
};