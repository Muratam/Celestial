#pragma once

#include "Suken.h"

#define CheatMP 0
#define CheatHP 0
#define CheatBall 0

class CCharacter;
class CWizard;

class CGraph{   
public:
	int Player[5] ;
	int Prayer[5] ;
	int Bomb[5];
	int Back;
	int Block[10];
	int Enemy[8];
	int Wizard[11];
	int EneBomb[8];
	int Gage[2];
	int MapTip;
	void GraphLoad( int ) ;
};

class CStuff{
public:
	int Stuff[6];
	int SE[2];
	int Chara[10];
	int Gage[2];
	void Load() ;
};

class CMusic{   
public:
	int BGM[7] ;
	int SE[20];
	void MusicLoad() ;
};

class CBase{
public:
	int Graph;
	bool Invisible ;
	void Draw(int);
	void Draw(int,int);
	void Draw(int,int,bool);
	int Left ;
	int Top;
	int Width;
	int Height;
	int Circle;//当たり判定のとき用
};

class CBall : public CBase{ //直線弾
public:
	int Attack;
	int Speed;
	int Dimension;//度です。
	bool Trans;
	void BallSet(CGraph,int,CCharacter*);
	void Move(int);
	void Move(int,int,int);
};


//キャラクター達(AI)
class CCharacter : public CBase{
public:
	int PlayerNumber;
	int Attack;
	int Diffence;
	int MP; int MaxMP;
	int HP; int MaxHP;
	int SpeedX; 
	int SpeedY;
	int MaxBall;
	void Move(int &SCROLL);
	void PushBomb(CGraph);
	void PushBomb2(CGraph);
	void CharaSet(int , CGraph);
	CBall *PastBall;
	CBall *MyBall;
	int NowMyMaxBall ;
	bool GirlBoy;
	bool ScrollSwitch;
	int PastX ;
	int PastY ;
	int FlashFirst;
	int FlashTime;
};

class CBlock : public CBase{
public:
	int BlockType;
};

class CKamikaze : public CBall{
public:
	int KamikazeType;	
	int HP; 
	bool WindSwitch;
	int BaseX;//ソファランとファソラン用
	int BaseY;
	bool Lead;//誘導弾なら、
	void KamikazeMove(int SCROLL ,CCharacter &Chara);
	void KamikazeSet(CGraph,int,CWizard*);
};

class CWizard : public CBall{
public:
	int WizardType;	
	int HP; 
	int MaxBall;
	int PastX ;
	int PastY ;
	CKamikaze *PastKamikaze;
	CKamikaze *MyKamikaze;
	int NowMyMaxKamikaze ;
	void IncreaseBomb(CGraph Pic);
	void WizardMove(int SCROLL ,CCharacter &Chara);
};

class CBack {
public:
	int Graph;
	int Width;
	int Height;
	int BlockNum;
	CBlock *Obstacle;
	int KamikazeNum;
	CKamikaze *Kamikaze;
	int WizardNum;
	CWizard *Wizard;
	bool LoadBlock(CGraph);
};

char *MapName(int N);
bool CircleATARI(CBase ,CBase );
void SQRATARI(CCharacter &Chara, CBlock Base ,int &SCROLL  );
void SQRATARIW(CWizard &Chara, CBlock Base, int &SCROLL  );
void SQRGATUN(CCharacter &Chara, CBase Base, int &SCROLL  );
void BallANDBlock( CBall &Ball,CBlock &Block,CGraph,CMusic );
void BallANDWizard(CBall &Ball,CWizard &Wizard ,CGraph Pic);
void BallANDKamikaze(CBall &Ball,CKamikaze &Kamikaze ,CGraph);
bool InWindow(CBase,int);
bool InWindow2(CBase,int);
void FirstAwake();
void MenuAwake();
bool MenuLoop();
void BlockSet(int &n,CBlock*& Obstacle,CBlock*& Past ,CGraph Pic,bool &CV,int i ,int j);
void KamikazeSet(int &n,CKamikaze*& Kamikaze,CKamikaze*& PastK ,CGraph Pic,bool &CV,int i ,int j,int Number,int Attack ,int HP ,int Dimension, int Speed );
void WizardSet(int &n,CWizard*& Wizard,CWizard*& PastW ,CGraph Pic,bool &CV,int i ,int j,int Number);