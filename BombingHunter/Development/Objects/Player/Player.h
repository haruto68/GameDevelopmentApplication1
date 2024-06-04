#pragma once

#include"../Object.h"

//�N���X��`
class Player : public Object
{
private:
	int animation[2];			//�A�j���[�V�����摜
	int animation_count;		//�A�j���[�V��������
	float speed;				//�X�s�[�h
	Vector2D velocity;			//�����x

public:
	Player();		//�R���X�g���N�^
	~Player();		//�f�X�g���N�^

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