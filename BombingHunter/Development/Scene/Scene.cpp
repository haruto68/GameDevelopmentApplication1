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
#define TIMELIMIT	(60)

//コンストラクタ
Scene::Scene() :
	objects(),
	factory(),
	trash(),
	bg_image(0),
	ti_image(0),
	he_image{},
	ui_image{},
	ev_image{},
	numbers{},
	bgm{},
	se_ev{},
	se_en{},
	se_bu{},
	timelimit(0),
	flame(0),
	score(0),
	highscore(0),
	evaluation(0),
	gamemain(FALSE),
	gameend(FALSE),
	gamehelp(FALSE),
	se_ev_check(FALSE)
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
	//画像取得処理
	//背景画像取得
	bg_image = LoadGraph("Resource/Images/UI/background.png");
	//タイトル画像取得
	ti_image = LoadGraph("Resource/Images/Player/1.png");
	//ヘルプ画像取得
	he_image[0] = LoadGraph("Resource/Images/Player/1.png");
	he_image[1] = LoadGraph("Resource/Images/Enemy/wing/1.png");
	he_image[2] = LoadGraph("Resource/Images/Enemy/box/1.png");
	he_image[3] = LoadGraph("Resource/Images/Enemy/gold/1.png");
	he_image[4] = LoadGraph("Resource/Images/Enemy/Harpy/1.png");
	he_image[5] = LoadGraph("Resource/Images/Bullets/Player/0.png");
	he_image[6] = LoadGraph("Resource/Images/Bullets/Enemy/0.png");
	//UI画像取得
	ui_image[0] = LoadGraph("Resource/Images/UI/timer.png");
	ui_image[1] = LoadGraph("Resource/Images/UI/score.png");
	ui_image[2] = LoadGraph("Resource/Images/UI/highscore.png");
	//評価画像取得
	ev_image[0] = LoadGraph("Resource/Images/Evaluation/0.png");
	ev_image[1] = LoadGraph("Resource/Images/Evaluation/1.png");
	ev_image[2] = LoadGraph("Resource/Images/Evaluation/2.png");
	ev_image[3] = LoadGraph("Resource/Images/Evaluation/3.png");
	ev_image[4] = LoadGraph("Resource/Images/Evaluation/4.png");
	//数字画像取得
	numbers[0] = LoadGraph("Resource/Images/Numbers/0.png");
	numbers[1] = LoadGraph("Resource/Images/Numbers/1.png");
	numbers[2] = LoadGraph("Resource/Images/Numbers/2.png");
	numbers[3] = LoadGraph("Resource/Images/Numbers/3.png");
	numbers[4] = LoadGraph("Resource/Images/Numbers/4.png");
	numbers[5] = LoadGraph("Resource/Images/Numbers/5.png");
	numbers[6] = LoadGraph("Resource/Images/Numbers/6.png");
	numbers[7] = LoadGraph("Resource/Images/Numbers/7.png");
	numbers[8] = LoadGraph("Resource/Images/Numbers/8.png");
	numbers[9] = LoadGraph("Resource/Images/Numbers/9.png");
	//エラーチェック
	if (bg_image == -1)
	{
		throw("背景の画像がありません\n");
	}
	if (ti_image == -1)
	{
		throw("タイトルの画像がありません\n");
	}
	if (he_image[0] == -1 || he_image[1] == -1 || he_image[2] == -1 || he_image[3] == -1 || he_image[4] == -1 || he_image[5] == -1 || he_image[6] == -1)
	{
		throw("ヘルプの画像がありません\n");
	}
	if (ui_image[0] == -1 || ui_image[1] == -1 || ui_image[2] == -1)
	{
		throw("UIの画像がありません\n");
	}
	if (ev_image[0] == -1 || ev_image[1] == -1 || ev_image[2] == -1 || ev_image[3] == -1 || ev_image[4] == -1)
	{
		throw("評価の画像がありません\n");
	}
	if (numbers[0] == -1 || numbers[1] == -1 || numbers[2] == -1 || numbers[3] == -1 || numbers[4] == -1 || numbers[5] == -1 || numbers[6] == -1 || numbers[7] == -1 || numbers[8] == -1 || numbers[9] == -1)
	{
		throw("数字の画像がありません\n");
	}

	//音声取得処理
	//BGM取得
	bgm[0] = LoadSoundMem("Resource/sounds/BGM/main.wav");
	bgm[1] = LoadSoundMem("Resource/sounds/BGM/timeup.wav");
	//評価SE取得
	se_ev[1] = LoadSoundMem("Resource/sounds/evaluation/bad.wav");
	se_ev[2] = LoadSoundMem("Resource/sounds/evaluation/ok.wav");
	se_ev[3] = LoadSoundMem("Resource/sounds/evaluation/good.wav");
	se_ev[4] = LoadSoundMem("Resource/sounds/evaluation/perfect.wav");
	//テキSE取得
	se_en[1] = LoadSoundMem("Resource/sounds/enemy/wing.wav");
	se_en[2] = LoadSoundMem("Resource/sounds/enemy/box.wav");
	se_en[3] = LoadSoundMem("Resource/sounds/enemy/gold.wav");
	se_en[4] = LoadSoundMem("Resource/sounds/enemy/Harpy.wav");
	//弾SE取得
	se_bu[1] = LoadSoundMem("Resource/sounds/bullets/Player/1.wav");
	se_bu[2] = LoadSoundMem("Resource/sounds/bullets/Player/2.wav");
	se_bu[3] = LoadSoundMem("Resource/sounds/bullets/Enemy/1.wav");
	se_bu[4] = LoadSoundMem("Resource/sounds/bullets/Enemy/2.wav");
	//エラーチェック
	if (bgm[0] == -1 || bgm[1] == -1)
	{
		throw("BGMがありません\n");
	}
	if (se_ev[0] == -1 || se_ev[1] == -1 || se_ev[2] == -1 || se_ev[3] == -1 || se_ev[4] == -1)
	{
		throw("評価のSEがありません\n");
	}
	if (se_en[0] == -1 || se_en[1] == -1 || se_en[2] == -1 || se_en[3] == -1 || se_en[4] == -1)
	{
		throw("テキのSEがありません\n");
	}
	if (se_bu[0] == -1 || se_bu[1] == -1 || se_bu[2] == -1 || se_bu[3] == -1 || se_bu[4] == -1)
	{
		throw("弾のSEがありません\n");
	}

	//音声調整
	ChangeVolumeSoundMem(150, se_bu[1]);

	//ハイスコア読み込み処理
	FILE* fp = nullptr;
	//ファイルオープン
	errno_t result = fopen_s(&fp, "Resource/data/highscore.csv", "r");

	//エラーチェック
	if (result != 0)
	{
		throw("Resource/data/highscore.csvが読み込めません\n");
	}

	//結果を読み込む
	fscanf_s(fp, "%6d", &highscore);

	//ファイルクローズ
	fclose(fp);

	PlaySoundMem(bgm[0], DX_PLAYTYPE_LOOP, TRUE);
}

