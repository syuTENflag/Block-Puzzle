/*
	�Q�[���Ŏg���萔�A�֐��A�O���ϐ����`����w�b�_�[
*/

// �g�p����w�b�_�[�Ȃǂ̃C���N���[�h
#include "DxLib.h"
#include <stdlib.h>
#include <time.h>
#include <string>	// stringstream ���g�����߂ɃC���|�[�g
#include <sstream>	// ifstream���g�����߂ɃC���|�[�g
#include <fstream>

using namespace std;	// std���Ȃ��Ǝg���Ȃ����̂��g����悤�ɂ���

/*
	�ȉ��Q�[���Ŏg�p����萔��`
*/

// �Q�[���̏�ԓ�
#define GAME_INIT 0		// �^�C�g����ʂ̎�
#define GAME_PLAYING 1	// �Q�[���v���C��
#define GAME_MENU 2		// ���j���[��ʂ��J���Ă���Ƃ�
#define GAME_OVER 3		// �Q�[���I�[�o�[��

// �u���b�N�֌W
#define BLOCK_WIDTH 4	// �u���b�N�̕�
#define BLOCK_HEIGHT 4	// �u���b�N�̍���
#define BLOCK_NONUM 7	// �u���b�N�̎�ނ̐�
#define BLOCK_PATTERN 4	// �u���b�N�̉�]�̎�ސ�

// �X�e�[�W�֌W
#define STAGE_WIDTH 17	// �X�e�[�W�̕��̃}�X�̐�
#define STAGE_HEIGHT 23	// �X�e�[�W�̍����̃}�X�̐�

// �`��֌W
#define DRAW_POSITION 140	// �X�e�[�W��X���W�̍��[�̒l
#define DRAW_BLOCK_WIDTH 20	// �`�悳���u���b�N�̕�
#define NEXT_BLOCK_X 500	// ���̃u���b�N���`�悳��鍶�[��X���W
#define NEXT_BLOCK_Y 20		// ���̃u���b�N���`�悳����[��y���W
#define HOLD_BLOCK_X 60		// �z�[���h����Ă���u���b�N���`�悳��鍶�[��X���W
#define HOLD_BLOCK_Y 20		// �z�[���h����Ă���u���b�N���`�悳����[��y���W

//�R���g���[���[

#define PAD_INPUT_DOWN								(0x00000001)	// ���`�F�b�N�}�X�N
#define PAD_INPUT_LEFT								(0x00000002)	// ���`�F�b�N�}�X�N
#define PAD_INPUT_RIGHT								(0x00000004)	// ���`�F�b�N�}�X�N
#define PAD_INPUT_UP								(0x00000008)	// ���`�F�b�N�}�X�N
#define PAD_INPUT_A									(0x00000010)	// �`�{�^���`�F�b�N�}�X�N
#define PAD_INPUT_B									(0x00000020)	// ?�{�^���`�F�b�N�}�X�N
#define PAD_INPUT_C									(0x00000040)	// �Z�{�^���`�F�b�N�}�X�N
#define PAD_INPUT_X									(0x00000080)	// �w�{�^���`�F�b�N�}�X�N
#define PAD_INPUT_Y									(0x00000100)	// ���{�^���`�F�b�N�}�X�N
#define PAD_INPUT_Z									(0x00000200)
#define PAD_INPUT_L									(0x00000400)
#define PAD_INPUT_R									(0x00000800)
#define PAD_INPUT_START								(0x00001000)
#define PAD_INPUT_M									(0x00002000)
#define PAD_INPUT_D									(0x00004000)
#define PAD_INPUT_F									(0x00008000)
#define PAD_INPUT_G									(0x00010000)    //�^�b�`�p�b�h
#define PAD_INPUT_H									(0x00020000)
#define PAD_INPUT_I									(0x00040000)
#define PAD_INPUT_J									(0x00080000)
#define PAD_INPUT_K									(0x00100000)
#define PAD_INPUT_LL								(0x00200000)
#define PAD_INPUT_N									(0x00400000)
#define PAD_INPUT_O									(0x00800000)
#define PAD_INPUT_P									(0x01000000)
#define PAD_INPUT_RR								(0x02000000)
#define PAD_INPUT_S									(0x04000000)
#define PAD_INPUT_T									(0x08000000)
#define PAD_INPUT_U									(0x10000000)
#define PAD_INPUT_V									(0x20000000)
#define PAD_INPUT_W									(0x40000000)


/*
	�Q�[���Ŏg�p����֐���`
*/

// �������֌W�̊֐�
void my_init_var();		// �Q�[���̏�����
void my_init_var2();	// �v���C���ɏ���������K�v������ϐ��̏�����
void LoadMino();		// �~�m��CSV�����荞��
void LoadStage();		// �X�e�[�W��CSV�����荞��

// �Q�[���̏�Ԃ�L�[���͊֌W�̊֐�
void my_get_key();		// �L�[���͎��̏���
void my_change_lv();	// �X�R�A�ɉ����ă��x����ς���֐�
void my_gameover();		// �Q�[���I�[�o�[���ǂ�������
void ChoiceBackTitle();	// �^�C�g���ɖ߂邩�ǂ����I��������֐�

