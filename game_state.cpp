/*
	ゲームの状態等を管理する関数を記述したソース
*/
#include "main.h"

// パブリック変数宣言
// 以下は配列
int stage[STAGE_HEIGHT][STAGE_WIDTH];	// ステージ

// 以下はゲームの状態やUI等
int game_state;			// ゲームの状態を定義する変数
int menu_img1;			// メニュー画像を格納する変数
int clear_count;		// 何回ブロックが一列揃い消されたか管理する変数
int choice;				// 選択肢の変数（0がいいえ、1がはい） 
bool firstInitFlg;		// 初回起動かどうか管理するフラグ
bool clear_flag;		// ブロックが一列揃い消されたか管理するフラグ
bool gameover_flag;		// ゲームオーバーかどうか管理するフラグ
bool holdflg;			// ホールドをしたかどうか管理するフラグ
bool first_hold_flag;	// 初回ホールドかどうか管理するフラグ

// 以下はブロック関係
int block_x;			// ブロックのx座標
int block_y;			// ブロックのy座標
int block_id;			// ブロックのidを格納する変数
int useBlockCnt;		// 何回ブロックが使われたか管理する変数
int next_block_id;		// 次のブロックのidを格納する変数
int hold_block_id;		// ホールドされているブロックのidを格納する変数
int turn_point;			// ブロックの向きを定義する変数
int hold_turn_point;	// ホールド時にブロックの向きをそのままにさせる変数
int block_y_point;		// ブロックのy座標を格納する変数
int fix_count;			// ブロック固定のカウント変数
float block_y_count;	// ブロックのy座標をカウントする変数
float block_speed;		// ブロックの落下するスピード
bool collision_flag;	// ブロックがぶつかっているかどうか管理するフラグ
bool turnFlg;			// ブロックが回転できるかどうかのフラグ
bool first_block_flag;	// 最初のブロックかどうか管理するフラグ
bool make_block_flag;	// ブロックが作られているかどうか管理するフラグ

// タイトル画面の時の変数の初期化処理
void my_init_var() {

	/*
		以下は初回起動時にのみ呼び出す処理
	*/
	if (firstInitFlg == true) {
		// 各色の初期化
		Color_Red = GetColor(255, 0, 0);
		Color_Black = GetColor(0, 0, 0);
		Color_Green = GetColor(0, 255, 0);
		Color_Blue = GetColor(0, 0, 255);
		Color_Yellow = GetColor(255, 255, 0);
		Color_Fuchsia = GetColor(255, 0, 255);
		Color_Aqua = GetColor(0, 255, 255);
		Color_Orange = GetColor(255, 165, 0);

		// 画像の取り込み
		back_img1 = LoadGraph("./Resorces/teto.png");		// 背景
		menu_img1 = LoadGraph("./Resorces/GameMenu.png");  // メニュー

		// BGMの取り込み
		gameSound = LoadSoundMem("./Resorces/RnI8fDSITxE.mp3");	// BGM

		// 音量の設定（0～255の範囲で設定）
		ChangeVolumeSoundMem(128, gameSound);

		// ミノのデータ読み込み
		LoadMino();

		game_state = GAME_INIT;	// ゲームの状態をタイトル画面の時にする
		firstInitFlg = false;	// 初回起動かどうかのフラグをfalseにする
	}

	/*
		以下は関数が呼び出されたときに毎回呼び出される処理
	*/
	// ステージの初期化
	LoadStage();

	// ホールド欄の初期化
	for (int i = 0; i < BLOCK_HEIGHT; i++) {
		for (int j = 0; j < BLOCK_WIDTH; j++) {
			hold_block[i][j] = 0;
		}
	}

	// 使われているブロック管理の初期化
	for (int i = 0; i < BLOCK_NONUM; i++) {
		// 0はOミノなため、使われていない7を代入して初期化
		useBlocks[i] = 7;
	}

	// 各変数の初期化
	// ブロックを出すたびに初期化が必要な変数の初期化
	my_init_var2();

	// ゲームスタート時に初期化が必要な変数の初期化
	// 以下はブロック関係
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
	// 以下はゲーム進行関係
	lv = 1;
	score = 0;
	choice = 0;

	// 乱数の初期化
	srand((unsigned)time(NULL));
}

// ブロックを出すたびに初期化が必要な変数の初期化を行う関数
void my_init_var2() {
	block_x = 7;
	block_y = 0;
	block_y_count = 0;
	make_block_flag = true;
	turn_point = 0;
	block_y_point = 0;
	fix_count = 0;
}

