#pragma once
#include "SceneBase.h"

#include "Camera.h"
#include "TitleBG.h"
#include "FadeButton.h"
#include "Fade.h"
class CTitleScene :
	public CSceneBase
{
private:
	CTitleScene* m_pScene;
	CTitleBG* m_pTitleBG;
	CCamera*	m_pCamera;
	CFadeButton* m_pButton;
	CFade*		m_pFade;
public:
	CTitleScene();
	virtual ~CTitleScene();

	CTitleScene* Create(CGraphics* pGraph);
	void Release();
	void Render();
	void Update();

	void InitObj();
	void FinObj();
	void UpdateObj();
	void DrawObj();
private:
	bool Initialize(CGraphics* pGraph);
	void Finalize();
	void Draw();
};

