#pragma once

#define D_KEYCODE_MAX	(256)

//�N���X��`
class InputControl
{
private:
	static char now_key[D_KEYCODE_MAX];				//�����Ă���L�[
	static char old_key[D_KEYCODE_MAX];				//�����Ă����L�[

public:
	static void Update();							//���͋@�\�X�V����

	static bool GetKey(int key_code);				//�����Ă���L�[�擾
	static bool GetKeyDown(int key_code);			//�������u�Ԏ擾
	static bool GetKeyUp(int key_code);				//�������u�Ԏ擾

private:
	static bool CheckKeyCodeRange(int key_code);	//�L�[�R�[�h�͈̓`�F�b�N
};