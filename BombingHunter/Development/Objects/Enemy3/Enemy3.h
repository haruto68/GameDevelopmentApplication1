#pragma once

#include"../GameObject.h"

//�N���X��`
class Enemy3 : public GameObject
{
private:
	int animation[5];			//�A�j���[�V�����摜
	int animation_count;		//�A�j���[�V��������
	float box_size;				//�����蔻��
	float speed;				//�X�s�[�h

public:
	Enemy3();		//�R���X�g���N�^
	~Enemy3();		//�f�X�g���N�^

	virtual void Initialize() override;		//����������
	virtual void Update() override; 		//�X�V����
	virtual void Draw() const override;		//�`�揈��
	virtual void Finalize() override;		//�I��������

	//�����蔻��ʒm����
	virtual bool OnHitCollision(GameObject* hit_object) override;

private:
	void Movement();				//�ړ�����
	void AnimationControl();		//�A�j���[�V��������
};