#pragma once

#include"../Utility//Vector2D.h"

#define OBJECTSIZE		(0.7)	//オブジェクトのサイズ倍率

//タイプ
#define PLAYER			(0)		//トリパイロット
#define ENEMY1			(1)		//ハネテキ
#define ENEMY2			(2)		//ハコテキ
#define ENEMY3			(3)		//金のテキ
#define ENEMY4			(4)		//ハーピィ
#define BULLETS_P		(5)		//トリ弾
#define BULLETS_E		(6)		//テキ弾
//オブジェクト数調整用
#define ENEMY_TOTAL		(7)		//テキ総数
#define OBJECT_TYPE_MAX	(8)		//オブジェクトタイプの数

//スコア
#define SCORE_ENEMY1	(100)	//ハネテキ
#define SCORE_ENEMY2	(200)	//ハコテキ
#define SCORE_ENEMY3	(500)	//金のテキ
#define SCORE_ENEMY4	(-100)	//ハーピィ
#define SCORE_BULLET_E	(-200)	//テキ弾

//ゲームオブジェクト基底クラス
class GameObject
{
protected:
	class Scene* MyScene;
	
protected:
	int object_type;		//オブジェクトのタイプ

	Vector2D location;		//位置座標
	Vector2D box_size;		//矩形の大きさ
	double radian;			//向き
	int image;				//画像
	int sound;				//再生する音源
	bool flip_flag;			//反転フラグ
	bool anime_flag;		//アニメフラグ
	bool delete_flag;		//削除フラグ
	int alpha;				//アルファ値

public:
	GameObject();				//コンストラクタ
	virtual ~GameObject();		//デストラクタ

	virtual void Initialize();		//初期化処理
	virtual void Update();			//更新処理
	virtual void Draw() const;		//描画処理
	virtual void Finalize();		//終了時処理

	//オブジェクトタイプ取得処理
	int GetObjectType()const;

	//当たり判定通知処理
	virtual bool OnHitCollision(GameObject* hit_object);

	//矩形情報取得処理
	Vector2D GetBoxSize() const;

	//位置情報取得処理
	Vector2D GetLocation() const;

	//位置情報変更処理
	void SetLocation(const Vector2D& location);

	//反転フラグ変更処理
	void SetFlipFlag(bool flip);

	//アニメフラグ変更処理
	void SetAnimeFlag(bool anime);

	//削除フラグ変更処理
	void SetDeleteFlag(bool del);

public:
	//シーン情報設定処理
	void SetMyScene(class Scene* scene);
};