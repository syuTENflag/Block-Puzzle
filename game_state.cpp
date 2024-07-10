/*
	�Q�[���̏�ԓ����Ǘ�����֐����L�q�����\�[�X
*/
#include "main.h"

// �p�u���b�N�ϐ��錾
// �ȉ��͔z��
int stage[STAGE_HEIGHT][STAGE_WIDTH];	// �X�e�[�W

// �ȉ��̓Q�[���̏�Ԃ�UI��
int game_state;			// �Q�[���̏�Ԃ��`����ϐ�
int menu_img1;			// ���j���[�摜���i�[����ϐ�
int clear_count;		// ����u���b�N����񑵂������ꂽ���Ǘ�����ϐ�
int choice;				// �I�����̕ϐ��i0���������A1���͂��j 
bool firstInitFlg;		// ����N�����ǂ����Ǘ�����t���O
bool clear_flag;		// �u���b�N����񑵂������ꂽ���Ǘ�����t���O
bool gameover_flag;		// �Q�[���I�[�o�[���ǂ����Ǘ�����t���O
bool holdflg;			// �z�[���h���������ǂ����Ǘ�����t���O
bool first_hold_flag;	// ����z�[���h���ǂ����Ǘ�����t���O

// �ȉ��̓u���b�N�֌W
int block_x;			// �u���b�N��x���W
int block_y;			// �u���b�N��y���W
int block_id;			// �u���b�N��id���i�[����ϐ�
int useBlockCnt;		// ����u���b�N���g��ꂽ���Ǘ�����ϐ�
int next_block_id;		// ���̃u���b�N��id���i�[����ϐ�
int hold_block_id;		// �z�[���h����Ă���u���b�N��id���i�[����ϐ�
int turn_point;			// �u���b�N�̌������`����ϐ�
int hold_turn_point;	// �z�[���h���Ƀu���b�N�̌��������̂܂܂ɂ�����ϐ�
int block_y_point;		// �u���b�N��y���W���i�[����ϐ�
int fix_count;			// �u���b�N�Œ�̃J�E���g�ϐ�
float block_y_count;	// �u���b�N��y���W���J�E���g����ϐ�
float block_speed;		// �u���b�N�̗�������X�s�[�h
bool collision_flag;	// �u���b�N���Ԃ����Ă��邩�ǂ����Ǘ�����t���O
bool turnFlg;			// �u���b�N����]�ł��邩�ǂ����̃t���O
bool first_block_flag;	// �ŏ��̃u���b�N���ǂ����Ǘ�����t���O
bool make_block_flag;	// �u���b�N������Ă��邩�ǂ����Ǘ�����t���O

// �^�C�g����ʂ̎��̕ϐ��̏���������
void my_init_var() {

	/*
		�ȉ��͏���N�����ɂ̂݌Ăяo������
	*/
	if (firstInitFlg == true) {
		// �e�F�̏�����
		Color_Red = GetColor(255, 0, 0);
		Color_Black = GetColor(0, 0, 0);
		Color_Green = GetColor(0, 255, 0);
		Color_Blue = GetColor(0, 0, 255);
		Color_Yellow = GetColor(255, 255, 0);
		Color_Fuchsia = GetColor(255, 0, 255);
		Color_Aqua = GetColor(0, 255, 255);
		Color_Orange = GetColor(255, 165, 0);

		// �摜�̎�荞��
		back_img1 = LoadGraph("./Resorces/teto.png");		// �w�i
		menu_img1 = LoadGraph("./Resorces/GameMenu.png");  // ���j���[

		// BGM�̎�荞��
		gameSound = LoadSoundMem("./Resorces/RnI8fDSITxE.mp3");	// BGM

		// ���ʂ̐ݒ�i0�`255�͈̔͂Őݒ�j
		ChangeVolumeSoundMem(128, gameSound);

		// �~�m�̃f�[�^�ǂݍ���
		LoadMino();

		game_state = GAME_INIT;	// �Q�[���̏�Ԃ��^�C�g����ʂ̎��ɂ���
		firstInitFlg = false;	// ����N�����ǂ����̃t���O��false�ɂ���
	}

	/*
		�ȉ��͊֐����Ăяo���ꂽ�Ƃ��ɖ���Ăяo����鏈��
	*/
	// �X�e�[�W�̏�����
	LoadStage();

	// �z�[���h���̏�����
	for (int i = 0; i < BLOCK_HEIGHT; i++) {
		for (int j = 0; j < BLOCK_WIDTH; j++) {
			hold_block[i][j] = 0;
		}
	}

	// �g���Ă���u���b�N�Ǘ��̏�����
	for (int i = 0; i < BLOCK_NONUM; i++) {
		// 0��O�~�m�Ȃ��߁A�g���Ă��Ȃ�7�������ď�����
		useBlocks[i] = 7;
	}

	// �e�ϐ��̏�����
	// �u���b�N���o�����тɏ��������K�v�ȕϐ��̏�����
	my_init_var2();

	// �Q�[���X�^�[�g���ɏ��������K�v�ȕϐ��̏�����
	// �ȉ��̓u���b�N�֌W
	block_speed = 0.5f;
	block_id = 0;
	useBlockCnt = 0;
	next_block_id = 0;
	hold_block_id = 0;
	clear_count = 0;
	hold_turn_point = 0;
	collision_flag = false;
	turnFlg = false;
	gameover_flag = false;
	first_block_flag = true;
	first_hold_flag = true;
	holdflg = false;
	// �ȉ��̓Q�[���i�s�֌W
	lv = 1;
	score = 0;
	choice = 0;

	// �����̏�����
	srand((unsigned)time(NULL));
}

