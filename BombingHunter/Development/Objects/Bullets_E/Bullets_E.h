#pragma once

#include"../Object.h"

//�N���X��`
class Bullets_E : public Object
{
private:
	int animation[4];	//�A�j���[�V�����摜
	int animation_count;//�A�j���[�V�����J�E���g
	float speed;		//�X�s�[�h
	Vector2D velocity;	//�����x
	Vector2D save;		//�����x�L��
	Vector2D p_l;		//�v���C���[���W
			

public:
	Bullets_E();	//�R���X�g���N�^
	~Bullets_E();	//�f�X�g���N�^

	void Initialize();		//����������
	void Update(); 			//�X�V����
	void Draw() const;		//�`�揈��
	void Finalize();		//�I��������

	//�����蔻��ʒm����
	bool OnHitCollision(GameObject* hit_object);

private:
	void Movement();				//�ړ�����
	void AnimationControl();		//�A�j���[�V��������

	Vector2D Tracking(Vector2D A, Vector2D B); //�ǔ�����
};