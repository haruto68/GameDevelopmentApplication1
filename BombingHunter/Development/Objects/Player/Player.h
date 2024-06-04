#pragma once

#include"../Object.h"

//クラス定義
class Player : public Object
{
private:
	int animation[2];			//アニメーション画像
	int animation_count;		//アニメーション時間
	float speed;				//スピード
	Vector2D velocity;			//加速度

public:
	Player();		//コンストラクタ
	~Player();		//デストラクタ

	virtual void Initialize() override;		//初期化処理
	virtual void Update() override; 		//更新処理
	virtual void Draw() const override;		//描画処理
	virtual void Finalize() override;		//終了時処理

	//当たり判定通知処理
	virtual bool OnHitCollision(GameObject* hit_object) override;

private:
	void Movement();				//移動処理
	void AnimationControl();		//アニメーション制御
};