//更新処理
void Scene::Update()
{
	

	//制限時間カウント処理
	TimeLimitCount();
	if (objects.size() == 0)
	{
		
	}

	//シーンに存在するオブジェクトの更新処理
	for (GameObject* obj : objects)
	{
		obj->Update();
	}

	//ゲームスタート
	if (InputControl::GetKeyDown(KEY_INPUT_RETURN) && objects.size() == 0 && gamehelp == FALSE)
	{
		StopSoundMem(bgm[1]);
		if(CheckSoundMem(bgm[0]) == FALSE)
		{
			PlaySoundMem(bgm[0], DX_PLAYTYPE_LOOP, TRUE);
		}
		
		gamemain = TRUE;
		timelimit = TIMELIMIT;
		evaluation = 0;
		score = 0;
	}

	//ゲームメイン
	if (gamemain == TRUE)
	{
		//プレイヤーを生成する
		if (objects.size() == 0)
		{
			CreateObject<Player>(Vector2D(320.0f, 50.0f), FALSE);
		}

		//オブジェクト創造処理
		Creation();

		//オブジェクト破壊処理
		destruction();

		//ゲームエンド
		if (timelimit < 0)
		{
			gamemain = FALSE;
			gameend = TRUE;
			StopSoundMem(bgm[0]);
			PlaySoundMem(bgm[1], DX_PLAYTYPE_LOOP, TRUE);
		}
	}

	//評価設定
	if (timelimit < -2)
	{
		if (score < 5000)
		{
			if (evaluation == 0)
			{
				PlaySoundMem(se_ev[1], DX_PLAYTYPE_BACK, TRUE);
			}
			evaluation = BAD;
			
		}
		else if (score < 7000)
		{
			if (evaluation == 0)
			{
				PlaySoundMem(se_ev[2], DX_PLAYTYPE_BACK, TRUE);
			}
			evaluation = OK;
			
		}
		else if (score < 10000)
		{
			if (evaluation == 0)
			{
				PlaySoundMem(se_ev[3], DX_PLAYTYPE_BACK, TRUE);
			}
			evaluation = GOOD;
			
		}
		else
		{
			if (evaluation == 0)
			{
				PlaySoundMem(se_ev[4], DX_PLAYTYPE_BACK, TRUE);
			}
			evaluation = Perfect;
			
		}

		//ハイスコア更新処理
		if (score > highscore)
		{
			highscore = score;

			//ハイスコア書き込み処理
			FILE* fp = nullptr;
			//ファイルオープン
			errno_t result = fopen_s(&fp, "Resource/data/highscore.csv", "w");

			//エラーチェック
			if (result != 0)
			{
				throw("Resource/data/highscore.csvが開けません\n");
			}

			//ハイスコアを保存
			fprintf(fp, "%6d,\n", highscore);

			//ファイルクローズ
			fclose(fp);
		}

		//オブジェクト全削除
		objects.clear();

		//タイトル画面へ戻る
		if (InputControl::GetKeyDown(KEY_INPUT_BACK))
		{
			gameend = FALSE;
			gamehelp = FALSE;
			StopSoundMem(bgm[1]);
			PlaySoundMem(bgm[0], DX_PLAYTYPE_LOOP, TRUE);
		}
	}

	//ヘルプ画面切り替え
	if (InputControl::GetKeyDown(KEY_INPUT_H))
	{
		if (gamehelp == FALSE)
		{
			gamehelp = TRUE;
		}
		else
		{
			gamehelp = FALSE;
		}
	}
}

