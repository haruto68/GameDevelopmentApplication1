#include"Bullets_P.h"
#include"../Player/Player.h"
#include"../../Utility/InputControl.h"
#include"../../Utility/UserTemplate.h"
#include"DxLib.h"
#include"math.h"

#define π	(3.141592653589793)	//円周率

//コンストラクタ
Bullets_P::Bullets_P() :
	animation(),
	animation_count(0),
	speed(0.0),
	velocity(0.0)
{
	animation[0] = NULL;
	animation[1] = NULL;
	animation[2] = NULL;
	animation[3] = NULL;
}

//デストラクタ
Bullets_P::~Bullets_P()
{

}

//初期化処理
void Bullets_P::Initialize()
{
	//オブジェクトタイプの設定
	object_type = BULLETS_P;

	//画像の読み込み
	animation[0] = LoadGraph("Resource/Images/Bullets/Player/0.png");
	animation[1] = LoadGraph("Resource/Images/Bullets/Player/1.png");
	animation[2] = LoadGraph("Resource/Images/Bullets/Player/2.png");
	animation[3] = LoadGraph("Resource/Images/Bullets/Player/3.png");

	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1 || animation[2] == -1 || animation[3] == -1)
	{
		throw("トリ弾の画像がありません\n");
	}

	//向きの設定
	radian = π / 2;

	//大きさの設定
	box_size = 48.0;

	//初期画像の設定
	image = animation[0];

	//スピードの設定
	speed = 1.0;

	//弾に(疑似的に)慣性をつける
	if ((InputControl::GetKey(KEY_INPUT_LEFT) || InputControl::GetKey(KEY_INPUT_A)) == FALSE &&	//左入力がない
		(InputControl::GetKey(KEY_INPUT_RIGHT) || InputControl::GetKey(KEY_INPUT_D)) == FALSE)	//右入力がない
	{
		velocity.x = 0.0;
	}
	if ((InputControl::GetKey(KEY_INPUT_LEFT) || InputControl::GetKey(KEY_INPUT_A)) == TRUE &&	//左入力がある
		(InputControl::GetKey(KEY_INPUT_RIGHT) || InputControl::GetKey(KEY_INPUT_D)) == FALSE)	//右入力がない
	{
		velocity.x -= 3.0;
	}
	if ((InputControl::GetKey(KEY_INPUT_LEFT) || InputControl::GetKey(KEY_INPUT_A)) == FALSE &&	//左入力がない
		(InputControl::GetKey(KEY_INPUT_RIGHT) || InputControl::GetKey(KEY_INPUT_D)) == TRUE)	//右入力がある
	{
		velocity.x += 3.0;
	}
}

//更新処理
void Bullets_P::Update()
{
	//移動処理
	if(anime_flag ==  FALSE)
	{
		Movement();
	}
	//アニメーション制御
	if (anime_flag == TRUE)
	{
		AnimationControl();
	}
	//地面着地
	if (location.y >= 420)
	{
		anime_flag = TRUE;
	}

}

//描画処理
void Bullets_P::Draw()const
{
	//トリ弾画像の描画
	DrawRotaGraphF(location.x, location.y, OBJECTSIZE, radian + (-velocity.x / 2), image, TRUE, FALSE);

	//デバッグ用
#if _DEBUG
	//当たり判定の可視化
	Vector2D ul = location - (box_size / 2.0f);		//box_collision_upper_left   =  ul  =  左上
	Vector2D lr = location + (box_size / 2.0f);		//box_collision_lower_right  =  lr  =  右下

	DrawBoxAA(ul.x, ul.y, lr.x, lr.y, GetColor(255, 0, 0), FALSE);
#endif
}

//終了時処理
void Bullets_P::Finalize()
{
	//使用した画像を開放する
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
	DeleteGraph(animation[2]);
	DeleteGraph(animation[3]);
}

//当たり判定通知処理
bool Bullets_P::OnHitCollision(GameObject* hit_object)
{
	bool value = FALSE;

	int type = hit_object->GetObjectType();

	switch (type)
	{
	case PLAYER:
		break;
	case BULLETS_P:
		break;
	case BULLETS_E:
		break;
	default:
		hit_object->SetAnimeFlag(TRUE);
		break;
	}

	return value;
}

//移動処理
void Bullets_P::Movement()
{
	//最高速度を超えないようにする
	float max_speed = Abs<float>((5.0f * 0.5 * speed));
	velocity.y += float(0.3 * speed);
	velocity.y = Min<float>(Max<float>(velocity.y, -max_speed), max_speed);
	
	//減速する
	if (velocity.x < -1e-6f)		//-1e-6f = (0に限りなく近い負の値)
	{
		//左移動の減速
		float calc_speed = velocity.x + 0.02f;
		velocity.x = Min<float>(calc_speed, 0.0f);
	}
	else if (velocity.x > 1e-6f)	//1e-6f = (0に限りなく近い正の値)
	{
		//右移動の減速
		float cale_spped = velocity.x - 0.02f;
		velocity.x = Max<float>(cale_spped, 0.0f);
	}

	//壁の衝突チェック
	if (location.x < (box_size.x / 2.0f))
	{
		//左壁
		velocity.x = 0.0f;
		location.x = box_size.x / 2.0f;
	}
	else if (location.x > (640.0f - box_size.x / 2.0f))
	{
		//右壁
		velocity.x = 0.0f;
		location.x = 640.0f - box_size.x / 2.0f;
	}

	location += velocity;
}

//アニメーション制御
void Bullets_P::AnimationControl()
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
			box_size = 30.0f;
			location.x = location.x - (velocity.x * 10);
			location.y = location.y - (velocity.y * 10);
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