#include "DxLib.h"
#include "Suken.h"
#include "JPB.h"
#include "math.h"
#pragma execution_character_set("utf-8")

double PI =3.1415926536;
double Scos(int Angle){
	return  cos( (double)Angle * PI / 180.0   ) ;
}
double Ssin(int Angle){
	return  sin( (double)Angle * PI / 180.0   ) ;
}
double Stan(int Angle){
	return  tan( (double)Angle * PI  / 180.0 ) ;
}
int AngleFromRad(double Angle){

	return (int)( Angle * 180 / PI) ;
}

void CBase::Draw(int SCROLL){
if(Invisible==0 && Left - SCROLL <  WINDOW_WIDTH  && Left - SCROLL + WINDOW_WIDTH >  0 && Top + Height > 0 && Top < WINDOW_HEIGHT    )
	DrawGraph( Left -SCROLL , Top + (WINDOW_REALHEIGHT - WINDOW_HEIGHT ), Graph  , TRUE );
}

void CBase::Draw(int Angle,int SCROLL){
if(Invisible==0 && Left - SCROLL <  WINDOW_WIDTH  && Left - SCROLL + WINDOW_WIDTH >  0 && Top + Height > 0 && Top < WINDOW_HEIGHT  )
	DrawRotaGraph( Left - SCROLL + Width / 2 , Top  + Height / 2  + (WINDOW_REALHEIGHT - WINDOW_HEIGHT ), 1.0f ,(double)(Angle * PI  / 180) , Graph , TRUE );
}

void CBase::Draw(int Angle,int SCROLL,bool B){
if(Invisible==0 && Left - SCROLL <  WINDOW_WIDTH  && Left - SCROLL + WINDOW_WIDTH >  0 ){
	if ( (Angle + 720) % 360 <=180) 
	DrawRotaGraph( Left - SCROLL + Width / 2 , Top  + Height / 2 , 1.0f ,(double)(Angle * PI  / 180) , Graph , TRUE );
	else
	DrawRotaGraph( Left - SCROLL + Width / 2 , Top  + Height / 2  + (WINDOW_REALHEIGHT - WINDOW_HEIGHT ), 1.0f ,(double)(Angle * PI  / 180) , Graph , TRUE,1);
}
}

void CCharacter::Move( int &SCROLL ){
	int Minus;
	Minus=CheckHitKey(KEY_INPUT_SPACE) + 1;

	if (CheckHitKey(KEY_INPUT_LEFT) == 1)
		Left -= SpeedX / Minus ;
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
		Left += SpeedX / Minus ;
	if (CheckHitKey(KEY_INPUT_UP) == 1)
		Top -= SpeedY / Minus ;
	if (CheckHitKey(KEY_INPUT_DOWN) == 1)
		Top += SpeedY / Minus ;
	if (Top<0)
		Top=0;
	if (Top>WINDOW_HEIGHT-Height)
		Top=WINDOW_HEIGHT-Height;
	if(ScrollSwitch && Left > SCROLL + WINDOW_WIDTH / 1.2 )	SCROLL = Left - WINDOW_WIDTH / 1.2 ;
	if(!ScrollSwitch && Left > SCROLL + WINDOW_WIDTH / 2 )	SCROLL = Left - WINDOW_WIDTH / 2 ;

	if(Left  < SCROLL){Left=SCROLL; }
	PastX = Left + Width / 2 ;
	PastY = Top + Height / 2 ;
}

void CCharacter::PushBomb( CGraph Pic){
if (MP>0 ){
	MP--;
	bool CV = 0;
	bool VB = 0;
	for(int j = 0 ; j< MaxBall ; j++ ){
		VB = 0;
		for(int jj = 0 ; jj < NowMyMaxBall ; jj++ ){
			if(MyBall[jj].Invisible == 1){
				MyBall[jj].BallSet( Pic , j , this); //前のが使えたら再利用。
				MyBall[jj].Trans=0;
				VB = 1 ;break ; 
			}
		}
		if( VB == 0 ){
			NowMyMaxBall ++ ;
			MyBall = new CBall[NowMyMaxBall]; CV = 0; /////////////////新しく領域を確保
			for(int i = 0; i < NowMyMaxBall - 1; i++ ){ //以前のデータを全部引っ越し
				MyBall[i] = PastBall[i];
				CV = 1;
			}
			if (CV == 1){delete [] PastBall ;} //引っ越し完了したので消去
			PastBall = MyBall; //新しいアドレスを確保
			MyBall[NowMyMaxBall - 1].BallSet( Pic , j , this); //更に新しく増えた分の設定
			MyBall[NowMyMaxBall - 1].Trans=0;
		}
	}
}
}

void CCharacter::PushBomb2( CGraph Pic){
if (MP>0 ){
	MP--;
	bool CV = 0;
	bool VB = 0;
	for(int j = 0 ; j< MaxBall ; j++ ){
		VB = 0;
		for(int jj = 0 ; jj < NowMyMaxBall ; jj++ ){
			if(MyBall[jj].Invisible == 1){
				MyBall[jj].BallSet( Pic , j , this); //前のが使えたら再利用。
				MyBall[jj].Trans=1;
				VB = 1 ;break ; 
			}
		}
		if( VB == 0 ){
			NowMyMaxBall ++ ;
			MyBall = new CBall[NowMyMaxBall]; CV = 0; /////////////////新しく領域を確保
			for(int i = 0; i < NowMyMaxBall - 1; i++ ){ //以前のデータを全部引っ越し
				MyBall[i] = PastBall[i];
				CV = 1;
			}
			if (CV == 1){delete [] PastBall ;} //引っ越し完了したので消去
			PastBall = MyBall; //新しいアドレスを確保
			MyBall[NowMyMaxBall - 1].BallSet( Pic , j , this); //更に新しく増えた分の設定
			MyBall[NowMyMaxBall - 1].Trans=1;
		}
	}
}
}

void CWizard::IncreaseBomb(CGraph Pic){
bool CV = 0;bool VB = 0;
for(int j = 0 ; j< MaxBall  ; j++ ){
	VB = 0;
	for(int jj = 0 ; jj < NowMyMaxKamikaze  ; jj++ ){
		if(MyKamikaze[jj].Invisible == 1){
			MyKamikaze[jj].KamikazeSet (Pic,j,this); //前のが使えたら再利用。
			VB = 1 ;break ; 
		}
	}

	if( VB == 0 ){
		NowMyMaxKamikaze  ++ ;
		MyKamikaze  = new CKamikaze[NowMyMaxKamikaze]; CV = 0; /////////////////新しく領域を確保
		for(int i = 0; i < NowMyMaxKamikaze  - 1; i++ ){ //以前のデータを全部引っ越し
			MyKamikaze[i] = PastKamikaze[i];
			CV = 1;
		}
		if (CV == 1){delete []  PastKamikaze ;} //引っ越し完了したので消去
		PastKamikaze = MyKamikaze; //新しいアドレスを確保
		MyKamikaze[NowMyMaxKamikaze -1].KamikazeSet (Pic,j,this);//更に新しく増えた分の設定
		}
	}
}

