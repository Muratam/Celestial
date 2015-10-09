//ここにメインのプログラムを書く
#include "DxLib.h"
#include "Suken.h"
#include "JPB.h"
#include <cstring>
#pragma execution_character_set("utf-8")
//cIntDataは(LeftData)
// 0 クリアステージ数(値は0~35 +36は全クリ)
// 1~36 クリア時間


int PlayType = 3;//ステージ::平原→空→海→工場→夜→亜空間　計８種類 icon
int MapType = 1 ;///1~6平原 7^12空 13^18海 19^24工場 25^30夜  31^36亜空間
int i ;
int Scroll = 0 ;
int BESTTIME = 256;
int Distance =100;//発射間隔
int T;
int Now;
CCharacter Me;
CStuff Stuff;
CGraph Pic;
CKeyPush KeyOne;
CBack cBack;
CMusic Music;
int STARTTIME ;
int Menu = 0;
int HomHom =0;int HomTime=0;
int Tihaya =0;int Kyouko=0;int Madoka =0;int Homura =0;int Sayaka =0;
int TiTime =0;int KyTime=0;int MaTime =0;int HoTime =0;int SaTime =0;
bool TihayaSw=0;
CIntData cIntData("MEUMEU.hb");
int ClearTime = 0;
bool DXCLEAR = false;
bool Cleared = false;
void FirstAwake(){
	unsigned int br = GetColor(0, 0, 0);
	unsigned int r = GetColor(255, 0, 0);
	unsigned int g = GetColor(0, 255, 0);
	unsigned int b = GetColor(0, 0, 255);
	unsigned int w = GetColor(255, 255, 255);
	SetFontSize(60);
	DrawFormatString(360, 290, sukenWHITE, "ロード中…");
	Music.MusicLoad ();
	cIntData.ReadData ();
	Me.GirlBoy =1;
}

void MenuAwake(){
	Scroll = 0 ;T = 1 ;
	Me.CharaSet(PlayType,Pic);Stuff.Load ();
	PlaySoundMem( Music.BGM[0] , DX_PLAYTYPE_LOOP ) ;
}
bool ClearLoop();

