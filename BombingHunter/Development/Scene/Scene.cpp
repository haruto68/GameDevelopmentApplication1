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

//�R���X�g���N�^
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

//�f�X�g���N�^
Scene::~Scene()
{
	//�Y��h�~
	Finalize();
}

//����������
void Scene::Initialize()
{
	//�摜�擾����
	//�w�i�摜�擾
	bg_image = LoadGraph("Resource/Images/UI/background.png");
	//�^�C�g���摜�擾
	ti_image = LoadGraph("Resource/Images/Player/1.png");
	//�w���v�摜�擾
	he_image[0] = LoadGraph("Resource/Images/Player/1.png");
	he_image[1] = LoadGraph("Resource/Images/Enemy/wing/1.png");
	he_image[2] = LoadGraph("Resource/Images/Enemy/box/1.png");
	he_image[3] = LoadGraph("Resource/Images/Enemy/gold/1.png");
	he_image[4] = LoadGraph("Resource/Images/Enemy/Harpy/1.png");
	he_image[5] = LoadGraph("Resource/Images/Bullets/Player/0.png");
	he_image[6] = LoadGraph("Resource/Images/Bullets/Enemy/0.png");
	//UI�摜�擾
	ui_image[0] = LoadGraph("Resource/Images/UI/timer.png");
	ui_image[1] = LoadGraph("Resource/Images/UI/score.png");
	ui_image[2] = LoadGraph("Resource/Images/UI/highscore.png");
	//�]���摜�擾
	ev_image[0] = LoadGraph("Resource/Images/Evaluation/0.png");
	ev_image[1] = LoadGraph("Resource/Images/Evaluation/1.png");
	ev_image[2] = LoadGraph("Resource/Images/Evaluation/2.png");
	ev_image[3] = LoadGraph("Resource/Images/Evaluation/3.png");
	ev_image[4] = LoadGraph("Resource/Images/Evaluation/4.png");
	//�����摜�擾
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
	//�G���[�`�F�b�N
	if (bg_image == -1)
	{
		throw("�w�i�̉摜������܂���\n");
	}
	if (ti_image == -1)
	{
		throw("�^�C�g���̉摜������܂���\n");
	}
	if (he_image[0] == -1 || he_image[1] == -1 || he_image[2] == -1 || he_image[3] == -1 || he_image[4] == -1 || he_image[5] == -1 || he_image[6] == -1)
	{
		throw("�w���v�̉摜������܂���\n");
	}
	if (ui_image[0] == -1 || ui_image[1] == -1 || ui_image[2] == -1)
	{
		throw("UI�̉摜������܂���\n");
	}
	if (ev_image[0] == -1 || ev_image[1] == -1 || ev_image[2] == -1 || ev_image[3] == -1 || ev_image[4] == -1)
	{
		throw("�]���̉摜������܂���\n");
	}
	if (numbers[0] == -1 || numbers[1] == -1 || numbers[2] == -1 || numbers[3] == -1 || numbers[4] == -1 || numbers[5] == -1 || numbers[6] == -1 || numbers[7] == -1 || numbers[8] == -1 || numbers[9] == -1)
	{
		throw("�����̉摜������܂���\n");
	}

	//�����擾����
	//BGM�擾
	bgm[0] = LoadSoundMem("Resource/sounds/BGM/main.wav");
	bgm[1] = LoadSoundMem("Resource/sounds/BGM/timeup.wav");
	//�]��SE�擾
	se_ev[1] = LoadSoundMem("Resource/sounds/evaluation/bad.wav");
	se_ev[2] = LoadSoundMem("Resource/sounds/evaluation/ok.wav");
	se_ev[3] = LoadSoundMem("Resource/sounds/evaluation/good.wav");
	se_ev[4] = LoadSoundMem("Resource/sounds/evaluation/perfect.wav");
	//�e�LSE�擾
	se_en[1] = LoadSoundMem("Resource/sounds/enemy/wing.wav");
	se_en[2] = LoadSoundMem("Resource/sounds/enemy/box.wav");
	se_en[3] = LoadSoundMem("Resource/sounds/enemy/gold.wav");
	se_en[4] = LoadSoundMem("Resource/sounds/enemy/Harpy.wav");
	//�eSE�擾
	se_bu[1] = LoadSoundMem("Resource/sounds/bullets/Player/1.wav");
	se_bu[2] = LoadSoundMem("Resource/sounds/bullets/Player/2.wav");
	se_bu[3] = LoadSoundMem("Resource/sounds/bullets/Enemy/1.wav");
	se_bu[4] = LoadSoundMem("Resource/sounds/bullets/Enemy/2.wav");
	//�G���[�`�F�b�N
	if (bgm[0] == -1 || bgm[1] == -1)
	{
		throw("BGM������܂���\n");
	}
	if (se_ev[0] == -1 || se_ev[1] == -1 || se_ev[2] == -1 || se_ev[3] == -1 || se_ev[4] == -1)
	{
		throw("�]����SE������܂���\n");
	}
	if (se_en[0] == -1 || se_en[1] == -1 || se_en[2] == -1 || se_en[3] == -1 || se_en[4] == -1)
	{
		throw("�e�L��SE������܂���\n");
	}
	if (se_bu[0] == -1 || se_bu[1] == -1 || se_bu[2] == -1 || se_bu[3] == -1 || se_bu[4] == -1)
	{
		throw("�e��SE������܂���\n");
	}

	//��������
	ChangeVolumeSoundMem(150, se_bu[1]);

	//�n�C�X�R�A�ǂݍ��ݏ���
	FILE* fp = nullptr;
	//�t�@�C���I�[�v��
	errno_t result = fopen_s(&fp, "Resource/data/highscore.csv", "r");

	//�G���[�`�F�b�N
	if (result != 0)
	{
		throw("Resource/data/highscore.csv���ǂݍ��߂܂���\n");
	}

	//���ʂ�ǂݍ���
	fscanf_s(fp, "%6d", &highscore);

	//�t�@�C���N���[�Y
	fclose(fp);

	PlaySoundMem(bgm[0], DX_PLAYTYPE_LOOP, TRUE);
}

