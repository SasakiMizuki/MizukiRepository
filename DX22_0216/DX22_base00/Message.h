#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include "main.h"

//----- 列挙体宣言 -----

//----- 構造体宣言 -----

//----- プロトタイプ宣言 -----
void InitMessage(void);
void UninitMessage(void);
void UpdateMessage(void);
void DrawMessage(void);

void SetMessageData(int,int,int,char*);				//Messageセット(X座標,Y座標,生存時間(frame),メッセージ内容)
void SetMessageData(int,int,int,char*,char*);
void SetMessageData(int,int,int,char*,char*,char*);
#endif