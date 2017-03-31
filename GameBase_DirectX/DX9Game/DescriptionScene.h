#pragma once
#include "SceneBase.h"
#include "Camera.h"
#include "DescriptionSceneBG.h"
#include "FadeButton.h"
#include "Fade.h"
class CDescriptionScene :
	public CSceneBase
{
private:
	CDescriptionScene* m_pScene;
	CDescriptionSceneBG* m_pDescriptionSceneBG;
	CCamera*	m_pCamera;
	CFadeButton* m_pButton;
	CFade*		m_pFade;
public:
	CDescriptionScene();
	virtual ~CDescriptionScene();

	CDescriptionScene* Create(CGraphics* pGraph);
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