// ミノのCSVデータ読み込みを行う関数
void LoadMino() {
	// getlineによって読み込まれた文字列を取り込むローカル変数
	string str;

	// strに取り込まれた文字列を読み込み配列へ格納させるローカル変数
	stringstream ss;

	// 以下のifstreamによって、ミノのデータが入ったCSVファイルを開く
	ifstream csvFile("./Resorces/Mino.csv");

	// 配列の値を初期化
	blocks[BLOCK_HEIGHT * BLOCK_NONUM][BLOCK_WIDTH * BLOCK_PATTERN] = { 0 };

	/*
		2重ループによりミノの状態分の数値を取り込む
	*/

	for (int i = 0; i < BLOCK_HEIGHT * BLOCK_NONUM; i++)
	{
		// 横は最後は改行コードまで読みこむので一つ手前まで読み込む
		for (int j = 0; j < (BLOCK_WIDTH * BLOCK_PATTERN) - 1; j++)
		{
			/*
				getlineの第1引数は読み出し開始位置を表す
				(このコードでは現在位置を表す)
				第2引数は読み出し先を指定
				第3引数は終端とする文字を指定
			*/
			getline(csvFile.seekg(0, ios_base::cur), str, ',');

			// stringstreamに読みだしたstringを流す
			ss.str(str);

			/*
				stringstreamから配列に流す
				この時にstring型からint型の変換が暗黙的に行われる
			*/
			ss >> blocks[i][j];

			/*
				前の文字が残って想定通りの数値が配列に格納できないため
				stringstreamを以下の２行のコードでクリアする
			*/
			ss.str("");
			ss.clear(stringstream::goodbit);
		}

		// 横の最後の数値は改行コードまで読み込み次の行へ移動させる
		getline(csvFile.seekg(0, ios_base::cur), str, '\n');
		ss.str(str);

		// BLOCK_WIDTH * BLOCK_PATTERNの値をそのまま使うと配列外になってしまうため-1する
		ss >> blocks[i][(BLOCK_WIDTH * BLOCK_PATTERN) - 1];

		/*
			ここでも前の文字が残って想定通りの数値が配列に格納できないため
			stringstreamを以下の２行のコードでクリアする
		*/
		ss.str("");
		ss.clear(stringstream::goodbit);
	}

	// CSVファイルを閉じてファイルへのアクセス権を開放する。
	csvFile.close();
}

// ステージのCSVデータ読み込みを行う関数
void LoadStage() {
	// getlineによって読み込まれた文字列を取り込むローカル変数
	string str;

	// strに取り込まれた文字列を読み込み配列へ格納させるローカル変数
	stringstream ss;

	// 以下のifstreamによって、ステージのデータが入ったCSVファイルを開く
	ifstream csvFile("./Resorces/Stage.csv");

	// 配列の値を初期化
	stage[STAGE_HEIGHT][STAGE_WIDTH] = { 0 };

	/*
		2重ループによりステージのデータ分の数値を取り込む
	*/

	for (int i = 0; i < STAGE_HEIGHT; i++)
	{
		// 横は最後は改行コードまで読みこむので一つ手前まで読み込む
		for (int j = 0; j < STAGE_WIDTH - 1; j++)
		{
			/*
				getlineの第1引数は読み出し開始位置を表す
				(このコードでは現在位置を表す)
				第2引数は読み出し先を指定
				第3引数は終端とする文字を指定
			*/
			getline(csvFile.seekg(0, ios_base::cur), str, ',');

			// stringstreamに読みだしたstringを流す
			ss.str(str);

			/*
				stringstreamから配列に流す
				この時にstring型からint型の変換が暗黙的に行われる
			*/
			ss >> stage[i][j];

			/*
				前の文字が残って想定通りの数値が配列に格納できないため
				stringstreamを以下の２行のコードでクリアする
			*/
			ss.str("");
			ss.clear(stringstream::goodbit);
		}

		// 横の最後の数値は改行コードまで読み込み次の行へ移動させる
		getline(csvFile.seekg(0, ios_base::cur), str, '\n');
		ss.str(str);

		// STAGE_WIDTHの値をそのまま使うと配列外になってしまうため-1する
		ss >> stage[i][STAGE_WIDTH - 1];

		/*
			ここでも前の文字が残って想定通りの数値が配列に格納できないため
			stringstreamを以下の２行のコードでクリアする
		*/
		ss.str("");
		ss.clear(stringstream::goodbit);
	}

	// CSVファイルを閉じてファイルへのアクセス権を開放する。
	csvFile.close();
}

// ゲームのレベルを管理し、条件に応じてレベルを上げる関数
// スコアの値に応じてレベルを設定し、レベルが上がるごとにブロックの速度が上がる
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

// メニュー画面を出したときの処理
// 関数内の入力処理はコントローラー使用/不使用によってコメント化するところを変える
void ChoiceBackTitle() {
	// 選択させる画面を描画
	DrawGraph(70, 70, menu_img1, TRUE);

	// キー入力により選択肢を変化
	if (choice < 1 && key[KEY_INPUT_UP] == 1){
	// if (choice < 1 && GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP) {
		choice++;
	}
	else if (choice > 0 && key[KEY_INPUT_DOWN] == 1) {
	// else if (choice > 0 && GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN) {
		choice--;
	}

	// 選択肢の値に応じて三角形を描画
	if (choice == 0) {
		DrawTriangle(370, 263, 395, 280, 395, 246, Color_Yellow, TRUE);
	}
	else {
		DrawTriangle(370, 210, 395, 227, 395, 193, Color_Yellow, TRUE);
	}

	// エスケープキーもしくはAボタンで画面遷移
	if (key[KEY_INPUT_ESCAPE] == 1) {
	//if (key[KEY_INPUT_ESCAPE] == 1 || GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_C) {
		if (choice == 0) {
			game_state = GAME_PLAYING;
		}
		else {
			StopSoundMem(gameSound);	// 音楽を止める
			game_state = GAME_INIT;		// ゲーム状態を初期状態へ
			// 初期化処理の呼び出し
			my_init_var();
			// タイマー処理
			//WaitTimer(100);
		}
	}
}