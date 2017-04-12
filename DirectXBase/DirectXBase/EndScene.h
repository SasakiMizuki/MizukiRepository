#pragma once
#include "SceneBase.h"
#include "EndBG.h"
#include "Camera.h"
#include "FadeButton.h"
#include "Fade.h"
class CEndScene :
	public CSceneBase
{
private:
	CEndScene*	m_pScene;
	CEndBG*		m_pEndBG;
	CCamera*	m_pCamera;
	CFadeButton* m_pButton;
	CFade*		m_pFade;
public:
	CEndScene();
	~CEndScene();

	CEndScene* Create(CGraphics* pGraph);
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
