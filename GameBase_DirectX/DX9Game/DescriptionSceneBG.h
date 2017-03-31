#pragma once
#include "C2DObj.h"
#define DESCRIPTION_BG_NAME _T("../data/image/description_bg.png")
class CDescriptionSceneBG :
	public C2DObj
{
private:
	static bool m_bLoad;
public:
	CDescriptionSceneBG(CSceneBase* pScene);
	virtual ~CDescriptionSceneBG();
	virtual void Init();
	virtual void Update();
	virtual void Fin();
	virtual void MakeVertexPolygon();
};

