#pragma once

#include "../GameObject.h"
#include"DxLib.h"
#include"../../Utility/InputManager.h"
#include"../Player/Player.h"
#include"../../Scenes/InGame/InGameScene.h"

#define	SECONDS	(1200)	//1秒当たりのだいたいのフレーム数

class EnemyBase : public GameObject
{
protected:
	// 進行方向状態
	enum eDirectionState : unsigned char
	{
		UP,
		RIGHT,
		DOWN,
		LEFT,
		NONE,
	};

	//挙動状態
	enum eBhaviorState : unsigned char
	{
		TERRITORY,
		TRACKING,
		WARP,
		RETURNING,
		RELEASE,
	};

protected:
	std::vector<int> move_animation;		//移動のアニメーション画像
	std::vector<int> eye_animation;			//目のアニメーション画像
	int image[2];							//画像

	Vector2D velocity;						//移動量
	eBhaviorState behavior_state;			//挙動状態
	eDirectionState direction;				//進行方向状態

	eDirectionState old_direction;			//過去進行方向状態
	bool direction_change_flag;				//進行方向変更フラグ

	Vector2D player_location;				//プレイヤー座標

	int point;								//通った分岐点
	Vector2D branch_points[65];				//分岐点
	int branch_pattern[65];					//分岐パターン	

	float animation_count;					//アニメーション添字
	float behaivor_count;					//挙動添字
	
	bool is_izike;							//いじけ状態
	bool old_izike;							//過去いじけ状態
	int izike_count;						//いじけ添字
	bool power_down_flag;					//パワーダウンフラグ

	float delta_second_copy;				//Utrunで使う

	bool home;								//巣
	bool go;								//出

public:
	EnemyBase();
	virtual ~EnemyBase();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;

	/// <summary>
	/// 当たり判定通知処理
	/// </summary>
	/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
	virtual void OnHitCollision(GameObjectBase* hit_object) override;

	//プレイヤー座標設定処理
	void SetPlayerLocation(Vector2D location);

	//挙動状態カウント処理
	void CountBhavior();

	//いじけ状態設定処理
	void SetIzike();
	//いじけ時間カウント処理
	void CountIzike();
	//いじけ状態取得処理
	bool GetIzike();
	//
	bool GetPowerDownFlag();

private:
	/// <summary>
	/// 移動処理
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	void Movement(float delta_second);

	/// <summary>
	/// アニメーション制御
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	void AnimationControl(float delta_second);



	//進行方向決定処理(ランダム)
	void DecisionDirectionRandom();

public:
	//進行方向決定処理(逃亡)
	void DecisionDirectionEscape();

	//進行方向決定処理(巣)
	void DecisionDirectionHome();

	//Uターン処理
	void Uturn();
};