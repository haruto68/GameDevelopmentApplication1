#pragma once

#include<vector>
#include<string>
#include"../Objects/GameObject.h"

#define ObjectSize	(0.7)	//オブジェクトのサイズ倍率

#define BAD			(1)
#define OK			(2)
#define GOOD		(3)
#define Perfect		(4)

class Scene
{
private:
protected:
	std::vector<GameObject*> objects;	//マイナンバー
	std::vector<GameObject*> trash;		//デスノート

	std::vector<Vector2D> factory;		//工場	オブジェクトタイプの指定ができない

	int bg_image;		//背景画像
	int ti_image;		//タイトル画像
	int he_image[7];	//ヘルプ画像
	int ui_image[3];	//UI画像
	int ev_image[5];	//評価画像
	int numbers[10];	//数字画像

	int bgm[2];			//BGM
	int se_ev[5];		//評価SE
	int se_en[5];		//テキSE
	int se_bu[5];		//弾SE

	int timelimit;		//制限時間
	int flame;			//フレーム
	int score;			//スコア
	int highscore;		//ハイスコア
	int evaluation;		//評価
	bool gamemain;		//ゲームメイン
	bool gameend;		//ゲームエンド
	bool gamehelp;		//ゲームヘルプ
	bool se_ev_check;	//評価SEチェック

public:
	Scene();
	~Scene();

	void Initialize();
	void Update();
	void Draw();
	void Finalize();

	//オブジェクト創造処理
	void Creation();

	//オブジェクト破壊処理
	void destruction();

	//trashに入れる処理
	void InsertTrash(GameObject* garbage);

	//factoryに入れる処理
	void InsertFactory(Vector2D product);

	//プレイヤー座標取得処理
	Vector2D GetPlayerLocation();

	//制限時間カウント処理
	void TimeLimitCount();

	//指定した位の数字を1桁で返す処理
	int OneDigit(int num, int digit);

	//スコア加算処理
	void GetScore(int value);

private:
	//当たり判定チェック処理
	bool HitCheckObject(GameObject* a, GameObject* b);

public:
	//オブジェクト生成処理
	template<class T>
	T* CreateObject(const Vector2D& location, bool flip)
	{
		//指定したクラスを生成する
		T* new_instance = new T();
		//GameObjectクラスを継承しているか確認
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		//エラーチェック
		if (new_object == nullptr)
		{
			delete new_instance;
			throw std::string("ゲームオブジェクトが生成できませんでした");
		}


		//シーンの情報を持たせる
		new_object->SetMyScene(this);


		//初期化処理
		new_object->Initialize();

		//位置情報の設定
		new_object->SetLocation(location);

		//反転情報の設定
		new_object->SetFlipFlag(flip);

		//オブジェクトリストに追加
		objects.push_back(new_object);

		//インスタンスのポインタを返却
		return new_instance;
	}
};