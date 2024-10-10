#include"Akabei.h"
#include"../../../Utility/ResourceManager.h"
#include"DxLib.h"

Akabei::Akabei()
{

}

Akabei::~Akabei()
{

}

void Akabei::Initialize()
{
	image[0] = move_animation[0];


	collision.is_blocking = true;
	collision.object_type = eObjectType::enemy;
	collision.hit_object_type.push_back(eObjectType::player);
	collision.radius = (D_OBJECT_SIZE - 1.0f) / 2.0f;

	z_layer = 5;

	mobility = eMobilityType::Movable;
}

void Akabei::Update(float delta_second)
{
	//アニメーション制御
	AnimationControl();
	old_direction = direction;
	//パネル情報がBRANCHでないなら 進行方向変更フラグをTRUEにする
	if (StageData::GetPanelData(location) != BRANCH)
	{
		old_direction = direction;
		direction_change_flag = TRUE;
	}

	//パネル情報がBRANCH かつ 進行方向変更フラグがTRUE なら進行方向を変える
	//if (StageData::GetPanelData(location) == ePanelID::BRANCH && direction_change_flag == TRUE)
	if (direction_change_flag == TRUE)
	{
		//進行方向決定
		DecisionDirection();

		//進行方向が変わっていれば進行方向変更フラグをFALSEにする
		if (old_direction != direction)
		{
			direction_change_flag = FALSE;
		}
	}

	//親クラスの更新処理を呼び出す
	__super::Update(delta_second);

	//仮の処理↓
	InputManager* input = InputManager::GetInstance();
	//巡回と追跡の切替
	if (input->GetKeyDown(KEY_INPUT_T))
	{
		if (behavior_state == TERRITORY)
		{
			behavior_state = TRACKING;
		}
		else
		{
			behavior_state = TERRITORY;
		}
	}
	//いじけ状態へ切り替え
	if (input->GetKeyDown(KEY_INPUT_I))
	{
		if (is_izike == FALSE)
		{
			is_izike = TRUE;
		}
		image[0] = move_animation[16];
	}

	

	//
	if (input->GetKeyDown(KEY_INPUT_R))
	{
		if (is_izike == TRUE)
		{
			behavior_state = RETURNING;
		}
		
	}
}

void Akabei::Draw(const Vector2D& screen_offset) const
{
	// 親クラスの描画処理を呼び出す
	__super::Draw(screen_offset);

	//変数チェック
	DrawFormatString(300, 10, 0xffffff, "x: %.1f\ny: %.1f", location.x, location.y);
	/*DrawFormatString(300, 50, 0xffffff, "   %d   %d", direction, point);
	DrawFormatString(270, 50, 0xffffff, "%d", direction_change_flag);
	DrawFormatString(400, 50, 0xffffff, "%d", branch_pattern[point]);*/

	if (is_izike)
	{
		DrawFormatString(300, 50, 0xffffff, "is_izike");
	}
	else
	{
		DrawFormatString(300, 50, 0xffffff, "no_izike");
	}
	
	if (behavior_state == eBhaviorState::TERRITORY)
	{
		DrawFormatString(500, 50, 0xffffff, "TERRITORY");
	}
	else if (behavior_state == eBhaviorState::TRACKING)
	{
		DrawFormatString(500, 50, 0xffffff, "TRACKING");
	}
	else
	{
		DrawFormatString(500, 50, 0xffffff, "RETURNING");
	}
}

void Akabei::Finalize()
{
	// 動的配列の解放
	move_animation.clear();
	eye_animation.clear();
}

void Akabei::AnimationControl()
{
	animation_count++;
	if (animation_count > (SECONDS * 0.2))	//240 = 0.2秒くらい
	{
		animation_count = 0;

		if (is_izike == FALSE)
		{
			//通常
			if (image[0] == move_animation[0])
			{
				image[0] = move_animation[1];
			}
			else
			{
				image[0] = move_animation[0];
			}
		}
		else
		{
			//いじけ
			if (image[0] == move_animation[16])
			{
				image[0] = move_animation[17];
			}
			else
			{
				image[0] = move_animation[16];
			}
		}
	}

	bool blink = FALSE;
	//点滅
	if (izike_count > ((SECONDS * 6) - (SECONDS * 2.0)))
	{
		if (izike_count > ((SECONDS * 6) - (SECONDS * 2.0)) && izike_count < ((SECONDS * 6) - (SECONDS * 1.8)))
		{
			blink = TRUE;
		}
		else if (izike_count > ((SECONDS * 6) - (SECONDS * 1.6)) && izike_count < ((SECONDS * 6) - (SECONDS * 1.4)))
		{
			blink = TRUE;
		}
		else if (izike_count > ((SECONDS * 6) - (SECONDS * 1.2)) && izike_count < ((SECONDS * 6) - (SECONDS * 1.0)))
		{
			blink = TRUE;
		}
		else if (izike_count > ((SECONDS * 6) - (SECONDS * 0.8)) && izike_count < ((SECONDS * 6) - (SECONDS * 0.6)))
		{
			blink = TRUE;
		}
		else if (izike_count > ((SECONDS * 6) - (SECONDS * 0.4)) && izike_count < ((SECONDS * 6) - (SECONDS * 0.2)))
		{
			blink = TRUE;
		}
		blink = TRUE;
	}
	if (blink == TRUE)
	{
		if (image[0] == move_animation[16])
		{
			image[0] = move_animation[18];
		}
		/*else
		{
			image[0] = move_animation[19];
		}*/
	}

	if (behavior_state == RETURNING)
	{
		image[0] = 0;
	}
}