void CKamikaze::KamikazeSet(CGraph Pic,int KamikazeNum, CWizard *WW){
	Invisible = 0;
	Left = WW->Left + WW->Width / 2 ; 
	Top = WW->Top + WW->Height / 2 ;
	Width = 20;
	Height = 20;
	Circle = 10;
	Graph = Pic.EneBomb[ WW->WizardType ] ;
	Attack = WW->Attack ;
	HP = 1 ; Lead = 0;Trans =0;
	switch(WW->WizardType){
	case 1://まほーどり
		Lead=1; Speed = WW->Speed * 1.5 ;break;
	case 2:case 3:case 4://仙人//Sealp//LasBos
		Speed = 6 ;break;
	case 5:case 7://固定砲台//火炎土管
		Speed = 9 ;break;
	case 6://律 	
		if (KamikazeNum % 20 == 0){Lead = 1 ; Speed  = 6 + GetRand(12); }//誘導弾
		else { Speed = 15; Graph = Pic.EneBomb[0]; }//直進弾
		break;
	}
	switch(WW->WizardType){
	case 1:case 3:case 4://まほーどり//Sealp//LasBos
		Dimension = KamikazeNum * 45 ; Left += 64* ( (int)(KamikazeNum / 3 ) -1);Top += 64 * ((KamikazeNum % 3)-1 );
		if(KamikazeNum == 4 ){  Left += 64;Top += 64; }
		break;
	case 7://火炎土管
		Dimension = WW->Dimension  ;break;
	case 2://仙人
		Dimension = 70 + 20 * KamikazeNum ;break;
	case 5://固定砲台
		Dimension = GetRand(360); break;
	case 6://律 	
		Dimension = 12 * KamikazeNum ; break;
	}
}

void CCharacter::CharaSet(int P,CGraph Pic){
	PlayerNumber = P ;
	Invisible=0;
	Left = 72;
	Top = WINDOW_HEIGHT / 2;
	Width=64;
	Height=64;
	Circle=24;
	PastBall = MyBall; //新しいアドレスを確保
	NowMyMaxBall = 0;
	GirlBoy == 0 ? Graph=Pic.Player[PlayerNumber -1] : Graph=Pic.Prayer[PlayerNumber -1] ;
	
	switch(PlayerNumber){
	case 1://Goast
		SpeedX=4;
		SpeedY=4;
		HP=360 + CheatHP;
		MP=40 + CheatMP;
		Attack=6;
		Diffence=8;
		MaxBall=13 + CheatBall;
		FlashTime=60;
		break;
	case 2://Tuinte
		SpeedX=6;
		SpeedY=9;
		HP=176 + CheatHP;
		MP=32 + CheatMP;
		Attack=10;
		Diffence=6;
		MaxBall=11 + CheatBall;
		FlashTime=50;
		break;
	case 3://Fairy
		SpeedX=9;
		SpeedY=9;
		HP=128 + CheatHP;
		MP=30 + CheatMP;
		Attack=15;
		Diffence=5;
		MaxBall=9 + CheatBall;
		FlashTime=30;
		break;
	case 4://Witch
		SpeedX=12;
		SpeedY=12;
		HP=64 + CheatHP;
		MP=48 + CheatMP;
		Attack=20;
		Diffence=2;
		MaxBall=11 + CheatBall;
		FlashTime=25;
		break;
	case 5://Rance
	default:
		SpeedX=18;
		SpeedY=20;
		HP=44 + CheatHP;
		MP=36 + CheatMP;
		Attack=30;
		Diffence=0;
		MaxBall=7 + CheatBall;
		FlashTime=20;
		break;
	}
	if(GirlBoy ){
		Diffence += 1;
		HP     = HP * 1.5;
		SpeedX = SpeedX * 0.8;
		SpeedY = SpeedY * 0.8;
		FlashTime+=5;
	}else{  
		Attack = Attack * 1.5;
		MP = MP * 1.5;
	}
	MaxHP = HP ; MaxMP = MP ;
	FlashFirst=-65536;
}

void SQRATARI(CCharacter &Chara, CBlock Base, int &SCROLL  ){//平方の考えを利用した、球同士の判定
if(CircleATARI(Chara ,Base )){
	if (Base.BlockType >=6 && Base.BlockType <=9  ){
		switch(Base.BlockType){
		case 6: Chara.Left += Chara.SpeedX ;break;// Base.Left + Base.Width + Chara.Circle  - Chara.Width / 2;  break;//Left
		case 7:	Chara.Left -= Chara.SpeedX ;break;//= Base.Left - Chara.Circle  - Chara.Width / 2;  break;//Right
		case 8: Chara.Top -= Chara.SpeedY ;break;//= Base.Top - Chara.Circle  - Chara.Height / 2; break;//Up
		case 9: Chara.Top += Chara.SpeedY ;break;//= Base.Top + Base.Height  + Chara.Circle  - Chara.Height / 2; break;//Down
		}
	}else{
		int Vx,Vy;
		Vx = Base.Left +  Base.Width / 2 - Chara.PastX  ;
		Vy = Base.Top +  Base.Height / 2 - Chara.PastY  ;
		if(Vx == 0 ){
			( Chara.PastY <= Base.Top +  Base.Height / 2) ? Chara.Top = Base.Top - 2 * Chara.Circle : Chara.Top = Base.Top + Base.Height  + Chara.Circle - Chara.Height / 2 ;
		}
		else {long double Angle;Angle = atan2((long double)Vy,(long double)Vx);
			if( Angle <= PI / 4 && Angle >= (-1) * PI * 1 / 4 ){
				Chara.Left = Base.Left - Chara.Circle  - Chara.Width / 2;
			}else if ( Angle >= (-1) *  PI * 3 / 4 && Angle < (-1) * PI / 4 ){
				Chara.Top = Base.Top + Base.Height  + Chara.Circle  - Chara.Height / 2;
			}else if ( Angle <= PI * 3 / 4 && Angle > PI * 1 / 4 ){
				Chara.Top = Base.Top - Chara.Circle  - Chara.Height / 2;
			}else {
				Chara.Left = Base.Left + Base.Width + Chara.Circle  - Chara.Width / 2;
			}
		}
	}
}
}

