/*
	�`��̊֐����L�q�����\�[�X
*/
#include "main.h"

// �p�u���b�N�ϐ��錾
int lv;				// �Q�[���̃��x�����`����ϐ�
int score;			// �X�R�A���i�[����ϐ�

// �ȉ��͂��ׂĐF�̕ϐ�
int Color_Red;		// ��
int Color_Black;	// ��
int Color_Green;	// ��
int Color_Blue;		// ��
int Color_Yellow;	// ��
int Color_Fuchsia;	// ��
int Color_Aqua;		// ��F
int Color_Orange;	// �I�����W

// �w�i��`�悷��
void my_draw_back() {
	DrawGraph(0, 0, back_img1, TRUE);
}

// UI��NEXT�AHOLD�̕`�揈�����s���֐�
void my_draw_variable() {
	// �g����`��
	DrawBox(470, 0, 610, 160, Color_Black, FALSE);
	DrawBox(30, 0, 170, 160, Color_Black, FALSE);

	// NEXT�̕�����`��
	DrawFormatString(520, 0, Color_Blue, "NEXT");

	// HOLD�̕�����`��
	DrawFormatString(80, 0, Color_Yellow, "HOLD");

	// �X�R�A�ƃ��x���̋��̕�����`��
	DrawFormatString(480, 100, Color_Red, "SCORE   %d", score * 10);
	DrawFormatString(480, 120, Color_Red, "LINE    %d", score);
	DrawFormatString(480, 140, Color_Red, "LV      %d", lv);

	// NEXT�̃u���b�N�`��
	for (int y = 0; y < BLOCK_HEIGHT; y++) {
		for (int x = 0; x < BLOCK_WIDTH; x++) {
			if (next_block[y][x] == 1)DrawFormatString(NEXT_BLOCK_X + x * 20, NEXT_BLOCK_Y + y * 20, Color_Yellow, "��");
			else if (next_block[y][x] == 2)DrawFormatString(NEXT_BLOCK_X + x * 20, NEXT_BLOCK_Y + y * 20, Color_Red, "��");
			else if (next_block[y][x] == 3)DrawFormatString(NEXT_BLOCK_X + x * 20, NEXT_BLOCK_Y + y * 20, Color_Green, "��");
			else if (next_block[y][x] == 4)DrawFormatString(NEXT_BLOCK_X + x * 20, NEXT_BLOCK_Y + y * 20, Color_Blue, "��");
			else if (next_block[y][x] == 5)DrawFormatString(NEXT_BLOCK_X + x * 20, NEXT_BLOCK_Y + y * 20, Color_Fuchsia, "��");
			else if (next_block[y][x] == 6)DrawFormatString(NEXT_BLOCK_X + x * 20, NEXT_BLOCK_Y + y * 20, Color_Aqua, "��");
			else if (next_block[y][x] == 7)DrawFormatString(NEXT_BLOCK_X + x * 20, NEXT_BLOCK_Y + y * 20, Color_Orange, "��");
		}
	}

	// HOLD�̃u���b�N�`��
	for (int y = 0; y < BLOCK_HEIGHT; y++) {
		for (int x = 0; x < BLOCK_WIDTH; x++) {
			if (hold_block[y][x] == 1)DrawFormatString(HOLD_BLOCK_X + x * 20, HOLD_BLOCK_Y + y * 20, Color_Yellow, "��");
			else if (hold_block[y][x] == 2)DrawFormatString(HOLD_BLOCK_X + x * 20, HOLD_BLOCK_Y + y * 20, Color_Red, "��");
			else if (hold_block[y][x] == 3)DrawFormatString(HOLD_BLOCK_X + x * 20, HOLD_BLOCK_Y + y * 20, Color_Green, "��");
			else if (hold_block[y][x] == 4)DrawFormatString(HOLD_BLOCK_X + x * 20, HOLD_BLOCK_Y + y * 20, Color_Blue, "��");
			else if (hold_block[y][x] == 5)DrawFormatString(HOLD_BLOCK_X + x * 20, HOLD_BLOCK_Y + y * 20, Color_Fuchsia, "��");
			else if (hold_block[y][x] == 6)DrawFormatString(HOLD_BLOCK_X + x * 20, HOLD_BLOCK_Y + y * 20, Color_Aqua, "��");
			else if (hold_block[y][x] == 7)DrawFormatString(HOLD_BLOCK_X + x * 20, HOLD_BLOCK_Y + y * 20, Color_Orange, "��");

		}
	}
}

