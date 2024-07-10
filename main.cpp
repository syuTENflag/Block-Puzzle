/*
	WinMain関数のあるメインの処理部分のソース
*/
#include "main.h"

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	/*
		ウィンドウやDXライブラリの初期化処理
	*/
	ChangeWindowMode(FALSE);			// ウィンドウ組み立て
	DxLib_Init();					// DXライブラリの初期化
	SetDrawScreen(DX_SCREEN_BACK);	// スクリーンをセット

	/*
		ゲームの初期化処理
	*/
	firstInitFlg = true;	// 初回起動時のみここの処理が実行されるのでtrueにセット
	my_init_var();			// ゲームの初期化関数を呼び出し

	/*
		ゲームのメイン処理（ウィンドウメッセージ処理が成功しているときのみ）
	*/
	while (ProcessMessage() == 0) {

		// 画面に描画されたものを一度消去する
		ClearDrawScreen();

		// 以下ゲームの進行処理
		/*
			ゲームの状態に関係なく処理されるもの
		*/
		my_get_key();	// キー入力時の処理
		my_draw_back();	// 背景描画処理

		/*
			以下の処理はゲームの状態によって処理を振り分け
		*/
		switch (game_state) {
			
		// game_state = GAME_INITの時（タイトル画面表示の時）
		case GAME_INIT:
			TitleDraw();	// タイトルの描画
			break;

		// game_state = GAME_PLAYINGの時（ゲームプレイ中）
		case GAME_PLAYING:

			/*
				ゲームプレイ中は必ず処理されるもの
			*/
			my_draw_stage();	// ステージの描画
			my_draw_variable();	// スコア、ネクストブロック、ホールドブロックの描画

			// ESCキーを押すとタイトルへ戻るかどうか選択
			if (key[KEY_INPUT_ESCAPE] == 1) {
			//if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_H) { //タッチパッド
				game_state = GAME_MENU;
			}

			/*
				ブロックが消せるかどうかで処理を振り分け
			*/
			// ブロックが消せない時
			if (clear_flag == false) {
				my_make_block();	// ブロックを生成する
				my_gameover();		// ゲームオーバーかどうか判定する
				my_move_block();	// キーボードを押したことによりブロックを動かす処理
				my_draw_block();	// ブロック落下中にブロックを描画する
				my_fix_block();		// ブロックを固定する
				my_fall_block();	// ブロックを落下させる
			}
			// ブロックが消せる時
			else {
				my_clear_line();	// ブロックが横一列埋まって消すときの処理をする
			}
			
			// ゲームオーバー時はgame_state = GAME_OVERにして音楽を止める
			if (gameover_flag == true) {
				game_state = GAME_OVER;
				StopSoundMem(gameSound);
			}

			break;

		// game_state = GAME_MENUの時（メニュー画面の時）
		case GAME_MENU:
			ChoiceBackTitle();	// タイトルに戻るか関数内で選択
			break;

		// game_state = GAME_OVERの時（ゲームオーバーの時）
		case GAME_OVER:
			my_ed();	// ゲームオーバー時の処理
			break;

		// それ以外の時（何もしないでbreak）
		default:
			break;
		}

		// 画面に描画
		ScreenFlip();
	}

	/*
		ゲームの終了処理
	*/
	DxLib_End();	// DXライブラリの終了処理
	return 0;
}