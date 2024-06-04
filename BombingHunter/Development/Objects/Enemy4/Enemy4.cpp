#include"Enemy4.h"
#include"DxLib.h"

//コンストラクタ
Enemy4::Enemy4() :
	animation_count(0),
	box_size(0.0)
{
	animation[0] = NULL;
	animation[1] = NULL;

	speed = float(GetRand(2) + 1);
}

//デストラクタ
Enemy4::~Enemy4()
{

}

//初期化処理
void Enemy4::Initialize()
{
	//オブジェクトタイプの設定
	object_type = ENEMY4;

	//画像の読み込み
	animation[0] = LoadGraph("Resource/images/テキ/ハーピー1.png");
	animation[1] = LoadGraph("Resource/images/テキ/ハーピー2.png");

	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("ハネテキの画像がありません\n");
	}

	//向きの設定
	radian = 0.0;

	//大きさの設定
	box_size = 64.0;

	//初期画像の設定
	image = animation[0];
}

//更新処理
void Enemy4::Update()
{
	//移動処理
	Movement();
	//アニメーション制御
	AnimationControl();
}

//描画処理
void Enemy4::Draw() const
{
	//ハネテキ画像の描画
	DrawRotaGraphF(location.x, location.y, OBJECTSIZE, radian, image, TRUE, flip_flag);

	//デバッグ用
#if _DEBUG
	//当たり判定の可視化
	Vector2D ul = location - (Vector2D(1.0f) * (float)box_size / 2.0f);
	Vector2D br = location + (Vector2D(1.0f) * (float)box_size / 2.0f);

	DrawBoxAA(ul.x, ul.y, br.x, br.y, GetColor(255, 0, 0), FALSE);
#endif
}

//終了時処理
void Enemy4::Finalize()
{
	//使用した画像を解放する
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

//当たり判定通知処理
bool Enemy4::OnHitCollision(GameObject* hit_object)
{
	//当たった時の処理
	bool value = FALSE;
	int type = hit_object->GetObjectType();

	return value;
}

//移動処理
void Enemy4::Movement()
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
void Enemy4::AnimationControl()
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