// �����ł͗������̃u���b�N��`��
void my_draw_block() {
	for (int y = 0; y < BLOCK_HEIGHT; y++) {
		for (int x = 0; x < BLOCK_WIDTH; x++) {
			if (block[y][x] == 1)DrawFormatString(DRAW_POSITION + block_x * DRAW_BLOCK_WIDTH + x * DRAW_BLOCK_WIDTH,
				(int)block_y_count + y * DRAW_BLOCK_WIDTH, Color_Yellow, "��");
			else if (block[y][x] == 2)DrawFormatString(DRAW_POSITION + block_x * DRAW_BLOCK_WIDTH + x * DRAW_BLOCK_WIDTH,
				(int)block_y_count + y * DRAW_BLOCK_WIDTH, Color_Red, "��");
			else if (block[y][x] == 3)DrawFormatString(DRAW_POSITION + block_x * DRAW_BLOCK_WIDTH + x * DRAW_BLOCK_WIDTH,
				(int)block_y_count + y * DRAW_BLOCK_WIDTH, Color_Green, "��");
			else if (block[y][x] == 4)DrawFormatString(DRAW_POSITION + block_x * DRAW_BLOCK_WIDTH + x * DRAW_BLOCK_WIDTH,
				(int)block_y_count + y * DRAW_BLOCK_WIDTH, Color_Blue, "��");
			else if (block[y][x] == 5)DrawFormatString(DRAW_POSITION + block_x * DRAW_BLOCK_WIDTH + x * DRAW_BLOCK_WIDTH,
				(int)block_y_count + y * DRAW_BLOCK_WIDTH, Color_Fuchsia, "��");
			else if (block[y][x] == 6)DrawFormatString(DRAW_POSITION + block_x * DRAW_BLOCK_WIDTH + x * DRAW_BLOCK_WIDTH,
				(int)block_y_count + y * DRAW_BLOCK_WIDTH, Color_Aqua, "��");
			else if (block[y][x] == 7)DrawFormatString(DRAW_POSITION + block_x * DRAW_BLOCK_WIDTH + x * DRAW_BLOCK_WIDTH,
				(int)block_y_count + y * DRAW_BLOCK_WIDTH, Color_Orange, "��");
		}
	}
}

// �����ł͐ڒn��̃u���b�N��`��
void my_draw_stage() {
	for (int y = 0; y < STAGE_HEIGHT - 2; y++) {
		for (int x = 2; x < STAGE_WIDTH - 2; x++) {
			if (stage[y][x] == 1)DrawFormatString(DRAW_POSITION + x * DRAW_BLOCK_WIDTH,
				y * DRAW_BLOCK_WIDTH, Color_Yellow, "��");
			else if (stage[y][x] == 2)DrawFormatString(DRAW_POSITION + x * DRAW_BLOCK_WIDTH,
				y * DRAW_BLOCK_WIDTH, Color_Red, "��");
			else if (stage[y][x] == 3)DrawFormatString(DRAW_POSITION + x * DRAW_BLOCK_WIDTH,
				y * DRAW_BLOCK_WIDTH, Color_Green, "��");
			else if (stage[y][x] == 4)DrawFormatString(DRAW_POSITION + x * DRAW_BLOCK_WIDTH,
				y * DRAW_BLOCK_WIDTH, Color_Blue, "��");
			else if (stage[y][x] == 5)DrawFormatString(DRAW_POSITION + x * DRAW_BLOCK_WIDTH,
				y * DRAW_BLOCK_WIDTH, Color_Fuchsia, "��");
			else if (stage[y][x] == 6)DrawFormatString(DRAW_POSITION + x * DRAW_BLOCK_WIDTH,
				y * DRAW_BLOCK_WIDTH, Color_Aqua, "��");
			else if (stage[y][x] == 7)DrawFormatString(DRAW_POSITION + x * DRAW_BLOCK_WIDTH,
				y * DRAW_BLOCK_WIDTH, Color_Orange, "��");
			else if (stage[y][x] == 9)DrawFormatString(DRAW_POSITION + x * DRAW_BLOCK_WIDTH,
				y * DRAW_BLOCK_WIDTH, Color_Black, "��");
		}
	}
}