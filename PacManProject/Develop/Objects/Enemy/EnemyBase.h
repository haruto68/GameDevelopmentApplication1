#pragma once

#include "../GameObject.h"

//エネミー状態
enum eEnemyState
{
	IDLE,		// 待機状態
	MOVE,		// 移動状態
	DIE,		// 死亡状態
};

class EnemyBase : public GameObject
{
protected:

private:
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

private:
	std::vector<int> move_animation;		// 移動のアニメーション画像
	std::vector<int> dying_animation;		// 死亡のアニメーション画像
	Vector2D velocity;						// 移動量
	eEnemyState enemy_state;				//エネミー状態
	eBhaviorState behavior_state;			//挙動状態
	eDirectionState now_direction;			//現在進行方向状態
	eDirectionState next_direction;			//次回進行方向状態
	float animation_time;					//アニメーション時間
	float animation_count;					//アニメーション添字
	float behaivor_time;					//挙動時間
	float behaivor_count;					//挙動添字

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

	/// <summary>
	/// エネミーの状態を取得する
	/// </summary>
	/// <returns>エネミーの状態</returns>
	eEnemyState GetEnemyState() const;

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
};