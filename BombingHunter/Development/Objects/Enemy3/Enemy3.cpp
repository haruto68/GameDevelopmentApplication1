#include"Enemy3.h"
#include"DxLib.h"

//コンストラクタ
Enemy3::Enemy3() :
	animation_count(0),
	animation_count2(0),
	box_size(0.0)
{
	animation[0] = NULL;
	animation[1] = NULL;
	animation[2] = NULL;
	animation[3] = NULL;
	animation[4] = NULL;

	speed = float(GetRand(2) + 1);
}

//デストラクタ
Enemy3::~Enemy3()
{

}

//初期化処理
void Enemy3::Initialize()
{
	//オブジェクトタイプの設定
	object_type = ENEMY3;

	//画像の読み込み
	animation[0] = LoadGraph("Resource/images/Enemy/gold/1.png");
	animation[1] = LoadGraph("Resource/images/Enemy/gold/2.png");
	animation[2] = LoadGraph("Resource/images/Enemy/gold/3.png");
	animation[3] = LoadGraph("Resource/images/Enemy/gold/4.png");
	animation[4] = LoadGraph("Resource/images/Enemy/gold/5.png");

	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1 || animation[2] == -1 || animation[3] == -1 || animation[4] == -1)
	{
		throw("金のテキの画像がありません\n");
	}

	//向きの設定
	radian = 0.0;

	//大きさの設定
	box_size = 48.0;

	//初期画像の設定
	image = animation[0];
}

//更新処理
void Enemy3::Update()
{
	//移動処理
	if (anime_flag == FALSE)
	{
		Movement();
	}
	//アニメーション制御
	AnimationControl();
	
}

//描画処理
void Enemy3::Draw() const
{
	//ハネテキ画像の描画
	if (anime_flag)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawRotaGraphF(location.x, location.y, OBJECTSIZE, radian, image, TRUE, flip_flag);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
	}
	else
	{
		DrawRotaGraphF(location.x, location.y, OBJECTSIZE, radian, image, TRUE, flip_flag);
	}

	//デバッグ用
#if _DEBUG
	//当たり判定の可視化
	Vector2D ul = location - (Vector2D(1.0f) * (float)box_size / 2.0f);
	Vector2D br = location + (Vector2D(1.0f) * (float)box_size / 2.0f);

	DrawBoxAA(ul.x, ul.y, br.x, br.y, GetColor(255, 0, 0), FALSE);
#endif
}

//終了時処理
void Enemy3::Finalize()
{
	//使用した画像を解放する
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
	DeleteGraph(animation[2]);
	DeleteGraph(animation[3]);
	DeleteGraph(animation[4]);
}

//当たり判定通知処理
bool Enemy3::OnHitCollision(GameObject* hit_object)
{
	bool value = FALSE;

	int type = hit_object->GetObjectType();

	if (type == BULLETS_P && anime_flag == FALSE)
	{
		hit_object->SetAnimeFlag(TRUE);
	}

	return value;
}

//移動処理
void Enemy3::Movement()
{
	//移動の速さ
	Vector2D velocity = 0.0f;

	//左右移動

	if (flip_flag == TRUE)
	{
		velocity.x -= speed;
	}
	else
	{
		velocity.x += speed;
	}

	//現在の位置座標に速さを加算する
	location += velocity;
}

//アニメーション制御
void Enemy3::AnimationControl()
{
	if (anime_flag == FALSE)
	{
		//フレームカウントを加算する
		animation_count++;

		//12フレーム目に到達したら
		if (animation_count >= 12)
		{
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
			}
			else if (image == animation[3])
			{
				image = animation[4];
			}
			else if (image == animation[4])
			{
				image = animation[0];
			}
		}
	}
	else
	{
		//フレームカウントを加算する
		animation_count2++;
		alpha -= 4;

		//60フレーム目に到達したら
		if (animation_count2 < 60)
		{
			location.y += 0.3f;
		}
		if (alpha <= 0)
		{
			DiscardObject(this);
		}
	}
}