void SQRATARIW(CWizard &Chara, CBlock Base, int &SCROLL  ){//平方の考えを利用した、球同士の判定
if(CircleATARI(Chara ,Base )){
	if (Base.BlockType >=6 && Base.BlockType <=9  ){
		switch(Base.BlockType){
		case 6: Chara.Left += Chara.Speed ;break;//= Base.Left + Base.Width + Chara.Circle  - Chara.Width / 2;  break;//Left
		case 7:	Chara.Left -= Chara.Speed ;break;//= Base.Left - Chara.Circle  - Chara.Width / 2;  break;//Right
		case 8: Chara.Top -= Chara.Speed ;break;//= Base.Top - Chara.Circle  - Chara.Height / 2; break;//Up
		case 9: Chara.Top += Chara.Speed ;break;//= Base.Top + Base.Height  + Chara.Circle  - Chara.Height / 2; break;//Down
		}
	}else{
		int Vx,Vy;
		Vx = Base.Left +  Base.Width / 2 - Chara.PastX  ;
		Vy = Base.Top +  Base.Height / 2 - Chara.PastY  ;
		if(Vx == 0 ){
			( Chara.PastY <= Base.Top +  Base.Height / 2) ? Chara.Top = Base.Top - 2 * Chara.Circle : Chara.Top = Base.Top + Base.Height  + Chara.Circle - Chara.Height / 2 ;
		}
		else {long double Angle;Angle = atan2((long double)Vy,(long double)Vx);
			if( Angle <= PI / 4 && Angle >= (-1) * PI * 1 / 4 ){
				Chara.Left = Base.Left - Chara.Circle  - Chara.Width / 2;
			}else if ( Angle >= (-1) *  PI * 3 / 4 && Angle < (-1) * PI / 4 ){
				Chara.Top = Base.Top + Base.Height  + Chara.Circle  - Chara.Height / 2;
			}else if ( Angle <= PI * 3 / 4 && Angle > PI * 1 / 4 ){
				Chara.Top = Base.Top - Chara.Circle  - Chara.Height / 2;
			}else {
				Chara.Left = Base.Left + Base.Width + Chara.Circle  - Chara.Width / 2;
			}
		}
	}
}
}

void SQRGATUN(CCharacter &Chara, CBase Base, int &SCROLL  ){//平方の考えを利用した、球同士の判定
int Vx,Vy;
Vx = Base.Left +  Base.Width / 2 - Chara.PastX  ;
Vy = Base.Top +  Base.Height / 2 - Chara.PastY  ;
if(Vx == 0 ){
	( Chara.PastY <= Base.Top +  Base.Height / 2) ? Chara.Top = Base.Top - 2 * Chara.Circle : Chara.Top = Base.Top + Base.Height  + Chara.Circle - Chara.Height / 2 ;
}else {long double Angle;Angle = atan2((long double)Vy,(long double)Vx);
if( Angle <= PI / 4 && Angle >= (-1) * PI * 1 / 4 ){
	Chara.Left = Base.Left - Chara.Circle  - Chara.Width / 2;
}else if ( Angle >= (-1) *  PI * 3 / 4 && Angle < (-1) * PI / 4 ){
	Chara.Top = Base.Top + Base.Height  + Chara.Circle  - Chara.Height / 2;
}else if ( Angle <= PI * 3 / 4 && Angle > PI * 1 / 4 ){
	Chara.Top = Base.Top - Chara.Circle  - Chara.Height / 2;
}else {
	Chara.Left = Base.Left + Base.Width + Chara.Circle  - Chara.Width / 2;
}
}
}

bool CircleATARI(CBase A1,CBase A2){
	int X1 = A1.Left + A1.Width / 2 ;
	int X2 = A2.Left + A2.Width / 2 ;
	int Y1 = A1.Top + A1.Height / 2 ;
	int Y2 = A2.Top + A2.Height / 2 ;

	if( (X1-X2) * (X1-X2) + (Y1-Y2) * (Y1-Y2) < ( A1.Circle + A2.Circle ) * ( A1.Circle + A2.Circle ))
	return 1;
	else
	return 0;
}

bool InWindow(CBase Base,int SCROLL){
	if(Base.Top <= WINDOW_HEIGHT && Base.Top +Base.Height >=0
		&& Base.Left +Base.Width >=  SCROLL && Base.Left <= WINDOW_WIDTH + SCROLL) return 1;
	else return 0;
}

bool InWindow2(CBase Base,int SCROLL){
	if(Base.Top <= WINDOW_HEIGHT && Base.Top +Base.Height >=0
		&& Base.Left <= WINDOW_WIDTH + SCROLL) return 1;
	else return 0;
}

void CBall::Move(int SCROLL){
	if(Invisible==0){
		Left +=(int)( Speed * Scos(Dimension));
		Top += (int)(Speed * Ssin(Dimension));
		if (Left> WINDOW_WIDTH + SCROLL || Top > WINDOW_HEIGHT || Left + Width <  SCROLL || Top + Height < 0 ){
			Invisible = 1;
		}
	}
}

void CBall::Move(int SCROLL,int X,int Y){
	if(Invisible==0){
		int Vx,Vy ; Vx= X - Left  - Width / 2 ; Vy= Y - Top -  Height / 2;
		if(Vx==0){ Vy>=0 ? Top += Speed : Top -= Speed  ;
		}else{
			Dimension= AngleFromRad(atan2((long double)Vy,(long double)Vx));
			Left +=(int)(Speed * Scos(Dimension));
			Top += (int)(Speed * Ssin(Dimension));
		}
		if (Left> WINDOW_WIDTH + SCROLL || Top > WINDOW_HEIGHT || Left + Width <  SCROLL || Top + Height < 0 )Invisible = 1;
	}
}

void CKamikaze::KamikazeMove(int SCROLL ,CCharacter &Chara ){
	int Vx,Vy ; Vx= Chara.Left + Chara.Width / 2 - Left   ; Vy= Chara.Top + Chara.Height / 2 - Top   ;
	switch(KamikazeType){
	case 0: 
		if(Dimension == 0)Dimension= AngleFromRad(atan2((long double)Vy,(long double)Vx));
		break;
	case  6:
		if(Dimension ==180 && Left < BaseX - 128  ){Dimension =0;}
		else if(Dimension == 0 && Left > BaseX + 128  ){Dimension =180;}
		break;
	case  7:
		if(Dimension == 90 && Top > BaseY + 128  ){Dimension =270;}
		else if(Dimension == 270 && Top < BaseY - 128 ){Dimension =90;}
		break;
	}
	Move(SCROLL);
}

void CWizard::WizardMove(int SCROLL ,CCharacter &Chara){
	int Vx,Vy ; Vx= Chara.Left + Chara.Width / 2 - Left   ; Vy= Chara.Top + Chara.Height / 2 - Top  ;
	if ( Vx==0 ) Vx = 1;
	switch(WizardType){
	case 0: case 1: case 3:
		Dimension= AngleFromRad(atan2((long double)Vy,(long double)Vx));
		break;
	}
	Move(SCROLL);
	PastX = Left + Width/2;
	PastY =Top + Height / 2;
}