void Akabei::DecisionDirection()
{
	point = 0;

	//分岐点チェック
	for (int i = 1; i < 65; i++)
	{
		if ((location.x <= (branch_points[i].x + 0.2) && location.x >= (branch_points[i].x - 0.2))	//X座標
			&&
			(location.y <= (branch_points[i].y + 0.2) && location.y >= (branch_points[i].y - 0.2)))	//Y座標
		{
			point = i;
			break;
		}
	}

	//状態ごとの処理
	switch (behavior_state)
	{
	case EnemyBase::TERRITORY:
		Territory();
		break;
	case EnemyBase::TRACKING:
		Tracking();
		break;
	case EnemyBase::WARP:
		break;
	case EnemyBase::RETURNING:
		Returning();
		break;
	case EnemyBase::RELEASE:
		break;
	default:
		break;
	}

	//いじけ状態処理
	if(is_izike && !home)
	{
		DecisionDirectionEscape();
	}

	//曲がり角処理
	switch (branch_pattern[point])
	{
	case 5:
		if (direction == eDirectionState::DOWN)
		{
			direction = eDirectionState::RIGHT;
			break;
		}
		else if (direction == eDirectionState::LEFT)
		{
			direction = eDirectionState::UP;
			break;
		}
		break;
	case 6:
		if (direction == eDirectionState::UP)
		{
			direction = eDirectionState::RIGHT;
			break;
		}
		else if (direction == eDirectionState::LEFT)
		{
			direction = eDirectionState::DOWN;
			break;
		}
		break;
	case 7:
		if (direction == eDirectionState::UP)
		{
			direction = eDirectionState::LEFT;
			break;
		}
		else if (direction == eDirectionState::RIGHT)
		{
			direction = eDirectionState::DOWN;
			break;
		}
		break;
	case 8:
		if (direction == eDirectionState::DOWN)
		{
			direction = eDirectionState::LEFT;
			break;
		}
		else if (direction == eDirectionState::RIGHT)
		{
			direction = eDirectionState::UP;
			break;
		}
		break;
	default:
		break;
	}
}

