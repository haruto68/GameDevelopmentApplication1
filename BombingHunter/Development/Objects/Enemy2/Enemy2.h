#pragma once

#include"../GameObject.h"

//クラス定義
class Enemy2 : public GameObject
{
private:
	int animation[2];			//アニメーション画像
	int animation_count;		//アニメーション時間
	float box_size;				//当たり判定
	float speed;				//スピード

public:
	Enemy2();		//コンストラクタ
	~Enemy2();		//デストラクタ

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