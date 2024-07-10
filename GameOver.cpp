/*
	ゲームオーバー処理のソース
*/
#include "main.h"

// ゲームオーバーかどうか判定する
// もし当たり判定のフラグがtrueのままであればゲームオーバーフラグをtrueする
void my_gameover() {
	my_collision_center();

	if (collision_flag == true) {
		gameover_flag = true;
	}
}

// ゲームオーバー画面の時の処理
void my_ed() {
	// 文字のフォントサイズを指定し描画させる
	SetFontSize(75);
	DrawFormatString(150, 100, Color_Red, "GAME OVER");
	SetFontSize(40);
	DrawFormatString(220, 240, Color_Aqua, "SCORE：%d", score * 10);

	SetFontSize(30);

	DrawFormatString(170, 340, Color_Aqua, "タッチパッドを押して\n  スタート画面へ");
	
	// エンターキーもしくはタッチパッドで初期化処理を行わせつつタイトルへ画面遷移させる
	if (key[KEY_INPUT_RETURN] == 1) {
	//if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_H) { //タッチパッド
		game_state = GAME_INIT;
		gameover_flag = false;
		my_init_var();
		//WaitTimer(100);
		// ゲーム内で使うフォントサイズを指定する(ないとスコアと同じになる)
		SetFontSize(DRAW_BLOCK_WIDTH);
	}
}