//縄張り巡回処理
void Akabei::Territory()
{
	//縄張りとの距離
	Vector2D outside = 0.0f;
	outside.x = 371.5f - location.x;
	outside.y = location.y - 204.5f;
	//xとyの優先度
	char X_or_Y = 'Z';
	if ((abs(outside.x) - abs(outside.y)) > 0.0f)
	{
		X_or_Y = 'X';	//X優先
	}
	else
	{
		X_or_Y = 'Y';	//Y優先
	}
	//2択確率
	int choices = GetRand(1);
	//直進確率
	int straight = GetRand(8);

	//縄張りに戻る
	if (outside.x > 0.0f || outside.y > 0.0f)
	{
		switch (branch_pattern[point])
		{
		case 9:
			switch (old_direction)
			{
			case eDirectionState::UP:
				if (outside.x > 0)
				{
					direction = eDirectionState::RIGHT;
				}
				break;
			case eDirectionState::RIGHT:
				if (outside.y > 0)
				{
					direction = eDirectionState::UP;
				}
				break;
			case eDirectionState::DOWN:
				if (X_or_Y == 'X')
				{
					direction = eDirectionState::RIGHT;
					break;
				}
				else
				{
					direction = eDirectionState::LEFT;
					break;
				}
				break;
			case eDirectionState::LEFT:
				direction = eDirectionState::UP;
				break;
			default:
				break;
			}
			break;
		case 1:
			if (old_direction == eDirectionState::UP)
			{
				direction = eDirectionState::RIGHT;
				break;
			}
			else if (old_direction == eDirectionState::LEFT && outside.y < 0.0f)
			{
				direction = eDirectionState::DOWN;
				break;
			}
			break;
		case 2:
			if (old_direction == eDirectionState::RIGHT)
			{
				direction = eDirectionState::UP;
				break;
			}
			else if (old_direction == eDirectionState::DOWN)
			{
				direction = eDirectionState::LEFT;
				break;
			}
			break;
		case 3:
			if (old_direction == eDirectionState::LEFT)
			{
				direction = eDirectionState::UP;
				break;
			}
			else if (old_direction == eDirectionState::DOWN)
			{
				direction = eDirectionState::RIGHT;
				break;
			}
			else if (outside.y > 0)
			{
				direction = eDirectionState::UP;
				break;
			}
			break;
		case 4:
			if (old_direction != eDirectionState::LEFT)
			{
				direction = eDirectionState::RIGHT;
				break;
			}
			else
			{
				direction = eDirectionState::UP;
				break;
			}
			break;
		default:
			break;
		}
	}

	//縄張り巡回
	switch (point)
	{
	case 5:
		if (direction == eDirectionState::UP)
		{
			if (choices)
			{
				direction = eDirectionState::LEFT;
			}
			else
			{
				direction = eDirectionState::RIGHT;
			}
			break;
		}
		else if (direction == eDirectionState::LEFT || direction == eDirectionState::RIGHT)
		{
			if (!straight)
			{
				direction = eDirectionState::DOWN;
			}
			break;
		}
		break;
	case 11:
		if (direction == eDirectionState::DOWN)
		{
			direction = eDirectionState::RIGHT;
			break;
		}
		else if (direction == eDirectionState::LEFT)
		{
			direction = eDirectionState::UP;
			break;
		}
		else if(choices)
		{
			direction = eDirectionState::UP;
			break;
		}
		break;
	case 12:
		if (direction == eDirectionState::UP)
		{
			if (choices)
			{
				direction = eDirectionState::LEFT;
			}
			else
			{
				direction = eDirectionState::RIGHT;
			}
		}
		break;
	case 13:
		if (!straight)
		{
			if (direction == eDirectionState::UP || direction == eDirectionState::DOWN)
			{
				if (choices)
				{
					direction = eDirectionState::RIGHT;
					break;
				}
				else
				{
					direction = eDirectionState::LEFT;
					break;
				}
			}
			else
			{
				if (choices)
				{
					direction = eDirectionState::UP;
					break;
				}
				else
				{
					direction = eDirectionState::DOWN;
					break;
				}
			}
		}
		break;
	case 14:
		if (direction == eDirectionState::RIGHT)
		{
			if (choices)
			{
				direction = eDirectionState::UP;
			}
			else
			{
				direction = eDirectionState::DOWN;
			}
			break;
		}
		else if (direction == eDirectionState::UP || direction == eDirectionState::DOWN)
		{
			if (!straight)
			{
				direction = eDirectionState::LEFT;
			}
			break;
		}
		break;
	case 21:
		if (direction == eDirectionState::DOWN)
		{
			direction = eDirectionState::RIGHT;
			break;
		}
		else if (direction == eDirectionState::LEFT)
		{
			direction = eDirectionState::UP;
			break;
		}
		else if (choices)
		{
			direction = eDirectionState::RIGHT;
			break;
		}
		break;
	default:
		break;
	}
}