//描画処理
void Scene::Draw()
{
	//背景描画
	DrawRotaGraphF(320, 240, OBJECTSIZE, 0, bg_image, TRUE, FALSE);

	//UI描画
	DrawRotaGraphF(15, 465, 0.5, 0, ui_image[0], TRUE, FALSE);
	DrawRotaGraphF(160, 465, 0.1, 0, ui_image[1], TRUE, FALSE);
	DrawRotaGraphF(420, 465, 0.175, 0, ui_image[2], TRUE, FALSE);

	//制限時間描画
	if (gamemain == TRUE)
	{
		DrawRotaGraphF(60, 465, 1.5, 0, numbers[OneDigit(timelimit, 2)], TRUE, FALSE);
		DrawRotaGraphF(80, 465, 1.5, 0, numbers[OneDigit(timelimit, 1)], TRUE, FALSE);
	}

	//スコア描画
	for (int i = 1; i <= 5; i++)
	{
		DrawRotaGraphF(340 - (i * 20), 465, 1.5, 0, numbers[OneDigit(score, i)], TRUE, FALSE);
	}

	//ハイスコア描画
	for (int i = 1; i <= 5; i++)
	{
		DrawRotaGraphF(620 - (i * 20), 465, 1.5, 0, numbers[OneDigit(highscore, i)], TRUE, FALSE);
	}
	
	//評価描画
	if (timelimit < 0 && gameend == TRUE)
	{
		DrawRotaGraphF(320, 240, OBJECTSIZE, 0, ev_image[evaluation], TRUE, FALSE);
	}
	if (timelimit < -4 && gameend == TRUE)
	{
		//DrawBox(120, 300, 520, 430, GetColor(0, 0, 0), TRUE);
		SetFontSize(30);
		DrawFormatString(130, 320, GetColor(0, 0, 0), "Enterキーでリスタート");
		DrawFormatString(90, 350, GetColor(0, 0, 0), "BackSPACEキーでタイトルへ戻る");
	}

	//ゲームメイン中なら描画する
	if (gamemain == TRUE)
	{
		//シーンに存在するオブジェクトの描画処理
		for (GameObject* obj : objects)
		{
			obj->Draw();
		}
	}

	//タイトル画面描画
	if (gamemain == FALSE && gameend == FALSE)
	{
		if(gamehelp == FALSE)
		{
			//タイトル表示
			SetFontSize(70);
			DrawFormatString(110, 50, GetColor(0, 0, 0), "爆撃ハンター");
			DrawRotaGraphF(80, 50, 1, -0.2, ti_image, TRUE, FALSE);
			//ゲーム案内表示
			SetFontSize(30);
			DrawFormatString(180, 220, GetColor(0, 0, 0), "Enterキーでスタート");
			DrawFormatString(180, 260, GetColor(0, 0, 0), "Hキーでヘルプを開く");
		}
		else
		{
			//ヘルプ画面表示
			DrawBox(70, 40, 570, 430, GetColor(0, 200, 50), TRUE);
			//操作説明
			SetFontSize(30);
			DrawRotaGraphF(130, 100, 0.5, 0, he_image[0], TRUE, FALSE);		//トリ
			DrawFormatString(180, 70, GetColor(0, 0, 0), "A・Dキー");
			DrawFormatString(180, 100, GetColor(0, 0, 0), "左右移動");
			DrawRotaGraphF(360, 100, 0.5, 1.57, he_image[5], TRUE, FALSE);	//トリ弾
			DrawFormatString(430, 70, GetColor(0, 0, 0), "Bキー");
			DrawFormatString(400, 100, GetColor(0, 0, 0), "爆弾発射");
			//ルール説明
			DrawRotaGraphF(150, 200, 0.5, 0, he_image[1], TRUE, FALSE);		//ハネテキ
			DrawFormatString(200, 185, GetColor(0, 0, 0), "+100pt");
			DrawRotaGraphF(160, 270, 0.5, 0, he_image[2], TRUE, FALSE);		//ハコテキ
			DrawFormatString(200, 255, GetColor(0, 0, 0), "+200pt");
			DrawRotaGraphF(155, 340, 0.5, 0, he_image[3], TRUE, FALSE);		//金のテキ
			DrawFormatString(200, 325, GetColor(0, 0, 0), "+500pt");
			DrawRotaGraphF(380, 200, 0.5, 0, he_image[4], TRUE, FALSE);		//ハーピー
			DrawFormatString(420, 185, GetColor(0, 0, 0), "-100pt");
			DrawRotaGraphF(385, 270, 0.5, 0, he_image[6], TRUE, FALSE);		//テキ弾
			DrawFormatString(420, 255, GetColor(0, 0, 0), "-200pt");
			//タイトルへ
			SetFontSize(30);
			DrawFormatString(160, 380, GetColor(0, 0, 0), "Hキーでヘルプを閉じる");
		}
	}
	
	//デバッグ用表示
	SetFontSize(40);
	bool a = 0;
	//オブジェクト数の表示
	if (a == 1)
	{
		int type_count[OBJECT_TYPE_MAX] = {};
		for (GameObject* obj : objects)
		{
			int type = obj->GetObjectType();
			type_count[type]++;
			type_count[7]++;
		}
		DrawFormatString(0, 0, 0xffffff, "PLY");
		DrawFormatString(0, 40, 0xffffff, "E_1");
		DrawFormatString(0, 80, 0xffffff, "E_2");
		DrawFormatString(0, 120, 0xffffff, "E_3");
		DrawFormatString(0, 160, 0xffffff, "E_4");
		DrawFormatString(0, 200, 0xffffff, "B_P");
		DrawFormatString(0, 240, 0xffffff, "B_E");
		DrawFormatString(0, 280, 0xffffff, "ALL");

		int y = 40;
		for (int i = 0; i < OBJECT_TYPE_MAX; i++)
		{
			DrawFormatString(90, y * i, 0xffffff, "%d", type_count[i]);
		}
	}
	//コンテナサイズの表示
	if(a == 2)
	{
		DrawFormatString(0, 0, 0xffffff, "%d", objects.size());
		DrawFormatString(0, 50, 0xffffff, "%d", factory.size());
		DrawFormatString(0, 100, 0xffffff, "%d", trash.size());
	}
}