bool MenuLoop(){
	if (DXCLEAR){
		if (ClearLoop()){
			DXCLEAR = false;
		}
		return 0;
	}
	else{
		if (cIntData.LeftData[0] != 36)DrawGraph(0, 0, Stuff.Stuff[4], false);
		else DrawGraph(0, 0, Stuff.Stuff[5], false);
		SetFontSize(16);
		KeyOne.ALLKEYCHECK();
		if (CheckHitKeyAll()){
			switch (HomHom){
			case 0:case 3:if (KeyOne.H == 1){ HomHom++; HomTime = 0; }break; case 1:case 4:if (KeyOne.O == 1){ HomHom++; HomTime = 0; }break; case 2:case 5:if (KeyOne.M == 1){ HomHom++; HomTime = 0; }break;
			}
		}HomTime++; if (HomHom && HomTime >= 30)HomHom = 0;
		if (HomHom == 6){ HomHom = 0; cIntData.LeftData[0] ++; PlaySoundMem(Music.SE[0], DX_PLAYTYPE_BACK); if (cIntData.LeftData[0] >= 35)cIntData.LeftData[0]--; cIntData.WriteData(); }

		int ColorType = 0;	switch (PlayType){ case 1:ColorType = GetColor(255, 102, 102); break; case 2:ColorType = GetColor(255, 255, 102); break; case 3:ColorType = GetColor(102, 255, 102); break; case 4:ColorType = GetColor(102, 255, 255); break; case 5:ColorType = GetColor(255, 102, 255); break; }

		Me.CharaSet(PlayType, Pic);
		DrawFormatString(90, 100, 0, "遂に開催飛行グランプリ「CELESTIAL」！それぞれ特徴ある５人の主人公から一人選んで");
		DrawFormatString(90, 130, 0, "いかに速くクリア出来るかを競います！目指せネットランキング最速クリア！");
		DrawFormatString(90, 160, sukenBLUE, "メニュー操作方法　");
		DrawFormatString(90, 190, 0, "→←キー::キャラクター変更　↑↓キー::ステージ変更  スペースキー::性別変更  エンターキー::グランプリ参加");
		DrawFormatString(90, 220, sukenBLUE, "ゲーム操作方法　　右端のゴールを目指せ！ ");
		DrawFormatString(90, 250, 0, "↑↓→←キー::移動　 Zキー::弾発射   Xキー::必殺技発動  スペースキー::遅移動  Backキー::リタイア");

		/*
		DrawFormatString( 0, 120, ColorType , "CHARACTER TYPE = %d  GIRLBOY = %d  MAPTYPE = %d",PlayType , (int)Me.GirlBoy,MapType   ) ;
		DrawFormatString( 0, 540, ColorType , "LAST YOUR BESTTIME = %d ", BESTTIME   ) ;
		*/
		DrawGraph(300, 20, Stuff.Stuff[0], true);

		DrawGraph(160, 280, Stuff.Chara[PlayType + Me.GirlBoy * 5 - 1], true);
		DrawTurnGraph(120, 280, Stuff.Gage[0], true);
		DrawGraph(230, 280, Stuff.Gage[0], true);
		DrawFormatString(300, 280, 0, "ＨＰ:%d ", Me.HP); for (int i = 0; i < Me.HP / 40; i++){ DrawGraph(400 + 20 * i, 280, Stuff.Gage[1], 0); }
		DrawFormatString(300, 310, 0, "防御:%d ", Me.Diffence); for (int i = 0; i < Me.Diffence / 1; i++){ DrawGraph(400 + 20 * i, 310, Stuff.Gage[1], 0); }
		DrawFormatString(300, 340, 0, "弾数:%d ", Me.MaxBall); for (int i = 0; i < Me.MaxBall / 1 - 3; i++){ DrawGraph(400 + 20 * i, 340, Stuff.Gage[1], 0); }
		DrawFormatString(300, 370, 0, "ＭＰ:%d ", Me.MP); for (int i = 0; i < Me.MP / 8; i++){ DrawGraph(400 + 20 * i, 370, Stuff.Gage[1], 0); }
		DrawFormatString(300, 400, 0, "攻撃:%d ", Me.Attack); for (int i = 0; i < Me.Attack / 3; i++){ DrawGraph(400 + 20 * i, 400, Stuff.Gage[1], 0); }
		DrawFormatString(300, 430, 0, "速さ:%d ", Me.SpeedX + Me.SpeedY); for (int i = 0; i < (Me.SpeedX + Me.SpeedY) / 3; i++){ DrawGraph(400 + 20 * i, 430, Stuff.Gage[1], 0); }
		switch (PlayType){
		case 1:DrawFormatString(300, 460, 0, "必殺技::  Phantom Flame 　　　　　　　　自分のＨＰを回復する"); break;
		case 2:DrawFormatString(300, 460, 0, "必殺技::  瞬間移動589nm 　　　　　　　　障害物をとび超える"); break;
		case 3:DrawFormatString(300, 460, 0, "必殺技::  アルテマグリーン　　　　　　　皆の技をよりどり緑"); break;
		case 4:DrawFormatString(300, 460, 0, "必殺技::  滅びのシルバースター  　　　　一度に大量に貫通弾を放つ"); break;
		case 5:DrawFormatString(300, 460, 0, "必殺技::  虚空と光明の精神統一　　　　　自分の能力を格段に上げる"); break;
		}
		if (MapType != 1)DrawRotaGraph(400, 530, 1.0, -1.57, Stuff.Gage[0], true);
		DrawGraph(150, 560, Stuff.Stuff[1], true);
		if (MapType != 36)DrawRotaGraph(400, 640, 1.0, 1.57, Stuff.Gage[0], true);
		DrawFormatString(160, 580, 0, MapName(MapType));
		if (cIntData.LeftData[0] >= MapType){
			DrawFormatString(460, 580, 0, "クリアタイム %d秒", cIntData.LeftData[MapType]);
		}
		if (KeyOne.SPACE == 1) { Me.GirlBoy == 0 ? Me.GirlBoy = 1 : Me.GirlBoy = 0; }
		if (KeyOne.RIGHT == 1) { PlayType == 5 ? PlayType = 5 : PlayType++; }
		if (KeyOne.LEFT == 1) { PlayType == 1 ? PlayType = 1 : PlayType--; }
		if (KeyOne.DOWN == 1) { MapType == 36 ? MapType = 36 : MapType++; if (cIntData.LeftData[0] < MapType - 1)MapType--; }
		if (KeyOne.UP == 1) { MapType == 1 ? MapType = 1 : MapType--; }
		if (KeyOne.UP == 1 || KeyOne.DOWN == 1 || KeyOne.LEFT == 1 || KeyOne.RIGHT == 1 || KeyOne.SPACE == 1) PlaySoundMem(Music.SE[0], DX_PLAYTYPE_BACK);
		if (KeyOne.X == 1) return 1;

		if (KeyOne.ESCAPE == 1)DxLib_End();
		return 0;
	}
}