//プレイヤー追跡処理
void Akabei::Tracking()
{
	//プレイヤーとの距離を算出
	Vector2D distance;
	distance.x = player_location.x - location.x;
	distance.y = player_location.y - location.y;
	//xとyの優先度
	char X_or_Y = 'Z';
	if ((abs(distance.x) - abs(distance.y)) > 0.0f)
	{
		X_or_Y = 'X';	//X優先
	}
	else
	{
		X_or_Y = 'Y';	//Y優先
	}
	//左右の優先度
	char L_or_R = 'N';
	if (distance.x < 0.0f)
	{
		L_or_R = 'L';	//左
	}
	else
	{
		L_or_R = 'R';	//右
	}
	//上下の優先度
	char U_or_D = 'N';
	if (distance.y < 0.0f)
	{
		U_or_D = 'U';	//上
	}
	else
	{
		U_or_D = 'D';	//下
	}

	//進行方向決定処理
	switch (branch_pattern[point])
	{
	case 9:
		switch (old_direction)
		{
		case eDirectionState::UP:
			if (X_or_Y == 'X')
			{
				if (L_or_R == 'L')
				{
					direction = eDirectionState::LEFT;
					break;
				}
				else
				{
					direction = eDirectionState::RIGHT;
					break;
				}
				break;
			}
			else if (U_or_D == 'D')
			{
				if (L_or_R == 'L')
				{
					direction = eDirectionState::LEFT;
					break;
				}
				else
				{
					direction = eDirectionState::RIGHT;
					break;
				}
				break;
			}
			break;
		case eDirectionState::RIGHT:
			if (X_or_Y == 'X')
			{
				if (L_or_R == 'L')
				{
					if (U_or_D == 'U')
					{
						direction = eDirectionState::UP;
						break;
					}
					else
					{
						direction = eDirectionState::DOWN;
						break;
					}
					break;
				}
				break;
			}
			else if (U_or_D == 'U')
			{
				direction = eDirectionState::UP;
				break;
			}
			else
			{
				direction = eDirectionState::DOWN;
				break;
			}
			break;
		case eDirectionState::DOWN:
			if (X_or_Y == 'X')
			{
				if (L_or_R == 'L')
				{
					direction = eDirectionState::LEFT;
					break;
				}
				else
				{
					direction = eDirectionState::RIGHT;
					break;
				}
				break;
			}
			else if (U_or_D == 'U')
			{
				if (L_or_R == 'L')
				{
					direction = eDirectionState::LEFT;
					break;
				}
				else
				{
					direction = eDirectionState::RIGHT;
					break;
				}
				break;
			}
			break;
		case eDirectionState::LEFT:
			if (X_or_Y == 'X')
			{
				if (L_or_R == 'R')
				{
					if (U_or_D == 'U')
					{
						direction = eDirectionState::UP;
						break;
					}
					else
					{
						direction = eDirectionState::DOWN;
						break;
					}
					break;
				}
				break;
			}
			else if (U_or_D == 'U')
			{
				direction = eDirectionState::UP;
				break;
			}
			else
			{
				direction = eDirectionState::DOWN;
				break;
			}
			break;

		default:
			break;
		}	
		case 1:
			if (old_direction == eDirectionState::UP)
			{
				if (L_or_R == 'L')
				{
					direction = eDirectionState::LEFT;
					break;
				}
				else
				{
					direction = eDirectionState::RIGHT;
					break;
				}
				break;
			}
			else if (X_or_Y == 'Y' && U_or_D == 'D')
			{
				direction = eDirectionState::DOWN;
				break;
			}
			break;
		case 2:
			if (old_direction == eDirectionState::RIGHT)
			{
				if (U_or_D == 'U')
				{
					direction = eDirectionState::UP;
					break;
				}
				else
				{
					direction = eDirectionState::DOWN;
					break;
				}
				break;
			}
			else if (X_or_Y == 'X' && L_or_R == 'L')
			{
				direction = eDirectionState::LEFT;
				break;
			}
			break;
		case 3:
			if (old_direction == eDirectionState::DOWN)
			{
				if (L_or_R == 'L')
				{
					direction = eDirectionState::LEFT;
					break;
				}
				else
				{
					direction = eDirectionState::RIGHT;
					break;
				}
				break;
			}
			else if (X_or_Y == 'Y' && U_or_D == 'U')
			{
				direction = eDirectionState::UP;
				break;
			}
			break;
		case 4:
			if (old_direction == eDirectionState::LEFT)
			{
				if (U_or_D == 'U')
				{
					direction = eDirectionState::UP;
					break;
				}
				else
				{
					direction = eDirectionState::DOWN;
					break;
				}
				break;
			}
			else if (X_or_Y == 'X' && L_or_R == 'R')
			{
				direction = eDirectionState::RIGHT;
				break;
			}
			break;
		default:
			break;
	}
}

