#include "SceneManager.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "EndScene.h"
#include "GameOverScene.h"
#include "DescriptionScene.h"

#include "Debug.h"

CSceneManager::CSceneManager() {
}


CSceneManager::~CSceneManager() {
}

// インスタンス獲得
CSceneManager* CSceneManager::Instance() {
	static CSceneManager pSceneManager;
	return &pSceneManager;
}

void CSceneManager::Create(CSceneBase* pScene) {

}

// シーン変更
CSceneBase* CSceneManager::ChangeScene(eEntireScene eNextScene) {
	switch(eNextScene) {
	case Scene_Title:
		if (m_pNowScene)
			SAFE_RELEASE(m_pNowScene);
		m_pNowScene = new CGameScene();
		Init();
		CFade::Start(FADEIN);
		break;
	case Scene_Description:
		if (m_pNowScene)
			SAFE_RELEASE(m_pNowScene);
		m_pNowScene = new CGameScene();
		Init();
		CFade::Start(FADEIN);
		break;
	case Scene_Game:
		if (m_pNowScene)
			SAFE_RELEASE(m_pNowScene);
		m_pNowScene = new CGameScene();
		Init();
		CFade::Start(FADEIN);
		break;
	case Scene_GameOver:
		if (m_pNowScene)
			SAFE_RELEASE(m_pNowScene);
		m_pNowScene = new CGameScene();
		Init();
		CFade::Start(FADEIN);
		break;
	case Scene_End:
		if (m_pNowScene)
			SAFE_RELEASE(m_pNowScene);
		m_pNowScene = new CGameScene();
		Init();
		CFade::Start(FADEIN);
		break;
	default:
		break;
	}
	return m_pNowScene;
}


void CSceneManager::Init() {
	m_pNowScene->Create(m_pGraph);
	m_pNowScene->InitObj();
}

void CSceneManager::Update() {
	m_pNowScene->Update();
}

void CSceneManager::Draw() {
	m_pNowScene->Render();
}

void CSceneManager::Fin() {
	m_pNowScene->FinObj();
}