#include"GameObject.h"
#include"DxLib.h"

//�R���X�g���N�^
GameObject::GameObject() :
	location(0.0),
	box_size(0.0),
	radian(0.0),
	image(0),
	sound(0),
	flip_flag(FALSE),
	object_type(0)
{

}

//�f�X�g���N�^
GameObject::~GameObject()
{

}

//����������
void GameObject::Initialize()
{

}

//�X�V����
void GameObject::Update()
{

}

//�`�揈��
void GameObject::Draw() const
{

}

//�I��������
void GameObject::Finalize()
{
	
}

//�I�u�W�F�N�g�^�C�v�擾����
int GameObject::GetObjectType()const
{
	return this->object_type;
}

//�����蔻��ʒm����
bool GameObject::OnHitCollision(GameObject* hit_object)
{
	//�����������ɍs������
	return FALSE;
}

//��`���擾����
Vector2D GameObject::GetBoxSize() const
{
	return this->box_size;
}

//�ʒu���擾����
Vector2D GameObject::GetLocation() const
{
	return this->location;
}

//�ʒu���ύX����
void GameObject::SetLocation(const Vector2D& location)
{
	this->location = location;
}

//���]���ύX����
void GameObject::SetFlipFlag(bool flip)
{
	this->flip_flag = flip;
}