#pragma once

#include<vector>
#include<string>
#include"../Objects/Object.h"

#define ObjectSize	(0.7)	//オブジェクトのサイズ倍率

class Scene
{
private:
protected:
	std::vector<GameObject*> objects;
	std::vector<GameObject*> trash;

public:
	Scene();
	~Scene();

	void Initialize();
	void Update();
	void Draw() const;
	void Finalize();

private:
	//当たり判定チェック処理
	bool HitCheckObject(GameObject* a, GameObject* b);

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

		//初期化処理
		new_object->Initialize();

		//位置情報の設定
		new_object->SetLocation(location);

		//反転情報の設定
		new_object->SetFlipFlag(flip);


		//シーンの情報を持たせる
		new_object->SetMySceneA(this);

		

		//オブジェクトリストに追加
		objects.push_back(new_object);

		//インスタンスのポインタを返却
		return new_instance;
	}
};