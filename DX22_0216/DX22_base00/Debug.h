#pragma once
#include "main.h"
#include <iostream>
#include <string>
#include <string.h>

using namespace std;
class CDebug
{
public:
	CDebug();
	~CDebug();

	void InitDebug();
	void UninitDebug();
	void UpdateDebug();
	void DrawDebug();
	void GetDebug();
private:
	string DebugMessage;
	//RECT rect;
	LPD3DXFONT	m_pD3DXFont;		// フォントへのポインタ

	int CountFPS;
	int FieldNumber;
	GAME_STATE eGameState;
	D3DXVECTOR3 PlayerPos;
	D3DXVECTOR3 PlayerRot;
	
};

