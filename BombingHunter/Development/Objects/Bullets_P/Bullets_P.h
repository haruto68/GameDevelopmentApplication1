#pragma once

#include"../Object.h"

//クラス定義
class Bullets_P : public Object
{
private:
	int animation[4];	//アニメーション画像
	int animation_count;//アニメーションカウント
	float speed;		//スピード
	Vector2D velocity;	//加速度

public:
	Bullets_P();	//コンストラクタ
	~Bullets_P();	//デストラクタ

	void Initialize();		//初期化処理
	void Update(); 			//更新処理
	void Draw() const;		//描画処理
	void Finalize();		//終了時処理

	//当たり判定通知処理
	bool OnHitCollision(GameObject* hit_object);

private:
	void Movement();				//移動処理
	void AnimationControl();		//アニメーション制御
};