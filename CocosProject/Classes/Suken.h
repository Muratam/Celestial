#pragma once
#pragma execution_character_set("utf-8")

//�Z�[�t�J���[�ɂ���
//0�A51�A102�A153�A204�A255��6�i�K��RGB�Ōv216�g���܂��B

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

class CIntData{///�}�C�i�X�ɂ͖��Ή�
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
	char BACK;//KEY_INPUT_BACK  // �o�b�N�X�y�[�X�L�[ 
	char TAB;//KEY_INPUT_TAB  // �^�u�L�[ 
	char RETURN;//KEY_INPUT_RETURN  // �G���^�[�L�[
	char LSHIFT;//KEY_INPUT_LSHIFT  // ���V�t�g�L�[ 
	char RSHIFT;//KEY_INPUT_RSHIFT  // �E�V�t�g�L�[ 
	char LCONTROL;//KEY_INPUT_LCONTROL  // ���R���g���[���L�[ 
	char RCONTROL;//KEY_INPUT_RCONTROL  // �E�R���g���[���L�[ 
	char ESCAPE;//KEY_INPUT_ESCAPE  // �G�X�P�[�v�L�[ 
	char SPACE;//KEY_INPUT_SPACE  // �X�y�[�X�L�[ 
	char LEFT;//KEY_INPUT_LEFT  // ���L�[ 
	char UP;//KEY_INPUT_UP  // ��L�[ 
	char RIGHT;//KEY_INPUT_RIGHT  // �E�L�[ 
	char DOWN;//KEY_INPUT_DOWN  // ���L�[ 
	char INSERT;//KEY_INPUT_INSERT  // �C���T�[�g�L�[ 
	char Delete;//KEY_INPUT_DELETE  // �f���[�g�L�[
	char LALT;//KEY_INPUT_LALT  // ���`�k�s�L�[ 
	char RALT;//KEY_INPUT_RALT  // �E�`�k�s�L�[ 
	char SCROLL;//KEY_INPUT_SCROLL  // ScrollLock�L�[
	char CAPSLOCK;//KEY_INPUT_CAPSLOCK  // CaspLock�L�[ 
	char PAUSE;//KEY_INPUT_PAUSE  // PauseBreak�L�[
	char MINUS ; // �|�L�[ 
	char YEN ;  // ���L�[ 
	char PREVTRACK ; // �O�L�[ 
	char PERIOD ; // �D�L�[ 
	char SLASH ; // �^�L�[ 
	char SEMICOLON ; // �G�L�[ 
	char COLON ; // �F�L�[ 
	char LBRACKET ; // �m�L�[ 
	char RBRACKET ; // �n�L�[ 
	char AT ; // ���L�[ 
	char BACKSLASH ; // �_�L�[ 
	char COMMA ; // �C�L�[ 
	char F1 ; // �e�P�L�[ 
	char F2 ; // �e�Q�L�[ 
	char F3 ; // �e�R�L�[ 
	char F4 ; // �e�S�L�[ 
	char F5 ; // �e�T�L�[ 
	char F6 ; // �e�U�L�[ 
	char F7 ; // �e�V�L�[ 
	char F8 ; // �e�W�L�[ 
	char F9 ; // �e�X�L�[ 
	char F10 ; // �e�P�O�L�[ 
	char F11 ; // �e�P�P�L�[ 
	char F12 ; // �e�P�Q�L�[
	char A ; // �`�L�[ 
	char B ; // �a�L�[ 
	char C ; // �b�L�[ 
	char D ; // �c�L�[ 
	char E ; // �d�L�[ 
	char F ; // �e�L�[ 
	char G ; // �f�L�[ 
	char H ; // �g�L�[ 
	char I ; // �h�L�[ 
	char J ; // �i�L�[ 
	char K ; // �j�L�[ 
	char L ; // �k�L�[ 
	char M ; // �l�L�[ 
	char N ; // �m�L�[ 
	char O ; // �n�L�[ 
	char P ; // �o�L�[ 
	char Q ; // �p�L�[ 
	char R ; // �q�L�[ 
	char S ; // �r�L�[ 
	char T ; // �s�L�[ 
	char U ; // �t�L�[ 
	char V ; // �u�L�[ 
	char W ; // �v�L�[ 
	char X ; // �w�L�[ 
	char Y ; // �x�L�[ 
	char Z ; // �y�L�[ 
	char Key0 ; // �O�L�[ 
	char Key1 ; // �P�L�[ 
	char Key2 ; // �Q�L�[ 
	char Key3 ; // �R�L�[ 
	char Key4 ; // �S�L�[ 
	char Key5 ; // �T�L�[ 
	char Key6 ; // �U�L�[ 
	char Key7 ; // �V�L�[ 
	char Key8 ; // �W�L�[ 
	char Key9 ; // �X�L�[ 
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