//終了時処理
void Scene::Finalize()
{
	//画像の解放
	DeleteGraph(bg_image);
	DeleteGraph(ti_image);
	for (int i = 0; i < 7; i++)
	{
		DeleteGraph(he_image[i]);
	}
	for (int i = 0; i < 3; i++)
	{
		DeleteGraph(ui_image[i]);
	}
	for (int i = 0; i < 5; i++)
	{
		DeleteGraph(ev_image[i]);
	}
	for (int i = 0; i < 10; i++)
	{
		DeleteGraph(numbers[i]);
	}

	//音声の解放
	for (int i = 0; i < 2; i++)
	{
		DeleteSoundMem(bgm[i]);
	}
	for (int i = 0; i < 4; i++)
	{
		DeleteSoundMem(se_ev[i]);
	}
	for (int i = 0; i < 4; i++)
	{
		DeleteSoundMem(se_en[i]);
	}
	for (int i = 0; i < 4; i++)
	{
		DeleteSoundMem(se_bu[i]);
	}

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

	if (factory.empty())
	{
		return;
	}
	factory.clear();

	if (trash.empty())
	{
		return;
	}
	trash.clear();
}

//オブジェクト創造処理
void Scene::Creation()
{
	//オブジェクトタイプごとのカウント
	int type_count[OBJECT_TYPE_MAX] = {};
	for (GameObject* obj : objects)
	{
		int type = obj->GetObjectType();
		type_count[type]++;
	}
	type_count[ENEMY_TOTAL] = type_count[ENEMY1] + type_count[ENEMY2] + type_count[ENEMY3] + type_count[ENEMY4];

	//テキの生成
	if (type_count[ENEMY_TOTAL] < 5)
	{
		//テキ乱数
		int random_e = GetRand(3);
		//X座標乱数
		int random_x = GetRand(1);
		float X = 0; int flip = FALSE;
		if (random_x == 0)
		{
			X = 0.0f; flip = FALSE;		//→
		}
		else
		{
			X = 640.0f; flip = TRUE;	//←
		}
		//Y座標乱数
		int random_y = GetRand(2);
		float Y_t = 170 + (float)(random_y * 80);	//空
		float Y_b = 170 + (3 * 80);					//地



		int random = GetRand(100);

		if (random < 50)
		{
			random_e = 0;
		}
		else if (random < 75)
		{
			random_e = 1;
		}
		else if (random < 85)
		{
			random_e = 2;
		}
		else
		{
			random_e = 3;
		}
		



		switch (random_e)
		{
		case 0:	//ハネテキ
			CreateObject<Enemy1>(Vector2D(X, Y_t), flip);
			break;
		case 1:	//ハコテキ
			CreateObject<Enemy2>(Vector2D(X, Y_b), flip);
			break;
		case 2:	//金のテキ
			CreateObject<Enemy3>(Vector2D(X, Y_b), flip);
			break;
		case 3:	//ハーピィ
			CreateObject<Enemy4>(Vector2D(X, Y_t), flip);
			break;
		default:
			break;
		}
	}

	//Playerの情報取得
	Vector2D p_l = 0.0;	//座標
	p_l = objects[0]->GetLocation();

	//トリ弾発射
	if (InputControl::GetKeyDown(KEY_INPUT_B) == TRUE)
	{
		CreateObject<Bullets_P>(Vector2D(p_l.x, p_l.y), TRUE);
		PlaySoundMem(se_bu[1], DX_PLAYTYPE_BACK, TRUE);
		
	}

	//テキ弾発射
	for (Vector2D fac : factory)
	{
		if (type_count[BULLETS_E] <= 2)
		{
			CreateObject<Bullets_E>(fac, TRUE);
			PlaySoundMem(se_bu[3], DX_PLAYTYPE_BACK, TRUE);
		}
	}
}

