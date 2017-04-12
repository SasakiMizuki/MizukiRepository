#pragma once
#include "C2DObj.h"
#define TITLE_BG_NAME _T("../data/image/title_bg.png")
//#define TITLE_BG_NAME ("title_bg.png")
class CTitleBG :
	public C2DObj
{
private:
	static bool m_bLoad;
public:
	CTitleBG(CSceneBase* pScene);
	~CTitleBG();
	virtual void Init();
	virtual void Update();
	virtual void Fin();
	virtual void MakeVertexPolygon();
};

