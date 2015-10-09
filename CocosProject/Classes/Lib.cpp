#include "Suken.h"
#include "DxLib.h"
#include <cstring>

void KEYCHECK(char &CC ,int INPUT  ){
	switch(CC){
		case 0:
		CC =INPUT;
		break;
		case 1:
		CC++ ;
		break;
		case 2:
		CC = 2 * INPUT ;
		break;
	}
	return;
}


void CKeyPush::ALLKEYCHECK (){
	KEYCHECK(A, CheckHitKey(KEY_INPUT_A));
	KEYCHECK(B, CheckHitKey(KEY_INPUT_B));
	KEYCHECK(C, CheckHitKey(KEY_INPUT_C));
	KEYCHECK(D, CheckHitKey(KEY_INPUT_D));
	KEYCHECK(E, CheckHitKey(KEY_INPUT_E));
	KEYCHECK(F, CheckHitKey(KEY_INPUT_F));
	KEYCHECK(G, CheckHitKey(KEY_INPUT_G));
	KEYCHECK(H, CheckHitKey(KEY_INPUT_H));
	KEYCHECK(I, CheckHitKey(KEY_INPUT_I));
	KEYCHECK(J, CheckHitKey(KEY_INPUT_J));
	KEYCHECK(K, CheckHitKey(KEY_INPUT_K));
	KEYCHECK(L, CheckHitKey(KEY_INPUT_L));
	KEYCHECK(M, CheckHitKey(KEY_INPUT_M));
	KEYCHECK(N, CheckHitKey(KEY_INPUT_N));
	KEYCHECK(O, CheckHitKey(KEY_INPUT_O));
	KEYCHECK(P, CheckHitKey(KEY_INPUT_P));
	KEYCHECK(Q, CheckHitKey(KEY_INPUT_Q));
	KEYCHECK(R, CheckHitKey(KEY_INPUT_R));
	KEYCHECK(S, CheckHitKey(KEY_INPUT_S));
	KEYCHECK(T, CheckHitKey(KEY_INPUT_T));
	KEYCHECK(U, CheckHitKey(KEY_INPUT_U));
	KEYCHECK(V, CheckHitKey(KEY_INPUT_V));
	KEYCHECK(W, CheckHitKey(KEY_INPUT_W));
	KEYCHECK(X, CheckHitKey(KEY_INPUT_X));
	KEYCHECK(Y, CheckHitKey(KEY_INPUT_Y));
	KEYCHECK(Z, CheckHitKey(KEY_INPUT_Z));
	KEYCHECK(Key0, CheckHitKey(KEY_INPUT_0));
	KEYCHECK(Key1, CheckHitKey(KEY_INPUT_1));
	KEYCHECK(Key2, CheckHitKey(KEY_INPUT_2));
	KEYCHECK(Key3, CheckHitKey(KEY_INPUT_3));
	KEYCHECK(Key4, CheckHitKey(KEY_INPUT_4));
	KEYCHECK(Key5, CheckHitKey(KEY_INPUT_5));
	KEYCHECK(Key6, CheckHitKey(KEY_INPUT_6));
	KEYCHECK(Key7, CheckHitKey(KEY_INPUT_7));
	KEYCHECK(Key8, CheckHitKey(KEY_INPUT_8));
	KEYCHECK(Key9, CheckHitKey(KEY_INPUT_9));
	KEYCHECK(F1, CheckHitKey(KEY_INPUT_F1));
	KEYCHECK(F2, CheckHitKey(KEY_INPUT_F2));
	KEYCHECK(F3, CheckHitKey(KEY_INPUT_F3));
	KEYCHECK(F4, CheckHitKey(KEY_INPUT_F4));
	KEYCHECK(F5, CheckHitKey(KEY_INPUT_F5));
	KEYCHECK(F6, CheckHitKey(KEY_INPUT_F6));
	KEYCHECK(F7, CheckHitKey(KEY_INPUT_F7));
	KEYCHECK(F8, CheckHitKey(KEY_INPUT_F8));
	KEYCHECK(F9, CheckHitKey(KEY_INPUT_F9));
	KEYCHECK(F10, CheckHitKey(KEY_INPUT_F10));
	KEYCHECK(F11, CheckHitKey(KEY_INPUT_F11));
	KEYCHECK(F12, CheckHitKey(KEY_INPUT_F12));
	KEYCHECK( BACK, CheckHitKey(KEY_INPUT_BACK));//KEY_INPUT_BACK  // バックスペースキー 
	KEYCHECK( TAB, CheckHitKey(KEY_INPUT_TAB));//KEY_INPUT_TAB  // タブキー 
	KEYCHECK( RETURN, CheckHitKey(KEY_INPUT_RETURN));//KEY_INPUT_RETURN  // エンターキー
	KEYCHECK( LSHIFT, CheckHitKey(KEY_INPUT_LSHIFT));//KEY_INPUT_LSHIFT  // 左シフトキー 
	KEYCHECK( RSHIFT, CheckHitKey(KEY_INPUT_RSHIFT));//KEY_INPUT_RSHIFT  // 右シフトキー 
	KEYCHECK( LCONTROL, CheckHitKey(KEY_INPUT_LCONTROL));//KEY_INPUT_LCONTROL  // 左コントロールキー 
	KEYCHECK( RCONTROL, CheckHitKey(KEY_INPUT_RCONTROL));//KEY_INPUT_RCONTROL  // 右コントロールキー 
	KEYCHECK( ESCAPE, CheckHitKey(KEY_INPUT_ESCAPE));//KEY_INPUT_ESCAPE  // エスケープキー 
	KEYCHECK( SPACE, CheckHitKey(KEY_INPUT_SPACE));//KEY_INPUT_SPACE  // スペースキー 
	KEYCHECK( LEFT, CheckHitKey(KEY_INPUT_LEFT));//KEY_INPUT_LEFT  // 左キー 
	KEYCHECK( UP, CheckHitKey(KEY_INPUT_UP));//KEY_INPUT_UP  // 上キー 
	KEYCHECK( RIGHT, CheckHitKey(KEY_INPUT_RIGHT));//KEY_INPUT_RIGHT  // 右キー 
	KEYCHECK( DOWN, CheckHitKey(KEY_INPUT_DOWN));//KEY_INPUT_DOWN  // 下キー 
	KEYCHECK( INSERT, CheckHitKey(KEY_INPUT_INSERT));//KEY_INPUT_INSERT  // インサートキー 
	KEYCHECK( Delete, CheckHitKey(KEY_INPUT_DELETE));//KEY_INPUT_DELETE  // デリートキー
	KEYCHECK( LALT, CheckHitKey(KEY_INPUT_LALT));//KEY_INPUT_LALT  // 左ＡＬＴキー 
	KEYCHECK( RALT, CheckHitKey(KEY_INPUT_RALT));//KEY_INPUT_RALT  // 右ＡＬＴキー 
	KEYCHECK( SCROLL, CheckHitKey(KEY_INPUT_SCROLL));//KEY_INPUT_SCROLL  // ScrollLockキー
	KEYCHECK( CAPSLOCK, CheckHitKey(KEY_INPUT_CAPSLOCK));//KEY_INPUT_CAPSLOCK  // CaspLockキー 
	KEYCHECK( PAUSE, CheckHitKey(KEY_INPUT_PAUSE));//KEY_INPUT_PAUSE  // PauseBreakキー
	KEYCHECK( MINUS , CheckHitKey(KEY_INPUT_MINUS)); // －キー 
	KEYCHECK( YEN , CheckHitKey(KEY_INPUT_YEN));  // ￥キー 
	KEYCHECK( PREVTRACK , CheckHitKey(KEY_INPUT_PREVTRACK)); // ＾キー 
	KEYCHECK( PERIOD , CheckHitKey(KEY_INPUT_PERIOD)); // ．キー 
	KEYCHECK( SLASH , CheckHitKey(KEY_INPUT_SLASH)); // ／キー 
	KEYCHECK( SEMICOLON , CheckHitKey(KEY_INPUT_SEMICOLON)); // ；キー 
	KEYCHECK( COLON , CheckHitKey(KEY_INPUT_COLON)); // ：キー 
	KEYCHECK( LBRACKET , CheckHitKey(KEY_INPUT_LBRACKET)); // ［キー 
	KEYCHECK( RBRACKET , CheckHitKey(KEY_INPUT_RBRACKET)); // ］キー 
	KEYCHECK( AT , CheckHitKey(KEY_INPUT_AT)); // ＠キー 
	KEYCHECK( BACKSLASH , CheckHitKey(KEY_INPUT_BACKSLASH)); // ＼キー 
	KEYCHECK( COMMA , CheckHitKey(KEY_INPUT_COMMA)); // ，キー 
}

