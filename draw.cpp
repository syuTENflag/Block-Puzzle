/*
	描画の関数を記述したソース
*/
#include "main.h"

// パブリック変数宣言
int lv;				// ゲームのレベルを定義する変数
int score;			// スコアを格納する変数

// 以下はすべて色の変数
int Color_Red;		// 赤
int Color_Black;	// 黒
int Color_Green;	// 緑
int Color_Blue;		// 青
int Color_Yellow;	// 黄
int Color_Fuchsia;	// 紫
int Color_Aqua;		// 空色
int Color_Orange;	// オレンジ

// 背景を描画する
void my_draw_back() {
	DrawGraph(0, 0, back_img1, TRUE);
}

// UIやNEXT、HOLDの描画処理を行う関数
void my_draw_variable() {
	// 枠線を描画
	DrawBox(470, 0, 610, 160, Color_Black, FALSE);
	DrawBox(30, 0, 170, 160, Color_Black, FALSE);

	// NEXTの文字を描画
	DrawFormatString(520, 0, Color_Blue, "NEXT");

	// HOLDの文字を描画
	DrawFormatString(80, 0, Color_Yellow, "HOLD");

	// スコアとレベルの区域の文字を描画
	DrawFormatString(480, 100, Color_Red, "SCORE   %d", score * 10);
	DrawFormatString(480, 120, Color_Red, "LINE    %d", score);
	DrawFormatString(480, 140, Color_Red, "LV      %d", lv);

	// NEXTのブロック描画
	for (int y = 0; y < BLOCK_HEIGHT; y++) {
		for (int x = 0; x < BLOCK_WIDTH; x++) {
			if (next_block[y][x] == 1)DrawFormatString(NEXT_BLOCK_X + x * 20, NEXT_BLOCK_Y + y * 20, Color_Yellow, "■");
			else if (next_block[y][x] == 2)DrawFormatString(NEXT_BLOCK_X + x * 20, NEXT_BLOCK_Y + y * 20, Color_Red, "■");
			else if (next_block[y][x] == 3)DrawFormatString(NEXT_BLOCK_X + x * 20, NEXT_BLOCK_Y + y * 20, Color_Green, "■");
			else if (next_block[y][x] == 4)DrawFormatString(NEXT_BLOCK_X + x * 20, NEXT_BLOCK_Y + y * 20, Color_Blue, "■");
			else if (next_block[y][x] == 5)DrawFormatString(NEXT_BLOCK_X + x * 20, NEXT_BLOCK_Y + y * 20, Color_Fuchsia, "■");
			else if (next_block[y][x] == 6)DrawFormatString(NEXT_BLOCK_X + x * 20, NEXT_BLOCK_Y + y * 20, Color_Aqua, "■");
			else if (next_block[y][x] == 7)DrawFormatString(NEXT_BLOCK_X + x * 20, NEXT_BLOCK_Y + y * 20, Color_Orange, "■");
		}
	}

	// HOLDのブロック描画
	for (int y = 0; y < BLOCK_HEIGHT; y++) {
		for (int x = 0; x < BLOCK_WIDTH; x++) {
			if (hold_block[y][x] == 1)DrawFormatString(HOLD_BLOCK_X + x * 20, HOLD_BLOCK_Y + y * 20, Color_Yellow, "■");
			else if (hold_block[y][x] == 2)DrawFormatString(HOLD_BLOCK_X + x * 20, HOLD_BLOCK_Y + y * 20, Color_Red, "■");
			else if (hold_block[y][x] == 3)DrawFormatString(HOLD_BLOCK_X + x * 20, HOLD_BLOCK_Y + y * 20, Color_Green, "■");
			else if (hold_block[y][x] == 4)DrawFormatString(HOLD_BLOCK_X + x * 20, HOLD_BLOCK_Y + y * 20, Color_Blue, "■");
			else if (hold_block[y][x] == 5)DrawFormatString(HOLD_BLOCK_X + x * 20, HOLD_BLOCK_Y + y * 20, Color_Fuchsia, "■");
			else if (hold_block[y][x] == 6)DrawFormatString(HOLD_BLOCK_X + x * 20, HOLD_BLOCK_Y + y * 20, Color_Aqua, "■");
			else if (hold_block[y][x] == 7)DrawFormatString(HOLD_BLOCK_X + x * 20, HOLD_BLOCK_Y + y * 20, Color_Orange, "■");

		}
	}
}

