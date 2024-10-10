#include"Pinky.h"
#include"../../../Utility/ResourceManager.h"
#include"DxLib.h"

Pinky::Pinky()
{

}

Pinky::~Pinky()
{

}

void Pinky::Initialize()
{
	image[0] = move_animation[2];
}

void Pinky::Update(float delta_second)
{
	//親クラスの更新処理を呼び出す
	__super::Update(delta_second);
	//アニメーション制御
	AnimationControl();

	//パネル情報がBRANCHでないなら 進行方向変更フラグをTRUEにする
	if (StageData::GetPanelData(location) != BRANCH)
	{
		old_direction = direction;
		direction_change_flag = TRUE;
	}

	//パネル情報がBRANCH かつ 進行方向変更フラグがTRUE なら進行方向を変える
	if (StageData::GetPanelData(location) == ePanelID::BRANCH && direction_change_flag == TRUE)
	{
		//進行方向決定
		DecisionDirection();

		//進行方向が変わっていれば進行方向変更フラグをFALSEにする
		if (old_direction != direction)
		{
			direction_change_flag = FALSE;
		}
	}
}

void Pinky::Draw(const Vector2D& screen_offset) const
{
	// 親クラスの描画処理を呼び出す
	__super::Draw(screen_offset);

	//変数チェック
	/*DrawFormatString(300, 10, 0xffffff, "x: %.1f\ny: %.1f", location.x, location.y);
	DrawFormatString(300, 50, 0xffffff, "   %d   %d", direction, point);
	DrawFormatString(270, 50, 0xffffff, "%d", direction_change_flag);
	DrawFormatString(400, 50, 0xffffff, "%d", branch_pattern[point]);*/
}

void Pinky::Finalize()
{
	// 動的配列の解放
	move_animation.clear();
	eye_animation.clear();
}

void Pinky::AnimationControl()
{
	animation_count++;
	if (animation_count > 240)
	{
		animation_count = 0;
		if (image[0] == move_animation[2])
		{
			image[0] = move_animation[3];
		}
		else
		{
			image[0] = move_animation[2];
		}
	}
}

void Pinky::DecisionDirection()
{

}