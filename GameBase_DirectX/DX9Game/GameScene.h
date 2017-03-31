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
	//-------- ゲーム用オブジェクト
	//CPlayer*	m_pPlayer;
	//CSky*		m_pSky;
	//CLand*		m_pLand;
	CCamera*	m_pCamera;
	//CJintai*    m_pPlayer;
	//CSword*		m_pSword;
	//CEnemy*		m_pEnemy;
	//CPlayerHP*	m_pPlayerHP;
	//CFade*		m_pFade;
	//CTreeManager* m_pTreeManager;
	//CParticle*	m_pParticle;

	CTree*		m_pTree;
public:
	CGameScene();
	virtual ~CGameScene();

	CGameScene* Create(CGraphics* pGraph);
	void Release();
	void Render();
	void Update();
	void SetFPS(int nFPS) {m_FPS = nFPS;}
	void AddDebugStr(LPCTSTR psz) {lstrcat(m_szDebug, psz);}

	//void Add(C3DObj* pObj);
	//void Del(C3DObj* pObj);
	//C3DObj* Find(UINT uID, C3DObj* p);
	void InitObj();
	void FinObj();
	void UpdateObj();
	void DrawObj();
	DWORD GetTick();

private:
	bool Initialize(CGraphics* pGraph);
	void Finalize();
	void Draw();
};

//=======================================================================================
//	End of File
//=======================================================================================