// ここでは落下中のブロックを描画
void my_draw_block() {
	for (int y = 0; y < BLOCK_HEIGHT; y++) {
		for (int x = 0; x < BLOCK_WIDTH; x++) {
			if (block[y][x] == 1)DrawFormatString(DRAW_POSITION + block_x * DRAW_BLOCK_WIDTH + x * DRAW_BLOCK_WIDTH,
				(int)block_y_count + y * DRAW_BLOCK_WIDTH, Color_Yellow, "■");
			else if (block[y][x] == 2)DrawFormatString(DRAW_POSITION + block_x * DRAW_BLOCK_WIDTH + x * DRAW_BLOCK_WIDTH,
				(int)block_y_count + y * DRAW_BLOCK_WIDTH, Color_Red, "■");
			else if (block[y][x] == 3)DrawFormatString(DRAW_POSITION + block_x * DRAW_BLOCK_WIDTH + x * DRAW_BLOCK_WIDTH,
				(int)block_y_count + y * DRAW_BLOCK_WIDTH, Color_Green, "■");
			else if (block[y][x] == 4)DrawFormatString(DRAW_POSITION + block_x * DRAW_BLOCK_WIDTH + x * DRAW_BLOCK_WIDTH,
				(int)block_y_count + y * DRAW_BLOCK_WIDTH, Color_Blue, "■");
			else if (block[y][x] == 5)DrawFormatString(DRAW_POSITION + block_x * DRAW_BLOCK_WIDTH + x * DRAW_BLOCK_WIDTH,
				(int)block_y_count + y * DRAW_BLOCK_WIDTH, Color_Fuchsia, "■");
			else if (block[y][x] == 6)DrawFormatString(DRAW_POSITION + block_x * DRAW_BLOCK_WIDTH + x * DRAW_BLOCK_WIDTH,
				(int)block_y_count + y * DRAW_BLOCK_WIDTH, Color_Aqua, "■");
			else if (block[y][x] == 7)DrawFormatString(DRAW_POSITION + block_x * DRAW_BLOCK_WIDTH + x * DRAW_BLOCK_WIDTH,
				(int)block_y_count + y * DRAW_BLOCK_WIDTH, Color_Orange, "■");
		}
	}
}

// ここでは接地後のブロックを描画
void my_draw_stage() {
	for (int y = 0; y < STAGE_HEIGHT - 2; y++) {
		for (int x = 2; x < STAGE_WIDTH - 2; x++) {
			if (stage[y][x] == 1)DrawFormatString(DRAW_POSITION + x * DRAW_BLOCK_WIDTH,
				y * DRAW_BLOCK_WIDTH, Color_Yellow, "■");
			else if (stage[y][x] == 2)DrawFormatString(DRAW_POSITION + x * DRAW_BLOCK_WIDTH,
				y * DRAW_BLOCK_WIDTH, Color_Red, "■");
			else if (stage[y][x] == 3)DrawFormatString(DRAW_POSITION + x * DRAW_BLOCK_WIDTH,
				y * DRAW_BLOCK_WIDTH, Color_Green, "■");
			else if (stage[y][x] == 4)DrawFormatString(DRAW_POSITION + x * DRAW_BLOCK_WIDTH,
				y * DRAW_BLOCK_WIDTH, Color_Blue, "■");
			else if (stage[y][x] == 5)DrawFormatString(DRAW_POSITION + x * DRAW_BLOCK_WIDTH,
				y * DRAW_BLOCK_WIDTH, Color_Fuchsia, "■");
			else if (stage[y][x] == 6)DrawFormatString(DRAW_POSITION + x * DRAW_BLOCK_WIDTH,
				y * DRAW_BLOCK_WIDTH, Color_Aqua, "■");
			else if (stage[y][x] == 7)DrawFormatString(DRAW_POSITION + x * DRAW_BLOCK_WIDTH,
				y * DRAW_BLOCK_WIDTH, Color_Orange, "■");
			else if (stage[y][x] == 9)DrawFormatString(DRAW_POSITION + x * DRAW_BLOCK_WIDTH,
				y * DRAW_BLOCK_WIDTH, Color_Black, "■");
		}
	}
}