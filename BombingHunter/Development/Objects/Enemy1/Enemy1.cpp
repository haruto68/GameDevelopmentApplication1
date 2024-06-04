#include"Enemy1.h"
#include"DxLib.h"

//�R���X�g���N�^
Enemy1::Enemy1() :
	animation_count(0),
	box_size(0.0)
{
	animation[0] = NULL;
	animation[1] = NULL;

	speed = float(GetRand(2) + 1);
}

//�f�X�g���N�^
Enemy1::~Enemy1()
{

}

//����������
void Enemy1::Initialize()
{
	//�I�u�W�F�N�g�^�C�v�̐ݒ�
	object_type = ENEMY1;

	//�摜�̓ǂݍ���
	animation[0] = LoadGraph("Resource/images/�e�L/�n�l�e�L1.png");
	animation[1] = LoadGraph("Resource/images/�e�L/�n�l�e�L2.png");

	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("�n�l�e�L�̉摜������܂���\n");
	}

	//�����̐ݒ�
	radian = 0.0;

	//�傫���̐ݒ�
	box_size = 64.0;

	//�����摜�̐ݒ�
	image = animation[0];
}

//�X�V����
void Enemy1::Update()
{
	//�ړ�����
	Movement();
	//�A�j���[�V��������
	AnimationControl();
}

//�`�揈��
void Enemy1::Draw() const
{
	//�n�l�e�L�摜�̕`��
	DrawRotaGraphF(location.x, location.y, OBJECTSIZE, radian, image, TRUE, flip_flag);

	//�f�o�b�O�p
#if _DEBUG
	//�����蔻��̉���
	Vector2D ul = location - (Vector2D(1.0f) * (float)box_size / 2.0f);
	Vector2D br = location + (Vector2D(1.0f) * (float)box_size / 2.0f);

	DrawBoxAA(ul.x, ul.y, br.x, br.y, GetColor(255, 0, 0), FALSE);
#endif
}

//�I��������
void Enemy1::Finalize()
{
	//�g�p�����摜���������
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

//�����蔻��ʒm����
bool Enemy1::OnHitCollision(GameObject* hit_object)
{
	//�����������̏���
	bool value = FALSE;
	int type = hit_object->GetObjectType();
	
	if (type == BULLETS_P)
	{
		value = TRUE;
	}

	return value;
}

//�ړ�����
void Enemy1::Movement()
{
	//�ړ��̑���
	Vector2D velocity = 0.0f;

	//���E�ړ�

	if (flip_flag == TRUE)
	{
		velocity.x -= speed;
	}
	else
	{
		velocity.x += speed;
	}	

	//���݂̈ʒu���W�ɑ��������Z����
	location += velocity;
}

//�A�j���[�V��������
void Enemy1::AnimationControl()
{
	//�t���[���J�E���g�����Z����
	animation_count++;

	//60�t���[���ڂɓ��B������
	if (animation_count >= 60)
	{
		//�J�E���g�̃��Z�b�g
		animation_count = 0;

		//�摜�̐؂�ւ�
		if (image == animation[0])
		{
			image = animation[1];
		}
		else
		{
			image = animation[0];
		}
	}
}