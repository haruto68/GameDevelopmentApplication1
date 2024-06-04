#include"Scene.h"
#include"DxLib.h"

#include"../Objects/Player/Player.h"
#include"../Objects/Enemy1/Enemy1.h"

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
	CreateObject<Player>(Vector2D(320.0f, 80.0f));

	//ハネテキを生成する
	//CreateObject<Enemy1>(Vector2D(0.0f, 400.0f));

	float random_x = GetRand(2) % 2;

	if (random_x == 0)
	{
		CreateObject<Enemy1>(Vector2D(0.0f, 200.0f));
	}
	else
	{
		CreateObject<Enemy1>(Vector2D(0.0f, 400.0f));
	}
}

//更新処理
void Scene::Update()
{
	//シーンに存在するオブジェクトの更新処理
	for (GameObject* obj : objects)
	{
		obj->Update();
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
}

//終了時処理
void Scene::Finalize()
{
	//動的配列が空なら処理を終了する
	if (objects.empty())
	{
		return;
	}

	//各オブジェクトを削除する
	for (GameObject* obj : objects)
	{
		obj->Finalize();
		delete obj;
	}

	//動的配列の解放
	objects.clear();
}