#include "Debug.h"
#include "model.h"
#include "field.h"


CDebug::CDebug()
{
}


CDebug::~CDebug()
{
}

#ifdef DEBUG_MODE
void CDebug::InitDebug() {
	m_pD3DXFont = NULL;
	// 情報表示用フォントを設定
	D3DXCreateFont(GetDevice(), 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pD3DXFont);
}
void CDebug::UninitDebug() {
	if (m_pD3DXFont != NULL)
	{// 情報表示用フォントの開放
		m_pD3DXFont->Release();
		m_pD3DXFont = NULL;
	}
}

// 更新
void CDebug::UpdateDebug() {
	CDebug::GetDebug();

	DebugMessage = "FPS:" + to_string((long double)CountFPS);
	DebugMessage += "\nPlayerPosX:" + to_string((long double)PlayerPos.x);
	DebugMessage += "\nPlayerPosY:" + to_string((long double)PlayerPos.y);
	DebugMessage += "\nPlayerPosZ:" + to_string((long double)PlayerPos.z);
	DebugMessage += "\nFieldNumber:" + to_string((long double)FieldNumber);
	DebugMessage += "\nGameState:" + to_string((long double)eGameState + 1);
}
void CDebug::DrawDebug() {
	//RECT rect = { 0,50,SCREEN_WIDTH,SCREEN_HEIGHT };
	// テキスト描画
	//m_pD3DXFont->DrawText(NULL, DebugMessage.c_str(), -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0x00, 0x00, 0x00));
}

// データ取得
void CDebug::GetDebug() {
	CountFPS = GetCountFPS();
	PlayerPos = GetModelPos();
	PlayerRot = GetModelRot();
	FieldNumber = GetFieldNumber();
	eGameState = GetGameState();
}
#endif