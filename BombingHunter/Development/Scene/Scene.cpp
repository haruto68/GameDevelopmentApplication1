#include"DxLib.h"
#include"Scene.h"
#include"../Objects/Player/Player.h"
#include"../Objects/Enemy1/Enemy1.h"
#include"../Objects/Enemy2/Enemy2.h"
#include"../Objects/Enemy3/Enemy3.h"
#include"../Objects/Enemy4/Enemy4.h"
#include"../Objects/Bullets_P/Bullets_P.h"
#include"../Objects/Bullets_E/Bullets_E.h"
#include"../Utility/InputControl.h"

#define D_PIVOT_CENTER

//コンストラクタ
Scene::Scene() : objects()
{

}

//デストラクタ
Scene::~Scene()
{
	//忘れ防止
	Finalize();
}

//初期化処理
void Scene::Initialize()
{
	//プレイヤーを生成する
	CreateObject<Player>(Vector2D(320.0f, 50.0f), FALSE);
}

//更新処理
void Scene::Update()
{
	//シーンに存在するオブジェクトの更新処理
	for (GameObject* obj : objects)
	{
		obj->Update();
	}

	//オブジェクトタイプごとのカウント
	int type_count[OBJECT_TYPE_MAX] = {};
	for (GameObject* obj : objects)
	{
		int type = obj->GetObjectType();
		type_count[type]++;
	}
	type_count[ENEMY_TOTAL] = type_count[ENEMY1] + type_count[ENEMY2] + type_count[ENEMY3] + type_count[ENEMY4];
	
	//テキの生成
	if (type_count[ENEMY_TOTAL] < 2)
	{
		int random_e = GetRand(0);			//テキ乱数
		int random_x = GetRand(1);			//X座標乱数
		int random_y = GetRand(3);			//Y座標乱数
		int Y = 170 + (random_y * 85);

		switch (random_e)
		{
		case 0:	//ハネテキ
			if (random_x == 0)
			{
				CreateObject<Enemy1>(Vector2D(0.0f, Y), FALSE);
			}
			else
			{
				CreateObject<Enemy1>(Vector2D(640.0f, Y), TRUE);
			}
			break;
		case 1:	//ハコテキ
			if (random_x == 0)
			{
				CreateObject<Enemy2>(Vector2D(0.0f, Y), FALSE);
			}
			else
			{
				CreateObject<Enemy2>(Vector2D(640.0f, Y), TRUE);
			}
			break;
		case 2:	//金のテキ
			if (random_x == 0)
			{
				CreateObject<Enemy3>(Vector2D(0.0f, Y), FALSE);
			}
			else
			{
				CreateObject<Enemy3>(Vector2D(640.0f, Y), TRUE);
			}
			break;
		case 3:	//ハーピィ
			if (random_x == 0)
			{
				CreateObject<Enemy4>(Vector2D(0.0f, Y), FALSE);
			}
			else
			{
				CreateObject<Enemy4>(Vector2D(640.0f, Y), TRUE);
			}
			break;
		default:
			break;
		}
	}

	//Playerの情報取得
	Vector2D p_l = 0.0;	//座標
	p_l = objects[0]->GetLocation();

	//トリ弾発射
	if (InputControl::GetKeyDown(KEY_INPUT_SPACE) == TRUE)
	{
		CreateObject<Bullets_P>(Vector2D(p_l.x, p_l.y), TRUE);
	}

	//画面外にでたオブジェクトの削除
	int i = 0;	//ループカウンタ
	for (GameObject* obj : objects)
	{
		Vector2D loc = obj->GetLocation();
		if (loc.x < -60.0 || 700.0 < loc.x || loc.y < -60.0 || 520.0 < loc.y)
		{
			objects.erase(objects.begin() + i);
			obj->Finalize();
			delete obj;
		}
		i++;
	}

	////当たり判定チェック処理
	//int a = 0;
	//for (GameObject* obj_a : objects)
	//{
	//	int b = 0;
	//	for (GameObject* obj_b : objects)
	//	{
	//		//オブジェクトの削除可否判定
	//		bool delete_a = FALSE;
	//		bool delete_b = FALSE;
	//		
	//		/*delete_b,*/ delete_a = HitCheckObject(obj_a, obj_b);
	//		//delete_b = HitCheckObject(obj_b, obj_a);

	//		//オブジェクトの削除
	//		if (delete_a == TRUE)
	//		{
	//			objects.erase(objects.begin() + a);
	//			obj_a->Finalize();
	//			delete obj_a;

	//			//trash.push_back(obj_a);
	//		}

	//		//
	//		if (delete_a ==TRUE)
	//		{
	//			objects.erase(objects.begin() + b);
	//			obj_b->Finalize();
	//			delete obj_b;
	//		}

	//		/*bool del = FALSE;

	//		del = HitCheckObject(obj_a, obj_b);
	//		if (del == TRUE)
	//		{
	//			objects.erase(objects.begin() + a);
	//			objects[a]->Finalize();
	//			delete objects[a];
	//		}*/

	//		b++;
	//	}
	//	a++;
	//}

	for (int a = 0; a < objects.size(); a++)
	{
		for (int b = 0; b < objects.size(); b++)
		{
			bool del = FALSE;
			del = HitCheckObject(objects[a], objects[b]);

			if (del == TRUE)
			{
				objects.erase(objects.begin() + a);
				objects[a]->Finalize();
				delete objects[a];
			}
		}
	}

	int z = 0;
	for (GameObject* tra : trash)
	{
		trash.erase(trash.begin() + z);
		tra->Finalize();
		delete tra;

		z++;
	}
}

