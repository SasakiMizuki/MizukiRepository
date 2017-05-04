#include "TreeManager.h"
#include "SceneBase.h"


CTreeManager::CTreeManager(CSceneBase* pScene) :
C3DObj(pScene){
	m_pScene = pScene;
	m_pScene->Add(this);
	for (int i = 0; i < 10; i++) {
		vecTree.push_back(CTree(m_pScene, D3DXVECTOR3(-1900.0f, 0.0f, -1900.0f + i * 380.0f)));
	}
	for (int i = 0; i < 10; i++) {
		vecTree.push_back(CTree(m_pScene, D3DXVECTOR3(1900.0f, 0.0f, -1900.0f + i * 380.0f)));
	}
	for (int i = 0; i < 10; i++) {
		vecTree.push_back(CTree(m_pScene, D3DXVECTOR3(-1900.0f + i * 380.0f, 0.0f, -1900.0f)));
	}
	for (int i = 0; i < 10; i++) {
		vecTree.push_back(CTree(m_pScene, D3DXVECTOR3(-1900.0f + i * 380.0f, 0.0f, 1900.0f)));
	}
}


CTreeManager::~CTreeManager() {
}

void CTreeManager::Init() {
	for (unsigned int i = 0; i < vecTree.size(); i++) {
		vecTree[i].Init();
	}
}

void CTreeManager::Fin() {
	for (unsigned int i = 0; i < vecTree.size(); i++) {
		vecTree[i].Fin();
	}
}

void CTreeManager::Draw(CShader* pShader) {
	for (unsigned int i = 0; i < vecTree.size(); i++) {
		vecTree[i].Draw(pShader);
	}
}