int Power2(int x, int y){
    int i,result;
    for( i=1, result = 1; i <= y; i++) {result *= x;}
    return result;
}

int Clng ( char *Str ,int n ){
	char s[10];int ns = 0; int ret = 0;
	while(!(Str[n] == '\0' )  && ns < 10){
		switch (Str[n]){
		case '0': s[ns] = 0 ;ns++;break;case '1': s[ns] = 1 ;ns++;break;  
		case '2': s[ns] = 2 ;ns++;break;case '3': s[ns] = 3 ;ns++;break;  
		case '4': s[ns] = 4 ;ns++;break;case '5': s[ns] = 5 ;ns++;break;  
		case '6': s[ns] = 6 ;ns++;break;case '7': s[ns] = 7 ;ns++;break;  
		case '8': s[ns] = 8 ;ns++;break;case '9': s[ns] = 9 ;ns++;break;   
		}
		n++;
	}
	int ss = 0;ns--;
	while(ns >= 0){
		ret += s[ns] * Power2(10,ss);
		ns--; ss++;
	}
	return ret ;
}

int ClngFrom ( char *Str ,char Word ){
	char s[10];int ns = 0; int ret = 0;
	int n = 0;
	while(!(Str[n] == '\0' || Str[n] == Word )  && ns < 10){n++;}
	while(!(Str[n] == '\0' )  && ns < 10){
		switch (Str[n]){
		case '0': s[ns] = 0 ;ns++;break;case '1': s[ns] = 1 ;ns++;break;  
		case '2': s[ns] = 2 ;ns++;break;case '3': s[ns] = 3 ;ns++;break;  
		case '4': s[ns] = 4 ;ns++;break;case '5': s[ns] = 5 ;ns++;break;  
		case '6': s[ns] = 6 ;ns++;break;case '7': s[ns] = 7 ;ns++;break;  
		case '8': s[ns] = 8 ;ns++;break;case '9': s[ns] = 9 ;ns++;break;   
		}
		n++;
	}
	int ss = 0;ns--;
	while(ns >= 0){
		ret += s[ns] * Power2(10,ss);
		ns--; ss++;
	}
	return ret ;
}

