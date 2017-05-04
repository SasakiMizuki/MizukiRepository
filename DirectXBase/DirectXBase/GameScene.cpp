//=======================================================================================
//
//	  �Q�[���V�[�� �N���X
//
//=======================================================================================
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include "define.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "Input.h"

#include "Debug.h"

// �S�I�u�W�F�N�g������
void CGameScene::InitObj()
{
	auto Iterator = m_mObj.begin();
	for (; Iterator != m_mObj.end(); ++Iterator) {
		if (Iterator->second == NULL) {
			continue;
		}
		Iterator->second->Init();
	}

	//m_pParticle->PostInit();
}

// �S�I�u�W�F�N�g�j��
void CGameScene::FinObj()
{
	auto Iterator = m_mObj.begin();
	for (; Iterator != m_mObj.end(); ++Iterator) {
		if (Iterator->second == NULL) {
			continue;
		}
		Iterator->second->Fin();
		delete Iterator->second;
	}
}

// �S�I�u�W�F�N�g�X�V
void CGameScene::UpdateObj()
{
	auto Iterator = m_mObj.begin();
	for (; Iterator != m_mObj.end(); ++Iterator) {
		if (Iterator->second == NULL) {
			continue;
		}
		Iterator->second->Update();
	}
	Iterator = m_mObj.begin();
	for (; Iterator != m_mObj.end(); ++Iterator) {
		if (Iterator->second == NULL) {
			continue;
		}
		Iterator->second->PostUpdate();
	}

	//m_pCamera->PostUpdate();	// �J�����X�V
	//m_pSword->PostUpdate();	// �J�����X�V
}

// �S�I�u�W�F�N�g�`��
//void CGameScene::DrawObj()
//{
//	//m_pCamera->PreDraw();		// �J�������f
//
//	// �s���������`��
//	auto Iterator = m_mObj.begin();
//	for (; Iterator != m_mObj.end(); ++Iterator) {
//		if (Iterator->second == NULL) {
//			continue;
//		}
//		if (Iterator->second->GetDamage() && (m_dwTick & 8)) {
//			continue;
//		}
//		Iterator->second->PreDraw();
//	}
//
//	Iterator = m_mObj.begin();
//	for (; Iterator != m_mObj.end(); ++Iterator) {
//		if (Iterator->second == NULL) {
//			continue;
//		}
//		if (Iterator->second->GetDamage() && (m_dwTick & 8)) {
//			continue;
//		}
//		Iterator->second->Draw(&m_shader);
//	}
//
//	// �����������`��
//	LPDIRECT3DDEVICE9 pD = CGraphics::GetDevice();
//	pD->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
//	pD->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
//	pD->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
//	pD->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
//	Iterator = m_mObj.begin();
//	for (; Iterator != m_mObj.end(); ++Iterator) {
//		if (Iterator->second == NULL) {
//			continue;
//		}
//		if (Iterator->second->GetDamage() && (m_dwTick & 8)) {
//			continue;
//		}
//		Iterator->second->DrawAlpha();
//	}
//	pD->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
//	pD->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
//}

//---------------------------------------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------------------------------------
CGameScene::CGameScene()
{
	m_szDebug[0] = _T('\0');

	//m_pPlayer = new CPlayer(this);
	new CFade(this);
	new CJintai(this, D3DXVECTOR3(-300.0f, 0.0f, -300.0f));
	new CEnemy(this);
	new CSword(this);
	new CSky(this);
	new CCamera(this);
	new CLand(this);
	new CPlayerHP(this);
	new CTreeManager(this);
}

//---------------------------------------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------------------------------------
CGameScene::~CGameScene()
{
	m_mObj.clear();
}

//---------------------------------------------------------------------------------------
// �V�[������
//---------------------------------------------------------------------------------------
CGameScene* CGameScene::Create(CGraphics* pGraph)
{
	m_pScene = new CGameScene();
	if (m_pScene) {
		if (!m_pScene->Initialize(pGraph)) {
			SAFE_DELETE(m_pScene);
		}
	}
	m_pGraph = pGraph;
	return m_pScene;
}

//---------------------------------------------------------------------------------------
// �f�o�C�X�A���\�[�X������
//---------------------------------------------------------------------------------------
bool CGameScene::Initialize(CGraphics* pGraph)
{
	m_pGraph = pGraph;
	m_target.Init();
	CJintai::LoadMesh();
	//-------- �Q�[���p�I�u�W�F�N�g�̏�����
	InitObj();

	m_shader.Load(_T("../data/shader/Toon.fx"));
	return true;
}

//---------------------------------------------------------------------------------------
// �f�o�C�X�A���\�[�X���
//---------------------------------------------------------------------------------------
void CGameScene::Finalize()
{
	//-------- �Q�[���p�I�u�W�F�N�g�̌�n��
	//SAFE_DELETE(m_pScene);
	m_shader.Release();
	FinObj();
}

//---------------------------------------------------------------------------------------
// �V�[�����
//---------------------------------------------------------------------------------------
void CGameScene::Release()
{
	Finalize();
	delete this;
}

//---------------------------------------------------------------------------------------
// �Q�[���`�揈���i���C�����[�v����R�[�������j
//---------------------------------------------------------------------------------------
void CGameScene::Render()
{
	if (m_pGraph->Begin()) {	// �`��J�n

		Draw();					// �`�揈��

		m_pGraph->End();		// �`��I��
	}
	m_pGraph->SwapBuffer();		// �o�b�N�o�b�t�@����
}

////---------------------------------------------------------------------------------------
//// �Q�[�����C�������i���C�����[�v����R�[�������j
////---------------------------------------------------------------------------------------
//void CGameScene::Update()
//{
//	++m_dwTick;
//
//	// ���͍X�V
//	CInput::Update();
//
//
//	//----- �����ɃQ�[���{�̏���
//		UpdateObj();
//
//		/*if (CInput::GetKeyPress(DIK_F1)) {
//			m_pPlayer->ChangeHP(-1000);
//		}
//		if (CInput::GetKeyPress(DIK_F2)) {
//			m_pEnemy->ChangeHP(-1000);
//		}
//
//		if (!m_bSceneChange && (m_pPlayer->GetHP() <= 0.0f || m_pEnemy->GetHP() <= 0.0f)){
//			m_bSceneChange = true;
//			m_pFade->Start(FADEOUT);
//		}
//		if (m_bSceneChange && !m_pFade->GetDoingFade() && m_pEnemy->GetHP() <= 0.0f) {
//			CSceneManager::Instance()->ChangeScene(Scene_End);
//		} else if (m_bSceneChange && !m_pFade->GetDoingFade() && m_pPlayer->GetHP() <= 0.0f){
//			CSceneManager::Instance()->ChangeScene(Scene_GameOver);	
//		}*/
//}
//
////---------------------------------------------------------------------------------------
//// �`�揈���iCGraphics::Render() ����R�[�������j
////---------------------------------------------------------------------------------------
//void CGameScene::Draw()
//{
//	m_szDebug[0] = _T('\0');	// �f�o�b�O�����񏉊���
//
//	// FPS ����ʂɕ`�悷�邽�߂̕�������쐬
//	TCHAR	str[256];
//	_stprintf(str, _T("FPS = %d\n"), m_FPS);
//	lstrcat(m_szDebug, str);
//
//	//----- �����ɕ`�揈��
//	DrawObj();
//
//	// �f�o�b�O������`��
//	m_pGraph->DrawText(0, 0, m_szDebug);
//}

//=======================================================================================
//	End of File
//=======================================================================================