#pragma once
#pragma execution_character_set("utf-8")

//セーフカラーについて
//0、51、102、153、204、255の6段階のRGBで計216使えます。

#define sukenRED GetColor( 255 , 0 , 0 )
#define sukenGREEN GetColor( 0 , 255 , 0 )
#define sukenBLUE GetColor( 0 , 0 , 255 )
#define sukenBLACK GetColor( 0 , 0 , 0 )
#define sukenWHITE GetColor( 255 , 255 , 255 )
#define sukenGRAY GetColor( 128 , 128 , 128 )
#define sukenLIGHTBLUE GetColor( 128 , 128 , 255 )
#define sukenLIGHTGREEN GetColor( 128 , 255 , 128 )
#define sukenPINK GetColor( 255 , 128 , 128 )


#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 640
#define WINDOW_REALHEIGHT 690

typedef struct CVector{
	double x;
	double y;
};

void SukenExecute(char *URL);

class CIntData{///マイナスには未対応
public:
	CIntData(char *_DataName);
	char *DataName;
	void NewMake();
	void WriteData();
	void ReadData();
	int RightData[2000];
	int LeftData[2000];
};

class CBox{
public:
	CBox();

	int Left;
	int Top;
	int Width;
	int Height;
	int Color;

	void Draw();
private:
	
};

class CCircle{
public:
	CCircle();

	int Left;
	int Top;
	int Radius;
	int Color;

	void Draw();
private:
};

class CommandButton{
public:
	CommandButton();
	CommandButton( int _left , int _right , int _width , int _height );
	int Left;
	int Top;
	int Width;
	int Height;
	int ForeColor;
	int BGColor; //BackGroundColor
	int FontSize;

	char *Caption;

	void (*Func)();

	void Update();
	void Draw();
	void Judge();
	void Click();
private:
};

class CKeyPush{
public:
	char BACK;//KEY_INPUT_BACK  // バックスペースキー 
	char TAB;//KEY_INPUT_TAB  // タブキー 
	char RETURN;//KEY_INPUT_RETURN  // エンターキー
	char LSHIFT;//KEY_INPUT_LSHIFT  // 左シフトキー 
	char RSHIFT;//KEY_INPUT_RSHIFT  // 右シフトキー 
	char LCONTROL;//KEY_INPUT_LCONTROL  // 左コントロールキー 
	char RCONTROL;//KEY_INPUT_RCONTROL  // 右コントロールキー 
	char ESCAPE;//KEY_INPUT_ESCAPE  // エスケープキー 
	char SPACE;//KEY_INPUT_SPACE  // スペースキー 
	char LEFT;//KEY_INPUT_LEFT  // 左キー 
	char UP;//KEY_INPUT_UP  // 上キー 
	char RIGHT;//KEY_INPUT_RIGHT  // 右キー 
	char DOWN;//KEY_INPUT_DOWN  // 下キー 
	char INSERT;//KEY_INPUT_INSERT  // インサートキー 
	char Delete;//KEY_INPUT_DELETE  // デリートキー
	char LALT;//KEY_INPUT_LALT  // 左ＡＬＴキー 
	char RALT;//KEY_INPUT_RALT  // 右ＡＬＴキー 
	char SCROLL;//KEY_INPUT_SCROLL  // ScrollLockキー
	char CAPSLOCK;//KEY_INPUT_CAPSLOCK  // CaspLockキー 
	char PAUSE;//KEY_INPUT_PAUSE  // PauseBreakキー
	char MINUS ; // －キー 
	char YEN ;  // ￥キー 
	char PREVTRACK ; // ＾キー 
	char PERIOD ; // ．キー 
	char SLASH ; // ／キー 
	char SEMICOLON ; // ；キー 
	char COLON ; // ：キー 
	char LBRACKET ; // ［キー 
	char RBRACKET ; // ］キー 
	char AT ; // ＠キー 
	char BACKSLASH ; // ＼キー 
	char COMMA ; // ，キー 
	char F1 ; // Ｆ１キー 
	char F2 ; // Ｆ２キー 
	char F3 ; // Ｆ３キー 
	char F4 ; // Ｆ４キー 
	char F5 ; // Ｆ５キー 
	char F6 ; // Ｆ６キー 
	char F7 ; // Ｆ７キー 
	char F8 ; // Ｆ８キー 
	char F9 ; // Ｆ９キー 
	char F10 ; // Ｆ１０キー 
	char F11 ; // Ｆ１１キー 
	char F12 ; // Ｆ１２キー
	char A ; // Ａキー 
	char B ; // Ｂキー 
	char C ; // Ｃキー 
	char D ; // Ｄキー 
	char E ; // Ｅキー 
	char F ; // Ｆキー 
	char G ; // Ｇキー 
	char H ; // Ｈキー 
	char I ; // Ｉキー 
	char J ; // Ｊキー 
	char K ; // Ｋキー 
	char L ; // Ｌキー 
	char M ; // Ｍキー 
	char N ; // Ｎキー 
	char O ; // Ｏキー 
	char P ; // Ｐキー 
	char Q ; // Ｑキー 
	char R ; // Ｒキー 
	char S ; // Ｓキー 
	char T ; // Ｔキー 
	char U ; // Ｕキー 
	char V ; // Ｖキー 
	char W ; // Ｗキー 
	char X ; // Ｘキー 
	char Y ; // Ｙキー 
	char Z ; // Ｚキー 
	char Key0 ; // ０キー 
	char Key1 ; // １キー 
	char Key2 ; // ２キー 
	char Key3 ; // ３キー 
	char Key4 ; // ４キー 
	char Key5 ; // ５キー 
	char Key6 ; // ６キー 
	char Key7 ; // ７キー 
	char Key8 ; // ８キー 
	char Key9 ; // ９キー 
	void ALLKEYCHECK();
};

void Awake();
bool GameLoop();

void GameOver();

int Clng( char *Str ,int n = 0) ;
int ClngTo ( char *Str ,char Word );
int ClngFrom ( char *Str ,char Word );
int Power2(int x, int y);
CVector GetIntersection( int a1 , int b1 , int a2 , int b2 );