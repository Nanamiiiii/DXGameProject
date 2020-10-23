#include "DxLib.h"
#include "MessageWindow.h"
#include <iostream>

/// <summary>
/// Construntor
/// </summary>
/// <param name="start_pos">ウィンドウ左上座標(x,y)</param>
/// <param name="end_pos">ウィンドウ右下座標(x,y)</param>
MessageWindow::MessageWindow(int start_pos[2], int end_pos[2]) {
	this->start_pos = start_pos;
	this->end_pos = end_pos;
	
	bg_flag = false;
	face_flag = false;

	visualizeMode = 0;
}

void MessageWindow::setPosition(int start_pos[2], int end_pos[2]) {
	this->start_pos = start_pos;
	this->end_pos = end_pos;
}

void MessageWindow::setFaceimage(std::string filename, int face_pos[2]) {
	face_flag = true;
	face_image = filename;
	this->face_pos = face_pos;
}

void MessageWindow::setBackground(std::string filename) {
	bg_flag = true;
	background = filename;
}

void MessageWindow::deleteFaceimage() {
	face_image = "";
	face_pos = NULL;
	face_flag = false;
}

void MessageWindow::deleteBackground() {
	background = "";
	bg_flag = false;
}

void MessageWindow::setMessage(char* Message) {
	MessageWithControl = Message;
}

void MessageWindow::setVisualizeMode(int Mode) {
	visualizeMode = Mode;
}

void MessageWindow::showMessage(){

}