//描画処理
void Scene::Draw() const
{
	//シーンに存在するオブジェクトの描画処理
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
	
	SetFontSize(50);
	DrawFormatString(0, 0, 0xffffff, "%d", objects.size());
}

//終了時処理
void Scene::Finalize()
{
	//動的配列が空なら処理を終了する
	if (objects.empty())
	{
		return;
	}
	if (trash.empty())
	{
		return;
	}

	//各オブジェクトを削除する
	for (GameObject* obj : objects)
	{
		obj->Finalize();
		delete obj;
	}
	for (GameObject* tra : trash)
	{
		tra->Finalize();
		delete tra;
	}

	//動的配列の解放
	objects.clear();
	trash.clear();
}

//D_PIVOT_CENTERがあれば上の処理、なければ下の処理
#ifdef D_PIVOT_CENTER

//当たり判定チェック処理（矩形の中心で当たり判定をとる）①距離を使用する方法
bool Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//bool del_a = FALSE;
	//bool del_b = FALSE;
	bool del = FALSE;

	//2つのオブジェクトの距離を取得
	Vector2D diff = a->GetLocation() - b->GetLocation();

	//2つのオブジェクトの当たり判定の大きさを取得
	Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;

	//距離より大きさが大きい場合、Hit判定とする
	if ((fabs(diff.x) < box_size.x) && (fabs(diff.y) < box_size.y))
	{
		//当たったことをオブジェクトに通知する
		//del_a = a->OnHitCollision(b);
		//del_b = b->OnHitCollision(a);

		del = a->OnHitCollision(b);
	}
	return (/*del_a, del_b*/del);
}

#else

//当たり判定チェック処理（左上頂点の座標から当たり判定計算を行う）②編の位置関係を使用する方法
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//右下頂点座標を取得する
	Vector2D a_lower_right = a->GetLocation() + a->GetBoxSize();
	Vector2D b_lower_right = b->GetLocation() + b->GetBoxSize();

	//矩形Aと矩形Bの位置関係を調べる
	if ((a->GetLocation().x < b_lower_right.x) &&
		(a->GetLocation().y < b_lower_right.y) &&
		(a_lower_right.x > b->GetLocation().x) &&
		(a_lower_right.y > b->GetLocation().y))
	{
		//オブジェクトに対してHit判定を通知する
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}

#endif // D_PIVOT_CENTER