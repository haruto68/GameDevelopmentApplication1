#include"Enemy4.h"
#include"DxLib.h"

//�R���X�g���N�^
Enemy4::Enemy4() :
	animation_count(0),
	animation_count2(0),
	box_size(0.0)
{
	animation[0] = NULL;
	animation[1] = NULL;

	speed = float(GetRand(2) + 1);
}

//�f�X�g���N�^
Enemy4::~Enemy4()
{

}

//����������
void Enemy4::Initialize()
{
	//�I�u�W�F�N�g�^�C�v�̐ݒ�
	object_type = ENEMY4;

	//�摜�̓ǂݍ���
	animation[0] = LoadGraph("Resource/images/Enemy/Harpy/1.png");
	animation[1] = LoadGraph("Resource/images/Enemy/Harpy/2.png");

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
void Enemy4::Update()
{
	//�ړ�����
	if (anime_flag == FALSE)
	{
		Movement();
	}
	//�A�j���[�V��������
	AnimationControl();
	
}

//�`�揈��
void Enemy4::Draw() const
{
	//�n�l�e�L�摜�̕`��
	if (anime_flag)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawRotaGraphF(location.x, location.y, OBJECTSIZE, radian, image, TRUE, flip_flag);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
	}
	else
	{
		DrawRotaGraphF(location.x, location.y, OBJECTSIZE, radian, image, TRUE, flip_flag);
	}

	//�f�o�b�O�p
#if _DEBUG
	//�����蔻��̉���
	Vector2D ul = location - (Vector2D(1.0f) * (float)box_size / 2.0f);
	Vector2D br = location + (Vector2D(1.0f) * (float)box_size / 2.0f);

	DrawBoxAA(ul.x, ul.y, br.x, br.y, GetColor(255, 0, 0), FALSE);
#endif
}

//�I��������
void Enemy4::Finalize()
{
	//�g�p�����摜���������
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

//�����蔻��ʒm����
bool Enemy4::OnHitCollision(GameObject* hit_object)
{
	bool value = FALSE;

	int type = hit_object->GetObjectType();

	if (type == BULLETS_P && anime_flag == FALSE)
	{
		hit_object->SetAnimeFlag(TRUE);
	}

	return value;
}

//�ړ�����
void Enemy4::Movement()
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
void Enemy4::AnimationControl()
{
	if (anime_flag == FALSE)
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
	else
	{
		//�t���[���J�E���g�����Z����
		animation_count2++;
		alpha -= 4;

		//60�t���[���ڂɓ��B������
		if (animation_count2 < 60)
		{
			location.y += 0.3f;
		}
		if (alpha <= 0)
		{
			DiscardObject(this);
		}
	}
}