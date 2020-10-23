#pragma once
#include <string>
class MessageWindow {
	bool bg_flag;
	std::string background;

	bool face_flag;
	std::string face_image;
	int* face_pos;

	// ウィンドウ座標をint型ポインタとして持つ
	// コンストラクタでサイズ2の配列をもつ
	int* start_pos;
	int* end_pos;

	int visualizeMode;
	char* MessageWithControl;

public:
	MessageWindow(int start_pos[2], int end_pos[2]);

	void setPosition(int start_pos[2], int end_pos[2]);

	void setFaceimage(std::string filename, int face_pos[2]);

	void setBackground(std::string filename);

	void deleteFaceimage();

	void deleteBackground();

	void setMessage(char* Message);

	void setVisualizeMode(int Mode);

	void showMessage();

	void changeMessage(char* Message);
};