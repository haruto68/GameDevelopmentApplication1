#include"Player.h"
#include"../../Utility/InputControl.h"
#include"../../Utility/UserTemplate.h"
#include"DxLib.h"

//�R���X�g���N�^
Player::Player() :animation_count(0)
{
	animation[0] = NULL;
	animation[1] = NULL;
	
	speed = 1.5f;
	velocity = 0.0f;
}

//�f�X�g���N�^
Player::~Player()
{

}

//����������
void Player::Initialize()
{
	//�I�u�W�F�N�g�^�C�v�̐ݒ�
	object_type = PLAYER;

	//�摜�̓ǂݍ���
	animation[0] = LoadGraph("Resource/Images/�g���p�C���b�g/���1.png");
	animation[1] = LoadGraph("Resource/Images/�g���p�C���b�g/���2.png");

	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("�g���p�C���b�g�̉摜������܂���\n");
	}

	//�����̐ݒ�
	radian = 0.0;

	//�傫���̐ݒ�
	box_size = 64.0;

	//�����摜�̐ݒ�
	image = animation[0];
}

//�X�V����
void Player::Update()
{
	//�ړ�����
	Movement();
	//�A�j���[�V��������
	AnimationControl();

	
}

//�`�揈��
void Player::Draw() const
{
	//�v���C���[�摜�̕`��
	DrawRotaGraphF(location.x, location.y, OBJECTSIZE, radian, image, TRUE, flip_flag);

	//�f�o�b�O�p
#if _DEBUG
	//�����蔻��̉���
	Vector2D ul = location - (box_size / 2.0f);		//box_collision_upper_left   =  ul  =  ����
	Vector2D lr = location + (box_size / 2.0f);		//box_collision_lower_right  =  lr  =  �E��

	DrawBoxAA(ul.x, ul.y, lr.x, lr.y, GetColor(255, 0, 0), FALSE);
#endif
}

//�I��������
void Player::Finalize()
{
	//�g�p�����摜���������
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

//�����蔻��ʒm����
bool Player::OnHitCollision(GameObject* hit_object)
{
	//�����������̏���
	return FALSE;
}

//�ړ�����
void Player::Movement()
{
	//���͏�Ԃɂ���Č�����ύX����
	float direction = 0.0f;
	if (InputControl::GetKey(KEY_INPUT_LEFT) || InputControl::GetKey(KEY_INPUT_A))			//���ړ�
	{
		direction -= speed;
		flip_flag = TRUE;
	}
	else if (InputControl::GetKey(KEY_INPUT_RIGHT) || InputControl::GetKey(KEY_INPUT_D))	//�E�ړ�
	{
		direction += speed;
		flip_flag = FALSE;
	}

	//�����ɂ���āA�ړ��ʂ̉������s��
	if (direction != 0.0f)
	{
		//�ō����x�𒴂��Ȃ��悤�ɂ���
		float max_speed = Abs<float>((5.0f * 0.5 * direction));
		velocity.x += float(0.3 * direction);
		velocity.x = Min<float>(Max<float>(velocity.x, -max_speed), max_speed);
	}
	else
	{
		//��������
		if (velocity.x < -1e-6f)		//-1e-6f = (0�Ɍ���Ȃ��߂����̒l)
		{
			//���ړ��̌���
			float calc_speed = velocity.x + 0.1f;
			velocity.x = Min<float>(calc_speed, 0.0f);
		}
		else if (velocity.x > 1e-6f)	//1e-6f = (0�Ɍ���Ȃ��߂����̒l)
		{
			//�E�ړ��̌���
			float cale_spped = velocity.x - 0.1f;
			velocity.x = Max<float>(cale_spped, 0.0f);
		}
	}

	//�ǂ̏Փ˃`�F�b�N
	if (location.x < (box_size.x / 2.0f))
	{
		//����
		velocity.x = 0.0f;
		location.x = box_size.x / 2.0f;
	}
	else if (location.x > (640.0f - box_size.x / 2.0f))
	{
		//�E��
		velocity.x = 0.0f;
		location.x = 640.0f - box_size.x / 2.0f;
	}

	//�ʒu���W�������x���ς���
	location += velocity;
}

//�A�j���[�V��������
void Player::AnimationControl()
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