//�X�V����
void Scene::Update()
{
	

	//�������ԃJ�E���g����
	TimeLimitCount();
	if (objects.size() == 0)
	{
		
	}

	//�V�[���ɑ��݂���I�u�W�F�N�g�̍X�V����
	for (GameObject* obj : objects)
	{
		obj->Update();
	}

	//�Q�[���X�^�[�g
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

	//�Q�[�����C��
	if (gamemain == TRUE)
	{
		//�v���C���[�𐶐�����
		if (objects.size() == 0)
		{
			CreateObject<Player>(Vector2D(320.0f, 50.0f), FALSE);
		}

		//�I�u�W�F�N�g�n������
		Creation();

		//�I�u�W�F�N�g�j�󏈗�
		destruction();

		//�Q�[���G���h
		if (timelimit < 0)
		{
			gamemain = FALSE;
			gameend = TRUE;
			StopSoundMem(bgm[0]);
			PlaySoundMem(bgm[1], DX_PLAYTYPE_LOOP, TRUE);
		}
	}

	//�]���ݒ�
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

		//�n�C�X�R�A�X�V����
		if (score > highscore)
		{
			highscore = score;

			//�n�C�X�R�A�������ݏ���
			FILE* fp = nullptr;
			//�t�@�C���I�[�v��
			errno_t result = fopen_s(&fp, "Resource/data/highscore.csv", "w");

			//�G���[�`�F�b�N
			if (result != 0)
			{
				throw("Resource/data/highscore.csv���J���܂���\n");
			}

			//�n�C�X�R�A��ۑ�
			fprintf(fp, "%6d,\n", highscore);

			//�t�@�C���N���[�Y
			fclose(fp);
		}

		//�I�u�W�F�N�g�S�폜
		objects.clear();

		//�^�C�g����ʂ֖߂�
		if (InputControl::GetKeyDown(KEY_INPUT_BACK))
		{
			gameend = FALSE;
			gamehelp = FALSE;
			StopSoundMem(bgm[1]);
			PlaySoundMem(bgm[0], DX_PLAYTYPE_LOOP, TRUE);
		}
	}

	//�w���v��ʐ؂�ւ�
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