//オブジェクト破壊処理
void Scene::destruction()
{
	//画面外にでたオブジェクトの削除
	int i = 0;	//ループカウンタ
	for (GameObject* obj : objects)
	{
		Vector2D loc = obj->GetLocation();
		if (loc.x < -60.0 || 700.0 < loc.x || loc.y < -60.0 || 600.0 < loc.y)
		{
			objects.erase(objects.begin() + i);
			obj->Finalize();
			delete obj;
		}
		i++;
	}

	//当たり判定チェック処理
	for (int a = 0; a < objects.size(); a++)
	{
		for (int b = 0; b < objects.size(); b++)
		{
			HitCheckObject(objects[a], objects[b]);
			HitCheckObject(objects[b], objects[a]);
		}
	}

	//trash内の削除
	int t = 0;
	for (GameObject* tra : trash)
	{
		int o = 0;
		for (GameObject* obj : objects)
		{
			if (tra == obj)
			{
				switch (obj->GetObjectType())
				{
				case ENEMY1:
					score += SCORE_ENEMY1;
					PlaySoundMem(se_en[1], DX_PLAYTYPE_BACK, TRUE);
					break;
				case ENEMY2:
					score += SCORE_ENEMY2;
					PlaySoundMem(se_en[2], DX_PLAYTYPE_BACK, TRUE);
					break;
				case ENEMY3:
					score += SCORE_ENEMY3;
					PlaySoundMem(se_en[3], DX_PLAYTYPE_BACK, TRUE);
					break;
				case ENEMY4:
					if(score >= -SCORE_ENEMY4)
					{
						score += SCORE_ENEMY4;
					}
					else
					{
						score = 0;
					}
					PlaySoundMem(se_en[4], DX_PLAYTYPE_BACK, TRUE);
					break;
				case BULLETS_P:
					PlaySoundMem(se_bu[2], DX_PLAYTYPE_BACK, TRUE);
					break;
				case BULLETS_E:
					if (score >= -SCORE_BULLET_E)
					{
						score += SCORE_BULLET_E;
					}
					else
					{
						score = 0;
					}
					PlaySoundMem(se_bu[4], DX_PLAYTYPE_BACK, TRUE);
				default:
					break;
				}
				
				objects.erase(objects.begin() + o);
				obj->Finalize();
				delete obj;
			}
			o++;
		}
		t++;
	}

	//factoryのリセット
	int ff = 0;
	for (Vector2D fac : factory)
	{
		factory.erase(factory.begin() + ff);
	}

	//trashのリセット
	int tt = 0;
	for (GameObject* tra : trash)
	{
		trash.erase(trash.begin() + tt);
	}
}

