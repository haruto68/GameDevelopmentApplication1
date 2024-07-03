#include"GameObject.h"
#include"../Scene/Scene.h"
#include"DxLib.h"

//コンストラクタ
GameObject::GameObject() :
	location(0.0),
	box_size(0.0),
	radian(0.0),
	image(0),
	sound(0),
	flip_flag(FALSE),
	anime_flag(FALSE),
	delete_flag(FALSE),
	alpha(255),
	object_type(0),
	MyScene(nullptr)
{
	
}

//デストラクタ
GameObject::~GameObject()
{

}

//初期化処理
void GameObject::Initialize()
{

}

//更新処理
void GameObject::Update()
{

}

//描画処理
void GameObject::Draw() const
{

}

//終了時処理
void GameObject::Finalize()
{
	
}

//オブジェクトタイプ取得処理
int GameObject::GetObjectType()const
{
	return this->object_type;
}

//当たり判定通知処理
bool GameObject::OnHitCollision(GameObject* hit_object)
{
	//当たった時に行う処理
	return FALSE;
}

//矩形情報取得処理
Vector2D GameObject::GetBoxSize() const
{
	return this->box_size;
}

//位置情報取得処理
Vector2D GameObject::GetLocation() const
{
	return this->location;
}

//位置情報変更処理
void GameObject::SetLocation(const Vector2D& location)
{
	this->location = location;
}

//反転フラグ変更勝利
void GameObject::SetFlipFlag(bool flip)
{
	this->flip_flag = flip;
}

//アニメフラグ変更処理
void GameObject::SetAnimeFlag(bool anime)
{
	this->anime_flag = anime;
}

//削除フラグ変更処理
void GameObject::SetDeleteFlag(bool del)
{
	this->delete_flag = del;
}

//シーン情報設定処理
void GameObject::SetMyScene(Scene* scene)
{
	this->MyScene = scene;
}