//�`�揈��
void Scene::Draw()
{
	//�w�i�`��
	DrawRotaGraphF(320, 240, OBJECTSIZE, 0, bg_image, TRUE, FALSE);

	//UI�`��
	DrawRotaGraphF(15, 465, 0.5, 0, ui_image[0], TRUE, FALSE);
	DrawRotaGraphF(160, 465, 0.1, 0, ui_image[1], TRUE, FALSE);
	DrawRotaGraphF(420, 465, 0.175, 0, ui_image[2], TRUE, FALSE);

	//�������ԕ`��
	if (gamemain == TRUE)
	{
		DrawRotaGraphF(60, 465, 1.5, 0, numbers[OneDigit(timelimit, 2)], TRUE, FALSE);
		DrawRotaGraphF(80, 465, 1.5, 0, numbers[OneDigit(timelimit, 1)], TRUE, FALSE);
	}

	//�X�R�A�`��
	for (int i = 1; i <= 5; i++)
	{
		DrawRotaGraphF(340 - (i * 20), 465, 1.5, 0, numbers[OneDigit(score, i)], TRUE, FALSE);
	}

	//�n�C�X�R�A�`��
	for (int i = 1; i <= 5; i++)
	{
		DrawRotaGraphF(620 - (i * 20), 465, 1.5, 0, numbers[OneDigit(highscore, i)], TRUE, FALSE);
	}
	
	//�]���`��
	if (timelimit < 0 && gameend == TRUE)
	{
		DrawRotaGraphF(320, 240, OBJECTSIZE, 0, ev_image[evaluation], TRUE, FALSE);
	}
	if (timelimit < -4 && gameend == TRUE)
	{
		//DrawBox(120, 300, 520, 430, GetColor(0, 0, 0), TRUE);
		SetFontSize(30);
		DrawFormatString(130, 320, GetColor(0, 0, 0), "Enter�L�[�Ń��X�^�[�g");
		DrawFormatString(90, 350, GetColor(0, 0, 0), "BackSPACE�L�[�Ń^�C�g���֖߂�");
	}

	//�Q�[�����C�����Ȃ�`�悷��
	if (gamemain == TRUE)
	{
		//�V�[���ɑ��݂���I�u�W�F�N�g�̕`�揈��
		for (GameObject* obj : objects)
		{
			obj->Draw();
		}
	}

	//�^�C�g����ʕ`��
	if (gamemain == FALSE && gameend == FALSE)
	{
		if(gamehelp == FALSE)
		{
			//�^�C�g���\��
			SetFontSize(70);
			DrawFormatString(110, 50, GetColor(0, 0, 0), "�����n���^�[");
			DrawRotaGraphF(80, 50, 1, -0.2, ti_image, TRUE, FALSE);
			//�Q�[���ē��\��
			SetFontSize(30);
			DrawFormatString(180, 220, GetColor(0, 0, 0), "Enter�L�[�ŃX�^�[�g");
			DrawFormatString(180, 260, GetColor(0, 0, 0), "H�L�[�Ńw���v���J��");
		}
		else
		{
			//�w���v��ʕ\��
			DrawBox(70, 40, 570, 430, GetColor(0, 200, 50), TRUE);
			//�������
			SetFontSize(30);
			DrawRotaGraphF(130, 100, 0.5, 0, he_image[0], TRUE, FALSE);		//�g��
			DrawFormatString(180, 70, GetColor(0, 0, 0), "A�ED�L�[");
			DrawFormatString(180, 100, GetColor(0, 0, 0), "���E�ړ�");
			DrawRotaGraphF(360, 100, 0.5, 1.57, he_image[5], TRUE, FALSE);	//�g���e
			DrawFormatString(430, 70, GetColor(0, 0, 0), "B�L�[");
			DrawFormatString(400, 100, GetColor(0, 0, 0), "���e����");
			//���[������
			DrawRotaGraphF(150, 200, 0.5, 0, he_image[1], TRUE, FALSE);		//�n�l�e�L
			DrawFormatString(200, 185, GetColor(0, 0, 0), "+100pt");
			DrawRotaGraphF(160, 270, 0.5, 0, he_image[2], TRUE, FALSE);		//�n�R�e�L
			DrawFormatString(200, 255, GetColor(0, 0, 0), "+200pt");
			DrawRotaGraphF(155, 340, 0.5, 0, he_image[3], TRUE, FALSE);		//���̃e�L
			DrawFormatString(200, 325, GetColor(0, 0, 0), "+500pt");
			DrawRotaGraphF(380, 200, 0.5, 0, he_image[4], TRUE, FALSE);		//�n�[�s�[
			DrawFormatString(420, 185, GetColor(0, 0, 0), "-100pt");
			DrawRotaGraphF(385, 270, 0.5, 0, he_image[6], TRUE, FALSE);		//�e�L�e
			DrawFormatString(420, 255, GetColor(0, 0, 0), "-200pt");
			//�^�C�g����
			SetFontSize(30);
			DrawFormatString(160, 380, GetColor(0, 0, 0), "H�L�[�Ńw���v�����");
		}
	}
	
	//�f�o�b�O�p�\��
	SetFontSize(40);
	bool a = 0;
	//�I�u�W�F�N�g���̕\��
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
	//�R���e�i�T�C�Y�̕\��
	if(a == 2)
	{
		DrawFormatString(0, 0, 0xffffff, "%d", objects.size());
		DrawFormatString(0, 50, 0xffffff, "%d", factory.size());
		DrawFormatString(0, 100, 0xffffff, "%d", trash.size());
	}
}

