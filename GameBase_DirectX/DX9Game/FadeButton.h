#pragma once
#include "C2DObj.h"
#define BUTTON_IMAGE_NAME _T("../data/image/press_button.png")
class CFadeButton :
	public C2DObj
{
private:
	static bool m_bLoad;
	float m_fFedeVol;
public:
	CFadeButton(CSceneBase* pScene);
	virtual ~CFadeButton();
	virtual void Init();
	virtual void Update();
	virtual void Fin();
	virtual void MakeVertexPolygon();
};

