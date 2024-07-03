#pragma once

#include"../Object.h"

//�N���X��`
class Enemy1 : public Object
{
private:
	int animation[2];			//�A�j���[�V�����摜
	int animation_count;		//�A�j���[�V��������
	int animation_count2;		//�A�j���[�V��������2
	float box_size;				//�����蔻��
	float speed;				//�X�s�[�h

public:
	Enemy1();		//�R���X�g���N�^
	~Enemy1();		//�f�X�g���N�^

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