/*
	WinMain�֐��̂��郁�C���̏��������̃\�[�X
*/
#include "main.h"

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	/*
		�E�B���h�E��DX���C�u�����̏���������
	*/
	ChangeWindowMode(FALSE);			// �E�B���h�E�g�ݗ���
	DxLib_Init();					// DX���C�u�����̏�����
	SetDrawScreen(DX_SCREEN_BACK);	// �X�N���[�����Z�b�g

	/*
		�Q�[���̏���������
	*/
	firstInitFlg = true;	// ����N�����݂̂����̏��������s�����̂�true�ɃZ�b�g
	my_init_var();			// �Q�[���̏������֐����Ăяo��

	/*
		�Q�[���̃��C�������i�E�B���h�E���b�Z�[�W�������������Ă���Ƃ��̂݁j
	*/
	while (ProcessMessage() == 0) {

		// ��ʂɕ`�悳�ꂽ���̂���x��������
		ClearDrawScreen();

		// �ȉ��Q�[���̐i�s����
		/*
			�Q�[���̏�ԂɊ֌W�Ȃ�������������
		*/
		my_get_key();	// �L�[���͎��̏���
		my_draw_back();	// �w�i�`�揈��

		/*
			�ȉ��̏����̓Q�[���̏�Ԃɂ���ď�����U�蕪��
		*/
		switch (game_state) {
			
		// game_state = GAME_INIT�̎��i�^�C�g����ʕ\���̎��j
		case GAME_INIT:
			TitleDraw();	// �^�C�g���̕`��
			break;

		// game_state = GAME_PLAYING�̎��i�Q�[���v���C���j
		case GAME_PLAYING:

			/*
				�Q�[���v���C���͕K��������������
			*/
			my_draw_stage();	// �X�e�[�W�̕`��
			my_draw_variable();	// �X�R�A�A�l�N�X�g�u���b�N�A�z�[���h�u���b�N�̕`��

			// ESC�L�[�������ƃ^�C�g���֖߂邩�ǂ����I��
			if (key[KEY_INPUT_ESCAPE] == 1) {
			//if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_H) { //�^�b�`�p�b�h
				game_state = GAME_MENU;
			}

			/*
				�u���b�N�������邩�ǂ����ŏ�����U�蕪��
			*/
			// �u���b�N�������Ȃ���
			if (clear_flag == false) {
				my_make_block();	// �u���b�N�𐶐�����
				my_gameover();		// �Q�[���I�[�o�[���ǂ������肷��
				my_move_block();	// �L�[�{�[�h�����������Ƃɂ��u���b�N�𓮂�������
				my_draw_block();	// �u���b�N�������Ƀu���b�N��`�悷��
				my_fix_block();		// �u���b�N���Œ肷��
				my_fall_block();	// �u���b�N�𗎉�������
			}
			// �u���b�N�������鎞
			else {
				my_clear_line();	// �u���b�N������񖄂܂��ď����Ƃ��̏���������
			}
			
			// �Q�[���I�[�o�[����game_state = GAME_OVER�ɂ��ĉ��y���~�߂�
			if (gameover_flag == true) {
				game_state = GAME_OVER;
				StopSoundMem(gameSound);
			}

			break;

		// game_state = GAME_MENU�̎��i���j���[��ʂ̎��j
		case GAME_MENU:
			ChoiceBackTitle();	// �^�C�g���ɖ߂邩�֐����őI��
			break;

		// game_state = GAME_OVER�̎��i�Q�[���I�[�o�[�̎��j
		case GAME_OVER:
			my_ed();	// �Q�[���I�[�o�[���̏���
			break;

		// ����ȊO�̎��i�������Ȃ���break�j
		default:
			break;
		}

		// ��ʂɕ`��
		ScreenFlip();
	}

	/*
		�Q�[���̏I������
	*/
	DxLib_End();	// DX���C�u�����̏I������
	return 0;
}