/*
	ゲームで使う定数、関数、外部変数を定義するヘッダー
*/

// 使用するヘッダーなどのインクルード
#include "DxLib.h"
#include <stdlib.h>
#include <time.h>
#include <string>	// stringstream を使うためにインポート
#include <sstream>	// ifstreamを使うためにインポート
#include <fstream>

using namespace std;	// stdがないと使えないものを使えるようにする

/*
	以下ゲームで使用する定数定義
*/

// ゲームの状態等
#define GAME_INIT 0		// タイトル画面の時
#define GAME_PLAYING 1	// ゲームプレイ中
#define GAME_MENU 2		// メニュー画面を開いているとき
#define GAME_OVER 3		// ゲームオーバー時

// ブロック関係
#define BLOCK_WIDTH 4	// ブロックの幅
#define BLOCK_HEIGHT 4	// ブロックの高さ
#define BLOCK_NONUM 7	// ブロックの種類の数
#define BLOCK_PATTERN 4	// ブロックの回転の種類数

// ステージ関係
#define STAGE_WIDTH 17	// ステージの幅のマスの数
#define STAGE_HEIGHT 23	// ステージの高さのマスの数

// 描画関係
#define DRAW_POSITION 140	// ステージのX座標の左端の値
#define DRAW_BLOCK_WIDTH 20	// 描画されるブロックの幅
#define NEXT_BLOCK_X 500	// 次のブロックが描画される左端のX座標
#define NEXT_BLOCK_Y 20		// 次のブロックが描画される上端のy座標
#define HOLD_BLOCK_X 60		// ホールドされているブロックが描画される左端のX座標
#define HOLD_BLOCK_Y 20		// ホールドされているブロックが描画される上端のy座標

//コントローラー

#define PAD_INPUT_DOWN								(0x00000001)	// ↓チェックマスク
#define PAD_INPUT_LEFT								(0x00000002)	// ←チェックマスク
#define PAD_INPUT_RIGHT								(0x00000004)	// →チェックマスク
#define PAD_INPUT_UP								(0x00000008)	// ↑チェックマスク
#define PAD_INPUT_A									(0x00000010)	// Ａボタンチェックマスク
#define PAD_INPUT_B									(0x00000020)	// ?ボタンチェックマスク
#define PAD_INPUT_C									(0x00000040)	// 〇ボタンチェックマスク
#define PAD_INPUT_X									(0x00000080)	// Ｘボタンチェックマスク
#define PAD_INPUT_Y									(0x00000100)	// □ボタンチェックマスク
#define PAD_INPUT_Z									(0x00000200)
#define PAD_INPUT_L									(0x00000400)
#define PAD_INPUT_R									(0x00000800)
#define PAD_INPUT_START								(0x00001000)
#define PAD_INPUT_M									(0x00002000)
#define PAD_INPUT_D									(0x00004000)
#define PAD_INPUT_F									(0x00008000)
#define PAD_INPUT_G									(0x00010000)    //タッチパッド
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
	ゲームで使用する関数定義
*/

// 初期化関係の関数
void my_init_var();		// ゲームの初期化
void my_init_var2();	// プレイ中に初期化する必要がある変数の初期化
void LoadMino();		// ミノをCSVから取り込み
void LoadStage();		// ステージをCSVから取り込み

// ゲームの状態やキー入力関係の関数
void my_get_key();		// キー入力時の処理
void my_change_lv();	// スコアに応じてレベルを変える関数
void my_gameover();		// ゲームオーバーかどうか判定
void ChoiceBackTitle();	// タイトルに戻るかどうか選択させる関数

// ブロック関係の関数
void my_make_block();		// ブロックを生成する関数
void my_hold_block();		// ブロックのホールド処理をする関数
void my_move_block();		// キーボードを押したことによりブロックを動かす処理
void my_fix_block();		// ブロックを固定する関数
void my_save_block();		// ブロックを保存する関数
void my_fall_block();		// ブロックを落下させる関数
void my_turn_right();		// ブロックの右向き回転の処理
void my_turn_left();		// ブロックの左向き回転の処理
void my_collision_left();	// ブロックの右移動の処理と接地判定
void my_collision_right();	// ブロックの左移動の処理と接地判定
void my_collision_bottom();	// ブロックの下移動（落下速度より早く）の処理と接地判定
void my_collision_center();	// 真ん中のブロックの接地判定
void my_collision_turn();	// ブロック回転時の接地判定
void my_search_line();		// ブロックが横一列すべてのマスにあるか判定
void my_clear_line();		// ブロックが横一列埋まって消すときの処理をする

