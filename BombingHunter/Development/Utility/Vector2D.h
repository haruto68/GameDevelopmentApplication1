#pragma once

//クラス定義
class Vector2D
{
public:
	float x;	//X座標
	float y;	//Y座標

public:
	Vector2D();						//コンストラクタ
	Vector2D(float scalar);			//コンストラクタ
	Vector2D(float mx, float my);	//コンストラクタ
	~Vector2D();					//デストラクタ

public:
	//演算子オーバーロード
	Vector2D& operator = (const Vector2D& location);

	const Vector2D& operator + (const Vector2D& location) const;
	Vector2D& operator += (const Vector2D& location);

	const Vector2D& operator - (const Vector2D& location) const;
	Vector2D& operator -= (const Vector2D& location);

	const Vector2D& operator * (const float& scalar) const;
	const Vector2D& operator * (const Vector2D& location) const;
	Vector2D& operator *= (const float& scalar);
	Vector2D& operator *= (const Vector2D& location);

	const Vector2D& operator / (const float& scalar) const;
	const Vector2D& operator / (const Vector2D& location) const;
	Vector2D& operator /= (const float& scalar);
	Vector2D& operator /= (const Vector2D& location);

	void ToInt(int* x, int* y) const;
};