void CBall::BallSet( CGraph Pic ,int BallNum ,CCharacter *CC ){
	Invisible = 0;
	Left = CC->Left + CC->Width / 2 ; 
	Top = CC->Top + CC->Height / 2 ;
	Width = 32;
	Height = 32;
	Circle = 16;
	Graph = Pic.Bomb[ CC->PlayerNumber  -1] ;
	switch(BallNum){
	case 0:
		Dimension = 0 ; break;
	case 1:
		Dimension = 20 ; break;//15
	case 2:
		Dimension = -20 ; break;//-15
	case 3:
		Dimension = 40 ; break;//30
	case 4:
		Dimension = -40 ; break;//-30
	case 5:
		Dimension = 120 ; break;//150
	case 6:
		Dimension = -120 ; break;//-150
	case 7:
		Dimension = 60 ; break;//45
	case 8:
		Dimension = -60 ; break;//-45
	case 9:
		Dimension = 80 ; break;//60
	case 10:
		Dimension = -80 ; break;//-60
	case 11:
		Dimension = 100 ; break;//90
	case 12:
		Dimension = -100 ; break;//-90
	case 13:
		Dimension = 140 ; break;//120
	case 14:
		Dimension = -140 ; break;//-120
	case 15:
		Dimension = 160 ; break;//165
	case 16:
		Dimension = -160 ; break;//-165
	case 17:
		Dimension = 180 ; break;
	default:
		Dimension =-170+(BallNum-18)*20;break;
	}
	
	Speed=(CC->SpeedX+CC->SpeedY)/2;
	Attack=CC->Attack;
	//switch(CC->PlayerNumber ){
	//case 1://Goast
	//	Speed = 5 ; Attack = 6 ; break;
	//case 2://Tuinte
	//	Speed = 8 ; Attack = 10 ; break;
	//case 3://Fairy
	//	Speed = 11 ; Attack = 15 ; break;
	//case 4://Witch
	//	Speed = 14 ; Attack = 20 ;break;
	//case 5://Rance
	//default:
	//	Speed = 21 ; Attack = 30 ; break;
	//}

}