void Awake(){
	Scroll = 0 ;
	Pic.GraphLoad ( MapType);
	Me.CharaSet(PlayType,Pic);
	Me.ScrollSwitch =cBack.LoadBlock ( Pic);
	StopSoundMem (Music.BGM[0]);
	PlaySoundMem( Music.BGM[(int)((MapType - 1) / 6) + 1] , DX_PLAYTYPE_LOOP ) ;
	STARTTIME =GetNowCount();  
}

bool GameLoop(){
	T++;
	KeyOne.ALLKEYCHECK();
	if(Me.ScrollSwitch )Scroll +=Me.SpeedX /3.5;
	Me.Move(Scroll);
	DrawGraph(0 , 0, Pic.Back , FALSE );
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	
	if(CheckHitKeyAll()){switch(Tihaya){
	case 0:if(KeyOne.T==1){Tihaya++;TiTime=0;}break;case 3:if(KeyOne.A==1){Tihaya++;TiTime=0;}break;
	case 1:if(KeyOne.I==1){Tihaya++;TiTime=0;}break;case 4:if(KeyOne.Y==1){Tihaya++;TiTime=0;}break;
	case 2:if(KeyOne.H==1){Tihaya++;TiTime=0;}break;case 5:if(KeyOne.A==1){Tihaya++;TiTime=0;}break;
	}switch(Homura){
	case 0:if(KeyOne.H==1){Homura++;HoTime=0;}break;case 3:if(KeyOne.U==1){Homura++;HoTime=0;}break;
	case 1:if(KeyOne.O==1){Homura++;HoTime=0;}break;case 4:if(KeyOne.R==1){Homura++;HoTime=0;}break;
	case 2:if(KeyOne.M==1){Homura++;HoTime=0;}break;case 5:if(KeyOne.A==1){Homura++;HoTime=0;}break;
	}switch(Sayaka){
	case 0:if(KeyOne.S==1){Sayaka++;SaTime=0;}break;case 3:if(KeyOne.A==1){Sayaka++;SaTime=0;}break;
	case 1:if(KeyOne.A==1){Sayaka++;SaTime=0;}break;case 4:if(KeyOne.K==1){Sayaka++;SaTime=0;}break;
	case 2:if(KeyOne.Y==1){Sayaka++;SaTime=0;}break;case 5:if(KeyOne.A==1){Sayaka++;SaTime=0;}break;
	}switch(Madoka){
	case 0:if(KeyOne.M==1){Madoka++;MaTime=0;}break;case 3:if(KeyOne.O==1){Madoka++;MaTime=0;}break;
	case 1:if(KeyOne.A==1){Madoka++;MaTime=0;}break;case 4:if(KeyOne.K==1){Madoka++;MaTime=0;}break;
	case 2:if(KeyOne.D==1){Madoka++;MaTime=0;}break;case 5:if(KeyOne.A==1){Madoka++;MaTime=0;}break;
	}switch(Kyouko){
	case 0:if(KeyOne.K==1){Kyouko++;KyTime=0;}break;case 3:if(KeyOne.U==1){Kyouko++;KyTime=0;}break;
	case 1:if(KeyOne.Y==1){Kyouko++;KyTime=0;}break;case 4:if(KeyOne.K==1){Kyouko++;KyTime=0;}break;
	case 2:if(KeyOne.O==1){Kyouko++;KyTime=0;}break;case 5:if(KeyOne.O==1){Kyouko++;KyTime=0;}break;
	}}HoTime++;MaTime++;KyTime++;SaTime++;TiTime++;
	if(Homura && HoTime>=30)Homura=0;if(Sayaka && SaTime>=30)Sayaka=0;if(Madoka && MaTime>=30)Madoka=0;
	if(Kyouko && KyTime>=30)Kyouko=0;if(Tihaya && TiTime>=30)Tihaya=0;
	if(Homura==6){Homura=0;Me.Attack  =999 ;Me.MaxBall=17 ;Me.MaxMP =999 ;PlaySoundMem( Music.SE[0] , DX_PLAYTYPE_BACK) ;}
	if(Madoka==6){Madoka=0;Me.SpeedX  *=2 ;Me.SpeedY  *=2 ;PlaySoundMem( Music.SE[0] , DX_PLAYTYPE_BACK) ;}
	if(Sayaka==6){Sayaka=0;Me.MP =Me.MaxMP ;Me.HP =Me.MaxHP ;PlaySoundMem( Music.SE[0] , DX_PLAYTYPE_BACK) ;}
	if(Kyouko==6){Kyouko=0;Me.Diffence  =999 ;PlaySoundMem( Music.SE[0] , DX_PLAYTYPE_BACK) ;}
	if(Tihaya==6){Tihaya=0;TihayaSw==0? TihayaSw=1:TihayaSw=0 ;PlaySoundMem( Music.SE[0] , DX_PLAYTYPE_BACK) ;}
	
	//////////////↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓ブロックについて↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
	for( i = 0; i < cBack.BlockNum ; i++ ){/////////////////////////////////////////////////////////////////////////
	if ( cBack.Obstacle[i].Invisible == 0 && InWindow(cBack.Obstacle[i],Scroll)  ){
		/////////////////////////////////////////////////////弾との関係
		for (int z = 0; z < Me.NowMyMaxBall ; z++ ){
			if(!Me.MyBall[z].Invisible  ) BallANDBlock(Me.MyBall[z],cBack.Obstacle[i],Pic,Music);
		}
		/////////////////////////////////////////////////////神風との関係
		for (int z = 0; z < cBack.KamikazeNum ; z++ ){
			if(!cBack.Kamikaze[z].Invisible) {
				if(cBack.Kamikaze[z].KamikazeType == 0) BallANDBlock(cBack.Kamikaze[z],cBack.Obstacle[i],Pic,Music);
				if((cBack.Kamikaze[z].KamikazeType == 1 || cBack.Kamikaze[z].KamikazeType == 2) && CircleATARI(cBack.Kamikaze[z],cBack.Obstacle[i])) {
					cBack.Obstacle[i].Invisible = 1;
				}
			}
		}
		/////////////////////////////////////////////////////Wizardとの関係
		for (int z = 0; z < cBack.WizardNum  ; z++ ){
			if(!cBack.Wizard[z].Invisible  && !( cBack.Wizard[z].WizardType ==4 || cBack.Wizard[z].WizardType ==3 ) ) SQRATARIW(cBack.Wizard[z],cBack.Obstacle[i],Scroll );
			for(int f = 0 ; f < cBack.Wizard[z].NowMyMaxKamikaze ; f++ ){/////////WizardBomb
				if(!cBack.Wizard[z].MyKamikaze[f].Invisible ){ BallANDBlock(cBack.Wizard[z].MyKamikaze[f],cBack.Obstacle[i],Pic,Music);	}
			}
		}

		//////////////////////////////////////////////////////主人公との関係
		if(!TihayaSw){SQRATARI(Me,cBack.Obstacle[i],Scroll );}
		cBack.Obstacle[i].Draw (Scroll);
	}
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑ブロックについて↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑



	/////////////////////////↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓神風たちについて↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
	for( i = 0; i < cBack.KamikazeNum  ; i++ ){//////////////////////////////////////////////////////////////
	if ( cBack.Kamikaze[i].Invisible == 0 && InWindow(cBack.Kamikaze[i],Scroll)  ){
		//////////////////////////////////////////////////////移動
		cBack.Kamikaze[i].KamikazeMove (Scroll,Me);
		if(!cBack.Kamikaze[i].WindSwitch &&( cBack.Kamikaze[i].KamikazeType==1 || cBack.Kamikaze[i].KamikazeType==2))
			{cBack.Kamikaze[i].WindSwitch=1;if(!CheckSoundMem(Music.SE[19]))PlaySoundMem( Music.SE[19] , DX_PLAYTYPE_BACK) ;}
		/////////////////////////////////////////////////////弾との関係
		for (int z = 0; z < Me.NowMyMaxBall ; z++ ){
			if(!Me.MyBall[z].Invisible) BallANDKamikaze(Me.MyBall[z],cBack.Kamikaze[i],Pic);
		}
		/////////////////////////////////////////////////////主人公との関係

		if (CircleATARI(Me,cBack.Kamikaze[i])  && Me.FlashFirst +Me.FlashTime < T && !TihayaSw ){
			Me.HP -= cBack.Kamikaze[i].Attack -Me.Diffence ;
			cBack.Kamikaze[i].Invisible = 1;cBack.Kamikaze[i].HP =0; 
			Me.FlashFirst = T;PlaySoundMem( Music.SE[9] , DX_PLAYTYPE_BACK) ;
		}
		cBack.Kamikaze[i].Draw (cBack.Kamikaze[i].Dimension ,Scroll);
	}
	}///////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑神風たちについて↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑


	/////////////////////////↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓Wizard&Bombについて↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
	for( i = 0; i < cBack.WizardNum   ; i++ ){//////////////////////////////////////////////////////////////
	if ( InWindow(cBack.Wizard[i],Scroll)  ){
		//////////////////////////////////////////////////////移動
		if (cBack.Wizard[i].Invisible == 0 ){
			cBack.Wizard[i].WizardMove (Scroll,Me);
			if( cBack.Wizard[i].WizardType == 4 &&  T % (int)(Distance/ 6) == 0 ){
				cBack.Wizard[i].Left += 64 *(GetRand(2) -1 ) ;
				cBack.Wizard[i].Top += 64 *(GetRand(2) -1 );
			}
			//////////////////////////////////////////////////////弾を増やす
			if(T % Distance == 0 ){	cBack.Wizard[i].IncreaseBomb (Pic);}
			else if(T  % (int)(Distance/ 9) == 0 && cBack.Wizard[i].WizardType == 7 ){
				cBack.Wizard[i].IncreaseBomb (Pic);}//炎土管
			else if(T  % (int)(Distance/ 3) == 0 && cBack.Wizard[i].WizardType == 5 ){
				cBack.Wizard[i].IncreaseBomb (Pic);}//固定砲台

			for (int z = 0; z < Me.NowMyMaxBall ; z++ ){////////////////弾との関係
			if(!Me.MyBall[z].Invisible) BallANDWizard(Me.MyBall[z],cBack.Wizard[i],Pic);}

			if (CircleATARI(Me,cBack.Wizard[i]) && Me.FlashFirst +Me.FlashTime < T && !TihayaSw ){
				if (cBack.Wizard[i].WizardType < 4) {////////主人公との関係
					Me.HP -= cBack.Wizard[i].Attack - Me.Diffence ;
					cBack.Wizard[i].HP = 0 ; cBack.Wizard[i].Invisible =1 ;
					Me.FlashFirst = T;PlaySoundMem( Music.SE[9] , DX_PLAYTYPE_BACK) ;
				}
				else SQRGATUN( Me , cBack.Wizard[i], Scroll );
			}
		}
	}
	if  ( InWindow2(cBack.Wizard[i],Scroll)  ){
		/////////////////////////////////////////////////////弾とKamikazeの関係
		
		for(int f = 0 ; f<cBack.Wizard[i].NowMyMaxKamikaze ; f++ ){
		if(!cBack.Wizard[i].MyKamikaze[f].Invisible ){
			for (int z = 0; z < Me.NowMyMaxBall ; z++ ){
				if(!Me.MyBall[z].Invisible) BallANDKamikaze(Me.MyBall[z],cBack.Wizard[i].MyKamikaze[f],Pic);
			}
			/////////////////////////////////////////////////////主人公とKamikazeの関係
			if (CircleATARI(Me,cBack.Wizard[i].MyKamikaze[f]) && Me.FlashFirst +Me.FlashTime < T  && !TihayaSw ){
				Me.HP -= cBack.Wizard[i].MyKamikaze[f].Attack -Me.Diffence ;
				cBack.Wizard[i].MyKamikaze[f].Invisible = 1;
				cBack.Wizard[i].MyKamikaze[f].HP =0;
				Me.FlashFirst = T;PlaySoundMem( Music.SE[9] , DX_PLAYTYPE_BACK) ;
			}
			//////////////////////////////////////////Kamikazeの移動
			cBack.Wizard[i].MyKamikaze[f].Lead ==0 ? cBack.Wizard[i].MyKamikaze[f].Move (Scroll) : cBack.Wizard[i].MyKamikaze[f].Move (Scroll,Me.Left +Me.Width /2 , Me.Top +Me.Height /2  );
			//////////////////////////////////////////Kamikazeの描画
			//////////////////////////////////////////増えた弾は、画面外で消えるように！
			if (!InWindow(cBack.Wizard[i].MyKamikaze[f],Scroll)) {cBack.Wizard[i].MyKamikaze[f].Invisible = 1 ; cBack.Wizard[i].MyKamikaze[f].HP =0;}
			cBack.Wizard[i].MyKamikaze[f].Draw (cBack.Wizard[i].MyKamikaze[f].Dimension ,Scroll);
		}
		}
	}
	////////////////////////////////////////////////////////////////////////Wizardの描画
	if (cBack.Wizard[i].Invisible == 0  && InWindow(cBack.Wizard[i],Scroll) ) cBack.Wizard[i].Draw (cBack.Wizard[i].Dimension ,Scroll);
	
	}///////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑Wizardについて↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑
	

	/////////////////////////↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓弾&Meについて↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
	if(KeyOne.Z ==1 && Me.Invisible == 0 && Me.MP >= 1 )////////////////////////////////////////////////////////////////
	{if(Me.PlayerNumber ==5)Me.PushBomb2 (Pic);else Me.PushBomb (Pic);PlaySoundMem( Music.SE[5] , DX_PLAYTYPE_BACK) ;}///////////////////////////////弾発射
	for( i = 0; i < Me.NowMyMaxBall; i++ ){
		Me.MyBall[i].Move(Scroll);
		Me.MyBall[i].Draw( Me.MyBall[i].Dimension ,Scroll  ); 
	}
	if(KeyOne.X ==1 && Me.Invisible == 0 && Me.MP>=2 ){/////////////////////HSW
		Me.MP -=2;
		switch(Me.PlayerNumber){int HH;
		case 1:
			Me.HP =Me.HP + 40 ; if(Me.HP>Me.MaxHP)Me.HP=Me.MaxHP; PlaySoundMem( Music.SE[7] , DX_PLAYTYPE_BACK) ; break;
		case 2:
			Me.Left +=200;PlaySoundMem( Music.SE[10] , DX_PLAYTYPE_BACK) ; break;
		case 3:
			Me.FlashFirst = T;HH =Me.MaxBall;Me.MaxBall = 3;Me.PushBomb2 (Pic);Me.MaxBall = HH;Me.MP ++;
                        Me.Left +=64;Me.HP =Me.HP + 5 ; if(Me.HP>Me.MaxHP)Me.HP=Me.MaxHP;PlaySoundMem( Music.SE[7] , DX_PLAYTYPE_BACK) ; break;
		case 4:
			HH =Me.MaxBall;Me.MaxBall = 35;Me.PushBomb2 (Pic);Me.MP ++;
			PlaySoundMem( Music.SE[6] , DX_PLAYTYPE_BACK) ;Me.MaxBall = HH;break;
		case 5:
			if(Me.SpeedX <30){Me.SpeedX *=1.2;Me.SpeedY *=1.2;Me.Attack *= 1.3;Me.Circle -- ; PlaySoundMem( Music.SE[7] , DX_PLAYTYPE_BACK) ;}
			else Me.MP +=2;
			break;
		}
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑弾について↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑



	if( Me.FlashFirst +Me.FlashTime < T || (T % 2 ) )Me.Draw(Scroll);

	///////////////////////////////文字描画
	DrawExtendGraph( 0 , 0 , WINDOW_WIDTH * Me.HP   / Me.MaxHP   , 16 , Pic.Gage [0] , TRUE ) ;
	DrawExtendGraph( 0 , 30 , WINDOW_WIDTH * Me.MP / Me.MaxMP  , 46 ,Pic.Gage [1] , TRUE ) ;

	DrawFormatString( 0, 0,    sukenBLACK , "HP %d" , Me.HP  ) ;
	DrawFormatString( 0, 30,   sukenBLACK , "MP %d" , Me.MP  ) ;
	DrawFormatString( 250, 0,  sukenBLACK , "ATTACK %d  DIFFENCE %d  SPEED %d SIZE %d",Me.Attack ,Me.Diffence,(int)((Me.SpeedX + Me.SpeedY)/2),Me.Circle   ) ;
	DrawFormatString( 400, 30, sukenBLACK , "TIME %d SECOND " , (GetNowCount() - STARTTIME) / 1000   ) ;

	///////////////////////////////////GAME OVER
	
	if (KeyOne.ESCAPE  == 1 || Me.Left >= 64*  (cBack.Width  -1 )|| Me.HP <= 0 || (Me.Left <Scroll && Me.ScrollSwitch  ) ){
		ClearTime =(GetNowCount() - STARTTIME) / 1000;SetFontSize(40);

		if(Me.Left >= 64* (cBack.Width  -1 )  &&  ( cIntData.LeftData [MapType] > ClearTime  || cIntData.LeftData [MapType]==0 ) )cIntData.LeftData [MapType] =  ClearTime ;//BESTTIME = 
		StopSoundMem( Music.BGM[(int)((MapType - 1) / 6) + 1] );
		if(cIntData.LeftData[0] <MapType && Me.Left >= 64* (cBack.Width  -1 )  )cIntData.LeftData [0]++;
		cIntData.WriteData ();
		if(Me.Left >= 64*  (cBack.Width  -1  ))PlaySoundMem( Stuff.SE[0] , DX_PLAYTYPE_BACK) ;else PlaySoundMem( Stuff.SE[1] , DX_PLAYTYPE_BACK) ;
		
		DXCLEAR = true;
		Cleared = (Me.Left >= 64 * (cBack.Width - 1));
		InitGraph();
		///////////////////////自分の弾、マップのブロック、神風、Wizard,WizardBombのメモリ解放
		if (Me.NowMyMaxBall >0){delete [] Me.MyBall ;}//delete [] Me.PastBall  ; }同じ場所
		if (cBack.BlockNum >0){delete [] cBack.Obstacle ; }
		if (cBack.KamikazeNum >0){delete [] cBack.Kamikaze ; }
		if (cBack.WizardNum >0){
			for (i = 0 ; i < cBack.WizardNum ; i++ ){
				if( cBack.Wizard [i].NowMyMaxKamikaze >0){delete [] cBack.Wizard [i].MyKamikaze ; }//delete [] Me.PastBall  ; }同じ場所
			}
			delete [] cBack.Wizard ;
		}
		return 1;
	}
	return 0;
}

bool ClearLoop(){
	DrawGraph(0, 0, Stuff.Stuff[5], false);
	KeyOne.ALLKEYCHECK();
	if (Cleared){////クリア
		DrawGraph(360, 200, Stuff.Stuff[3], true);
		DrawFormatString(300, 380, 0, "クリアタイム %d 秒", ClearTime);
	}
	else{////失敗
		DrawGraph(360, 200, Stuff.Stuff[2], true);
	}
	DrawFormatString(220, 450, 0, "エンターキーを押して下さい", ClearTime);
	DrawGraph(450, 300, Stuff.Chara[PlayType + Me.GirlBoy * 5 - 1], true);
	if (CheckHitKey(KEY_INPUT_ESCAPE) || CheckHitKey(KEY_INPUT_X)) return true;
	else return false;
}