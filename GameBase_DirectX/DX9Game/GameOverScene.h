#pragma once
#include "SceneBase.h"
#include "GameOverBG.h"
#include "Camera.h"
#include "FadeButton.h"
#include "Fade.h"
class CGameOverScene :
	public CSceneBase
{
private:
	CGameOverScene* m_pScene;
	CGameOverBG* m_pGameOverBG;
	CCamera*	m_pCamera;
	CFadeButton* m_pButton;
	CFade*		m_pFade;
public:
	CGameOverScene();
	virtual ~CGameOverScene();

	CGameOverScene* Create(CGraphics* pGraph);
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