void CGraph::GraphLoad (int Map ){
	switch((int)((Map - 1) / 6)){
	case 0:
		Back=LoadGraph( "PICLIB/Map/Back1.jpg" ) ;
		if((Map-1) % 6 == 0) MapTip = LoadSoftImage( "PICLIB/Map/GrassMap1.png" );
		if((Map-1) % 6 == 1) MapTip = LoadSoftImage( "PICLIB/Map/GrassMap2.png" );
		if((Map-1) % 6 == 2) MapTip = LoadSoftImage( "PICLIB/Map/GrassMap3.png" );
		if((Map-1) % 6 == 3) MapTip = LoadSoftImage( "PICLIB/Map/GrassMap4.png" );
		if((Map-1) % 6 == 4) MapTip = LoadSoftImage( "PICLIB/Map/GrassMap5.png" );
		if((Map-1) % 6 == 5) MapTip = LoadSoftImage( "PICLIB/Map/GrassMap6.png" );
		break;
	case 1:
		Back=LoadGraph( "PICLIB/Map/Back2.jpg" ) ;
		if((Map-1) % 6 == 0) MapTip = LoadSoftImage( "PICLIB/Map/SkyMap1.png" );
		if((Map-1) % 6 == 1) MapTip = LoadSoftImage( "PICLIB/Map/SkyMap2.png" );
		if((Map-1) % 6 == 2) MapTip = LoadSoftImage( "PICLIB/Map/SkyMap3.png" );
		if((Map-1) % 6 == 3) MapTip = LoadSoftImage( "PICLIB/Map/SkyMap4.png" );
		if((Map-1) % 6 == 4) MapTip = LoadSoftImage( "PICLIB/Map/SkyMap5.png" );
		if((Map-1) % 6 == 5) MapTip = LoadSoftImage( "PICLIB/Map/SkyMap6.png" );
		break;
	case 2:
		Back=LoadGraph( "PICLIB/Map/Back3.jpg" ) ;
		if((Map-1) % 6 == 0) MapTip = LoadSoftImage( "PICLIB/Map/SeaMap1.png" );
		if((Map-1) % 6 == 1) MapTip = LoadSoftImage( "PICLIB/Map/SeaMap2.png" );
		if((Map-1) % 6 == 2) MapTip = LoadSoftImage( "PICLIB/Map/SeaMap3.png" );
		if((Map-1) % 6 == 3) MapTip = LoadSoftImage( "PICLIB/Map/SeaMap4.png" );
		if((Map-1) % 6 == 4) MapTip = LoadSoftImage( "PICLIB/Map/SeaMap5.png" );
		if((Map-1) % 6 == 5) MapTip = LoadSoftImage( "PICLIB/Map/SeaMap6.png" );
		break;
	case 3:
		Back=LoadGraph( "PICLIB/Map/Back4.jpg" ) ;
		if((Map-1) % 6 == 0) MapTip = LoadSoftImage( "PICLIB/Map/FuctoryMap1.png" );
		if((Map-1) % 6 == 1) MapTip = LoadSoftImage( "PICLIB/Map/FuctoryMap2.png" );
		if((Map-1) % 6 == 2) MapTip = LoadSoftImage( "PICLIB/Map/FuctoryMap3.png" );
		if((Map-1) % 6 == 3) MapTip = LoadSoftImage( "PICLIB/Map/FuctoryMap4.png" );
		if((Map-1) % 6 == 4) MapTip = LoadSoftImage( "PICLIB/Map/FuctoryMap5.png" );
		if((Map-1) % 6 == 5) MapTip = LoadSoftImage( "PICLIB/Map/FuctoryMap6.png" );		
		break;
	case 4:
		Back=LoadGraph( "PICLIB/Map/Back5.jpg" ) ;
		if((Map-1) % 6 == 0) MapTip = LoadSoftImage( "PICLIB/Map/CosmosMap1.png" );
		if((Map-1) % 6 == 1) MapTip = LoadSoftImage( "PICLIB/Map/CosmosMap2.png" );
		if((Map-1) % 6 == 2) MapTip = LoadSoftImage( "PICLIB/Map/CosmosMap3.png" );
		if((Map-1) % 6 == 3) MapTip = LoadSoftImage( "PICLIB/Map/CosmosMap4.png" );
		if((Map-1) % 6 == 4) MapTip = LoadSoftImage( "PICLIB/Map/CosmosMap5.png" );
		if((Map-1) % 6 == 5) MapTip = LoadSoftImage( "PICLIB/Map/CosmosMap6.png" );
		break;
	case 5: default:
		Back=LoadGraph( "PICLIB/Map/Back6.jpg" ) ;
		if((Map-1) % 6 == 0) MapTip = LoadSoftImage( "PICLIB/Map/LightningMap1.png" );
		if((Map-1) % 6 == 1) MapTip = LoadSoftImage( "PICLIB/Map/LightningMap2.png" );
		if((Map-1) % 6 == 2) MapTip = LoadSoftImage( "PICLIB/Map/LightningMap3.png" );
		if((Map-1) % 6 == 3) MapTip = LoadSoftImage( "PICLIB/Map/LightningMap4.png" );
		if((Map-1) % 6 == 4) MapTip = LoadSoftImage( "PICLIB/Map/LightningMap5.png" );
		if((Map-1) % 6 == 5) MapTip = LoadSoftImage( "PICLIB/Map/LightningMap6.png" );
		break;
	}

	Bomb[0]=LoadGraph( "PICLIB/Bomb/KanehoBomb.png" );
	Bomb[1]=LoadGraph( "PICLIB/Bomb/KaturaBomb.png" );
	Bomb[2]=LoadGraph( "PICLIB/Bomb/AyumiBomb.png" );
	Bomb[3]=LoadGraph( "PICLIB/Bomb/SilverBomb.png" );
	Bomb[4]=LoadGraph( "PICLIB/Bomb/KyoukoBomb.png" );
	Gage[0]=LoadGraph( "PICLIB/CHARA/HPGage.png" );
	Gage[1]=LoadGraph( "PICLIB/CHARA/MPGage.png" );
	Player[0]=LoadGraph( "PICLIB/CHARA/Kaneho.png" ) ;
	Player[1]=LoadGraph( "PICLIB/CHARA/Katura.png" ) ;
	Player[2]=LoadGraph( "PICLIB/CHARA/Ayumi.png" ) ;
	Player[3]=LoadGraph( "PICLIB/CHARA/Silver.png" ) ;
	Player[4]=LoadGraph( "PICLIB/CHARA/Kyouko.png" ) ;
	Prayer[0]=LoadGraph( "PICLIB/CHARA/Kaneho2.png" ) ;
	Prayer[1]=LoadGraph( "PICLIB/CHARA/Katura2.png" ) ;
	Prayer[2]=LoadGraph( "PICLIB/CHARA/Ayumi2.png" ) ;
	Prayer[3]=LoadGraph( "PICLIB/CHARA/Silver2.png" ) ;
	Prayer[4]=LoadGraph( "PICLIB/CHARA/Kyouko2.png" ) ;
	Block[0]=LoadGraph( "PICLIB/Block/Block1.png" ) ;
	Block[1]=LoadGraph( "PICLIB/Block/Block2.png" ) ;
	Block[2]=LoadGraph( "PICLIB/Block/ReflectBlock.png" ) ;
	Block[3]=LoadGraph( "PICLIB/Block/InvisibleBlock.png" ) ;
	Block[4]=LoadGraph( "PICLIB/Block/TwoBlock.png" ) ;
	Block[5]=LoadGraph( "PICLIB/Block/TwoBlock2.png" ) ;
	Block[6]=LoadGraph( "PICLIB/Block/LeftBlock.png" ) ;//Yellow
	Block[7]=LoadGraph( "PICLIB/Block/RightBlock.png" ) ;//Red
	Block[8]=LoadGraph( "PICLIB/Block/UpBlock.png" ) ;//Blue
	Block[9]=LoadGraph( "PICLIB/Block/DownBlock.png" ); // Green
	Enemy[0]=LoadGraph( "PICLIB/Enemy/StarPuyo.png" );
	Enemy[1]=LoadGraph( "PICLIB/Enemy/Missile.png" );
	Enemy[2]=LoadGraph( "PICLIB/Enemy/Meteo.png" );
	Enemy[3]=LoadGraph( "PICLIB/Enemy/Goast.png" );
	Enemy[4]=LoadGraph( "PICLIB/Enemy/UFO.png" );
	Enemy[5]=LoadGraph( "PICLIB/Enemy/Togesama.png" );
	Enemy[6]=LoadGraph( "PICLIB/Enemy/Fasoran.png" );
	Enemy[7]=LoadGraph( "PICLIB/Enemy/Sofaran.png" );
	Wizard[0]=LoadGraph( "PICLIB/Enemy/Killerbee.png" );
	Wizard[1]=LoadGraph( "PICLIB/Enemy/Mahoudori.png" );
	Wizard[2]=LoadGraph( "PICLIB/Enemy/Sennin.png" );
	Wizard[3]=LoadGraph( "PICLIB/Enemy/SEALP.png" );
	Wizard[4]=LoadGraph( "PICLIB/Enemy/Lasbos.png" );
	Wizard[5]=LoadGraph( "PICLIB/Enemy/Canon.png" );
	Wizard[6]=LoadGraph( "PICLIB/Enemy/Ritu.png" );
	Wizard[7]=LoadGraph( "PICLIB/Enemy/FireCaveRight.png" );
	Wizard[8]=LoadGraph( "PICLIB/Enemy/FireCaveLeft.png" );
	Wizard[9]=LoadGraph( "PICLIB/Enemy/FireCaveUp.png" );
	Wizard[10]=LoadGraph( "PICLIB/Enemy/FireCaveDown.png" );
	EneBomb[0]=LoadGraph( "PICLIB/Bomb/RituBombStraight.png" );/////////////律の直進弾
	EneBomb[1]=LoadGraph( "PICLIB/Bomb/MahoudoriBomb.png" );
	EneBomb[2]=LoadGraph( "PICLIB/Bomb/SenninBomb.png" );
	EneBomb[3]=LoadGraph( "PICLIB/Bomb/SEALPBomb.png" );
	EneBomb[4]=LoadGraph( "PICLIB/Bomb/LasbosBomb.png" );
	EneBomb[5]=LoadGraph( "PICLIB/Bomb/CanonBomb.png" );
	EneBomb[6]=LoadGraph( "PICLIB/Bomb/RituBomb.png" );
	EneBomb[7]=LoadGraph( "PICLIB/Bomb/FireBomb.png" );


}
void CStuff::Load (){
	Stuff[0]=LoadGraph( "PICLIB/CELESTIAL.png" );
	Stuff[1]=LoadGraph( "PICLIB/STAGE.png" );
	Stuff[2]=LoadGraph( "PICLIB/FAILED.png" );
	Stuff[3]=LoadGraph( "PICLIB/CLEAR.png" );
	Stuff[4]=LoadGraph( "PICLIB/TitleBack.jpg" );
	Stuff[5]=LoadGraph( "PICLIB/ChilnoB.jpg" );
	Chara[0]=LoadGraph( "PICLIB/CHARA/Kaneho.png" ) ;
	Chara[1]=LoadGraph( "PICLIB/CHARA/Katura.png" ) ;
	Chara[2]=LoadGraph( "PICLIB/CHARA/Ayumi.png" ) ;
	Chara[3]=LoadGraph( "PICLIB/CHARA/Silver.png" ) ;
	Chara[4]=LoadGraph( "PICLIB/CHARA/Kyouko.png" ) ;
	Chara[5]=LoadGraph( "PICLIB/CHARA/Kaneho2.png" ) ;
	Chara[6]=LoadGraph( "PICLIB/CHARA/Katura2.png" ) ;
	Chara[7]=LoadGraph( "PICLIB/CHARA/Ayumi2.png" ) ;
	Chara[8]=LoadGraph( "PICLIB/CHARA/Silver2.png" ) ;
	Chara[9]=LoadGraph( "PICLIB/CHARA/Kyouko2.png" ) ;
	Gage[0]=LoadGraph( "PICLIB/SANKAKU.png" );
	Gage[1]=LoadGraph( "PICLIB/bit.png" );
	SE[0] =LoadSoundMem( "MUSICLIB/Clear.mp3" ) ;
	SE[1] =LoadSoundMem( "MUSICLIB/Finish.mp3" ) ;
}

