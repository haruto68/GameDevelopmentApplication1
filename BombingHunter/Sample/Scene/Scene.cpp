#include"Scene.h"
#include"DxLib.h"

#include"../Objects/Player/Player.h"
#include"../Objects/Enemy1/Enemy1.h"

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
	CreateObject<Player>(Vector2D(320.0f, 80.0f));

	//�n�l�e�L�𐶐�����
	//CreateObject<Enemy1>(Vector2D(0.0f, 400.0f));

	float random_x = GetRand(2) % 2;

	if (random_x == 0)
	{
		CreateObject<Enemy1>(Vector2D(0.0f, 200.0f));
	}
	else
	{
		CreateObject<Enemy1>(Vector2D(0.0f, 400.0f));
	}
}

//�X�V����
void Scene::Update()
{
	//�V�[���ɑ��݂���I�u�W�F�N�g�̍X�V����
	for (GameObject* obj : objects)
	{
		obj->Update();
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
}

//�I��������
void Scene::Finalize()
{
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
}