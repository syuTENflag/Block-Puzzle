/*
	ブロックの回転の関数を記述したソース
*/
#include "main.h"

/*
	ここでは、ブロックの右回り回転を行う
	回転時の接地判定をとり、当たり判定とともに大丈夫であれば、
	回転後のブロック情報を落下しているブロックに書き込んで回転を終わらせる。
	もし回転できないのであれば回転する向きをもとに戻す
*/
void my_turn_right() {
	turn_point++;

	my_collision_turn();

	if (collision_flag == false && turnFlg == true) {
		for (int y = 0; y < BLOCK_HEIGHT; y++) {
			for (int x = 0; x < BLOCK_WIDTH; x++) {
				block[y][x] = turn_block[y][x];
			}
		}
	}
	else {
		turn_point--;
	}
}

/*
	ここでは、ブロックの左回り回転を行う
	回転時の接地判定をとり、当たり判定とともに大丈夫であれば、
	回転後のブロック情報を落下しているブロックに書き込んで回転を終わらせる。
	もし回転できないのであれば回転する向きをもとに戻す
*/
void my_turn_left() {
	turn_point += 3;

	my_collision_turn();

	if (collision_flag == false && turnFlg == true) {
		for (int y = 0; y < BLOCK_HEIGHT; y++) {
			for (int x = 0; x < BLOCK_WIDTH; x++) {
				block[y][x] = turn_block[y][x];
			}
		}
	}
	else {
		turn_point -= 3;
	}
}

/*
	ここでは、ブロックの左側の当たり判定をとる
	ブロックがあるマスを見つけたのち、ブロックの左側に何かある場合はフラグをtrueにする
	もしなくとも、ブロックのy座標カウント-ブロックのy座標×ブロックの幅をした値が0より大きく、
	ブロックの左下に何かある場合もフラグをtrueにする
*/
void my_collision_left() {
	collision_flag = false;

	for (int y = 0; y < BLOCK_HEIGHT; y++) {
		for (int x = 0; x < BLOCK_WIDTH; x++) {
			if (block[y][x] != 0) {
				if (stage[block_y + y][block_x + (x - 1)] != 0) {
					collision_flag = true;
				}
				else if ((int)(block_y_count - (block_y * DRAW_BLOCK_WIDTH)) > 0) {
					if (stage[block_y + (y + 1)][block_x + (x - 1)] != 0) {
						collision_flag = true;
					}
				}
			}
		}
	}
}

/*
	ここでは、ブロックの右側の当たり判定をとる
	ブロックがあるマスを見つけたのち、ブロックの右側に何かある場合はフラグをtrueにする
	もしなくとも、ブロックのy座標カウント-ブロックのy座標×ブロックの幅をした値が0より大きく、
	ブロックの右下に何かある場合もフラグをtrueにする
*/
void my_collision_right() {
	collision_flag = false;

	for (int y = 0; y < BLOCK_HEIGHT; y++) {
		for (int x = 0; x < BLOCK_WIDTH; x++) {
			if (block[y][x] != 0) {
				if (stage[block_y + y][block_x + (x + 1)] != 0) {
					collision_flag = true;
				}
				else if ((int)(block_y_count - (block_y * DRAW_BLOCK_WIDTH)) > 0) {
					if (stage[block_y + (y + 1)][block_x + (x + 1)] != 0) {
						collision_flag = true;
					}
				}
			}
		}
	}
}

/*
	ここでは、ブロックの下側の当たり判定をとる
	ブロックがあるマスを見つけたのち、ブロックの下側に何かある場合はフラグをtrueにする
*/
void my_collision_bottom() {
	collision_flag = false;

	for (int y = 0; y < BLOCK_HEIGHT; y++) {
		for (int x = 0; x < BLOCK_WIDTH; x++) {
			if (block[y][x] != 0) {
				if (stage[block_y + (y + 1)][block_x + x] != 0) {
					collision_flag = true;
				}
			}
		}
	}
}

/*
	ここでは、ブロックがあるところの当たり判定をとる
	ブロックがあるマスを見つけたのち、ブロックのとおなじところに何かある場合はフラグをtrueにする
*/
void my_collision_center() {
	collision_flag = false;

	for (int y = 0; y < BLOCK_HEIGHT; y++) {
		for (int x = 0; x < BLOCK_WIDTH; x++) {
			if (block[y][x] != 0) {
				if (stage[block_y + y][block_x + x] != 0) {
					collision_flag = true;
				}
			}
		}
	}
}

/*
	ここでは、ブロックの回転時の当たり判定をとる

	まず回転後のブロックを回転しているブロックに入れて一度回転できる状態にする
	その後、ブロックがあるマスを見つけたのち、ブロックの上下左右すべてを判定し、
	何かある場合は何もない方にブロックの座標をずらす
	この時、一つずらすだけでは対応できないブロック（5）があり、そのパターンになった場合はさらに一つずらす
	そして、何もないところにブロックがたどり着いたら回転後のブロックに生成されているブロックを入れる
*/
void my_collision_turn() {
	for (int y = 0; y < BLOCK_HEIGHT; y++) {
		for (int x = 0; x < BLOCK_WIDTH; x++) {
			turn_block[y][x] =
				blocks[(block_id * BLOCK_HEIGHT) + y][(turn_point % 4 * BLOCK_WIDTH) + x];
		}
	}

	collision_flag = false;
	turnFlg = true;

	for (int y = 0; y < BLOCK_HEIGHT; y++) {
		for (int x = 0; x < BLOCK_WIDTH; x++) {
			if (turn_block[y][x] != 0) {
				if (stage[block_y + y][block_x + x] != 0) {
					if (x <= 1) {
						block_x++;
						if (stage[block_y + y][block_x + x + 2] != 0) {
							block_x--;
							turnFlg = false;
							return;
						}
						else if (block_id == 5) {
							if (stage[block_y + y][block_x + x + 3] != 0) {
								block_x--;
								turnFlg = false;
								return;
							}
							else if (x == 1) {
								block_x++;
							}
						}
					}
					else if (x >= 2) {
						block_x--;
						if (stage[block_y + y][block_x + x - 2] != 0) {
							block_x++;
							turnFlg = false;
							return;
						}
						else if (block_id == 5) {
							if (stage[block_y + y][block_x + x - 3] != 0) {
								block_x++;
								turnFlg = false;
								return;
							}
							else if (x == 2) {
								block_x--;
							}
						}
					}
					else if (y <= 1) {
						block_y++;
						if (stage[block_y + y + 2][block_x + x] != 0) {
							block_y--;
							turnFlg = false;
							return;
						}
						else if (block_id == 5) {
							if (stage[block_y + y + 3][block_x + x] != 0) {
								block_y--;
								turnFlg = false;
								return;
							}
							else if (y == 1) {
								block_y++;
							}
						}
					}
					else if (y >= 2) {
						block_y--;
						if (stage[block_y + y - 2][block_x + x] != 0) {
							block_y++;
							turnFlg = false;
							return;
						}
						else if (block_id == 5) {
							if (stage[block_y + y - 3][block_x + x] != 0) {
								block_y++;
								turnFlg = false;
								return;
							}
							else if (y == 2) {
								block_y--;
							}
						}
					}
					else {
						turn_block[y][x] = block[y][x];
					}
				}
			}
		}
	}
}