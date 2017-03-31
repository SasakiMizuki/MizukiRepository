#pragma once
#include "Billboard.h"
#include "Jintai.h"

#define PLAYER_HP_TEXTRUE _T("../data/image/player_hp.png")
class CPlayerHP :
	public CBillboard
{
private:
	float	 m_fMaxPlayerHP;
	float    m_fPlayerHP;
	CJintai* m_pPlayer;
public:
	CPlayerHP(CSceneBase* pScene);
	~CPlayerHP();
	void Init();
	void Fin();
	void Update();
	void Draw();
	void DrawAlpha();
	void MakeVertex();
};