// 描画関係の関数
void my_draw_back();		// 背景描画処理
void TitleDraw();			// タイトル画面の描画
void my_draw_variable();	// UIやNEXT、HOLDの描画処理
void my_draw_block();		// 落下中のブロックの描画処理
void my_draw_stage();		// 落下後のブロックの描画処理
void my_ed();				// ゲームオーバー画面の処理

/*
	ゲームで使用する外部変数定義
*/

// ブロック等の配列の外部変数
extern int block[BLOCK_HEIGHT][BLOCK_WIDTH];								// 現在メインで生成され落下しているブロック
extern int turn_block[BLOCK_HEIGHT][BLOCK_WIDTH];							// 回転しているブロック
extern int next_block[BLOCK_HEIGHT][BLOCK_WIDTH];							// 次のブロック
extern int hold_block[BLOCK_HEIGHT][BLOCK_WIDTH];							// ホールドされているブロック
extern int stage[STAGE_HEIGHT][STAGE_WIDTH];								// ステージ
extern int blocks[BLOCK_HEIGHT * BLOCK_NONUM][BLOCK_WIDTH * BLOCK_PATTERN];	// ブロックの各種のすべての向きを定義したもの
extern int clear_line_point[STAGE_HEIGHT - 3];								// ステージの各列そろっているかどうかみるもの
extern int useBlocks[BLOCK_NONUM];											// 今どのブロックが使われているか

// ゲームの状態やUI等の外部変数
extern int game_state;			// ゲームの状態を定義する変数
extern int lv;					// ゲームのレベルを定義する変数
extern int score;				// スコアを格納する変数
extern int back_img1;			// 背景画像を格納する変数
extern int menu_img1;			// メニュー画像を格納する変数
extern int gameSound;			// BGMを格納する変数
extern int key[256];			// 入力されたキーコードを格納する変数
extern int clear_count;			// 何回ブロックが一列揃い消されたか管理する変数
extern int choice;				// 選択肢の変数（0がいいえ、1がはい）
extern bool firstInitFlg;		// 初回起動かどうか管理するフラグ
extern bool clear_flag;			// ブロックが一列揃い消されたか管理するフラグ
extern bool gameover_flag;		// ゲームオーバーかどうか管理するフラグ
extern bool holdflg;			// ホールドをしたかどうか管理するフラグ
extern bool first_hold_flag;	// 初回ホールドかどうか管理するフラグ

// 色の外部変数
extern int Color_Red;		// 赤
extern int Color_Black;		// 黒
extern int Color_Green;		// 緑
extern int Color_Blue;		// 青
extern int Color_Yellow;	// 黄
extern int Color_Fuchsia;	// 紫
extern int Color_Aqua;		// 空色
extern int Color_Orange;	// オレンジ

// ブロック関係の外部変数
extern int block_x;				// ブロックのx座標
extern int block_y;				// ブロックのy座標
extern int block_id;			// ブロックのidを格納する変数
extern int useBlockCnt;			// 何回ブロックが使われたか管理する変数
extern int next_block_id;		// 次のブロックのidを格納する変数
extern int hold_block_id;		// ホールドされているブロックのidを格納する変数
extern int turn_point;			// ブロックの向きを定義する変数
extern int hold_turn_point;		// ホールド時にブロックの向きをそのままにさせる変数
extern int block_y_point;		// ブロックのy座標を格納する変数
extern int fix_count;			// ブロック固定のカウント変数
extern float block_y_count;		// ブロックのy座標をカウントする変数
extern float block_speed;		// ブロックの落下するスピード
extern bool collision_flag;		// ブロックがぶつかっているかどうか管理するフラグ
extern bool turnFlg;			// ブロックが回転できるかどうかのフラグ
extern bool first_block_flag;	// 最初のブロックかどうか管理するフラグ
extern bool make_block_flag;	// ブロックが作られているかどうか管理するフラグ