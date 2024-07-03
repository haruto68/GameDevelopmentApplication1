#include"Bullets_E.h"
#include"DxLib.h"
#include"../../Utility/UserTemplate.h"

//�R���X�g���N�^
Bullets_E::Bullets_E() :
	animation(),
	animation_count(0),
	speed(1.0),
	velocity(0.0),
	p_l(0.0),
	save(0.0)
{
	animation[0] = NULL;
	animation[1] = NULL;
	animation[2] = NULL;
	animation[3] = NULL;
}

//�f�X�g���N�^
Bullets_E::~Bullets_E()
{

}

//����������
void Bullets_E::Initialize()
{
	//�I�u�W�F�N�g�^�C�v�̐ݒ�
	object_type = BULLETS_E;

	//�摜�̓ǂݍ���
	animation[0] = LoadGraph("Resource/Images/Bullets/Enemy/0.png");
	animation[1] = LoadGraph("Resource/Images/Bullets/Enemy/1.png");
	animation[2] = LoadGraph("Resource/Images/Bullets/Enemy/2.png");
	animation[3] = LoadGraph("Resource/Images/Bullets/Enemy/3.png");

	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1 || animation[2] == -1 || animation[3] == -1)
	{
		throw("�e�L�e�̉摜������܂���\n");
	}

	//�����̐ݒ�
	radian = 0;

	//�傫���̐ݒ�
	box_size = 30.0;

	//�����摜�̐ݒ�
	image = animation[0];

	//�X�s�[�h�̐ݒ�
	speed = 1.5;

	//�v���C���[���W�擾
	p_l = MyScene->GetPlayerLocation();
}

//�X�V����
void Bullets_E::Update()
{
	//�ړ�����
	if (image == animation[0])
	{
		Movement();
	}
	//�A�j���[�V��������
	if (anime_flag == TRUE)
	{
		AnimationControl();
	}
}

//�`�揈��
void Bullets_E::Draw()const
{
	//�e�L�e�摜�̕`��
	DrawRotaGraphF(location.x, location.y, OBJECTSIZE, radian, image, TRUE, FALSE);

	//�f�o�b�O�p
#if _DEBUG
	//�����蔻��̉���
	Vector2D ul = location - (box_size / 2.0f);		//box_collision_upper_left   =  ul  =  ����
	Vector2D lr = location + (box_size / 2.0f);		//box_collision_lower_right  =  lr  =  �E��

	DrawBoxAA(ul.x, ul.y, lr.x, lr.y, GetColor(255, 0, 0), FALSE);
#endif
}

//�I��������
void Bullets_E::Finalize()
{
	//�g�p�����摜���J������
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
	DeleteGraph(animation[2]);
	DeleteGraph(animation[3]);
}

//�����蔻��ʒm����
bool Bullets_E::OnHitCollision(GameObject* hit_object)
{
	bool value = FALSE;

	int type = hit_object->GetObjectType();

	switch (type)
	{
	case PLAYER:
		break;
	default:
		break;
	}

	return value;
}

//�ړ�����
void Bullets_E::Movement()
{
	//���K��
	velocity = Tracking(location, p_l);

	velocity *= speed;

	if (location.y > p_l.y)
	{
		location += velocity;
		save = velocity;
	}
	else
	{
		location += save;
	}
}

//�A�j���[�V��������
void Bullets_E::AnimationControl()
{
	//�t���[���J�E���g�����Z����
	animation_count++;

	//12�t���[���ڂɓ��B������
	if (animation_count >= 12)
	{
		if (delete_flag == TRUE)
		{
			DiscardObject(this);
		}

		//�J�E���g�̃��Z�b�g
		animation_count = 0;

		//�摜�̐؂�ւ�
		if (image == animation[0])
		{
			image = animation[1];
		}
		else if (image == animation[1])
		{
			image = animation[2];
		}
		else if (image == animation[2])
		{
			image = animation[3];
			delete_flag = TRUE;
		}
	}
}

//�ǔ�����
Vector2D Bullets_E::Tracking(Vector2D A, Vector2D B)
{
	Vector2D velocity;	//�����x
	float distance;		//����

	velocity.x = A.x - B.x;
	velocity.y = A.y - B.y;

	distance = sqrt(pow(velocity.x, 2.0) + pow(velocity.y, 2.0));

	velocity.x /= distance;
	velocity.y /= distance;

	velocity *= -1;

	return velocity;
}