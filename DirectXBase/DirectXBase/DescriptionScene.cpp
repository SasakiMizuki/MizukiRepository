#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include "define.h"
#include "DescriptionScene.h"
#include "SceneManager.h"
#include "Input.h"


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
#include "TitleScene.h"
#include "Input.h"

// �S�I�u�W�F�N�g������
void CDescriptionScene::InitObj() {
	CObjectBase* pObj = m_pObj;
	for (; pObj; pObj = pObj->GetNext()) {
		pObj->Init();
	}
}

// �S�I�u�W�F�N�g�j��
void CDescriptionScene::FinObj() {
	CObjectBase* pObj = m_pObj;
	CObjectBase* pNext;
	for (; pObj; pObj = pNext) {
		pNext = pObj->GetNext();
		pObj->Fin();
	}
}

// �S�I�u�W�F�N�g�X�V
void CDescriptionScene::UpdateObj() {
	CObjectBase* pObj = m_pObj;
	CObjectBase* pNext;
	for (; pObj; pObj = pNext) {
		pNext = pObj->GetNext();
		pObj->Update();
	}

	m_pCamera->PostUpdate();	// �J�����X�V
}

// �S�I�u�W�F�N�g�`��
void CDescriptionScene::DrawObj() {
	m_pCamera->PreDraw();		// �J�������f

								// �s���������`��
	CObjectBase* pObj = m_pObj;
	for (; pObj; pObj = pObj->GetNext()) {
		if (pObj->GetDamage() && (m_dwTick & 8)) {
			continue;
		}
		pObj->Draw();
	}

	// �����������`��
	LPDIRECT3DDEVICE9 pD = CGraphics::GetDevice();
	pD->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pD->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pD->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pD->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pObj = m_pObj;
	for (; pObj; pObj = pObj->GetNext()) {
		if (pObj->GetDamage() && (m_dwTick & 8)) {
			continue;
		}
		pObj->DrawAlpha();
	}
	pD->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pD->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

//---------------------------------------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------------------------------------
CDescriptionScene::CDescriptionScene() {
	m_szDebug[0] = _T('\0');

	m_pCamera = new CCamera(this);
	m_pFade = new CFade(this);
	m_pButton = new CFadeButton(this);
	m_pDescriptionSceneBG = new CDescriptionSceneBG(this);
}

//---------------------------------------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------------------------------------
CDescriptionScene::~CDescriptionScene() {
	delete m_pDescriptionSceneBG;
	delete m_pCamera;
	delete m_pButton;
	delete m_pFade;
}

//---------------------------------------------------------------------------------------
// �V�[������
//---------------------------------------------------------------------------------------
CDescriptionScene* CDescriptionScene::Create(CGraphics* pGraph) {
	m_pScene = new CDescriptionScene();
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
bool CDescriptionScene::Initialize(CGraphics* pGraph) {

	//-------- �Q�[���p�I�u�W�F�N�g�̏�����
	InitObj();

	return true;
}

//---------------------------------------------------------------------------------------
// �f�o�C�X�A���\�[�X���
//---------------------------------------------------------------------------------------
void CDescriptionScene::Finalize() {
	//-------- �Q�[���p�I�u�W�F�N�g�̌�n��
	if (m_pScene) {
		delete m_pScene;
		m_pScene = NULL;
	}
	FinObj();
}

//---------------------------------------------------------------------------------------
// �V�[�����
//---------------------------------------------------------------------------------------
void CDescriptionScene::Release() {
	Finalize();
	delete this;
}

//---------------------------------------------------------------------------------------
// �Q�[���`�揈���i���C�����[�v����R�[�������j
//---------------------------------------------------------------------------------------
void CDescriptionScene::Render() {
	if (m_pGraph->Begin()) {	// �`��J�n

		Draw();					// �`�揈��

		m_pGraph->End();		// �`��I��
	}
	m_pGraph->SwapBuffer();		// �o�b�N�o�b�t�@����
}

//---------------------------------------------------------------------------------------
// �Q�[�����C�������i���C�����[�v����R�[�������j
//---------------------------------------------------------------------------------------
void CDescriptionScene::Update() {
	++m_dwTick;

	// ���͍X�V
	CInput::Update();

	//----- �����ɃQ�[���{�̏���
	UpdateObj();
	if (CInput::GetKeyTrigger(DIK_U)) {
		m_pFade->Start(FADEOUT);
		m_bSceneChange = true;
	}

	if (m_bSceneChange && (!m_pFade->GetDoingFade()))
		CSceneManager::Instance()->ChangeScene(Scene_Game);
}

//---------------------------------------------------------------------------------------
// �`�揈���iCGraphics::Render() ����R�[�������j
//---------------------------------------------------------------------------------------
void CDescriptionScene::Draw() {
	m_szDebug[0] = _T('\0');	// �f�o�b�O�����񏉊���

								// FPS ����ʂɕ`�悷�邽�߂̕�������쐬
	TCHAR	str[256];
	_stprintf(str, _T("FPS = %d\n"), m_FPS);
	lstrcat(m_szDebug, str);

	//----- �����ɕ`�揈��
	DrawObj();

	// �f�o�b�O������`��
	m_pGraph->DrawText(0, 0, m_szDebug);
}

//=======================================================================================
//	End of File
//=======================================================================================