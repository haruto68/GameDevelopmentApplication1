#pragma once

#include"../Utility//Vector2D.h"
//#include"../Scene/Scene.h"
//#include"Object.h"

#define OBJECTSIZE		(0.7)	//�I�u�W�F�N�g�̃T�C�Y�{��

#define PLAYER			(0)		//�g���p�C���b�g
#define ENEMY1			(1)		//�n�l�e�L
#define ENEMY2			(2)		//�n�R�e�L
#define ENEMY3			(3)		//���̃e�L
#define ENEMY4			(4)		//�n�[�s�B
#define BULLETS_P		(5)		//�g���e
#define BULLETS_E		(6)		//�e�L�e
#define ENEMY_TOTAL		(7)		//�e�L����
#define OBJECT_TYPE_MAX	(8)		//�I�u�W�F�N�g�^�C�v�̐�

//�Q�[���I�u�W�F�N�g���N���X
class GameObject /*: public Scene*/
{
protected:
	class Scene* MyScene;

	int object_type;		//�I�u�W�F�N�g�̃^�C�v

	Vector2D location;		//�ʒu���W
	Vector2D box_size;		//��`�̑傫��
	double radian;			//����
	int image;				//�摜
	int sound;				//�Đ����鉹��
	bool flip_flag;			//���]�t���O

public:
	GameObject();				//�R���X�g���N�^
	virtual ~GameObject();		//�f�X�g���N�^

	virtual void Initialize();		//����������
	virtual void Update();			//�X�V����
	virtual void Draw() const;		//�`�揈��
	virtual void Finalize();		//�I��������

	//�I�u�W�F�N�g�^�C�v�擾����
	int GetObjectType()const;

	//�����蔻��ʒm����
	virtual bool OnHitCollision(GameObject* hit_object);

	//��`���擾����
	Vector2D GetBoxSize() const;

	//�ʒu���擾����
	Vector2D GetLocation() const;

	//�ʒu���ύX����
	void SetLocation(const Vector2D& location);

	//���]���ύX����
	void SetFlipFlag(bool flip);



public:
	void SetMySceneA(class Scene* scene)
	{
		MyScene = scene;

		
	}
};