#pragma once

#define D_KEYCODE_MAX	(256)

//クラス定義
class InputControl
{
private:
	static char now_key[D_KEYCODE_MAX];				//押しているキー
	static char old_key[D_KEYCODE_MAX];				//押していたキー

public:
	static void Update();							//入力機能更新処理

	static bool GetKey(int key_code);				//押しているキー取得
	static bool GetKeyDown(int key_code);			//押した瞬間取得
	static bool GetKeyUp(int key_code);				//離した瞬間取得

private:
	static bool CheckKeyCodeRange(int key_code);	//キーコード範囲チェック
};