#include "DxLib.h"
#include "Player.h"
#include <cmath>

#define DEFAULT_DX_MAX 5
#define DEFAULT_DY_MAX 5
#define DEFAULT_DECAY 0.9


// キー入力フレーム格納変数
static int Key[256];

/// <summary>
/// 入力キーの更新
/// </summary>
/// <returns></returns>
int updateKeyInput() {

	char tmp[256];						// 入力キーを格納
	GetHitKeyStateAll(tmp);

	for (int i = 0; i < 256; i++) {
		if (tmp[i] != 0) Key[i]++;		// 入力があればフレームを加算
		else Key[i] = 0;				// 無ければ0に
	}

	return 0;
}

/// <summary>
/// Playerコンストラクタ（イメージファイル，操作可否指定）
/// </summary>
/// <param name="Filename">キャラクターイメージ</param>
/// <param name="opeFlag">操作可否フラグ</param>
Player::Player(std::string Filename, bool opeFlag) {

	setImage(Filename);									// キャラチップ設定
	x = 0; y = 0;										// 座標初期化
	dx = 0; dy = 0;										// 速度初期化
	dx_MAX = DEFAULT_DX_MAX; dy_MAX = DEFAULT_DY_MAX;	// 最大速度の初期化
	decay = DEFAULT_DECAY;								// 減衰の初期化
	operate_Flag = opeFlag;								// 操作フラグの設定
	overhangFlag = TRUE;								// ハミダシ可否フラグの初期化

}

/// <summary>
/// Playerコンストラクタ（引数なし）（デフォルトキャラクター）
/// </summary>
Player::Player() {

	setImage("res/test.png");							// キャラチップ設定
	x = 0; y = 0;										// 座標初期化
	dx = 0; dy = 0;										// 速度初期化
	dx_MAX = DEFAULT_DX_MAX; dy_MAX = DEFAULT_DY_MAX;	// 最大速度初期化
	decay = DEFAULT_DECAY;								// 減衰の初期化
	operate_Flag = TRUE;								// 操作フラグの初期化
	overhangFlag = TRUE;								// ハミダシ可否フラグの初期化

}

/// <summary>
/// Player画像の設定，およびキャラチップオフセットの設定
/// </summary>
/// <param name="Filename">画像ファイルのパス指定(string)</param>
void Player::setImage(std::string Filename) {

	player_image_file = Filename;						// メンバ変数にファイルパスを格納
	Handle = LoadGraph(player_image_file.c_str());		// 画像ハンドル格納

	int gx, gy;											// 画像サイズ格納用
	GetGraphSize(Handle, &gx, &gy);						// 画像サイズ取得

	offset_X = gx / 2.0;								// オフセットの設定
	offset_Y = gy / 2.0;								// (画像サイズ / 2)

	return;
}

/// <summary>
/// 速度最大値，減速度の設定
/// </summary>
/// <param name="max_x">x方向の最大速度</param>
/// <param name="max_y">y方向の最大速度</param>
void Player::setVeloMAX(int max_x, int max_y, double td) {

	dx_MAX = max_x;										// x方向速度最大値
	dy_MAX = max_y;										// y方向速度最大値
	decay = td;											// 減衰係数

	return;
}

/// <summary>
/// プレイヤー座標の直接指定
/// </summary>
/// <param name="x">x座標</param>
/// <param name="y">y座標</param>
void Player::setPos(int x, int y) {

	this->x = x;										// x座標
	this->y = y;										// y座標

	return;
}

/// <summary>
/// 操作可否の変更
/// </summary>
/// <param name="opeFlag">操作可否</param>
void Player::changeOperation(bool opeFlag) {

	operate_Flag = opeFlag;

	return;
}

/// <summary>
/// 操作キャラの画面ハミダシを許容するか
/// </summary>
/// <param name="ohFlag">可否フラグ</param>
void Player::overhangSetting(bool ohFlag) {

	overhangFlag = ohFlag;
	
	return;
}

/// <summary>
/// キャラクター位置の更新
/// </summary>
void Player::pos_Update() {

	if (operate_Flag) {													// 操作フラグが立っているか

		updateKeyInput();												// キー入力更新

		if (Key[KEY_INPUT_RIGHT] >= 1) dx += 0.5;						// →入力
		if (Key[KEY_INPUT_LEFT] >= 1) dx -= 0.5;						// ←入力
		if (Key[KEY_INPUT_UP] >= 1) dy -= 0.5;							// ↑入力
		if (Key[KEY_INPUT_DOWN] >= 1) dy += 0.5;						// ↓入力

		if (Key[KEY_INPUT_RIGHT] == 0 && Key[KEY_INPUT_LEFT] == 0) {	// 左右入力がないか

			dx *= decay;												// x方向に減衰をかける

		}

		if (Key[KEY_INPUT_UP] == 0 && Key[KEY_INPUT_DOWN] == 0) {		// 上下入力がないか

			dy *= decay;												// y方向に減衰をかける

		}

		if (std::abs(dx) > dx_MAX) dx = dx_MAX * dx / std::abs(dx);		// 最大速度を超えてたら制限
		if (std::abs(dy) > dy_MAX) dy = dy_MAX * dy / std::abs(dy);

		x += dx;														// 速度を座標に加算
		y += dy;

		if (!overhangFlag) {											// 画面外ハミダシNGなら処理追加

			int sx, sy;
			GetDrawScreenSize(&sx, &sy);								// スクリーンサイズ取得

			if (x + offset_X < 0) x = -offset_X;						// x座標のハミダシ防止(オフセットあり)
			else if (x + offset_X > sx) x = sx - offset_X;

			if (y + offset_Y < 0) y = -offset_Y;						// y座標のハミダシ防止(オフセットあり)
			else if (y + offset_Y > sy) y = sy - offset_Y;
		}

		draw();															// 描画処理
	}

	return;
}

/// <summary>
/// キャラクター描画
/// </summary>
void Player::draw() {

	SetDrawMode(DX_DRAWMODE_BILINEAR);			// 補間をバイリニアに
	DrawGraphF(x, y, Handle, TRUE);				// 描画
	SetDrawMode(DX_DRAWMODE_NEAREST);			// 補間をニアレストに戻す

	return;
}

/// <summary>
/// 終了処理
/// </summary>
void Player::finalize() {

	DeleteGraph(Handle);				// ハンドル削除

	return;
}