//�I��������
void Scene::Finalize()
{
	//�摜�̉��
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

	//�����̉��
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

	//���I�z�񂪋�Ȃ珈�����I������
	if (objects.empty())
	{
		return;
	}

	//�e�I�u�W�F�N�g���폜����
	for (GameObject* obj : objects)
	{
		obj->Finalize();
		delete obj;
	}

	//���I�z��̉��
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

//�I�u�W�F�N�g�n������
void Scene::Creation()
{
	//�I�u�W�F�N�g�^�C�v���Ƃ̃J�E���g
	int type_count[OBJECT_TYPE_MAX] = {};
	for (GameObject* obj : objects)
	{
		int type = obj->GetObjectType();
		type_count[type]++;
	}
	type_count[ENEMY_TOTAL] = type_count[ENEMY1] + type_count[ENEMY2] + type_count[ENEMY3] + type_count[ENEMY4];

	//�e�L�̐���
	if (type_count[ENEMY_TOTAL] < 5)
	{
		//�e�L����
		int random_e = GetRand(3);
		//X���W����
		int random_x = GetRand(1);
		float X = 0; int flip = FALSE;
		if (random_x == 0)
		{
			X = 0.0f; flip = FALSE;		//��
		}
		else
		{
			X = 640.0f; flip = TRUE;	//��
		}
		//Y���W����
		int random_y = GetRand(2);
		float Y_t = 170 + (float)(random_y * 80);	//��
		float Y_b = 170 + (3 * 80);					//�n



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
		case 0:	//�n�l�e�L
			CreateObject<Enemy1>(Vector2D(X, Y_t), flip);
			break;
		case 1:	//�n�R�e�L
			CreateObject<Enemy2>(Vector2D(X, Y_b), flip);
			break;
		case 2:	//���̃e�L
			CreateObject<Enemy3>(Vector2D(X, Y_b), flip);
			break;
		case 3:	//�n�[�s�B
			CreateObject<Enemy4>(Vector2D(X, Y_t), flip);
			break;
		default:
			break;
		}
	}

	//Player�̏��擾
	Vector2D p_l = 0.0;	//���W
	p_l = objects[0]->GetLocation();

	//�g���e����
	if (InputControl::GetKeyDown(KEY_INPUT_B) == TRUE)
	{
		CreateObject<Bullets_P>(Vector2D(p_l.x, p_l.y), TRUE);
		PlaySoundMem(se_bu[1], DX_PLAYTYPE_BACK, TRUE);
		
	}

	//�e�L�e����
	for (Vector2D fac : factory)
	{
		if (type_count[BULLETS_E] <= 2)
		{
			CreateObject<Bullets_E>(fac, TRUE);
			PlaySoundMem(se_bu[3], DX_PLAYTYPE_BACK, TRUE);
		}
	}
}

