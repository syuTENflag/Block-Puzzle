/*
	�^�C�g����ʏ����̃\�[�X
*/
#include "main.h"

// �p�u���b�N�ϐ��錾
int gameSound;	// BGM���i�[����ϐ�

// �^�C�g����ʂ̕`�������֐�
void TitleDraw() {
	// �^�C�g�����̃t�H���g�T�C�Y���w�肵�w��̍��W�ɕ`�悷��
	SetFontSize(75);
	DrawFormatString(88, 150, Color_Yellow, "BLOCK PUZZLE");

	// �w���̃t�H���g�T�C�Y���w�肵�w��̍��W�ɕ`�悷��
	SetFontSize(40);
	DrawFormatString(50, 240, Color_Yellow, "ENTER�L�[orPS�R���g���[���[��\n�^�b�`�p�b�h��������\n�@�@�@�X�^�[�g");

	if (key[KEY_INPUT_RETURN] == 1) {
		if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_H) {// �^�b�`�p�b�h
			game_state = GAME_PLAYING;
			PlaySoundMem(gameSound, DX_PLAYTYPE_LOOP);
			//WaitTimer(100);

			// �Q�[�����Ŏg���t�H���g�T�C�Y���w�肷��(�Ȃ��Ǝw���Ɠ����ɂȂ�)
			SetFontSize(DRAW_BLOCK_WIDTH);
		}
	}
}