#include "EnemyBase.h"
#include "stdio.h"
#include"../../Scenes/SceneBase.h"
#include"../../Utility/ResourceManager.h"

EnemyBase::EnemyBase() :
	move_animation(),
	eye_animation(),
	image{},
	velocity(0.0f),
	behavior_state(eBhaviorState::TRACKING),
	direction(eDirectionState::RIGHT),
	old_direction(eDirectionState::RIGHT),
	direction_change_flag(FALSE),
	player_location(),
	point(0),
	branch_points{},
	branch_pattern{},
	animation_count(0),
	behaivor_count(0),
	is_izike(FALSE),
	old_izike(FALSE),
	izike_count(0),
	power_down_flag(FALSE),
	delta_second_copy(0.0),
	home(FALSE),
	go(FALSE)
{
	//ファイルオープン
	FILE* fp = nullptr;

	fopen_s(&fp, "Resource/Map/branchpoints.csv", "r");

	for (int i = 1; i < 65; i++)
	{
		fscanf_s(fp, "%f,%f,%d", &branch_points[i].x, &branch_points[i].y, &branch_pattern[i]);
	}

	fclose(fp);

	// アニメーション画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	move_animation = rm->GetImages("Resource/Images/monster.png", 20, 20, 1, 32, 32);
	eye_animation = rm->GetImages("Resource/Images/eyes.png", 4, 4, 1, 32, 32);
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Initialize()
{
}

void EnemyBase::Update(float delta_second)
{
	delta_second_copy = delta_second;
	//挙動状態カウント処理
	CountBhavior();
	//いじけ時間カウント処理
	CountIzike();
	// 移動処理
	Movement(delta_second);
	// アニメーション制御
	AnimationControl(delta_second);
}

void EnemyBase::Draw(const Vector2D& screen_offset) const
{
	// オフセット値を基に画像の描画を行う
	Vector2D graph_location = this->location + screen_offset;
	DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, image[0], TRUE);
	if(is_izike == FALSE)
	{
		DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, image[1], TRUE);
	}
	if (behavior_state == RETURNING)
	{
		DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, image[1], TRUE);
	}

	//変数チェック
	int x = 0;
	if(x == 1)
	{
		DrawBox(100, 200, 600, 700, 0xffffff, TRUE);
		for (int i = 1; i < 33; i++)
		{
			DrawFormatString(120, (200 + i * 15), 0x000000, "%2d   %3.f    %3.f   %d", i, branch_points[i].x, branch_points[i].y, branch_pattern[i]);
		}
		for (int i = 33; i < 65; i++)
		{
			DrawFormatString(370, (200 + (i - 32) * 15), 0x000000, "%2d   %3.f    %3.f   %d", i, branch_points[i].x, branch_points[i].y, branch_pattern[i]);
		}
	}
	else if (x == 2)
	{
		DrawBox(100, 200, 600, 700, 0xffffff, TRUE);
		DrawFormatString(300, 450, 0x000000, "%.1f\n%.1f", player_location.x, player_location.y);
	}
	else if (x == 3)
	{
		DrawBox(100, 200, 600, 700, 0xffffff, TRUE);
		DrawFormatString(300, 450, 0x000000, "%d", behavior_state);
	}
}

void EnemyBase::Finalize()
{
	move_animation.clear();
	eye_animation.clear();
}

void EnemyBase::OnHitCollision(GameObjectBase* hit_object)
{
	if (hit_object->GetCollision().object_type == eObjectType::player)
	{
		if (is_izike == TRUE)
		{
			behavior_state = RETURNING;
		}
	}
}

void EnemyBase::SetPlayerLocation(Vector2D location)
{
	player_location = location;
}

void EnemyBase::CountBhavior()
{
	if(behavior_state==TERRITORY || behavior_state==TRACKING)
	{
		behaivor_count++;
	}
	if (behavior_state == eBhaviorState::TERRITORY)
	{
		if (behaivor_count > (SECONDS * 4.5))
		{
			behaivor_count = 0;
			behavior_state = eBhaviorState::TRACKING;

			Uturn();
		}
	}
	else
	{
		if (behaivor_count > (SECONDS * 15))
		{
			behaivor_count = 0;
			behavior_state = eBhaviorState::TERRITORY;

			Uturn();
		}
	}
}

void EnemyBase::SetIzike()
{
	is_izike = TRUE;
	image[0] = move_animation[16];
}

void EnemyBase::CountIzike()
{
	if (old_izike != is_izike)
	{
		Uturn();
	}
	if(is_izike)
	{
		izike_count++;
	}
	if (izike_count > (SECONDS * 6))
	{
		izike_count = 0;
		is_izike = FALSE;

		power_down_flag = TRUE;

		Uturn();
	}
	old_izike = is_izike;
}

bool EnemyBase::GetIzike()
{
	return is_izike;
}

bool EnemyBase::GetPowerDownFlag()
{
	if(power_down_flag)
	{
		power_down_flag = FALSE;
		return TRUE;
	}
	return FALSE;
}