int ClngTo ( char *Str ,char Word ){
	char s[10];int ns = 0; int ret = 0;
	int n = 0;
	while(!(Str[n] == '\0' || Str[n] == Word)  && ns < 10){
		switch (Str[n]){
		case '0': s[ns] = 0 ;ns++;break;case '1': s[ns] = 1 ;ns++;break;  
		case '2': s[ns] = 2 ;ns++;break;case '3': s[ns] = 3 ;ns++;break;  
		case '4': s[ns] = 4 ;ns++;break;case '5': s[ns] = 5 ;ns++;break;  
		case '6': s[ns] = 6 ;ns++;break;case '7': s[ns] = 7 ;ns++;break;  
		case '8': s[ns] = 8 ;ns++;break;case '9': s[ns] = 9 ;ns++;break;   
		}
		n++;
	}
	int ss = 0;ns--;
	while(ns >= 0){
		ret += s[ns] * Power2(10,ss);
		ns--; ss++;
	}
	return ret ;
}

CIntData::CIntData(char *_DataName){
	int Len;
	Len = std::strlen (_DataName);
	DataName = new char [Len + 1];
	std::strcpy(DataName , _DataName);
	DataName[Len] = '\0';
}

void CIntData::NewMake(){
	FILE *fp;
	fp = UserDatafopen( DataName , "w+");/////////////書き込み
	if (fp == NULL){
		DataName = "iMaGiNaRy.imr";
		fp = UserDatafopen( DataName , "w+");
	}
	for(int i = 0; i <2000 ;i++){
	fputs("0:0\r\n" , fp);//書き込み
	}
	fclose(fp);
}

