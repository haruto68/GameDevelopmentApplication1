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

//�R���X�g���N�^
Scene::Scene() : objects()
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
	//�v���C���[�𐶐�����
	CreateObject<Player>(Vector2D(320.0f, 50.0f), FALSE);
}

//�X�V����
void Scene::Update()
{
	//�V�[���ɑ��݂���I�u�W�F�N�g�̍X�V����
	for (GameObject* obj : objects)
	{
		obj->Update();
	}

	//�I�u�W�F�N�g�^�C�v���Ƃ̃J�E���g
	int type_count[OBJECT_TYPE_MAX] = {};
	for (GameObject* obj : objects)
	{
		int type = obj->GetObjectType();
		type_count[type]++;
	}
	type_count[ENEMY_TOTAL] = type_count[ENEMY1] + type_count[ENEMY2] + type_count[ENEMY3] + type_count[ENEMY4];
	
	//�e�L�̐���
	if (type_count[ENEMY_TOTAL] < 2)
	{
		int random_e = GetRand(0);			//�e�L����
		int random_x = GetRand(1);			//X���W����
		int random_y = GetRand(3);			//Y���W����
		int Y = 170 + (random_y * 85);

		switch (random_e)
		{
		case 0:	//�n�l�e�L
			if (random_x == 0)
			{
				CreateObject<Enemy1>(Vector2D(0.0f, Y), FALSE);
			}
			else
			{
				CreateObject<Enemy1>(Vector2D(640.0f, Y), TRUE);
			}
			break;
		case 1:	//�n�R�e�L
			if (random_x == 0)
			{
				CreateObject<Enemy2>(Vector2D(0.0f, Y), FALSE);
			}
			else
			{
				CreateObject<Enemy2>(Vector2D(640.0f, Y), TRUE);
			}
			break;
		case 2:	//���̃e�L
			if (random_x == 0)
			{
				CreateObject<Enemy3>(Vector2D(0.0f, Y), FALSE);
			}
			else
			{
				CreateObject<Enemy3>(Vector2D(640.0f, Y), TRUE);
			}
			break;
		case 3:	//�n�[�s�B
			if (random_x == 0)
			{
				CreateObject<Enemy4>(Vector2D(0.0f, Y), FALSE);
			}
			else
			{
				CreateObject<Enemy4>(Vector2D(640.0f, Y), TRUE);
			}
			break;
		default:
			break;
		}
	}

	//Player�̏��擾
	Vector2D p_l = 0.0;	//���W
	p_l = objects[0]->GetLocation();

	//�g���e����
	if (InputControl::GetKeyDown(KEY_INPUT_SPACE) == TRUE)
	{
		CreateObject<Bullets_P>(Vector2D(p_l.x, p_l.y), TRUE);
	}

	//��ʊO�ɂł��I�u�W�F�N�g�̍폜
	int i = 0;	//���[�v�J�E���^
	for (GameObject* obj : objects)
	{
		Vector2D loc = obj->GetLocation();
		if (loc.x < -60.0 || 700.0 < loc.x || loc.y < -60.0 || 520.0 < loc.y)
		{
			objects.erase(objects.begin() + i);
			obj->Finalize();
			delete obj;
		}
		i++;
	}

	////�����蔻��`�F�b�N����
	//int a = 0;
	//for (GameObject* obj_a : objects)
	//{
	//	int b = 0;
	//	for (GameObject* obj_b : objects)
	//	{
	//		//�I�u�W�F�N�g�̍폜�۔���
	//		bool delete_a = FALSE;
	//		bool delete_b = FALSE;
	//		
	//		/*delete_b,*/ delete_a = HitCheckObject(obj_a, obj_b);
	//		//delete_b = HitCheckObject(obj_b, obj_a);

	//		//�I�u�W�F�N�g�̍폜
	//		if (delete_a == TRUE)
	//		{
	//			objects.erase(objects.begin() + a);
	//			obj_a->Finalize();
	//			delete obj_a;

	//			//trash.push_back(obj_a);
	//		}

	//		//
	//		if (delete_a ==TRUE)
	//		{
	//			objects.erase(objects.begin() + b);
	//			obj_b->Finalize();
	//			delete obj_b;
	//		}

	//		/*bool del = FALSE;

	//		del = HitCheckObject(obj_a, obj_b);
	//		if (del == TRUE)
	//		{
	//			objects.erase(objects.begin() + a);
	//			objects[a]->Finalize();
	//			delete objects[a];
	//		}*/

	//		b++;
	//	}
	//	a++;
	//}

	for (int a = 0; a < objects.size(); a++)
	{
		for (int b = 0; b < objects.size(); b++)
		{
			bool del = FALSE;
			del = HitCheckObject(objects[a], objects[b]);

			if (del == TRUE)
			{
				objects.erase(objects.begin() + a);
				objects[a]->Finalize();
				delete objects[a];
			}
		}
	}

	int z = 0;
	for (GameObject* tra : trash)
	{
		trash.erase(trash.begin() + z);
		tra->Finalize();
		delete tra;

		z++;
	}
}

//�`�揈��
void Scene::Draw() const
{
	//�V�[���ɑ��݂���I�u�W�F�N�g�̕`�揈��
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
	
	SetFontSize(50);
	DrawFormatString(0, 0, 0xffffff, "%d", objects.size());
}

//�I��������
void Scene::Finalize()
{
	//���I�z�񂪋�Ȃ珈�����I������
	if (objects.empty())
	{
		return;
	}
	if (trash.empty())
	{
		return;
	}

	//�e�I�u�W�F�N�g���폜����
	for (GameObject* obj : objects)
	{
		obj->Finalize();
		delete obj;
	}
	for (GameObject* tra : trash)
	{
		tra->Finalize();
		delete tra;
	}

	//���I�z��̉��
	objects.clear();
	trash.clear();
}

//D_PIVOT_CENTER������Ώ�̏����A�Ȃ���Ή��̏���
#ifdef D_PIVOT_CENTER

//�����蔻��`�F�b�N�����i��`�̒��S�œ����蔻����Ƃ�j�@�������g�p������@
bool Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//bool del_a = FALSE;
	//bool del_b = FALSE;
	bool del = FALSE;

	//2�̃I�u�W�F�N�g�̋������擾
	Vector2D diff = a->GetLocation() - b->GetLocation();

	//2�̃I�u�W�F�N�g�̓����蔻��̑傫�����擾
	Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;

	//�������傫�����傫���ꍇ�AHit����Ƃ���
	if ((fabs(diff.x) < box_size.x) && (fabs(diff.y) < box_size.y))
	{
		//�����������Ƃ��I�u�W�F�N�g�ɒʒm����
		//del_a = a->OnHitCollision(b);
		//del_b = b->OnHitCollision(a);

		del = a->OnHitCollision(b);
	}
	return (/*del_a, del_b*/del);
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