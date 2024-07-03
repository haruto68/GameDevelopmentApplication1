#pragma once

#include"../Utility//Vector2D.h"

#define OBJECTSIZE		(0.7)	//�I�u�W�F�N�g�̃T�C�Y�{��

//�^�C�v
#define PLAYER			(0)		//�g���p�C���b�g
#define ENEMY1			(1)		//�n�l�e�L
#define ENEMY2			(2)		//�n�R�e�L
#define ENEMY3			(3)		//���̃e�L
#define ENEMY4			(4)		//�n�[�s�B
#define BULLETS_P		(5)		//�g���e
#define BULLETS_E		(6)		//�e�L�e
//�I�u�W�F�N�g�������p
#define ENEMY_TOTAL		(7)		//�e�L����
#define OBJECT_TYPE_MAX	(8)		//�I�u�W�F�N�g�^�C�v�̐�

//�X�R�A
#define SCORE_ENEMY1	(100)	//�n�l�e�L
#define SCORE_ENEMY2	(200)	//�n�R�e�L
#define SCORE_ENEMY3	(500)	//���̃e�L
#define SCORE_ENEMY4	(-100)	//�n�[�s�B
#define SCORE_BULLET_E	(-200)	//�e�L�e

//�Q�[���I�u�W�F�N�g���N���X
class GameObject
{
protected:
	class Scene* MyScene;
	
protected:
	int object_type;		//�I�u�W�F�N�g�̃^�C�v

	Vector2D location;		//�ʒu���W
	Vector2D box_size;		//��`�̑傫��
	double radian;			//����
	int image;				//�摜
	int sound;				//�Đ����鉹��
	bool flip_flag;			//���]�t���O
	bool anime_flag;		//�A�j���t���O
	bool delete_flag;		//�폜�t���O
	int alpha;				//�A���t�@�l

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

	//���]�t���O�ύX����
	void SetFlipFlag(bool flip);

	//�A�j���t���O�ύX����
	void SetAnimeFlag(bool anime);

	//�폜�t���O�ύX����
	void SetDeleteFlag(bool del);

public:
	//�V�[�����ݒ菈��
	void SetMyScene(class Scene* scene);
};