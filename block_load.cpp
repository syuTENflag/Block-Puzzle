/*
	ブロック生成と動作（一部）の関数を記述したソース
*/
#include "main.h"

// パブリック変数宣言
int block[BLOCK_HEIGHT][BLOCK_WIDTH];									// 現在メインで生成され落下しているブロック
int turn_block[BLOCK_HEIGHT][BLOCK_WIDTH];								// 回転しているブロック
int next_block[BLOCK_HEIGHT][BLOCK_WIDTH];								// 次のブロック
int hold_block[BLOCK_HEIGHT][BLOCK_WIDTH];								// ホールドされているブロック
int useBlocks[BLOCK_NONUM];												// 今どのブロックが使われているか
int blocks[BLOCK_HEIGHT * BLOCK_NONUM][BLOCK_WIDTH * BLOCK_PATTERN];	// ブロックの各種のすべての向きを定義したもの

/*
	ブロック生成を２段階に分けて行う
	まず先に生成したブロックを「next_block_id」に保存
	すぐに「block_id」に保存し直す
	再びブロック生成処理を行い「next_block_id」に保存する
	２回目以降はこれを繰り返す
*/
void my_make_block() {
	// この関数でのみ使用するプライベート変数定義
	bool randBlockFlg = true;	// ランダムなブロックIDが取得できるかどうかのフラグ

	// 最初のブロックのフラグがtrueなときに最初のブロックを取得
	if (first_block_flag == true) {
		// 最初は3種類の中から選ぶ
		next_block_id = (rand() % 3);

		// 使っているブロックの配列にIDを入れカウントを増やす
		useBlocks[useBlockCnt] = next_block_id;
		useBlockCnt++;

		// IDに対応したブロックを生成
		for (int y = 0; y < BLOCK_HEIGHT; y++) {
			for (int x = 0; x < BLOCK_WIDTH; x++) {
				next_block[y][x] = blocks[(next_block_id * BLOCK_HEIGHT) + y][x];
			}
		}

		// 最初の生成かどうかのフラグをfalseにする
		first_block_flag = false;
	}

	/*七種一巡の処理*/

	// ブロックが作れるかどうかのフラグがtrueなときに作る
	if (make_block_flag == true) {
		// 次のIDを今のIDに入れる
		block_id = next_block_id;

		// ランダムなブロックIDが取得できるかどうかのフラグがtrueなときにランダムなブロックIDを取得する
		while (randBlockFlg == true) {
			next_block_id = (rand() % BLOCK_NONUM);
			// 使われているブロックのカウントが0の時はそのまま入れてループを抜ける
			if (useBlockCnt == 0) {
				useBlocks[useBlockCnt] = next_block_id;
				randBlockFlg = false;
			}

			// それ以外の時はループで重複を調べる
			for (int i = 0; i < useBlockCnt; i++) {
				if (next_block_id == useBlocks[i]) {
					break;
				}
				// iがuseBlockCnt - 1のときは値を入れてループを抜ける
				else if (i == useBlockCnt - 1) {
					useBlocks[useBlockCnt] = next_block_id;
					randBlockFlg = false;
				}
			}
		}

		// IDに対応したブロックを生成（今と次の）
		for (int y = 0; y < BLOCK_HEIGHT; y++) {
			for (int x = 0; x < BLOCK_WIDTH; x++) {
				block[y][x] = next_block[y][x];
				next_block[y][x] = blocks[(next_block_id * BLOCK_HEIGHT) + y][x];
			}
		}

		// フラグをfalseにする
		make_block_flag = false;

		// カウントが6になったら初期化（それ以外はuseBlockCntを増やす）
		if (useBlockCnt >= BLOCK_NONUM - 1) {
			useBlockCnt = 0;
			for (int i = 0; i < BLOCK_NONUM; i++) {
				// 0はOミノなため、使われていない7を代入して初期化
				useBlocks[i] = 7;
			}
		}
		else
		{
			useBlockCnt++;
		}
	}
}

/*
	以下はブロックホールド処理
	初回ホールド時はそのまま「hold_block[BLOCK_HEIGHT][BLOCK_WIDTH]」にホールドするブロック情報を入れる
	その時の「block_id」など共に保存、初期化の「my_init_var2()」を行う
	２回目以降は先ほどの「hold_block[BLOCK_HEIGHT][BLOCK_WIDTH]」との入れ替え処理を行い
	そのままブロックの位置だけを元に戻す
*/
void my_hold_block() {
	// この関数でのみ使用するプライベート変数定義
	int tmp_block[BLOCK_HEIGHT][BLOCK_WIDTH] = { 0 };	// 入れ替え用のブロック
	int tmp_block_id;									// 入れ替え用のブロックID
	int tmp_turn_point;									// 入れ替え用のブロックの向き

	// 処理の前にフラグをtrueにする
	holdflg = true;

	/*
		最初のホールドの時
		直接ホールド用の変数にホールドしたいブロック情報を入れる
	*/
	if (first_hold_flag == true) {
		for (int y = 0; y < BLOCK_HEIGHT; y++) {
			for (int x = 0; x < BLOCK_WIDTH; x++) {
				hold_block[y][x] = block[y][x];
			}
		}
		hold_block_id = block_id;
		hold_turn_point = turn_point;

		// 以下次のブロック出現に向けた初期化、生成処理
		my_init_var2();
		my_make_block();
		first_hold_flag = false;
	}

	/*
		最初ではない時
		入れ替え用のtmpがついた変数を用いて
		ホールドしたいブロック情報をそれぞれ入れ替えながら入れる
	*/
	else {
		for (int y = 0; y < BLOCK_HEIGHT; y++) {
			for (int x = 0; x < BLOCK_WIDTH; x++) {
				// 入れ替え処理（ブロック）
				tmp_block[y][x] = block[y][x];
				block[y][x] = hold_block[y][x];
				hold_block[y][x] = tmp_block[y][x];
			}
		}
		// 入れ替え処理（IDと向き情報）
		tmp_block_id = block_id;
		tmp_turn_point = turn_point;
		block_id = hold_block_id;
		turn_point = hold_turn_point;
		hold_block_id = tmp_block_id;
		hold_turn_point = tmp_turn_point;

		// 座標と向きをリセット
		block_x = 7;
		block_y = 0;
		block_y_count = 0;
	}
}