// �u���b�N�֌W�̊֐�
void my_make_block();		// �u���b�N�𐶐�����֐�
void my_hold_block();		// �u���b�N�̃z�[���h����������֐�
void my_move_block();		// �L�[�{�[�h�����������Ƃɂ��u���b�N�𓮂�������
void my_fix_block();		// �u���b�N���Œ肷��֐�
void my_save_block();		// �u���b�N��ۑ�����֐�
void my_fall_block();		// �u���b�N�𗎉�������֐�
void my_turn_right();		// �u���b�N�̉E������]�̏���
void my_turn_left();		// �u���b�N�̍�������]�̏���
void my_collision_left();	// �u���b�N�̉E�ړ��̏����Ɛڒn����
void my_collision_right();	// �u���b�N�̍��ړ��̏����Ɛڒn����
void my_collision_bottom();	// �u���b�N�̉��ړ��i�������x��葁���j�̏����Ɛڒn����
void my_collision_center();	// �^�񒆂̃u���b�N�̐ڒn����
void my_collision_turn();	// �u���b�N��]���̐ڒn����
void my_search_line();		// �u���b�N������񂷂ׂẴ}�X�ɂ��邩����
void my_clear_line();		// �u���b�N������񖄂܂��ď����Ƃ��̏���������

// �`��֌W�̊֐�
void my_draw_back();		// �w�i�`�揈��
void TitleDraw();			// �^�C�g����ʂ̕`��
void my_draw_variable();	// UI��NEXT�AHOLD�̕`�揈��
void my_draw_block();		// �������̃u���b�N�̕`�揈��
void my_draw_stage();		// ������̃u���b�N�̕`�揈��
void my_ed();				// �Q�[���I�[�o�[��ʂ̏���

/*
	�Q�[���Ŏg�p����O���ϐ���`
*/

// �u���b�N���̔z��̊O���ϐ�
extern int block[BLOCK_HEIGHT][BLOCK_WIDTH];								// ���݃��C���Ő������ꗎ�����Ă���u���b�N
extern int turn_block[BLOCK_HEIGHT][BLOCK_WIDTH];							// ��]���Ă���u���b�N
extern int next_block[BLOCK_HEIGHT][BLOCK_WIDTH];							// ���̃u���b�N
extern int hold_block[BLOCK_HEIGHT][BLOCK_WIDTH];							// �z�[���h����Ă���u���b�N
extern int stage[STAGE_HEIGHT][STAGE_WIDTH];								// �X�e�[�W
extern int blocks[BLOCK_HEIGHT * BLOCK_NONUM][BLOCK_WIDTH * BLOCK_PATTERN];	// �u���b�N�̊e��̂��ׂĂ̌������`��������
extern int clear_line_point[STAGE_HEIGHT - 3];								// �X�e�[�W�̊e�񂻂���Ă��邩�ǂ����݂����
extern int useBlocks[BLOCK_NONUM];											// ���ǂ̃u���b�N���g���Ă��邩

// �Q�[���̏�Ԃ�UI���̊O���ϐ�
extern int game_state;			// �Q�[���̏�Ԃ��`����ϐ�
extern int lv;					// �Q�[���̃��x�����`����ϐ�
extern int score;				// �X�R�A���i�[����ϐ�
extern int back_img1;			// �w�i�摜���i�[����ϐ�
extern int menu_img1;			// ���j���[�摜���i�[����ϐ�
extern int gameSound;			// BGM���i�[����ϐ�
extern int key[256];			// ���͂��ꂽ�L�[�R�[�h���i�[����ϐ�
extern int clear_count;			// ����u���b�N����񑵂������ꂽ���Ǘ�����ϐ�
extern int choice;				// �I�����̕ϐ��i0���������A1���͂��j
extern bool firstInitFlg;		// ����N�����ǂ����Ǘ�����t���O
extern bool clear_flag;			// �u���b�N����񑵂������ꂽ���Ǘ�����t���O
extern bool gameover_flag;		// �Q�[���I�[�o�[���ǂ����Ǘ�����t���O
extern bool holdflg;			// �z�[���h���������ǂ����Ǘ�����t���O
extern bool first_hold_flag;	// ����z�[���h���ǂ����Ǘ�����t���O

// �F�̊O���ϐ�
extern int Color_Red;		// ��
extern int Color_Black;		// ��
extern int Color_Green;		// ��
extern int Color_Blue;		// ��
extern int Color_Yellow;	// ��
extern int Color_Fuchsia;	// ��
extern int Color_Aqua;		// ��F
extern int Color_Orange;	// �I�����W

// �u���b�N�֌W�̊O���ϐ�
extern int block_x;				// �u���b�N��x���W
extern int block_y;				// �u���b�N��y���W
extern int block_id;			// �u���b�N��id���i�[����ϐ�
extern int useBlockCnt;			// ����u���b�N���g��ꂽ���Ǘ�����ϐ�
extern int next_block_id;		// ���̃u���b�N��id���i�[����ϐ�
extern int hold_block_id;		// �z�[���h����Ă���u���b�N��id���i�[����ϐ�
extern int turn_point;			// �u���b�N�̌������`����ϐ�
extern int hold_turn_point;		// �z�[���h���Ƀu���b�N�̌��������̂܂܂ɂ�����ϐ�
extern int block_y_point;		// �u���b�N��y���W���i�[����ϐ�
extern int fix_count;			// �u���b�N�Œ�̃J�E���g�ϐ�
extern float block_y_count;		// �u���b�N��y���W���J�E���g����ϐ�
extern float block_speed;		// �u���b�N�̗�������X�s�[�h
extern bool collision_flag;		// �u���b�N���Ԃ����Ă��邩�ǂ����Ǘ�����t���O
extern bool turnFlg;			// �u���b�N����]�ł��邩�ǂ����̃t���O
extern bool first_block_flag;	// �ŏ��̃u���b�N���ǂ����Ǘ�����t���O
extern bool make_block_flag;	// �u���b�N������Ă��邩�ǂ����Ǘ�����t���O