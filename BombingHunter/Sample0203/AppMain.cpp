#include"Dxlib.h"
#include"Utility/InputControl.h"
#include"Scene/Scene.h"

//���C���֐�(�v���O�����͂�������n�܂�܂��B)
int WINAPI WinMain
(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR pCmdLine,
	_In_ int nShowCmd
)
{
	//�E�B���h�E���[�h�ŋN��
	ChangeWindowMode(TRUE);

	//�E�B���h�E�T�C�Y(640�~480)��ݒ�
	SetGraphMode(640, 480, 32);

	//Dx���C�u�����̏�����
	if (DxLib_Init() == -1)
	{
		//�ُ��ʒm
		return -1;
	}

	//�`���𗠉�ʂ���n�߂�悤�Ɏw�肷��
	SetDrawScreen(DX_SCREEN_BACK);

	//���[�J���ϐ���`
	Scene* scene = new Scene();		//�V�[������
	int result = 0;					//�I����ԏ��

	try
	{
		//�V�[���̏�����
		scene->Initialize();

		//���C�����[�v(�E�B���h�E�ُ̈픭�� or ESC�L�[�������ꂽ��A���[�v�I��)
		while (ProcessMessage() != -1 && CheckHitKey(KEY_INPUT_ESCAPE) != TRUE)
		{
			//���͋@�\�̍X�V
			InputControl::Update();

			//�V�[���̍X�V����
			scene->Update();

			//��ʂ̏�����
			ClearDrawScreen();

			//�V�[���̕`�揈��
			scene->Draw();

			//����ʂ̓��e��\��ʂ֔��f
			ScreenFlip();
		}
	}
	catch (const char* error_log)
	{
		//�G���[����Log.txt�ɏo�͂���
		OutputDebugString(error_log);
		//�ُ��Ԃ�ʒm
		result = -1;
	}

	//�V�[�����̍폜
	if (scene != nullptr)
	{
		scene->Finalize();
		delete scene;
		scene = nullptr;
	}

	//Dx���C�u�����g�p�̏I������
	DxLib_End();

	//�I����Ԃ�ʒm
	return result;
}