// キーボードを押したことによりブロックを動かす処理
void my_move_block() {
	// コントローラー使用時の処理

	// コントローラー用のプライベート変数定義
	//int GetJoypadNum(void);
	//int GetJoypadInputState(int InputType);
	//int joypadState = GetJoypadInputState(DX_INPUT_PAD1);
	//int flg = 0;

	// 左矢印が押されているとき、左との当たり判定をとって、大丈夫ならブロックを左に動かす
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT)
	{
		my_collision_left();
		if (collision_flag == false) {
			block_x--;
			WaitTimer(60);// 待機時間（ミリ秒）を設定（例えば100ミリ秒）
			return;
		}// 押されている
	}
	// 右矢印が押されているとき、右との当たり判定をとって、大丈夫ならブロックを右に動かす
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT)
	{
		my_collision_right();
		if (collision_flag == false) {
			block_x++;
			WaitTimer(60);// 待機時間（ミリ秒）を設定（例えば100ミリ秒）
		}// 押されている
	}
	// 下矢印が押されているとき、下との当たり判定をとって、大丈夫ならブロックの落下速度を上げる
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN)
	{
		my_collision_bottom();
		if (collision_flag == false) {
			block_y++;
			block_y_count = (float)(block_y * DRAW_BLOCK_WIDTH);
			WaitTimer(50);// 待機時間（ミリ秒）を設定（例えば100ミリ秒）
		}// 押されている
	}
	// 上矢印が押されているときは、現状下と同じ処理を行う
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP)
	{
			my_collision_bottom();
			if (collision_flag == false){
				block_y++;
				block_y_count = (float)(block_y * DRAW_BLOCK_WIDTH);
			}

		// 押されている
	}

	// ○ボタンが押されているときは、当たり判定をとり、大丈夫ならブロックを右回転させる
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_C)
	{
		my_turn_right();// 押されている
		WaitTimer(200);// 待機時間（ミリ秒）を設定
	}
	// ×ボタンが押されているときは、当たり判定をとり、大丈夫ならブロックを左回転させる
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_B)
	{
		my_turn_left();// 押されている
		WaitTimer(200);// 待機時間（ミリ秒）を設定
	}
	// □ボタンが押されていてかつ、現在のブロックが出てから一度もホールドしてないときは、ブロックをホールドさせる
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_A && holdflg == false)
	{
		my_hold_block();// 押されている
		WaitTimer(200);// 待機時間（ミリ秒）を設定
		return;
	}

	// キーボード使用時の処理

	// 左矢印が押されているとき、左との当たり判定をとって、大丈夫ならブロックを左に動かす
	if (key[KEY_INPUT_LEFT] % 7 == 1) {
		my_collision_left();
		if (collision_flag == false) {
			block_x--;
		}
	}

	// 右矢印が押されているとき、右との当たり判定をとって、大丈夫ならブロックを右に動かす
	if (key[KEY_INPUT_RIGHT] % 7 == 1) {
		my_collision_right();
		if (collision_flag == false) {
			block_x++;
		}
	}

	// 下矢印が押されているとき、下との当たり判定をとって、大丈夫ならブロックの落下速度を上げる
	if (key[KEY_INPUT_DOWN] % 7 == 1) {
		my_collision_bottom();
		if (collision_flag == false) {
			block_y++;
			block_y_count = (float)(block_y * DRAW_BLOCK_WIDTH);
		}
	}
	// 上矢印は現状なにもなし
	/*
	if (key[KEY_INPUT_UP]) {
		int x, y;
		my_collision_bottom();
		if (collision_flag == false) {
			block_y++;
			block_y_count = (float)(block_y * DRAW_BLOCK_WIDTH);
		}
	}
		switch (KEY_INPUT_UP)
		{
		case KEY_INPUT_UP:
			while (stage[4][3]);
			stage[4][3];
			break;
		}
	}*/

	// Xキーが押されているときは、当たり判定をとり、大丈夫ならブロックを右回転させる
	if (key[KEY_INPUT_X] == 1) {
		my_turn_right();
	}

	// Zキーが押されているときは、当たり判定をとり、大丈夫ならブロックを左回転させる
	if (key[KEY_INPUT_Z] == 1) {
		my_turn_left();
	}

	// Hキーを押したときにホールド処理（今のブロックが出てから一度もホールドしてない時のみホールド処理を呼び出す）
	if (key[KEY_INPUT_H] == 1 && holdflg == false) {
		my_hold_block();
	}
}