void CMusic::MusicLoad(){
	SetCreateSoundDataType(DX_SOUNDDATATYPE_MEMPRESS);
	BGM[0] = LoadSoundMem( "MUSICLIB/Calculate!.mp3" ) ;
	BGM[1] = LoadSoundMem( "MUSICLIB/GrassPrincess.mp3" ) ;
	BGM[2] = LoadSoundMem( "MUSICLIB/SkyConvinience.mp3" ) ;
	BGM[3] = LoadSoundMem( "MUSICLIB/SeaThemeOfKitora.mp3" ) ;
	BGM[4] = LoadSoundMem( "MUSICLIB/FuctoryRaceStorm.mp3" ) ;
	BGM[5] = LoadSoundMem( "MUSICLIB/CosmosClistal.mp3" ) ;
	BGM[6] = LoadSoundMem( "MUSICLIB/LightningRotus.mp3" ) ;
	SetCreateSoundDataType(DX_SOUNDDATATYPE_MEMNOPRESS);
	SE[0] = LoadSoundMem(  "MUSICLIB/SE/Decision.mp3" ) ;
	SE[1] = LoadSoundMem(  "MUSICLIB/SE/LeftMat.mp3" ) ;
	SE[2] = LoadSoundMem(  "MUSICLIB/SE/RightMat.mp3" ) ;
	SE[3] = LoadSoundMem(  "MUSICLIB/SE/UpMat.mp3" ) ;
	SE[4] = LoadSoundMem(  "MUSICLIB/SE/DownMat.mp3" ) ;
	SE[5] = LoadSoundMem(  "MUSICLIB/SE/MP1.mp3" ) ;
	SE[6] = LoadSoundMem(  "MUSICLIB/SE/MP2.mp3" ) ;//////////////////////////////////
	SE[7] = LoadSoundMem(  "MUSICLIB/SE/Cure.mp3" ) ;///////////////////////////////
	SE[8] = LoadSoundMem(  "MUSICLIB/SE/Reflection.mp3" ) ;////////////////////////
	SE[9] = LoadSoundMem(  "MUSICLIB/SE/Attack.mp3" ) ;///////////////////////////////
	SE[10] = LoadSoundMem( "MUSICLIB/SE/Warp.mp3" ) ;////////////////////////////
	SE[11] = LoadSoundMem( "MUSICLIB/SE/Noise.mp3" ) ;//////////////////////////
	SE[12] = LoadSoundMem( "MUSICLIB/SE/MagicEne.mp3" ) ;/////////////////////////
	SE[13] = LoadSoundMem( "MUSICLIB/SE/Canon.mp3" ) ;///////////////////////////
	SE[14] = LoadSoundMem( "MUSICLIB/SE/Block1.mp3" ) ;
	SE[15] = LoadSoundMem( "MUSICLIB/SE/Puyo.mp3" ) ;///////////////////////
	SE[16] = LoadSoundMem( "MUSICLIB/SE/UFO.mp3" ) ;/////////////////////
	SE[17] = LoadSoundMem( "MUSICLIB/SE/Ritu.mp3" ) ;/////////////////////////
	SE[18] = LoadSoundMem( "MUSICLIB/SE/KnockOut.mp3" ) ;/////////////////////
	SE[19] = LoadSoundMem( "MUSICLIB/SE/Wind.mp3" ) ;/////////////////////////
}

void BlockSet(int &n,CBlock*& Obstacle,CBlock*& Past ,CGraph Pic,bool &CV,int i ,int j,int Number){
	Obstacle = new CBlock[n + 1]; CV = 0; /////////////////新しく領域を確保
	for(int k = 0; k < n ; k++ ){ //以前のデータを全部引っ越し
		Obstacle[k] = Past[k];CV = 1;
	}
	if (CV == 1){delete [] Past ;} //引っ越し完了したので消去
	Past = Obstacle; //新しいアドレスを確保

	Obstacle[n].Left = 64 * j ;Obstacle[n].Top = 64 * i ;Obstacle[n].Invisible = 0 ;Obstacle[n].Height=64;Obstacle[n].Width =64;Obstacle[n].Circle =32;
	Obstacle[n].Graph =Pic.Block[ Number];
	Obstacle[n].BlockType =  Number ;
	n++;
}

void KamikazeSet(int &n,CKamikaze*& Kamikaze,CKamikaze*& PastK ,CGraph Pic,bool &CV,int i ,int j,int Number,int Attack ,int HP ,int Dimension, int Speed ){
	Kamikaze = new CKamikaze[n + 1]; CV = 0; /////////////////新しく領域を確保
	for(int k = 0; k < n ; k++ ){ //以前のデータを全部引っ越し
		Kamikaze[k] = PastK[k];CV = 1;
	}
	if (CV == 1){delete [] PastK ;} //引っ越し完了したので消去
	PastK = Kamikaze; //新しいアドレスを確保

	Kamikaze[n].Left = 64 * j ;Kamikaze[n].Top = 64 * i ;Kamikaze[n].Invisible = 0 ;Kamikaze[n].Height=64;Kamikaze[n].Width =64;
	Kamikaze[n].Circle =32;Kamikaze[n].BaseX = 64 * j ;Kamikaze[n].BaseY  = 64 * i ;
	Kamikaze[n].Graph =Pic.Enemy[Number];
	Kamikaze[n].KamikazeType  =  Number;Kamikaze[n].WindSwitch =0;
	Kamikaze[n].Attack =Attack ; Kamikaze[n].HP = HP ;Kamikaze[n].Dimension = Dimension ;Kamikaze[n].Speed = Speed;
	n++; 
}

void WizardSet(int &n,CWizard*& Wizard,CWizard*& PastW ,CGraph Pic,bool &CV,int i ,int j,int Number){
	Wizard = new CWizard[n + 1]; CV = 0; /////////////////新しく領域を確保
	for(int k = 0; k < n ; k++ ){ //以前のデータを全部引っ越し
		Wizard[k] = PastW[k];CV = 1;
	}
	if (CV == 1){delete [] PastW ;} //引っ越し完了したので消去
	PastW = Wizard; //新しいアドレスを確保
	Wizard[n].Left = 64 * j ;Wizard[n].Top = 64 * i ;Wizard[n].Invisible = 0 ;Wizard[n].Height=64;Wizard[n].Width =64;
	Wizard[n].Circle =32 ; Wizard[n].Graph =Pic.Wizard[Number];
	Wizard[n].NowMyMaxKamikaze = 0;
}

