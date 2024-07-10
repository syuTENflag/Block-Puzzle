/*
	タイトル画面処理のソース
*/
#include "main.h"

// パブリック変数宣言
int gameSound;	// BGMを格納する変数

// タイトル画面の描画をする関数
void TitleDraw() {
	// タイトル名のフォントサイズを指定し指定の座標に描画する
	SetFontSize(75);
	DrawFormatString(88, 150, Color_Yellow, "BLOCK PUZZLE");

	// 指示のフォントサイズを指定し指定の座標に描画する
	SetFontSize(40);
	DrawFormatString(50, 240, Color_Yellow, "ENTERキーorPSコントローラーの\nタッチパッドを押して\n　　　スタート");

	if (key[KEY_INPUT_RETURN] == 1) {
		if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_H) {// タッチパッド
			game_state = GAME_PLAYING;
			PlaySoundMem(gameSound, DX_PLAYTYPE_LOOP);
			//WaitTimer(100);

			// ゲーム内で使うフォントサイズを指定する(ないと指示と同じになる)
			SetFontSize(DRAW_BLOCK_WIDTH);
		}
	}
}