//trashに入れる処理
void Scene::InsertTrash(GameObject* garbage)
{
	trash.push_back(garbage);
}

//factoryに入れる処理
void Scene::InsertFactory(Vector2D product)
{
	factory.push_back(product);
}

//プレイヤー座標取得処理
Vector2D Scene::GetPlayerLocation()
{
	Vector2D location = objects[0]->GetLocation();

	return location;
}

//制限時間カウント処理
void Scene::TimeLimitCount()
{
	//フレームカウント
	flame++;

	//1秒経過したら
	if (flame >= 120)
	{
		timelimit--;

		//カウントリセット
		flame = 0;
	}
}

//指定した位の数字を1桁で返す処理
int Scene::OneDigit(int num, int digit)
{
	int value = 0;

	int remainder = pow(10, digit);
	int quotient = pow(10, digit - 1);


	value = (num % remainder) / quotient;

	if (digit !=1 && num < quotient)
	{
		return 10;
	}

	return value;
}

//スコア加算処理
void Scene::GetScore(int value)
{
	this->score += value;
}

//D_PIVOT_CENTERがあれば上の処理、なければ下の処理
#ifdef D_PIVOT_CENTER

//当たり判定チェック処理（矩形の中心で当たり判定をとる）①距離を使用する方法
bool Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	bool del = FALSE;

	//2つのオブジェクトの距離を取得
	Vector2D diff = a->GetLocation() - b->GetLocation();

	//2つのオブジェクトの当たり判定の大きさを取得
	Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;

	//距離より大きさが大きい場合、Hit判定とする
	if ((fabs(diff.x) < box_size.x) && (fabs(diff.y) < box_size.y))
	{
		//当たったことをオブジェクトに通知する
		del = a->OnHitCollision(b);
	}
	return (del);
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