bool CBack::LoadBlock ( CGraph Pic){
	bool SCSW=0;
	int r,g,b,a;
	//////////////////////////////////////////////////////////////////////BlockSet
	int n = 0;
	bool CV = 0;
	CBlock BBB;
	CBlock *Past ;
	Obstacle = &BBB ; Past = Obstacle ;
	Graph = Pic.MapTip ;
	// 画像のサイズを取得
	GetSoftImageSize( Graph, &Width, &Height ) ;
	// 画像の色を１ドットづつ参照
	for(int i = 0; i < Height; i ++ ){
		for(int j = 0; j < Width; j ++ ){
			
			GetPixelSoftImage( Graph, j, i, &r, &g, &b, &a ) ;

			if(r==0 && g==0 && b==0 ){/////////////////////////////////星ブロック/////////////黒
				BlockSet(n,Obstacle,Past,Pic,CV,i,j,0);}
			else if(r == 255 && g==0 && b==0) {	////////////////////レンガブロック///////////////赤
				BlockSet(n,Obstacle,Past,Pic,CV,i,j,1);}
			else if(r == 0 && g==255 && b==0) {	////////////////////リフレクブロック//////////////緑
				BlockSet(n,Obstacle,Past,Pic,CV,i,j,2);}
			else if(r == 255 && g==0 && b==255) {	////////////////////不可視ブロック//////////////マゼンタ
				BlockSet(n,Obstacle,Past,Pic,CV,i,j,3);}
			else if(r == 0 && g==0 && b==255) {	////////////////////2回ブロック//////////////青///４，５どちらも
				BlockSet(n,Obstacle,Past,Pic,CV,i,j,4);}
			else if(r == 255 && g==255 && b==153) {	////////////////////移動マットLeft//////////////LightYellow////255と153の組み合わせ
				BlockSet(n,Obstacle,Past,Pic,CV,i,j,6);
			if(i==0 && j==0 ){SCSW=1;}}
			else if(r == 255 && g==153 && b==153) {	////////////////////移動マットRight//////////////LightRed
				BlockSet(n,Obstacle,Past,Pic,CV,i,j,7);
				
				}
			else if(r == 153 && g==255 && b==255) {	////////////////////移動マットUp//////////////LightBlue
				BlockSet(n,Obstacle,Past,Pic,CV,i,j,8);}
			else if(r == 153 && g==255 && b==153) {	////////////////////移動マットDown//////////////LightGreen
				BlockSet(n,Obstacle,Past,Pic,CV,i,j,9);}
		}
	}
	BlockNum = n ;

	//////////////////////////////////////////////////////////////////////KamikazeSet
	n = 0;
	CV = 0;
	CKamikaze KKK;
	CKamikaze *PastK ;
	Kamikaze = &KKK ; PastK = Kamikaze ;
	// 画像の色を１ドットづつ参照
	for(int i = 0; i < Height; i ++ ){
		for(int j = 0; j < Width; j ++ ){
			
			GetPixelSoftImage( Graph, j, i, &r, &g, &b, &a ) ;//255と102の組み合わせ
			if(r==255 && g==255 && b==0 ){/////////////////////////////////流星ぷよ/////////////黄
				KamikazeSet(n,Kamikaze,PastK,Pic,CV,i,j,0,10,6,0,8);}
			else if(r==102 && g==102 && b==102 ){/////////////////////////////////ミサイル/////////////濃灰
				KamikazeSet(n,Kamikaze,PastK,Pic,CV,i,j,1,150,150,180,10);}
			else if(r==255 && g==102 && b==255  ){/////////////////////////////////流星隕石/////////////紫
				KamikazeSet(n,Kamikaze,PastK,Pic,CV,i,j,2,100,100,135,10);}
			else if(r==255 && g==102 && b==102 ){/////////////////////////////////幽霊/////////////薄赤
				KamikazeSet(n,Kamikaze,PastK,Pic,CV,i,j,3,15,15,180,5);}
			else if(r==102 && g==255 && b==255 ){/////////////////////////////////UFO/////////////薄水色
				KamikazeSet(n,Kamikaze,PastK,Pic,CV,i,j,4,15,15,90,3);}
			else if(r==255 && g==0 && b==102 ){/////////////////////////////////トゲさま/////////////赤紫
				KamikazeSet(n,Kamikaze,PastK,Pic,CV,i,j,5,100,2000,0,0);}
			else if(r==102 && g==255 && b==102 ){/////////////////////////////////ファソラン(左右)/////////////薄緑
				KamikazeSet(n,Kamikaze,PastK,Pic,CV,i,j,6,15,15,180,5);}
			else if(r==102 && g==102 && b==255 ){/////////////////////////////////ソファラン(上下)/////////////薄青
				KamikazeSet(n,Kamikaze,PastK,Pic,CV,i,j,7,15,15,90,5);}
		}
	}
	KamikazeNum = n ;

	//////////////////////////////////////////////////////////////////////WizardSet
	n = 0;
	CV = 0;
	CWizard WWW;
	CWizard *PastW ;
	Wizard = &WWW ; PastW = Wizard ;
	// 画像の色を１ドットづつ参照
	for(int i = 0; i < Height; i ++ ){
		for(int j = 0; j < Width; j ++ ){
			
			GetPixelSoftImage( Graph, j, i, &r, &g, &b, &a ) ;//255と204と51の組み合わせ
			if(r==255 && g==204 && b==255 ){/////////////////////////////////蜂/////////////薄紫
				WizardSet(n,Wizard,PastW,Pic,CV,i,j,0);
				Wizard[n].MaxBall = 0 ; Wizard[n].Attack =15;Wizard[n].HP =15;Wizard[n].Speed = 3 ;Wizard[n].Dimension =180;
				Wizard[n].WizardType = 0; n++;}
			else if(r==51 && g==204 && b==51 ){/////////////////////////////////まほーどり/////////////緑
				WizardSet(n,Wizard,PastW,Pic,CV,i,j,1);
				Wizard[n].MaxBall = 8 ; Wizard[n].Attack =15;Wizard[n].HP =25;Wizard[n].Speed = 4 ;Wizard[n].Dimension =180;
				Wizard[n].WizardType = 1; n++;}
			else if(r==204 && g==204 && b==51 ){/////////////////////////////////仙人/////////////萌黄色
				WizardSet(n,Wizard,PastW,Pic,CV,i,j,2);
				Wizard[n].MaxBall = 3 ; Wizard[n].Attack =15;Wizard[n].HP =15;Wizard[n].Speed = 3 ;Wizard[n].Dimension =180;
				Wizard[n].WizardType = 2; n++;}
			else if(r==51 && g==204 && b==204 ){/////////////////////////////////SEALP/////////////水道色
				WizardSet(n,Wizard,PastW,Pic,CV,i,j,3);
				Wizard[n].MaxBall = 8 ; Wizard[n].Attack =15;Wizard[n].HP =40;Wizard[n].Speed = 5 ;Wizard[n].Dimension =180;
				Wizard[n].WizardType = 3; n++;}
			else if(r==204 && g==51 && b==51 ){/////////////////////////////////LASBOS/////////////ワインレッド
				WizardSet(n,Wizard,PastW,Pic,CV,i,j,4);
				Wizard[n].MaxBall = 8 ; Wizard[n].Attack =15;Wizard[n].HP =80;Wizard[n].Speed = 0 ;Wizard[n].Dimension =0;
				Wizard[n].WizardType = 4; n++;}
			else if(r==51 && g==51 && b==51 ){/////////////////////////////////固定砲台/////////////濃灰
				WizardSet(n,Wizard,PastW,Pic,CV,i,j,5);
				Wizard[n].MaxBall = 5 ; Wizard[n].Attack = 20;Wizard[n].HP =300;Wizard[n].Speed = 0 ;Wizard[n].Dimension =0;
				Wizard[n].WizardType = 5; n++;}
			else if(r==204 && g==204 && b==204 ){/////////////////////////////////律/////////////超濃灰
				WizardSet(n,Wizard,PastW,Pic,CV,i,j,6);
				Wizard[n].MaxBall = 30 ; Wizard[n].Attack = 20;Wizard[n].HP =300;Wizard[n].Speed = 0 ;Wizard[n].Dimension =0;
				Wizard[n].WizardType = 6; n++;}
			else if(r==204 && g==0 && b==204 ){/////////////////////////////////炎土管右////////////マゼ紫
				WizardSet(n,Wizard,PastW,Pic,CV,i,j,7);
				Wizard[n].MaxBall = 1 ; Wizard[n].Attack = 16;Wizard[n].HP =150;Wizard[n].Speed = 0 ;Wizard[n].Dimension =0;
				Wizard[n].WizardType = 7; n++;}
			else if(r==0 && g==204 && b==204 ){/////////////////////////////////炎土管左////////////シア青
				WizardSet(n,Wizard,PastW,Pic,CV,i,j,8);
				Wizard[n].MaxBall = 1 ; Wizard[n].Attack = 16;Wizard[n].HP =150;Wizard[n].Speed = 0 ;Wizard[n].Dimension =180;
				Wizard[n].WizardType = 7; n++;}
			else if(r==204 && g==204 && b==0 ){/////////////////////////////////炎土管上////////////イエ黄
				WizardSet(n,Wizard,PastW,Pic,CV,i,j,9);
				Wizard[n].MaxBall = 1 ; Wizard[n].Attack = 16;Wizard[n].HP =150;Wizard[n].Speed = 0 ;Wizard[n].Dimension =270;
				Wizard[n].WizardType = 7; n++;}
			else if(r==204 && g==255 && b==204 ){/////////////////////////////////炎土管下////////////超濃緑
				WizardSet(n,Wizard,PastW,Pic,CV,i,j,10);
				Wizard[n].MaxBall = 1 ; Wizard[n].Attack = 16;Wizard[n].HP =150;Wizard[n].Speed = 0 ;Wizard[n].Dimension =90;
				Wizard[n].WizardType = 7; n++;}
		}
	}
	WizardNum = n ;

	DeleteSoftImage( Graph ) ;
	return SCSW;
}

