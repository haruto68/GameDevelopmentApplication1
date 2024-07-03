#pragma once

#include<vector>
#include<string>
#include"../Objects/GameObject.h"

#define ObjectSize	(0.7)	//�I�u�W�F�N�g�̃T�C�Y�{��

#define BAD			(1)
#define OK			(2)
#define GOOD		(3)
#define Perfect		(4)

class Scene
{
private:
protected:
	std::vector<GameObject*> objects;	//�}�C�i���o�[
	std::vector<GameObject*> trash;		//�f�X�m�[�g

	std::vector<Vector2D> factory;		//�H��	�I�u�W�F�N�g�^�C�v�̎w�肪�ł��Ȃ�

	int bg_image;		//�w�i�摜
	int ti_image;		//�^�C�g���摜
	int he_image[7];	//�w���v�摜
	int ui_image[3];	//UI�摜
	int ev_image[5];	//�]���摜
	int numbers[10];	//�����摜

	int bgm[2];			//BGM
	int se_ev[5];		//�]��SE
	int se_en[5];		//�e�LSE
	int se_bu[5];		//�eSE

	int timelimit;		//��������
	int flame;			//�t���[��
	int score;			//�X�R�A
	int highscore;		//�n�C�X�R�A
	int evaluation;		//�]��
	bool gamemain;		//�Q�[�����C��
	bool gameend;		//�Q�[���G���h
	bool gamehelp;		//�Q�[���w���v
	bool se_ev_check;	//�]��SE�`�F�b�N

public:
	Scene();
	~Scene();

	void Initialize();
	void Update();
	void Draw();
	void Finalize();

	//�I�u�W�F�N�g�n������
	void Creation();

	//�I�u�W�F�N�g�j�󏈗�
	void destruction();

	//trash�ɓ���鏈��
	void InsertTrash(GameObject* garbage);

	//factory�ɓ���鏈��
	void InsertFactory(Vector2D product);

	//�v���C���[���W�擾����
	Vector2D GetPlayerLocation();

	//�������ԃJ�E���g����
	void TimeLimitCount();

	//�w�肵���ʂ̐�����1���ŕԂ�����
	int OneDigit(int num, int digit);

	//�X�R�A���Z����
	void GetScore(int value);

private:
	//�����蔻��`�F�b�N����
	bool HitCheckObject(GameObject* a, GameObject* b);

public:
	//�I�u�W�F�N�g��������
	template<class T>
	T* CreateObject(const Vector2D& location, bool flip)
	{
		//�w�肵���N���X�𐶐�����
		T* new_instance = new T();
		//GameObject�N���X���p�����Ă��邩�m�F
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		//�G���[�`�F�b�N
		if (new_object == nullptr)
		{
			delete new_instance;
			throw std::string("�Q�[���I�u�W�F�N�g�������ł��܂���ł���");
		}


		//�V�[���̏�����������
		new_object->SetMyScene(this);


		//����������
		new_object->Initialize();

		//�ʒu���̐ݒ�
		new_object->SetLocation(location);

		//���]���̐ݒ�
		new_object->SetFlipFlag(flip);

		//�I�u�W�F�N�g���X�g�ɒǉ�
		objects.push_back(new_object);

		//�C���X�^���X�̃|�C���^��ԋp
		return new_instance;
	}
};