void CIntData::ReadData(){
	FILE *fp;	
	char s[64];
	fp = UserDatafopen( DataName , "a"); //ファイルを強引に作成or確保
	if (fp == NULL){
		DataName = "iMaGiNaRy.imr";
		fp = UserDatafopen( DataName , "a");
	}	
	fclose(fp);
	fp = UserDatafopen( DataName , "r+");/////////////読み込み
	int n = 0;
	while (fgets(s, 64, fp) != NULL && n < 2000) {
		LeftData[n] = ClngTo(s,':');
		RightData[n] = ClngFrom(s,':');
		n++;
	}
	fclose(fp);
	if(n == 0){NewMake ();ReadData() ;}
}

void CIntData::WriteData(){
	FILE *fp;	
	fp = UserDatafopen( DataName , "a"); //ファイルを強引に作成or確保
	if (fp == NULL){
		DataName = "iMaGiNaRy.imr";
		fp = UserDatafopen( DataName , "a");
	}	
	fclose(fp);
	fp = UserDatafopen( DataName , "r+");/////////////読み込み
 
	for(int i=0;i<2000;i++){/////////////書き込み	
	fprintf( fp, "%d:%d\r\n",LeftData[i],RightData[i] );
	}
	fclose(fp);

}


CBox::CBox(){
	Color = GetColor( 128 , 128 , 128 );
}

void CBox::Draw(){
	DrawBox( Left , Top , Left + Width , Top + Height , Color , TRUE );
}

CommandButton::CommandButton(){
	Left = 32;
	Top = 32;
	Width = 32;
	Height = 32;
	FontSize = 24;
	ForeColor = GetColor( 0 , 0 , 0 );
	BGColor = GetColor( 128 , 128 , 128 );
}

CommandButton::CommandButton( int _left , int _right , int _width , int _height ){
	Left = _left;
	Top = _right;
	Width = _width;
	Height = _height;
	FontSize = 24;
	ForeColor = GetColor( 0 , 0 , 0 );
	BGColor = GetColor( 128 , 128 , 128 );
}

void CommandButton::Draw(){
	int StringWidth;

	SetFontSize( FontSize );
	//StringWidth = GetDrawFormatStringWidth( "%s" , Caption );
	DrawBox( Left , Top , Left + Width , Top + Height , BGColor , TRUE );
	DrawFormatString( Left + ((Width - StringWidth)/2) , Top + ((Height - FontSize)/2) , ForeColor , "%s" , Caption );
}

void CommandButton::Judge(){
if( !(GetMouseInput() & MOUSE_INPUT_LEFT) ){
	return;
}

	int x;
	int y;
	
	GetMousePoint( &x , &y );

	if ( x > Left && y > Top && x < Left+Width && y < Top + Height ){
		if( Func != NULL ){
			Func();
		} else {
			Click();
		}
	}
}

void CommandButton::Update(){
	Draw();
	Judge();
}

void CommandButton::Click(){

}



CCircle::CCircle(){
	Left = 32;
	Top = 32;
	Radius = 8;
	Color = sukenRED;
}

void CCircle::Draw(){
	DrawCircle( Left , Top , Radius , Color , true );
}



CVector GetIntersection( int a1 , int b1 , int a2 , int b2 ){
	CVector Point;

	if( a1 != a2 ){
		Point.x = ( b2 - b1 ) / ( a1 - a2 );
	} else {
		Point.x = NULL;
		Point.y = NULL;
		return Point;
	}

	Point.y = (a1 * Point.x) + b1;

	return Point;
}