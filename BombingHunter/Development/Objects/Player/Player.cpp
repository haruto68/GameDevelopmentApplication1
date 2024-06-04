#include"Player.h"
#include"../../Utility/InputControl.h"
#include"../../Utility/UserTemplate.h"
#include"DxLib.h"

//コンストラクタ
Player::Player() :animation_count(0)
{
	animation[0] = NULL;
	animation[1] = NULL;
	
	speed = 1.5f;
	velocity = 0.0f;
}

//デストラクタ
Player::~Player()
{

}

//初期化処理
void Player::Initialize()
{
	//オブジェクトタイプの設定
	object_type = PLAYER;

	//画像の読み込み
	animation[0] = LoadGraph("Resource/Images/トリパイロット/飛ぶ1.png");
	animation[1] = LoadGraph("Resource/Images/トリパイロット/飛ぶ2.png");

	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("トリパイロットの画像がありません\n");
	}

	//向きの設定
	radian = 0.0;

	//大きさの設定
	box_size = 64.0;

	//初期画像の設定
	image = animation[0];
}

//更新処理
void Player::Update()
{
	//移動処理
	Movement();
	//アニメーション制御
	AnimationControl();

	
}

//描画処理
void Player::Draw() const
{
	//プレイヤー画像の描画
	DrawRotaGraphF(location.x, location.y, OBJECTSIZE, radian, image, TRUE, flip_flag);

	//デバッグ用
#if _DEBUG
	//当たり判定の可視化
	Vector2D ul = location - (box_size / 2.0f);		//box_collision_upper_left   =  ul  =  左上
	Vector2D lr = location + (box_size / 2.0f);		//box_collision_lower_right  =  lr  =  右下

	DrawBoxAA(ul.x, ul.y, lr.x, lr.y, GetColor(255, 0, 0), FALSE);
#endif
}

//終了時処理
void Player::Finalize()
{
	//使用した画像を解放する
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

//当たり判定通知処理
bool Player::OnHitCollision(GameObject* hit_object)
{
	//当たった時の処理
	return FALSE;
}

//移動処理
void Player::Movement()
{
	//入力状態によって向きを変更する
	float direction = 0.0f;
	if (InputControl::GetKey(KEY_INPUT_LEFT) || InputControl::GetKey(KEY_INPUT_A))			//左移動
	{
		direction -= speed;
		flip_flag = TRUE;
	}
	else if (InputControl::GetKey(KEY_INPUT_RIGHT) || InputControl::GetKey(KEY_INPUT_D))	//右移動
	{
		direction += speed;
		flip_flag = FALSE;
	}

	//向きによって、移動量の加減を行う
	if (direction != 0.0f)
	{
		//最高速度を超えないようにする
		float max_speed = Abs<float>((5.0f * 0.5 * direction));
		velocity.x += float(0.3 * direction);
		velocity.x = Min<float>(Max<float>(velocity.x, -max_speed), max_speed);
	}
	else
	{
		//減速する
		if (velocity.x < -1e-6f)		//-1e-6f = (0に限りなく近い負の値)
		{
			//左移動の減速
			float calc_speed = velocity.x + 0.1f;
			velocity.x = Min<float>(calc_speed, 0.0f);
		}
		else if (velocity.x > 1e-6f)	//1e-6f = (0に限りなく近い正の値)
		{
			//右移動の減速
			float cale_spped = velocity.x - 0.1f;
			velocity.x = Max<float>(cale_spped, 0.0f);
		}
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

	//位置座標を加速度分変える
	location += velocity;
}

//アニメーション制御
void Player::AnimationControl()
{
	//フレームカウントを加算する
	animation_count++;

	//60フレーム目に到達したら
	if (animation_count >= 60)
	{
		//カウントのリセット
		animation_count = 0;

		//画像の切り替え
		if (image == animation[0])
		{
			image = animation[1];
		}
		else
		{
			image = animation[0];
		}
	}
}