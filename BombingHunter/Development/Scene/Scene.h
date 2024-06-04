#pragma once

#include<vector>
#include<string>
#include"../Objects/Object.h"

#define ObjectSize	(0.7)	//�I�u�W�F�N�g�̃T�C�Y�{��

class Scene
{
private:
protected:
	std::vector<GameObject*> objects;
	std::vector<GameObject*> trash;

public:
	Scene();
	~Scene();

	void Initialize();
	void Update();
	void Draw() const;
	void Finalize();

private:
	//�����蔻��`�F�b�N����
	bool HitCheckObject(GameObject* a, GameObject* b);

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

		//����������
		new_object->Initialize();

		//�ʒu���̐ݒ�
		new_object->SetLocation(location);

		//���]���̐ݒ�
		new_object->SetFlipFlag(flip);


		//�V�[���̏�����������
		new_object->SetMySceneA(this);

		

		//�I�u�W�F�N�g���X�g�ɒǉ�
		objects.push_back(new_object);

		//�C���X�^���X�̃|�C���^��ԋp
		return new_instance;
	}
};