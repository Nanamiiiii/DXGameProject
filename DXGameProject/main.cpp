#include <iostream>
#include "DXLib.h"
#include "Player.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	
	ChangeWindowMode(TRUE);
	SetGraphMode(640, 480, 32);
	SetOutApplicationLogValidFlag(FALSE);

	if (DxLib_Init() == -1) return -1;

	Player* testPlayer = new Player();
	testPlayer->overhangSetting(FALSE);

	while (ProcessMessage() == 0) {
		ClearDrawScreen();
		SetDrawScreen(DX_SCREEN_BACK);

		// Write Here
		testPlayer->pos_Update();

		ScreenFlip();

	}

	testPlayer->finalize();

	DxLib_End();

	return 0;

}