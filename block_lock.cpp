/*
	ブロック固定関係の関数を記述したソース
*/
#include "main.h"

// パブリック変数宣言
int clear_line_point[STAGE_HEIGHT - 3];	// ステージの各列そろっているかどうかみるもの
int back_img1;							// 背景画像を格納する変数
int key[256];							// 入力されたキーコードを格納する変数

/*
	ブロック固定を２段階に分けて行う
	最初は固定せずにその時のブロックのy座標を保存し、固定までのカウントを始める
	その後、指定したカウント後も同じy座標にブロックがあるようなら固定させる
*/
void my_fix_block() {
	// 落下速度より早く下との当たり判定をとる
	my_collision_bottom();

	/*
		当たり判定が大丈夫なら、
		ブロックが接地しているかを判定し、
		接地していたらブロックを保存し、横一列そろっているかを判定する
		もしブロックが消されなかったらここでブロックを出すたびに初期化が必要な変数の初期化を行う

		ブロックが接地していない場合は、格納しているy座標とブロックのy座標が同じかどうか判定し、
		同じならブロック固定カウントを増やし、同じでなければブロック固定カウントを0クリアする
		そしてy座標を格納し、y座標のカウントを落下スピード分減らす
	*/
	if (collision_flag == true) {
		if (block_y_point == block_y && fix_count > 10) {
			my_save_block();
			my_search_line();
			if (clear_flag == false) {
				my_init_var2();
			}
		}
		else {
			if (block_y_point == block_y) {
				fix_count++;
			}
			else {
				fix_count = 0;
			}
			block_y_point = block_y;
			block_y_count -= block_speed;
		}
	}
}

/*
	ブロックが接地した際、横一列全てのマスにブロックがある場合消さないといけない

	まずステージの各列がそろっているかどうかを見る変数を0クリアする。
	その後、横のマスを調べていき、何もないマス（0）を見つけたらclear_line_pointを1にしてその列は終わりにする
	最後まで終わったところでclear_line_pointが0な列があったら消されたか管理するフラグをtrueにしてスコアを増やす
*/
void my_search_line() {
	for (int i = 0; i < STAGE_HEIGHT - 3; i++) {
		clear_line_point[i] = 0;
	}

	for (int i = 0; i < STAGE_HEIGHT - 3; i++) {
		for (int j = 3; j < STAGE_WIDTH - 3; j++) {
			if (stage[i][j] == 0) {
				clear_line_point[i] = 1;
				break;
			}
		}
	}

	for (int i = 0; i < STAGE_HEIGHT - 3; i++) {
		if (clear_line_point[i] == 0) {
			clear_flag = true;
			score++;
		}
	}
}

/*
	ここではブロックを横一列消す処理をする

	まず横の列が消されたかどうかの変数が横のステージ（10）分になっていなければすべてブロックで埋まっている列を何もなしにしていく
	その後、消された列と消されてない列を区別するプライベートな配列を用いて消された列とそうでない列を区別する
	そして区別が終わったら、消された列の上にあるブロックをすべて消された分だけ下に下げる

	これらの処理が終わったら消されたかどうかのフラグをfalseにしカウンターを0にし、
	ブロックを出すたびに初期化が必要な変数の初期化を行い、レベルの管理をする
*/
void my_clear_line() {
	// この関数でのみ使用するプライベート変数定義
	// 二つともこの関数が呼ばれた際に0クリアする
	int remain_line_point[20] = { 0 };	// 消された列と消されてない列を区別する配列
	int remain_line_index = 0;			// 列用のカウンター

	if (clear_count < 10) {
		for (int i = 0; i < STAGE_HEIGHT - 4; i++) {
			if (clear_line_point[i] == 0) {
				stage[i][clear_count + 4] = 0;
			}
		}
		clear_count++;
	}
	else {
		for (int i = STAGE_HEIGHT - 4; i >= 0; i--) {
			if (clear_line_point[i] != 0) {
				remain_line_point[remain_line_index] = i;
				remain_line_index++;
			}
		}

		remain_line_index = 0;
		for (int i = STAGE_HEIGHT - 4; i >= 0; i--) {
			for (int j = 3; j < STAGE_WIDTH - 3; j++) {
				stage[i][j] = stage[remain_line_point[remain_line_index]][j];
			}
			remain_line_index++;
		}

		clear_flag = false;
		clear_count = 0;
		my_init_var2();
		my_change_lv();
	}
}

/*
	ここでは接地したブロックをステージの座標に保存する
*/
void my_save_block() {
	int x, y;

	for (y = 0; y < BLOCK_HEIGHT; y++) {
		for (x = 0; x < BLOCK_WIDTH; x++) {
			stage[block_y + y][block_x + x] += block[y][x];
		}
	}

	//もしそのブロックが落ちている最中にホールドしていたらフラグをfalseに戻す
	if (holdflg == true)
	{
		holdflg = false;
	}
}

/*
	ここではブロックのy座標を管理する
	スピードやカウントはy座標よりWIDTH分大きいため割る
*/
void my_fall_block() {
	if (make_block_flag == false) {
		block_y_count += block_speed;
		block_y = (int)block_y_count / DRAW_BLOCK_WIDTH;
	}
}

/*
	ここでは入力されたキーの値を配列に取り込む処理をする
*/
void my_get_key() {
	char keys[256];

	GetHitKeyStateAll(keys);
	for (int i = 0; i < 256; i++) {
		if (keys[i] != 0) {
			key[i]++;
		}
		else {
			key[i] = 0;
		}
	}
}