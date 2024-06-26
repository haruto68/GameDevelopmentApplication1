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
	
	//代入演算
	Vector2D& operator = (const Vector2D& location);
	
	//加算
	const Vector2D& operator + (const Vector2D& location) const;
	Vector2D& operator += (const Vector2D& location);

	//減算
	const Vector2D& operator - (const Vector2D& location) const;
	Vector2D& operator -= (const Vector2D& location);

	//乗算
	const Vector2D& operator * (const float& scalar) const;
	const Vector2D& operator * (const Vector2D& location) const;
	Vector2D& operator *= (const float& scalar);
	Vector2D& operator *= (const Vector2D& location);

	//除算
	const Vector2D& operator / (const float& scalar) const;
	const Vector2D& operator / (const Vector2D& location) const;
	Vector2D& operator /= (const float& scalar);
	Vector2D& operator /= (const Vector2D& location);

	//整数値にキャストする
	void ToInt(int* x, int* y) const;
};