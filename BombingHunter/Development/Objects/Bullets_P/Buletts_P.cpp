#include"Bullets_P.h"
#include"../Player/Player.h"
#include"../../Utility/InputControl.h"
#include"../../Utility/UserTemplate.h"
#include"DxLib.h"
#include"math.h"

#define ��	(3.141592653589793)	//�~����

//�R���X�g���N�^
Bullets_P::Bullets_P() :
	animation(),
	speed(1.0)
{
	animation[0] = NULL;
	animation[1] = NULL;
	animation[2] = NULL;
	animation[3] = NULL;

	velocity = 0.0;
}

//�f�X�g���N�^
Bullets_P::~Bullets_P()
{

}

//����������
void Bullets_P::Initialize()
{
	//�I�u�W�F�N�g�^�C�v�̐ݒ�
	object_type = BULLETS_P;

	//�摜�̓ǂݍ���
	animation[0] = LoadGraph("Resource/Images/�g���e/���e.png");
	animation[1] = LoadGraph("Resource/Images/�g���e/����1.png");
	animation[2] = LoadGraph("Resource/Images/�g���e/����2.png");
	animation[3] = LoadGraph("Resource/Images/�g���e/����3.png");

	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1 || animation[2] == -1 || animation[3] == -1)
	{
		throw("�g���e�̉摜������܂���\n");
	}

	//�����̐ݒ�
	radian = �� / 2;

	//�傫���̐ݒ�
	box_size = 48.0;

	//�����摜�̐ݒ�
	image = animation[0];

	//�e��(�^���I��)����������
	if ((InputControl::GetKey(KEY_INPUT_LEFT) || InputControl::GetKey(KEY_INPUT_A)) == FALSE &&	//�����͂��Ȃ�
		(InputControl::GetKey(KEY_INPUT_RIGHT) || InputControl::GetKey(KEY_INPUT_D)) == FALSE)	//�E���͂��Ȃ�
	{
		velocity.x = 0.0;
	}
	if ((InputControl::GetKey(KEY_INPUT_LEFT) || InputControl::GetKey(KEY_INPUT_A)) == TRUE &&	//�����͂�����
		(InputControl::GetKey(KEY_INPUT_RIGHT) || InputControl::GetKey(KEY_INPUT_D)) == FALSE)	//�E���͂��Ȃ�
	{
		velocity.x -= 3.0;
	}
	if ((InputControl::GetKey(KEY_INPUT_LEFT) || InputControl::GetKey(KEY_INPUT_A)) == FALSE &&	//�����͂��Ȃ�
		(InputControl::GetKey(KEY_INPUT_RIGHT) || InputControl::GetKey(KEY_INPUT_D)) == TRUE)	//�E���͂�����
	{
		velocity.x += 3.0;
	}
}

//�X�V����
void Bullets_P::Update()
{
	//�ړ�����
	Movement();
	//�`�揈��
	Draw();
}

//�`�揈��
void Bullets_P::Draw()const
{
	//�g���e�摜�̕`��
	DrawRotaGraphF(location.x, location.y, OBJECTSIZE, radian + (-velocity.x / ��), image, TRUE, FALSE);

	//�f�o�b�O�p
#if _DEBUG
	//�����蔻��̉���
	Vector2D ul = location - (box_size / 2.0f);		//box_collision_upper_left   =  ul  =  ����
	Vector2D lr = location + (box_size / 2.0f);		//box_collision_lower_right  =  lr  =  �E��

	DrawBoxAA(ul.x, ul.y, lr.x, lr.y, GetColor(255, 0, 0), FALSE);
#endif
}

//�I��������
void Bullets_P::Finalize()
{
	//�g�p�����摜���J������
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
	DeleteGraph(animation[2]);
	DeleteGraph(animation[3]);
}

//�����蔻��ʒm����
bool Bullets_P::OnHitCollision(GameObject* hit_object)
{
	//�����������̏���
	bool value = FALSE;
	int type = hit_object->GetObjectType();

	if (type == ENEMY1)
	{
		value = TRUE;
	}

	return value;
}

//�ړ�����
void Bullets_P::Movement()
{
	//�ō����x�𒴂��Ȃ��悤�ɂ���
	float max_speed = Abs<float>((5.0f * 0.5 * speed));
	velocity.y += float(0.3 * speed);
	velocity.y = Min<float>(Max<float>(velocity.y, -max_speed), max_speed);
	
	//��������
	if (velocity.x < -1e-6f)		//-1e-6f = (0�Ɍ���Ȃ��߂����̒l)
	{
		//���ړ��̌���
		float calc_speed = velocity.x + 0.02f;
		velocity.x = Min<float>(calc_speed, 0.0f);
	}
	else if (velocity.x > 1e-6f)	//1e-6f = (0�Ɍ���Ȃ��߂����̒l)
	{
		//�E�ړ��̌���
		float cale_spped = velocity.x - 0.02f;
		velocity.x = Max<float>(cale_spped, 0.0f);
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

	location += velocity;
}

//�A�j���[�V��������
void Bullets_P::AnimationControl()
{

}