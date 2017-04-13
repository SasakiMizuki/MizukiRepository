#pragma once
#include "C2DObj.h"
#define GAMEOVER_BG_NAME _T("../data/image/gameover_bg.png")
class CGameOverBG :
	public C2DObj
{
private:
	static bool m_bLoad;
public:
	CGameOverBG(CSceneBase* pScene);
	~CGameOverBG();
	virtual void Init();
	virtual void Update();
	virtual void Draw();
	virtual void Fin();
};

