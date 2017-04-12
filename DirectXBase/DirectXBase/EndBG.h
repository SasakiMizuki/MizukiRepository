#pragma once
#include "C2DObj.h"
#define END_BG_NAME _T("../data/image/end_bg.png")
class CEndBG :
	public C2DObj
{
private:
	static bool m_bLoad;
public:
	CEndBG(CSceneBase* pScene);
	~CEndBG();
	virtual void Init();
	virtual void Update();
	virtual void Draw();
	virtual void Fin();
};

