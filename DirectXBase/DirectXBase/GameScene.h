//=======================================================================================
//
//	  ゲームシーン クラス定義
//
//=======================================================================================
#pragma once

#include "SceneBase.h"

#include "Player.h"
#include "Sky.h"
#include "Land.h"
#include "Jintai.h"
#include "Sword.h"
#include "Enemy.h"
#include "PlayerHP.h"
#include "Fade.h"
#include "TreeManager.h"
#include "Particle.h"

#include "Tree.h"

#include "Camera.h"

#include "Debug.h"

class CGameScene : public CSceneBase
{
private:
	CGameScene* m_pScene;

	CTree*		m_pTree;
public:
	CGameScene();
	virtual ~CGameScene();

	CGameScene* Create(CGraphics* pGraph);
	void Release();
	void Render();
	void SetFPS(int nFPS) {m_FPS = nFPS;}
	void AddDebugStr(LPCTSTR psz) {lstrcat(m_szDebug, psz);}

	void InitObj();
	void FinObj();
	void UpdateObj();
	DWORD GetTick();

private:
	bool Initialize(CGraphics* pGraph);
	void Finalize();
};

//=======================================================================================
//	End of File
//=======================================================================================