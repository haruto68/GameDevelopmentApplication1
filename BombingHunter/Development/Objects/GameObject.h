#pragma once

#include"../Utility//Vector2D.h"
//#include"../Scene/Scene.h"
//#include"Object.h"

#define OBJECTSIZE		(0.7)	//オブジェクトのサイズ倍率

#define PLAYER			(0)		//トリパイロット
#define ENEMY1			(1)		//ハネテキ
#define ENEMY2			(2)		//ハコテキ
#define ENEMY3			(3)		//金のテキ
#define ENEMY4			(4)		//ハーピィ
#define BULLETS_P		(5)		//トリ弾
#define BULLETS_E		(6)		//テキ弾
#define ENEMY_TOTAL		(7)		//テキ総数
#define OBJECT_TYPE_MAX	(8)		//オブジェクトタイプの数

//ゲームオブジェクト基底クラス
class GameObject /*: public Scene*/
{
protected:
	class Scene* MyScene;

	int object_type;		//オブジェクトのタイプ

	Vector2D location;		//位置座標
	Vector2D box_size;		//矩形の大きさ
	double radian;			//向き
	int image;				//画像
	int sound;				//再生する音源
	bool flip_flag;			//反転フラグ

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

	//反転情報変更処理
	void SetFlipFlag(bool flip);



public:
	void SetMySceneA(class Scene* scene)
	{
		MyScene = scene;

		
	}
};