//帰巣
void Akabei::Returning()
{
	//巣座標（入口）
	Vector2D nest = Vector2D(336.0f, 276.0f);

	//巣との距離
	Vector2D distance;
	distance.x = nest.x - location.x;
	distance.y = nest.y - location.y;

	//xとyの優先度
	char X_or_Y = 'Z';
	if ((abs(distance.x) - abs(distance.y)) > 0.0f)
	{
		X_or_Y = 'X';	//X優先
	}
	else
	{
		X_or_Y = 'Y';	//Y優先
	}
	//左右の優先度
	char L_or_R = 'N';
	if (distance.x < 0.0f)
	{
		L_or_R = 'L';	//左
	}
	else
	{
		L_or_R = 'R';	//右
	}
	//上下の優先度
	char U_or_D = 'N';
	if (distance.y < 0.0f)
	{
		U_or_D = 'U';	//上
	}
	else
	{
		U_or_D = 'D';	//下
	}

	//帰巣処理
	switch (branch_pattern[point])
	{
	case 9:
		switch (old_direction)
		{
		case eDirectionState::UP:
			if (X_or_Y == 'X')
			{
				if (L_or_R == 'L')
				{
					direction = eDirectionState::LEFT;
					break;
				}
				else
				{
					direction = eDirectionState::RIGHT;
					break;
				}
				break;
			}
			else if (U_or_D == 'D')
			{
				if (L_or_R == 'L')
				{
					direction = eDirectionState::LEFT;
					break;
				}
				else
				{
					direction = eDirectionState::RIGHT;
					break;
				}
				break;
			}
			break;
		case eDirectionState::RIGHT:
			if (X_or_Y == 'X')
			{
				if (L_or_R == 'L')
				{
					if (U_or_D == 'U')
					{
						direction = eDirectionState::UP;
						break;
					}
					else
					{
						direction = eDirectionState::DOWN;
						break;
					}
					break;
				}
				break;
			}
			else if (U_or_D == 'U')
			{
				direction = eDirectionState::UP;
				break;
			}
			else
			{
				direction = eDirectionState::DOWN;
				break;
			}
			break;
		case eDirectionState::DOWN:
			if (X_or_Y == 'X')
			{
				if (L_or_R == 'L')
				{
					direction = eDirectionState::LEFT;
					break;
				}
				else
				{
					direction = eDirectionState::RIGHT;
					break;
				}
				break;
			}
			else if (U_or_D == 'U')
			{
				if (L_or_R == 'L')
				{
					direction = eDirectionState::LEFT;
					break;
				}
				else
				{
					direction = eDirectionState::RIGHT;
					break;
				}
				break;
			}
			break;
		case eDirectionState::LEFT:
			if (X_or_Y == 'X')
			{
				if (L_or_R == 'R')
				{
					if (U_or_D == 'U')
					{
						direction = eDirectionState::UP;
						break;
					}
					else
					{
						direction = eDirectionState::DOWN;
						break;
					}
					break;
				}
				break;
			}
			else if (U_or_D == 'U')
			{
				direction = eDirectionState::UP;
				break;
			}
			else
			{
				direction = eDirectionState::DOWN;
				break;
			}
			break;

		default:
			break;
		}
	case 1:
		if (old_direction == eDirectionState::UP)
		{
			if (L_or_R == 'L')
			{
				direction = eDirectionState::LEFT;
				break;
			}
			else
			{
				direction = eDirectionState::RIGHT;
				break;
			}
			break;
		}
		else if (X_or_Y == 'Y' && U_or_D == 'D')
		{
			direction = eDirectionState::DOWN;
			break;
		}
		break;
	case 2:
		if (old_direction == eDirectionState::RIGHT)
		{
			if (U_or_D == 'U')
			{
				direction = eDirectionState::UP;
				break;
			}
			else
			{
				direction = eDirectionState::DOWN;
				break;
			}
			break;
		}
		else if (X_or_Y == 'X' && L_or_R == 'L')
		{
			direction = eDirectionState::LEFT;
			break;
		}
		break;
	case 3:
		if (old_direction == eDirectionState::DOWN)
		{
			if (L_or_R == 'L')
			{
				direction = eDirectionState::LEFT;
				break;
			}
			else
			{
				direction = eDirectionState::RIGHT;
				break;
			}
			break;
		}
		else if (X_or_Y == 'Y' && U_or_D == 'U')
		{
			direction = eDirectionState::UP;
			break;
		}
		break;
	case 4:
		if (old_direction == eDirectionState::LEFT)
		{
			if (U_or_D == 'U')
			{
				direction = eDirectionState::UP;
				break;
			}
			else
			{
				direction = eDirectionState::DOWN;
				break;
			}
			break;
		}
		else if (X_or_Y == 'X' && L_or_R == 'R')
		{
			direction = eDirectionState::RIGHT;
			break;
		}
		break;
	default:
		break;
	}

	//巣到着フラグ
	bool goal = FALSE;
	if (location.x >= 335.8f && location.x <= 336.2f && location.y >= 275.8f && location.y <= 276.2f)
	{
		goal = TRUE;
	}

	if (goal)
	{
		if(go == FALSE)
		{
			//巣に入る処理
			home = TRUE;
		}
		else
		{
			if (direction == eDirectionState::UP)
			{
				direction = eDirectionState::RIGHT;
				behavior_state = TRACKING;
			}
		}
	}

}