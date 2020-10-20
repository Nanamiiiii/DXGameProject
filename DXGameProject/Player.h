#pragma once
#include <string>

/// <summary>
/// Playerクラス定義
/// </summary>
class Player {
	
	std::string player_image_file;		// キャラクター画像のパス
	double offset_X, offset_Y;			// キャラチップ中心へのオフセット
	double x, y;						// プレイヤー座標
	double dx, dy;						// プレイヤー座標変化
	double dx_MAX, dy_MAX;				// 最大速度
	double decay;						// 減速
	int Handle;							// イメージハンドル
	bool operate_Flag;					// ユーザー操作フラグ（デフォルトはTRUE）
	bool overhangFlag;					// 画面ハミダシフラグ（デフォルトはTRUE）

public:
	// 外部から扱える関数類
	
	/// <summary>
	/// Playerコンストラクタ（引数なし）（デフォルトキャラクター）
	/// </summary>
	Player();

	/// <summary>
	/// Playerコンストラクタ（イメージファイル，操作可否指定）
	/// </summary>
	/// <param name="Filename">キャラクターイメージ</param>
	/// <param name="opeFlag">操作可否フラグ</param>
	Player(std::string Filename, bool opeFlag);
	
	/// <summary>
	/// Player画像の設定
	/// </summary>
	/// <param name="Filename">画像ファイルのパス指定(string)</param>
	void setImage(std::string Filename);

	/// <summary>
	/// 速度最大値，減速度の設定
	/// </summary>
	/// <param name="max_x">x方向の最大速度</param>
	/// <param name="max_y">y方向の最大速度</param>
	void setVeloMAX(int max_x, int max_y, double td);

	/// <summary>
	/// プレイヤー座標の直接指定
	/// </summary>
	/// <param name="x">x座標</param>
	/// <param name="y">y座標</param>
	void setPos(int x, int y);

	/// <summary>
	/// 操作可否の変更
	/// </summary>
	/// <param name="opeFlag">操作可否</param>
	void changeOperation(bool opeFlag);

	/// <summary>
	/// 操作キャラの画面ハミダシを許容するか
	/// </summary>
	/// <param name="ohFlag">可否フラグ</param>
	void overhangSetting(bool ohFlag);

	/// <summary>
	/// キャラクター位置の更新
	/// </summary>
	void pos_Update();

	/// <summary>
	/// 終了処理
	/// </summary>
	void finalize();

private:
	/// <summary>
	/// キャラクター描画
	/// </summary>
	void draw();
};