void EnemyBase::Movement(float delta_second)
{
	velocity = 0.0f;

	//巣
	if (home)
	{
		DecisionDirectionHome();
	}

	//進行方向によって移動量を設定
	switch (direction)
	{
	case eDirectionState::UP:
		velocity.y = -1.0f;
		break;
	case eDirectionState::RIGHT:
		velocity.x = 1.0f;
		break;
	case eDirectionState::DOWN:
		velocity.y = 1.0f;
		break;
	case eDirectionState::LEFT:
		velocity.x = -1.0f;
		break;
	}
	
	////パネル情報がBRANCHでないなら 進行方向変更フラグをTRUEにする
	//if (StageData::GetPanelData(location) != BRANCH)
	//{
	//	old_direction = direction;
	//	direction_change_flag = TRUE;
	//}

	////パネル情報がBRANCH かつ 進行方向変更フラグがTRUE なら進行方向を変える
	//if (StageData::GetPanelData(location) == ePanelID::BRANCH && direction_change_flag == TRUE)
	//{
	//	//進行方向決定
	//	DecisionDirectionRandom();

	//	//進行方向が変わっていれば進行方向変更フラグをFALSEにする
	//	if (old_direction != direction)
	//	{
	//		direction_change_flag = FALSE;
	//	}
	//}


	//移動量を座標に加算
	if(is_izike == false)
	{
		location += (velocity * 50.0f * delta_second) * 1;
	}
	else
	{
		location += (velocity * 50.0f * delta_second) * 0.7;
	}

	if (behavior_state == RETURNING)
	{
		location += (velocity * 50.0f * delta_second) * 2.5;
	}


	//ワープ
	if (location.x <= 0.0f)
	{
		location.x = 641.9f;
	}
	if (location.x >= 642.0f)
	{
		location.x = 0.1f;
	}

	if (location.y <= 0.0f)
	{
		location.y = 719.9f;
	}
	if (location.y >= 720.0f)
	{
		location.y = 0.1f;
	}
}

void EnemyBase::AnimationControl(float delta_second)
{
	switch (direction)
	{
	case eDirectionState::UP:
		image[1] = eye_animation[0];
		break;
	case eDirectionState::RIGHT:
		image[1] = eye_animation[1];
		break;
	case eDirectionState::DOWN:
		image[1] = eye_animation[2];
		break;
	case eDirectionState::LEFT:
		image[1] = eye_animation[3];
		break;
	case eDirectionState::NONE:
		break;
	default:
		break;
	}
}

//進行方向決定処理(ランダム)
void EnemyBase::DecisionDirectionRandom()
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


	//2択確率
	int choices = GetRand(1);
	//直進確率
	int straight = GetRand(5);

	//進行方向決定
	switch (branch_pattern[point])
	{
	case 9:
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

	case 1:
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

	case 2:
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

	case 3:
		if (direction == eDirectionState::DOWN)
		{
			if (choices)
			{
				direction = eDirectionState::RIGHT;
			}
			else
			{
				direction = eDirectionState::LEFT;
			}
			break;
		}
		else if (direction == eDirectionState::RIGHT || direction == eDirectionState::LEFT)
		{
			if (!straight)
			{
				direction = eDirectionState::UP;
			}
			break;
		}
		break;

	case 4:
		if (direction == eDirectionState::LEFT)
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
				direction = eDirectionState::RIGHT;
			}
			break;
		}
		break;

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

//進行方向決定処理(逃亡)
void EnemyBase::DecisionDirectionEscape()
{
	//プレイヤーとの距離を算出
	Vector2D distance;
	distance.x = player_location.x - location.x;
	distance.y = player_location.y - location.y;
	//xとyの優先度
	char X_or_Y = 'Z';
	if ((abs(distance.x) - abs(distance.y)) > 0.0f)
	{
		X_or_Y = 'Y';	//Y優先
	}
	else
	{
		X_or_Y = 'X';	//X優先
	}
	//左右の優先度
	char L_or_R = 'N';
	if (distance.x < 0.0f)
	{
		L_or_R = 'R';	//右
	}
	else
	{
		L_or_R = 'L';	//左
	}
	//上下の優先度
	char U_or_D = 'N';
	if (distance.y < 0.0f)
	{
		U_or_D = 'D';	//下
	}
	else
	{
		U_or_D = 'U';	//上
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

//進行方向決定処理(巣)
void EnemyBase::DecisionDirectionHome()
{
	
	if (location.y <= (324.0f - 0.0f) && go == FALSE)
	{
		direction = eDirectionState::DOWN;
	}
	if (location.y >= (372.0f + 0.0f))
	{
		direction = eDirectionState::UP;
		go = TRUE;
	}
}

//Uターン処理
void EnemyBase::Uturn()
{
	velocity = 0.0f;
	while (StageData::GetPanelData(location) == BRANCH)
	{
		switch (direction)
		{
		case eDirectionState::UP:
			velocity.y = -1.0f;
			break;
		case eDirectionState::RIGHT:
			velocity.x = 1.0f;
			break;
		case eDirectionState::DOWN:
			velocity.y = 1.0f;
			break;
		case eDirectionState::LEFT:
			velocity.x = -1.0f;
			break;
		}
		location += (velocity * 50.0f * delta_second_copy) * 5;
	}

	if (behavior_state != RETURNING)
	{
		switch (direction)
		{
		case eDirectionState::UP:
			direction = eDirectionState::DOWN;
			break;
		case eDirectionState::RIGHT:
			direction = eDirectionState::LEFT;
			break;
		case eDirectionState::DOWN:
			direction = eDirectionState::UP;
			break;
		case eDirectionState::LEFT:
			direction = eDirectionState::RIGHT;
			break;
		}
	}
}