void BallANDBlock( CBall &Ball,CBlock &Block,CGraph Pic,CMusic Music){
if (CircleATARI(Ball,Block)) {
	switch(Block.BlockType){
		case 0:////////////////////////////////////星ブロック
			Block.Invisible = 1;if(!Ball.Trans )Ball.Invisible =1;PlaySoundMem( Music.SE[14] , DX_PLAYTYPE_BACK)  ;break;
		case 1:////////////////////////////////////レンガブロック
			if(!Ball.Trans )Ball.Invisible =1;break;
		case 2:////////////////////////////////////リフレクブロック
			Ball.Dimension += 180 +GetRand(30) -15 ;if(!CheckSoundMem(Music.SE[8]))PlaySoundMem( Music.SE[8] , DX_PLAYTYPE_BACK) ;break;
		case 3:////////////////////////////////////不可視ブロック
			if(!Ball.Trans )Ball.Invisible =1;break;
		case 4:////////////////////////////////////2回ブロック２
			if(!Ball.Trans )Ball.Invisible =1 ;Block.BlockType =5;PlaySoundMem( Music.SE[14] , DX_PLAYTYPE_BACK) ; Block.Graph =Pic.Block [5]; break;
		case 5:////////////////////////////////////2回ブロック１
			Block.Invisible = 1 ;if(!Ball.Trans ) Ball.Invisible =1;PlaySoundMem( Music.SE[14] , DX_PLAYTYPE_BACK) ;break;
		case 6:////////////////////////////////////移動マットLeft
			Ball.Dimension = 0  ; break;//if(!CheckSoundMem(Music.SE[1]))PlaySoundMem( Music.SE[1] , DX_PLAYTYPE_BACK) ; break;
		case 7:////////////////////////////////////移動マットRight
			Ball.Dimension = 180  ; break;//if(!CheckSoundMem(Music.SE[2]))PlaySoundMem( Music.SE[2] , DX_PLAYTYPE_BACK) ; break;
		case 8:////////////////////////////////////移動マットUp
			Ball.Dimension = 270  ; break;//if(!CheckSoundMem(Music.SE[3])) PlaySoundMem( Music.SE[3] , DX_PLAYTYPE_BACK) ;break;
		case 9:////////////////////////////////////移動マットDown
			Ball.Dimension = 90 ; break;//if(!CheckSoundMem(Music.SE[4]))PlaySoundMem( Music.SE[4] , DX_PLAYTYPE_BACK) ; break;
	}
}
}

void BallANDKamikaze(CBall &Ball,CKamikaze &Kamikaze ,CGraph Pic){
if (CircleATARI(Ball,Kamikaze)) {
	Kamikaze.HP -= Ball.Attack ;
	if(!Ball.Trans )Ball.Invisible = 1;else Ball.Attack *= 0.9;
	if (Kamikaze.HP <=0 )Kamikaze.Invisible = 1 ;
}
}

void BallANDWizard(CBall &Ball,CWizard &Wizard ,CGraph Pic){
if (CircleATARI(Ball,Wizard)) {
	Wizard.HP -= Ball.Attack ;
	if(!Ball.Trans )Ball.Invisible = 1;else Ball.Attack *= 0.9;
	if (Wizard.HP <=0 )Wizard.Invisible = 1 ;
}
}

char *MapName(int N){
	switch (N){
	case 1:return "WORLD_1-1_始まりのそうげん";
	case 2:return "WORLD_1-2_まあまあそうげん";
	case 3:return "WORLD_1-3_ふつうのそうげん";
	case 4:return "WORLD_1-4_こいしいそうげん";
	case 5:return "WORLD_1-5_おいしいそうめん";
	case 6:return "WORLD_1-6_最後の草原";
	case 7:return "WORLD_2-1_空中";
	case 8:return "WORLD_2-2_青い空";
	case 9:return "WORLD_2-3_日和";
	case 10:return "WORLD_2-4_晴天";
	case 11:return "WORLD_2-5_快晴";
	case 12:return "WORLD_2-6_浮遊";
	case 13:return "WORLD_3-1_すいちゅう";
	case 14:return "WORLD_3-2_水深1000m";
	case 15:return "WORLD_3-3_太平洋";
	case 16:return "WORLD_3-4_しんかい";
	case 17:return "WORLD_3-5_竜宮城";
	case 18:return "WORLD_3-6_海底都市";
	case 19:return "WORLD_4-1_E缶工場";
	case 20:return "WORLD_4-2_工場探検";
	case 21:return "WORLD_4-3_はちのすくつ";
	case 22:return "WORLD_4-4_工場見学";
	case 23:return "WORLD_4-5_数学研究所";
	case 24:return "WORLD_4-6_パーフェクト数学教室";
	case 25:return "WORLD_5-1_星空の下";
	case 26:return "WORLD_5-2_スターライン";
	case 27:return "WORLD_5-3_黒";
	case 28:return "WORLD_5-4_ペデルギウス";
	case 29:return "WORLD_5-5_流星群";
	case 30:return "WORLD_5-6_宇宙空間";
	case 31:return "WORLD_6-1_異空間";
	case 32:return "WORLD_6-2_四次元空間";
	case 33:return "WORLD_6-3_10次元空間";
	case 34:return "WORLD_6-4_26次元空間";
	case 35:return "WORLD_6-5_ぬるぽっ！";
	case 36:
	default:return "WORLD_6-6_終点";
	}
}