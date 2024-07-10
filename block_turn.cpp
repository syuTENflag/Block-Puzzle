/*
	�u���b�N�̉�]�̊֐����L�q�����\�[�X
*/
#include "main.h"

/*
	�����ł́A�u���b�N�̉E����]���s��
	��]���̐ڒn������Ƃ�A�����蔻��ƂƂ��ɑ��v�ł���΁A
	��]��̃u���b�N���𗎉����Ă���u���b�N�ɏ�������ŉ�]���I��点��B
	������]�ł��Ȃ��̂ł���Ή�]������������Ƃɖ߂�
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
	�����ł́A�u���b�N�̍�����]���s��
	��]���̐ڒn������Ƃ�A�����蔻��ƂƂ��ɑ��v�ł���΁A
	��]��̃u���b�N���𗎉����Ă���u���b�N�ɏ�������ŉ�]���I��点��B
	������]�ł��Ȃ��̂ł���Ή�]������������Ƃɖ߂�
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
	�����ł́A�u���b�N�̍����̓����蔻����Ƃ�
	�u���b�N������}�X���������̂��A�u���b�N�̍����ɉ�������ꍇ�̓t���O��true�ɂ���
	�����Ȃ��Ƃ��A�u���b�N��y���W�J�E���g-�u���b�N��y���W�~�u���b�N�̕��������l��0���傫���A
	�u���b�N�̍����ɉ�������ꍇ���t���O��true�ɂ���
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
	�����ł́A�u���b�N�̉E���̓����蔻����Ƃ�
	�u���b�N������}�X���������̂��A�u���b�N�̉E���ɉ�������ꍇ�̓t���O��true�ɂ���
	�����Ȃ��Ƃ��A�u���b�N��y���W�J�E���g-�u���b�N��y���W�~�u���b�N�̕��������l��0���傫���A
	�u���b�N�̉E���ɉ�������ꍇ���t���O��true�ɂ���
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
	�����ł́A�u���b�N�̉����̓����蔻����Ƃ�
	�u���b�N������}�X���������̂��A�u���b�N�̉����ɉ�������ꍇ�̓t���O��true�ɂ���
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
	�����ł́A�u���b�N������Ƃ���̓����蔻����Ƃ�
	�u���b�N������}�X���������̂��A�u���b�N�̂Ƃ��Ȃ��Ƃ���ɉ�������ꍇ�̓t���O��true�ɂ���
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
	�����ł́A�u���b�N�̉�]���̓����蔻����Ƃ�

	�܂���]��̃u���b�N����]���Ă���u���b�N�ɓ���Ĉ�x��]�ł����Ԃɂ���
	���̌�A�u���b�N������}�X���������̂��A�u���b�N�̏㉺���E���ׂĂ𔻒肵�A
	��������ꍇ�͉����Ȃ����Ƀu���b�N�̍��W�����炷
	���̎��A����炷�����ł͑Ή��ł��Ȃ��u���b�N�i5�j������A���̃p�^�[���ɂȂ����ꍇ�͂���Ɉ���炷
	�����āA�����Ȃ��Ƃ���Ƀu���b�N�����ǂ蒅�������]��̃u���b�N�ɐ�������Ă���u���b�N������
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