// �u���b�N���o�����тɏ��������K�v�ȕϐ��̏��������s���֐�
void my_init_var2() {
	block_x = 7;
	block_y = 0;
	block_y_count = 0;
	make_block_flag = true;
	turn_point = 0;
	block_y_point = 0;
	fix_count = 0;
}

// �~�m��CSV�f�[�^�ǂݍ��݂��s���֐�
void LoadMino() {
	// getline�ɂ���ēǂݍ��܂ꂽ���������荞�ރ��[�J���ϐ�
	string str;

	// str�Ɏ�荞�܂ꂽ�������ǂݍ��ݔz��֊i�[�����郍�[�J���ϐ�
	stringstream ss;

	// �ȉ���ifstream�ɂ���āA�~�m�̃f�[�^��������CSV�t�@�C�����J��
	ifstream csvFile("./Resorces/Mino.csv");

	// �z��̒l��������
	blocks[BLOCK_HEIGHT * BLOCK_NONUM][BLOCK_WIDTH * BLOCK_PATTERN] = { 0 };

	/*
		2�d���[�v�ɂ��~�m�̏�ԕ��̐��l����荞��
	*/

	for (int i = 0; i < BLOCK_HEIGHT * BLOCK_NONUM; i++)
	{
		// ���͍Ō�͉��s�R�[�h�܂œǂ݂��ނ̂ň��O�܂œǂݍ���
		for (int j = 0; j < (BLOCK_WIDTH * BLOCK_PATTERN) - 1; j++)
		{
			/*
				getline�̑�1�����͓ǂݏo���J�n�ʒu��\��
				(���̃R�[�h�ł͌��݈ʒu��\��)
				��2�����͓ǂݏo������w��
				��3�����͏I�[�Ƃ��镶�����w��
			*/
			getline(csvFile.seekg(0, ios_base::cur), str, ',');

			// stringstream�ɓǂ݂�����string�𗬂�
			ss.str(str);

			/*
				stringstream����z��ɗ���
				���̎���string�^����int�^�̕ϊ����ÖٓI�ɍs����
			*/
			ss >> blocks[i][j];

			/*
				�O�̕������c���đz��ʂ�̐��l���z��Ɋi�[�ł��Ȃ�����
				stringstream���ȉ��̂Q�s�̃R�[�h�ŃN���A����
			*/
			ss.str("");
			ss.clear(stringstream::goodbit);
		}

		// ���̍Ō�̐��l�͉��s�R�[�h�܂œǂݍ��ݎ��̍s�ֈړ�������
		getline(csvFile.seekg(0, ios_base::cur), str, '\n');
		ss.str(str);

		// BLOCK_WIDTH * BLOCK_PATTERN�̒l�����̂܂܎g���Ɣz��O�ɂȂ��Ă��܂�����-1����
		ss >> blocks[i][(BLOCK_WIDTH * BLOCK_PATTERN) - 1];

		/*
			�����ł��O�̕������c���đz��ʂ�̐��l���z��Ɋi�[�ł��Ȃ�����
			stringstream���ȉ��̂Q�s�̃R�[�h�ŃN���A����
		*/
		ss.str("");
		ss.clear(stringstream::goodbit);
	}

	// CSV�t�@�C������ăt�@�C���ւ̃A�N�Z�X�����J������B
	csvFile.close();
}

