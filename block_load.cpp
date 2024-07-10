/*
	�u���b�N�����Ɠ���i�ꕔ�j�̊֐����L�q�����\�[�X
*/
#include "main.h"

// �p�u���b�N�ϐ��錾
int block[BLOCK_HEIGHT][BLOCK_WIDTH];									// ���݃��C���Ő������ꗎ�����Ă���u���b�N
int turn_block[BLOCK_HEIGHT][BLOCK_WIDTH];								// ��]���Ă���u���b�N
int next_block[BLOCK_HEIGHT][BLOCK_WIDTH];								// ���̃u���b�N
int hold_block[BLOCK_HEIGHT][BLOCK_WIDTH];								// �z�[���h����Ă���u���b�N
int useBlocks[BLOCK_NONUM];												// ���ǂ̃u���b�N���g���Ă��邩
int blocks[BLOCK_HEIGHT * BLOCK_NONUM][BLOCK_WIDTH * BLOCK_PATTERN];	// �u���b�N�̊e��̂��ׂĂ̌������`��������

/*
	�u���b�N�������Q�i�K�ɕ����čs��
	�܂���ɐ��������u���b�N���unext_block_id�v�ɕۑ�
	�����Ɂublock_id�v�ɕۑ�������
	�Ăуu���b�N�����������s���unext_block_id�v�ɕۑ�����
	�Q��ڈȍ~�͂�����J��Ԃ�
*/
void my_make_block() {
	// ���̊֐��ł̂ݎg�p����v���C�x�[�g�ϐ���`
	bool randBlockFlg = true;	// �����_���ȃu���b�NID���擾�ł��邩�ǂ����̃t���O

	// �ŏ��̃u���b�N�̃t���O��true�ȂƂ��ɍŏ��̃u���b�N���擾
	if (first_block_flag == true) {
		// �ŏ���3��ނ̒�����I��
		next_block_id = (rand() % 3);

		// �g���Ă���u���b�N�̔z���ID�����J�E���g�𑝂₷
		useBlocks[useBlockCnt] = next_block_id;
		useBlockCnt++;

		// ID�ɑΉ������u���b�N�𐶐�
		for (int y = 0; y < BLOCK_HEIGHT; y++) {
			for (int x = 0; x < BLOCK_WIDTH; x++) {
				next_block[y][x] = blocks[(next_block_id * BLOCK_HEIGHT) + y][x];
			}
		}

		// �ŏ��̐������ǂ����̃t���O��false�ɂ���
		first_block_flag = false;
	}

	/*����ꏄ�̏���*/

	// �u���b�N�����邩�ǂ����̃t���O��true�ȂƂ��ɍ��
	if (make_block_flag == true) {
		// ����ID������ID�ɓ����
		block_id = next_block_id;

		// �����_���ȃu���b�NID���擾�ł��邩�ǂ����̃t���O��true�ȂƂ��Ƀ����_���ȃu���b�NID���擾����
		while (randBlockFlg == true) {
			next_block_id = (rand() % BLOCK_NONUM);
			// �g���Ă���u���b�N�̃J�E���g��0�̎��͂��̂܂ܓ���ă��[�v�𔲂���
			if (useBlockCnt == 0) {
				useBlocks[useBlockCnt] = next_block_id;
				randBlockFlg = false;
			}

			// ����ȊO�̎��̓��[�v�ŏd���𒲂ׂ�
			for (int i = 0; i < useBlockCnt; i++) {
				if (next_block_id == useBlocks[i]) {
					break;
				}
				// i��useBlockCnt - 1�̂Ƃ��͒l�����ă��[�v�𔲂���
				else if (i == useBlockCnt - 1) {
					useBlocks[useBlockCnt] = next_block_id;
					randBlockFlg = false;
				}
			}
		}

		// ID�ɑΉ������u���b�N�𐶐��i���Ǝ��́j
		for (int y = 0; y < BLOCK_HEIGHT; y++) {
			for (int x = 0; x < BLOCK_WIDTH; x++) {
				block[y][x] = next_block[y][x];
				next_block[y][x] = blocks[(next_block_id * BLOCK_HEIGHT) + y][x];
			}
		}

		// �t���O��false�ɂ���
		make_block_flag = false;

		// �J�E���g��6�ɂȂ����珉�����i����ȊO��useBlockCnt�𑝂₷�j
		if (useBlockCnt >= BLOCK_NONUM - 1) {
			useBlockCnt = 0;
			for (int i = 0; i < BLOCK_NONUM; i++) {
				// 0��O�~�m�Ȃ��߁A�g���Ă��Ȃ�7�������ď�����
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
	�ȉ��̓u���b�N�z�[���h����
	����z�[���h���͂��̂܂܁uhold_block[BLOCK_HEIGHT][BLOCK_WIDTH]�v�Ƀz�[���h����u���b�N��������
	���̎��́ublock_id�v�Ȃǋ��ɕۑ��A�������́umy_init_var2()�v���s��
	�Q��ڈȍ~�͐�قǂ́uhold_block[BLOCK_HEIGHT][BLOCK_WIDTH]�v�Ƃ̓���ւ��������s��
	���̂܂܃u���b�N�̈ʒu���������ɖ߂�
*/
void my_hold_block() {
	// ���̊֐��ł̂ݎg�p����v���C�x�[�g�ϐ���`
	int tmp_block[BLOCK_HEIGHT][BLOCK_WIDTH] = { 0 };	// ����ւ��p�̃u���b�N
	int tmp_block_id;									// ����ւ��p�̃u���b�NID
	int tmp_turn_point;									// ����ւ��p�̃u���b�N�̌���

	// �����̑O�Ƀt���O��true�ɂ���
	holdflg = true;

	/*
		�ŏ��̃z�[���h�̎�
		���ڃz�[���h�p�̕ϐ��Ƀz�[���h�������u���b�N��������
	*/
	if (first_hold_flag == true) {
		for (int y = 0; y < BLOCK_HEIGHT; y++) {
			for (int x = 0; x < BLOCK_WIDTH; x++) {
				hold_block[y][x] = block[y][x];
			}
		}
		hold_block_id = block_id;
		hold_turn_point = turn_point;

		// �ȉ����̃u���b�N�o���Ɍ������������A��������
		my_init_var2();
		my_make_block();
		first_hold_flag = false;
	}

	/*
		�ŏ��ł͂Ȃ���
		����ւ��p��tmp�������ϐ���p����
		�z�[���h�������u���b�N�������ꂼ�����ւ��Ȃ�������
	*/
	else {
		for (int y = 0; y < BLOCK_HEIGHT; y++) {
			for (int x = 0; x < BLOCK_WIDTH; x++) {
				// ����ւ������i�u���b�N�j
				tmp_block[y][x] = block[y][x];
				block[y][x] = hold_block[y][x];
				hold_block[y][x] = tmp_block[y][x];
			}
		}
		// ����ւ������iID�ƌ������j
		tmp_block_id = block_id;
		tmp_turn_point = turn_point;
		block_id = hold_block_id;
		turn_point = hold_turn_point;
		hold_block_id = tmp_block_id;
		hold_turn_point = tmp_turn_point;

		// ���W�ƌ��������Z�b�g
		block_x = 7;
		block_y = 0;
		block_y_count = 0;
	}
}

// �L�[�{�[�h�����������Ƃɂ��u���b�N�𓮂�������
void my_move_block() {
	// �R���g���[���[�g�p���̏���

	// �R���g���[���[�p�̃v���C�x�[�g�ϐ���`
	//int GetJoypadNum(void);
	//int GetJoypadInputState(int InputType);
	//int joypadState = GetJoypadInputState(DX_INPUT_PAD1);
	//int flg = 0;

	// ����󂪉�����Ă���Ƃ��A���Ƃ̓����蔻����Ƃ��āA���v�Ȃ�u���b�N�����ɓ�����
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT)
	{
		my_collision_left();
		if (collision_flag == false) {
			block_x--;
			WaitTimer(60);// �ҋ@���ԁi�~���b�j��ݒ�i�Ⴆ��100�~���b�j
			return;
		}// ������Ă���
	}
	// �E��󂪉�����Ă���Ƃ��A�E�Ƃ̓����蔻����Ƃ��āA���v�Ȃ�u���b�N���E�ɓ�����
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT)
	{
		my_collision_right();
		if (collision_flag == false) {
			block_x++;
			WaitTimer(60);// �ҋ@���ԁi�~���b�j��ݒ�i�Ⴆ��100�~���b�j
		}// ������Ă���
	}
	// ����󂪉�����Ă���Ƃ��A���Ƃ̓����蔻����Ƃ��āA���v�Ȃ�u���b�N�̗������x���グ��
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN)
	{
		my_collision_bottom();
		if (collision_flag == false) {
			block_y++;
			block_y_count = (float)(block_y * DRAW_BLOCK_WIDTH);
			WaitTimer(50);// �ҋ@���ԁi�~���b�j��ݒ�i�Ⴆ��100�~���b�j
		}// ������Ă���
	}
	// ���󂪉�����Ă���Ƃ��́A���󉺂Ɠ����������s��
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP)
	{
			my_collision_bottom();
			if (collision_flag == false){
				block_y++;
				block_y_count = (float)(block_y * DRAW_BLOCK_WIDTH);
			}

		// ������Ă���
	}

	// ���{�^����������Ă���Ƃ��́A�����蔻����Ƃ�A���v�Ȃ�u���b�N���E��]������
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_C)
	{
		my_turn_right();// ������Ă���
		WaitTimer(200);// �ҋ@���ԁi�~���b�j��ݒ�
	}
	// �~�{�^����������Ă���Ƃ��́A�����蔻����Ƃ�A���v�Ȃ�u���b�N������]������
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_B)
	{
		my_turn_left();// ������Ă���
		WaitTimer(200);// �ҋ@���ԁi�~���b�j��ݒ�
	}
	// ���{�^����������Ă��Ă��A���݂̃u���b�N���o�Ă����x���z�[���h���ĂȂ��Ƃ��́A�u���b�N���z�[���h������
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_A && holdflg == false)
	{
		my_hold_block();// ������Ă���
		WaitTimer(200);// �ҋ@���ԁi�~���b�j��ݒ�
		return;
	}

	// �L�[�{�[�h�g�p���̏���

	// ����󂪉�����Ă���Ƃ��A���Ƃ̓����蔻����Ƃ��āA���v�Ȃ�u���b�N�����ɓ�����
	if (key[KEY_INPUT_LEFT] % 7 == 1) {
		my_collision_left();
		if (collision_flag == false) {
			block_x--;
		}
	}

	// �E��󂪉�����Ă���Ƃ��A�E�Ƃ̓����蔻����Ƃ��āA���v�Ȃ�u���b�N���E�ɓ�����
	if (key[KEY_INPUT_RIGHT] % 7 == 1) {
		my_collision_right();
		if (collision_flag == false) {
			block_x++;
		}
	}

	// ����󂪉�����Ă���Ƃ��A���Ƃ̓����蔻����Ƃ��āA���v�Ȃ�u���b�N�̗������x���グ��
	if (key[KEY_INPUT_DOWN] % 7 == 1) {
		my_collision_bottom();
		if (collision_flag == false) {
			block_y++;
			block_y_count = (float)(block_y * DRAW_BLOCK_WIDTH);
		}
	}
	// ����͌���Ȃɂ��Ȃ�
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

	// X�L�[��������Ă���Ƃ��́A�����蔻����Ƃ�A���v�Ȃ�u���b�N���E��]������
	if (key[KEY_INPUT_X] == 1) {
		my_turn_right();
	}

	// Z�L�[��������Ă���Ƃ��́A�����蔻����Ƃ�A���v�Ȃ�u���b�N������]������
	if (key[KEY_INPUT_Z] == 1) {
		my_turn_left();
	}

	// H�L�[���������Ƃ��Ƀz�[���h�����i���̃u���b�N���o�Ă����x���z�[���h���ĂȂ����̂݃z�[���h�������Ăяo���j
	if (key[KEY_INPUT_H] == 1 && holdflg == false) {
		my_hold_block();
	}
}