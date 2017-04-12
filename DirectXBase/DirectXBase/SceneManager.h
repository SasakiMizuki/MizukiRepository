#pragma once

#include "SceneBase.h"
#include "Fade.h"
typedef enum {
	Scene_Title,
	Scene_Description,
	Scene_Game,
	Scene_GameOver,
	Scene_End,

	MAX_SCENE
} eEntireScene;	// 全体のシーン	
				// 追加予定(？)

class CSceneManager
{
private:
	CGraphics*	m_pGraph;			// 描画デバイス クラス
	CSceneBase* m_pNowScene;
	CSceneManager();
public:
	static CSceneManager* Instance();
	~CSceneManager();
	CSceneBase* ChangeScene(eEntireScene NextScene);

	virtual void Create(CSceneBase* pScene);
	virtual void Init();
	virtual void Update();
	virtual void Draw();
	virtual void Fin();
	void SetGraphics(CGraphics* Graphics) { m_pGraph = Graphics; }
	CGraphics* GetGraphics() { return m_pGraph; }
	CSceneBase* GetScene() { return m_pNowScene; }
};