//�I�u�W�F�N�g�j�󏈗�
void Scene::destruction()
{
	//��ʊO�ɂł��I�u�W�F�N�g�̍폜
	int i = 0;	//���[�v�J�E���^
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

	//�����蔻��`�F�b�N����
	for (int a = 0; a < objects.size(); a++)
	{
		for (int b = 0; b < objects.size(); b++)
		{
			HitCheckObject(objects[a], objects[b]);
			HitCheckObject(objects[b], objects[a]);
		}
	}

	//trash���̍폜
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

	//factory�̃��Z�b�g
	int ff = 0;
	for (Vector2D fac : factory)
	{
		factory.erase(factory.begin() + ff);
	}

	//trash�̃��Z�b�g
	int tt = 0;
	for (GameObject* tra : trash)
	{
		trash.erase(trash.begin() + tt);
	}
}

//trash�ɓ���鏈��
void Scene::InsertTrash(GameObject* garbage)
{
	trash.push_back(garbage);
}

//factory�ɓ���鏈��
void Scene::InsertFactory(Vector2D product)
{
	factory.push_back(product);
}

//�v���C���[���W�擾����
Vector2D Scene::GetPlayerLocation()
{
	Vector2D location = objects[0]->GetLocation();

	return location;
}

//�������ԃJ�E���g����
void Scene::TimeLimitCount()
{
	//�t���[���J�E���g
	flame++;

	//1�b�o�߂�����
	if (flame >= 120)
	{
		timelimit--;

		//�J�E���g���Z�b�g
		flame = 0;
	}
}

//�w�肵���ʂ̐�����1���ŕԂ�����
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

//�X�R�A���Z����
void Scene::GetScore(int value)
{
	this->score += value;
}

//D_PIVOT_CENTER������Ώ�̏����A�Ȃ���Ή��̏���
#ifdef D_PIVOT_CENTER

//�����蔻��`�F�b�N�����i��`�̒��S�œ����蔻����Ƃ�j�@�������g�p������@
bool Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	bool del = FALSE;

	//2�̃I�u�W�F�N�g�̋������擾
	Vector2D diff = a->GetLocation() - b->GetLocation();

	//2�̃I�u�W�F�N�g�̓����蔻��̑傫�����擾
	Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;

	//�������傫�����傫���ꍇ�AHit����Ƃ���
	if ((fabs(diff.x) < box_size.x) && (fabs(diff.y) < box_size.y))
	{
		//�����������Ƃ��I�u�W�F�N�g�ɒʒm����
		del = a->OnHitCollision(b);
	}
	return (del);
}

#else

//�����蔻��`�F�b�N�����i���㒸�_�̍��W���瓖���蔻��v�Z���s���j�A�҂̈ʒu�֌W���g�p������@
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//�E�����_���W���擾����
	Vector2D a_lower_right = a->GetLocation() + a->GetBoxSize();
	Vector2D b_lower_right = b->GetLocation() + b->GetBoxSize();

	//��`A�Ƌ�`B�̈ʒu�֌W�𒲂ׂ�
	if ((a->GetLocation().x < b_lower_right.x) &&
		(a->GetLocation().y < b_lower_right.y) &&
		(a_lower_right.x > b->GetLocation().x) &&
		(a_lower_right.y > b->GetLocation().y))
	{
		//�I�u�W�F�N�g�ɑ΂���Hit�����ʒm����
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}

#endif // D_PIVOT_CENTER