// �X�e�[�W��CSV�f�[�^�ǂݍ��݂��s���֐�
void LoadStage() {
	// getline�ɂ���ēǂݍ��܂ꂽ���������荞�ރ��[�J���ϐ�
	string str;

	// str�Ɏ�荞�܂ꂽ�������ǂݍ��ݔz��֊i�[�����郍�[�J���ϐ�
	stringstream ss;

	// �ȉ���ifstream�ɂ���āA�X�e�[�W�̃f�[�^��������CSV�t�@�C�����J��
	ifstream csvFile("./Resorces/Stage.csv");

	// �z��̒l��������
	stage[STAGE_HEIGHT][STAGE_WIDTH] = { 0 };

	/*
		2�d���[�v�ɂ��X�e�[�W�̃f�[�^���̐��l����荞��
	*/

	for (int i = 0; i < STAGE_HEIGHT; i++)
	{
		// ���͍Ō�͉��s�R�[�h�܂œǂ݂��ނ̂ň��O�܂œǂݍ���
		for (int j = 0; j < STAGE_WIDTH - 1; j++)
		{
			/*
				getline�̑�1�����͓ǂݏo���J�n�ʒu��\��
				(���̃R�[�h�ł͌��݈ʒu��\��)
				��2�����͓ǂݏo������w��
				��3�����͏I�[�Ƃ��镶�����w��
			*/
			getline(csvFile.seekg(0, ios_base::cur), str, ',');

			// stringstream�ɓǂ݂�����string�𗬂�
			ss.str(str);

			/*
				stringstream����z��ɗ���
				���̎���string�^����int�^�̕ϊ����ÖٓI�ɍs����
			*/
			ss >> stage[i][j];

			/*
				�O�̕������c���đz��ʂ�̐��l���z��Ɋi�[�ł��Ȃ�����
				stringstream���ȉ��̂Q�s�̃R�[�h�ŃN���A����
			*/
			ss.str("");
			ss.clear(stringstream::goodbit);
		}

		// ���̍Ō�̐��l�͉��s�R�[�h�܂œǂݍ��ݎ��̍s�ֈړ�������
		getline(csvFile.seekg(0, ios_base::cur), str, '\n');
		ss.str(str);

		// STAGE_WIDTH�̒l�����̂܂܎g���Ɣz��O�ɂȂ��Ă��܂�����-1����
		ss >> stage[i][STAGE_WIDTH - 1];

		/*
			�����ł��O�̕������c���đz��ʂ�̐��l���z��Ɋi�[�ł��Ȃ�����
			stringstream���ȉ��̂Q�s�̃R�[�h�ŃN���A����
		*/
		ss.str("");
		ss.clear(stringstream::goodbit);
	}

	// CSV�t�@�C������ăt�@�C���ւ̃A�N�Z�X�����J������B
	csvFile.close();
}

// �Q�[���̃��x�����Ǘ����A�����ɉ����ă��x�����グ��֐�
// �X�R�A�̒l�ɉ����ă��x����ݒ肵�A���x�����オ�邲�ƂɃu���b�N�̑��x���オ��
void my_change_lv() {
	if (score < 10) {
		lv = 1;
		block_speed = 0.3f;
	}
	else if (score < 20) {
		lv = 2;
		block_speed = 0.5f;
	}
	else if (score < 30) {
		lv = 3;
		block_speed = 1.0f;
	}
	else if (score < 40) {
		lv = 4;
		block_speed = 1.5f;
	}
	else {
		lv = 5;
		block_speed = 2.0f;
	}
}

// ���j���[��ʂ��o�����Ƃ��̏���
// �֐����̓��͏����̓R���g���[���[�g�p/�s�g�p�ɂ���ăR�����g������Ƃ����ς���
void ChoiceBackTitle() {
	// �I���������ʂ�`��
	DrawGraph(70, 70, menu_img1, TRUE);

	// �L�[���͂ɂ��I������ω�
	if (choice < 1 && key[KEY_INPUT_UP] == 1){
	// if (choice < 1 && GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP) {
		choice++;
	}
	else if (choice > 0 && key[KEY_INPUT_DOWN] == 1) {
	// else if (choice > 0 && GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN) {
		choice--;
	}

	// �I�����̒l�ɉ����ĎO�p�`��`��
	if (choice == 0) {
		DrawTriangle(370, 263, 395, 280, 395, 246, Color_Yellow, TRUE);
	}
	else {
		DrawTriangle(370, 210, 395, 227, 395, 193, Color_Yellow, TRUE);
	}

	// �G�X�P�[�v�L�[��������A�{�^���ŉ�ʑJ��
	if (key[KEY_INPUT_ESCAPE] == 1) {
	//if (key[KEY_INPUT_ESCAPE] == 1 || GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_C) {
		if (choice == 0) {
			game_state = GAME_PLAYING;
		}
		else {
			StopSoundMem(gameSound);	// ���y���~�߂�
			game_state = GAME_INIT;		// �Q�[����Ԃ�������Ԃ�
			// �����������̌Ăяo��
			my_init_var();
			// �^�C�}�[����
			//WaitTimer(100);
		}
	}
}