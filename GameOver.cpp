/*
	�Q�[���I�[�o�[�����̃\�[�X
*/
#include "main.h"

// �Q�[���I�[�o�[���ǂ������肷��
// ���������蔻��̃t���O��true�̂܂܂ł���΃Q�[���I�[�o�[�t���O��true����
void my_gameover() {
	my_collision_center();

	if (collision_flag == true) {
		gameover_flag = true;
	}
}

// �Q�[���I�[�o�[��ʂ̎��̏���
void my_ed() {
	// �����̃t�H���g�T�C�Y���w�肵�`�悳����
	SetFontSize(75);
	DrawFormatString(150, 100, Color_Red, "GAME OVER");
	SetFontSize(40);
	DrawFormatString(220, 240, Color_Aqua, "SCORE�F%d", score * 10);

	SetFontSize(30);

	DrawFormatString(170, 340, Color_Aqua, "�^�b�`�p�b�h��������\n  �X�^�[�g��ʂ�");
	
	// �G���^�[�L�[�������̓^�b�`�p�b�h�ŏ������������s�킹�^�C�g���։�ʑJ�ڂ�����
	if (key[KEY_INPUT_RETURN] == 1) {
	//if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_H) { //�^�b�`�p�b�h
		game_state = GAME_INIT;
		gameover_flag = false;
		my_init_var();
		//WaitTimer(100);
		// �Q�[�����Ŏg���t�H���g�T�C�Y���w�肷��(�Ȃ��ƃX�R�A�Ɠ����ɂȂ�)
		SetFontSize(DRAW_BLOCK_WIDTH);
	}
}