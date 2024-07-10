/*
	�u���b�N�Œ�֌W�̊֐����L�q�����\�[�X
*/
#include "main.h"

// �p�u���b�N�ϐ��錾
int clear_line_point[STAGE_HEIGHT - 3];	// �X�e�[�W�̊e�񂻂���Ă��邩�ǂ����݂����
int back_img1;							// �w�i�摜���i�[����ϐ�
int key[256];							// ���͂��ꂽ�L�[�R�[�h���i�[����ϐ�

/*
	�u���b�N�Œ���Q�i�K�ɕ����čs��
	�ŏ��͌Œ肹���ɂ��̎��̃u���b�N��y���W��ۑ����A�Œ�܂ł̃J�E���g���n�߂�
	���̌�A�w�肵���J�E���g�������y���W�Ƀu���b�N������悤�Ȃ�Œ肳����
*/
void my_fix_block() {
	// �������x��葁�����Ƃ̓����蔻����Ƃ�
	my_collision_bottom();

	/*
		�����蔻�肪���v�Ȃ�A
		�u���b�N���ڒn���Ă��邩�𔻒肵�A
		�ڒn���Ă�����u���b�N��ۑ����A����񂻂���Ă��邩�𔻒肷��
		�����u���b�N��������Ȃ������炱���Ńu���b�N���o�����тɏ��������K�v�ȕϐ��̏��������s��

		�u���b�N���ڒn���Ă��Ȃ��ꍇ�́A�i�[���Ă���y���W�ƃu���b�N��y���W���������ǂ������肵�A
		�����Ȃ�u���b�N�Œ�J�E���g�𑝂₵�A�����łȂ���΃u���b�N�Œ�J�E���g��0�N���A����
		������y���W���i�[���Ay���W�̃J�E���g�𗎉��X�s�[�h�����炷
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
	�u���b�N���ڒn�����ہA�����S�Ẵ}�X�Ƀu���b�N������ꍇ�����Ȃ��Ƃ����Ȃ�

	�܂��X�e�[�W�̊e�񂪂�����Ă��邩�ǂ���������ϐ���0�N���A����B
	���̌�A���̃}�X�𒲂ׂĂ����A�����Ȃ��}�X�i0�j����������clear_line_point��1�ɂ��Ă��̗�͏I���ɂ���
	�Ō�܂ŏI������Ƃ����clear_line_point��0�ȗ񂪂�����������ꂽ���Ǘ�����t���O��true�ɂ��ăX�R�A�𑝂₷
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
	�����ł̓u���b�N��������������������

	�܂����̗񂪏����ꂽ���ǂ����̕ϐ������̃X�e�[�W�i10�j���ɂȂ��Ă��Ȃ���΂��ׂău���b�N�Ŗ��܂��Ă����������Ȃ��ɂ��Ă���
	���̌�A�����ꂽ��Ə�����ĂȂ������ʂ���v���C�x�[�g�Ȕz���p���ď����ꂽ��Ƃ����łȂ������ʂ���
	�����ċ�ʂ��I�������A�����ꂽ��̏�ɂ���u���b�N�����ׂď����ꂽ���������ɉ�����

	�����̏������I�����������ꂽ���ǂ����̃t���O��false�ɂ��J�E���^�[��0�ɂ��A
	�u���b�N���o�����тɏ��������K�v�ȕϐ��̏��������s���A���x���̊Ǘ�������
*/
void my_clear_line() {
	// ���̊֐��ł̂ݎg�p����v���C�x�[�g�ϐ���`
	// ��Ƃ����̊֐����Ă΂ꂽ�ۂ�0�N���A����
	int remain_line_point[20] = { 0 };	// �����ꂽ��Ə�����ĂȂ������ʂ���z��
	int remain_line_index = 0;			// ��p�̃J�E���^�[

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
	�����ł͐ڒn�����u���b�N���X�e�[�W�̍��W�ɕۑ�����
*/
void my_save_block() {
	int x, y;

	for (y = 0; y < BLOCK_HEIGHT; y++) {
		for (x = 0; x < BLOCK_WIDTH; x++) {
			stage[block_y + y][block_x + x] += block[y][x];
		}
	}

	//�������̃u���b�N�������Ă���Œ��Ƀz�[���h���Ă�����t���O��false�ɖ߂�
	if (holdflg == true)
	{
		holdflg = false;
	}
}

/*
	�����ł̓u���b�N��y���W���Ǘ�����
	�X�s�[�h��J�E���g��y���W���WIDTH���傫�����ߊ���
*/
void my_fall_block() {
	if (make_block_flag == false) {
		block_y_count += block_speed;
		block_y = (int)block_y_count / DRAW_BLOCK_WIDTH;
	}
}

/*
	�����ł͓��͂��ꂽ�L�[�̒l��z��Ɏ�荞�ޏ���������
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