#include "DxLib.h"
#include "Suken.h"
#include "JPB.h"

void AppDelegate::CCDxInit(){
	SetMainWindowText("CELESTIAL");
	SetGraphMode(WINDOW_WIDTH, WINDOW_REALHEIGHT, 32);
	ChangeWindowMode(TRUE);
	EMULATE_TOUCH_BY_MOUSEFUNCTIONS();  //タッチ操作でマウスの関数を反応できるように
	SetBackgroundColor(0, 0, 0);  //画面の初期色の設定
}

void CCDxStart(){
	
	//EMULATE_KEYBOARD_BY_IMAGINARY_BUTTON(KEY_INPUT_DOWN);
	//EMULATE_KEYBOARD_BY_IMAGINARY_BUTTON(KEY_INPUT_UP);
	//EMULATE_KEYBOARD_BY_IMAGINARY_BUTTON(KEY_INPUT_RIGHT);
	//EMULATE_KEYBOARD_BY_IMAGINARY_BUTTON(KEY_INPUT_LEFT);
	EMULATE_KEYBOARD_BY_IMAGINARY_BUTTON(KEY_INPUT_Z);
	EMULATE_KEYBOARD_BY_IMAGINARY_BUTTON(KEY_INPUT_X);
	EMULATE_KEYBOARD_BY_IMAGINARY_BUTTON(KEY_INPUT_SPACE);
	ClearDrawScreen();
	EMULATE_KEYBOARD_ARROWS_BY_SWIPE();
	//EMULATE_KEYBOARD_BY_SINGLETOUCH(KEY_INPUT_P);
	FirstAwake();
}
bool isMenuLoop = true;
bool FirstLoop = true;
int x = 0, y = 0;
void CCDxLoop(float deltaTime){
	ClearDrawScreen();
	if (FirstLoop){
		if (isMenuLoop)	MenuAwake();
		else Awake();
		FirstLoop = false;
	}
	if (isMenuLoop){
		FirstLoop = MenuLoop();
	}else {
		FirstLoop = GameLoop();
		//if (!FirstLoop)FirstLoop = true;
	}
	if (FirstLoop)isMenuLoop = !isMenuLoop;
}