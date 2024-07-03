#pragma once

#include"../Object.h"

//クラス定義
class Bullets_E : public Object
{
private:
	int animation[4];	//アニメーション画像
	int animation_count;//アニメーションカウント
	float speed;		//スピード
	Vector2D velocity;	//加速度
	Vector2D save;		//加速度記憶
	Vector2D p_l;		//プレイヤー座標
			

public:
	Bullets_E();	//コンストラクタ
	~Bullets_E();	//デストラクタ

	void Initialize();		//初期化処理
	void Update(); 			//更新処理
	void Draw() const;		//描画処理
	void Finalize();		//終了時処理

	//当たり判定通知処理
	bool OnHitCollision(GameObject* hit_object);

private:
	void Movement();				//移動処理
	void AnimationControl();		//アニメーション制御

	Vector2D Tracking(Vector2D A, Vector2D B); //追尾処理
};