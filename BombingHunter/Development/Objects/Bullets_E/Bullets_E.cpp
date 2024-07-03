#include"Bullets_E.h"
#include"DxLib.h"
#include"../../Utility/UserTemplate.h"

//コンストラクタ
Bullets_E::Bullets_E() :
	animation(),
	animation_count(0),
	speed(1.0),
	velocity(0.0),
	p_l(0.0),
	save(0.0)
{
	animation[0] = NULL;
	animation[1] = NULL;
	animation[2] = NULL;
	animation[3] = NULL;
}

//デストラクタ
Bullets_E::~Bullets_E()
{

}

//初期化処理
void Bullets_E::Initialize()
{
	//オブジェクトタイプの設定
	object_type = BULLETS_E;

	//画像の読み込み
	animation[0] = LoadGraph("Resource/Images/Bullets/Enemy/0.png");
	animation[1] = LoadGraph("Resource/Images/Bullets/Enemy/1.png");
	animation[2] = LoadGraph("Resource/Images/Bullets/Enemy/2.png");
	animation[3] = LoadGraph("Resource/Images/Bullets/Enemy/3.png");

	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1 || animation[2] == -1 || animation[3] == -1)
	{
		throw("テキ弾の画像がありません\n");
	}

	//向きの設定
	radian = 0;

	//大きさの設定
	box_size = 30.0;

	//初期画像の設定
	image = animation[0];

	//スピードの設定
	speed = 1.5;

	//プレイヤー座標取得
	p_l = MyScene->GetPlayerLocation();
}

//更新処理
void Bullets_E::Update()
{
	//移動処理
	if (image == animation[0])
	{
		Movement();
	}
	//アニメーション制御
	if (anime_flag == TRUE)
	{
		AnimationControl();
	}
}

//描画処理
void Bullets_E::Draw()const
{
	//テキ弾画像の描画
	DrawRotaGraphF(location.x, location.y, OBJECTSIZE, radian, image, TRUE, FALSE);

	//デバッグ用
#if _DEBUG
	//当たり判定の可視化
	Vector2D ul = location - (box_size / 2.0f);		//box_collision_upper_left   =  ul  =  左上
	Vector2D lr = location + (box_size / 2.0f);		//box_collision_lower_right  =  lr  =  右下

	DrawBoxAA(ul.x, ul.y, lr.x, lr.y, GetColor(255, 0, 0), FALSE);
#endif
}

//終了時処理
void Bullets_E::Finalize()
{
	//使用した画像を開放する
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
	DeleteGraph(animation[2]);
	DeleteGraph(animation[3]);
}

//当たり判定通知処理
bool Bullets_E::OnHitCollision(GameObject* hit_object)
{
	bool value = FALSE;

	int type = hit_object->GetObjectType();

	switch (type)
	{
	case PLAYER:
		break;
	default:
		break;
	}

	return value;
}

//移動処理
void Bullets_E::Movement()
{
	//正規化
	velocity = Tracking(location, p_l);

	velocity *= speed;

	if (location.y > p_l.y)
	{
		location += velocity;
		save = velocity;
	}
	else
	{
		location += save;
	}
}

//アニメーション制御
void Bullets_E::AnimationControl()
{
	//フレームカウントを加算する
	animation_count++;

	//12フレーム目に到達したら
	if (animation_count >= 12)
	{
		if (delete_flag == TRUE)
		{
			DiscardObject(this);
		}

		//カウントのリセット
		animation_count = 0;

		//画像の切り替え
		if (image == animation[0])
		{
			image = animation[1];
		}
		else if (image == animation[1])
		{
			image = animation[2];
		}
		else if (image == animation[2])
		{
			image = animation[3];
			delete_flag = TRUE;
		}
	}
}

//追尾処理
Vector2D Bullets_E::Tracking(Vector2D A, Vector2D B)
{
	Vector2D velocity;	//加速度
	float distance;		//距離

	velocity.x = A.x - B.x;
	velocity.y = A.y - B.y;

	distance = sqrt(pow(velocity.x, 2.0) + pow(velocity.y, 2.0));

	velocity.x /= distance;
	velocity.y /= distance;

	velocity *= -1;

	return velocity;
}