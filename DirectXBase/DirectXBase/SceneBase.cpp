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
#include "SceneBase.h"
#include "SceneManager.h"
#include "Input.h"

// �V�[���ɃI�u�W�F�N�g��ǉ�
void CSceneBase::Add(CObjectBase* pObj) {
	int i = 0;
	for (; i < m_mObj.size(); ++i) {
		auto Iterator = m_mObj.find(i);
		if (Iterator == m_mObj.end())
			break;
	}

	std::pair<int, CObjectBase*> NewObjectPair(i, pObj);

	m_mObj.insert(NewObjectPair);
	pObj->SetNumber(i);

}

// �V�[������I�u�W�F�N�g���폜
void CSceneBase::Del(int nNumber) {
	auto Iterator = m_mObj.find(nNumber);
	if (Iterator == m_mObj.end()) {
		return;
	}

	delete Iterator->second;
	m_mObj.erase(nNumber);
	//m_nNumberOfObj--;
}

// �I�u�W�F�N�g����
CObjectBase* CSceneBase::Find(UINT uID, int nNumber) {
	//auto Iterator = m_mObj.find(nNumber);
	//if (Iterator == m_mObj.end())
	//	return NULL;
	//if (Iterator->second->GetID() != uID)
	//	return NULL;

	auto Iterator = m_mObj.begin();
	for (; Iterator != m_mObj.end(); ++Iterator) {
		if (Iterator->first < nNumber)
			continue;
		if (Iterator->second->GetID() == uID)
			return Iterator->second;
	}

	return NULL;
}

// �S�I�u�W�F�N�g������
void CSceneBase::InitObj() {
	auto Iterator = m_mObj.begin();
	for (; Iterator != m_mObj.end(); ++Iterator) {
		if (Iterator->second == NULL) {
			continue;
		}
		Iterator->second->Init();
	}
}

// �S�I�u�W�F�N�g�j��
void CSceneBase::FinObj() {
	auto Iterator = m_mObj.begin();
	for (; Iterator != m_mObj.end(); ++Iterator) {
		if (Iterator->second == NULL) {
			continue;
		}
		Iterator->second->Fin();
	}
}

// �S�I�u�W�F�N�g�X�V
void CSceneBase::UpdateObj() {
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
}

// �S�I�u�W�F�N�g�`��
void CSceneBase::DrawObj() {
	//m_pCamera->PreDraw();		// �J�������f
	// �s���������`��
	auto Iterator = m_mObj.begin();
	for (; Iterator != m_mObj.end(); ++Iterator) {
		if (Iterator->second == NULL) {
			continue;
		}
		if (Iterator->second->GetDamage() && (m_dwTick & 8)) {
			continue;
		}
		Iterator->second->PreDraw();
	}

	Iterator = m_mObj.begin();
	// �s���������`��
	for (; Iterator != m_mObj.end(); ++Iterator) {
		if (Iterator->second == NULL) {
			continue;
		}
		if (Iterator->second->GetDamage() && (m_dwTick & 8)) {
			continue;
		}
		Iterator->second->Draw(&m_shader);
	}

	// �����������`��
	LPDIRECT3DDEVICE9 pD = CGraphics::GetDevice();
	pD->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pD->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pD->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pD->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	Iterator = m_mObj.begin();
	for (; Iterator != m_mObj.end(); ++Iterator) {
		if (Iterator->second == NULL) {
			continue;
		}
		if (Iterator->second->GetDamage() && (m_dwTick & 8)) {
			continue;
		}
		Iterator->second->DrawAlpha();
	}
	pD->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pD->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

//---------------------------------------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------------------------------------
CSceneBase::CSceneBase() :
	m_pGraph(NULL),
	m_FPS(),
	m_dwTick(0) {
	m_mObj.clear();
	m_szDebug[0] = _T('\0');
	m_bSceneChange = false;
	m_nNumberOfObj = 0;
}

//---------------------------------------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------------------------------------
CSceneBase::~CSceneBase() {

}

//---------------------------------------------------------------------------------------
// �V�[������
//---------------------------------------------------------------------------------------
CSceneBase* CSceneBase::Create(CGraphics* pGraph) {
	CSceneBase* pScene = new CSceneBase();
	if (pScene) {
		if (!pScene->Initialize(pGraph)) {
			SAFE_DELETE(pScene);
		}
	}
	return pScene;
}

//---------------------------------------------------------------------------------------
// �f�o�C�X�A���\�[�X������
//---------------------------------------------------------------------------------------
bool CSceneBase::Initialize(CGraphics* pGraph) {
	m_pGraph = pGraph;

	//-------- �Q�[���p�I�u�W�F�N�g�̏�����
	InitObj();

	return true;
}

//---------------------------------------------------------------------------------------
// �f�o�C�X�A���\�[�X���
//---------------------------------------------------------------------------------------
void CSceneBase::Finalize() {
	//-------- �Q�[���p�I�u�W�F�N�g�̌�n��
	FinObj();
}

//---------------------------------------------------------------------------------------
// �V�[�����
//---------------------------------------------------------------------------------------
void CSceneBase::Release() {
	Finalize();
	delete this;
}

//---------------------------------------------------------------------------------------
// �Q�[���`�揈���i���C�����[�v����R�[�������j
//---------------------------------------------------------------------------------------
void CSceneBase::Render() {
	if (m_pGraph->Begin()) {	// �`��J�n

		Draw();					// �`�揈��

		m_pGraph->End();		// �`��I��
	}
	m_pGraph->SwapBuffer();		// �o�b�N�o�b�t�@����
}

//---------------------------------------------------------------------------------------
// �Q�[�����C�������i���C�����[�v����R�[�������j
//---------------------------------------------------------------------------------------
void CSceneBase::Update() {
	++m_dwTick;

	// ���͍X�V
	CInput::Update();

	//----- �����ɃQ�[���{�̏���
	UpdateObj();
}

//---------------------------------------------------------------------------------------
// �`�揈���iCGraphics::Render() ����R�[�������j
//---------------------------------------------------------------------------------------
void CSceneBase::Draw() {
	m_szDebug[0] = _T('\0');	// �f�o�b�O�����񏉊���

								// FPS ����ʂɕ`�悷�邽�߂̕�������쐬
	TCHAR	str[256];
	_stprintf(str, _T("FPS = %d\n"), m_FPS);
	lstrcat(m_szDebug, str);

	//----- �����ɕ`�揈��
	m_shader.SetViewMatrix(&m_pGraph->GetViewMatrix());
	m_shader.SetProjMatrix(&m_pGraph->GetProjMatrix());
	m_shader.SetLight(&m_pGraph->GetLight());
	DrawObj();

	// �f�o�b�O������`��
	m_pGraph->DrawText(0, 0, m_szDebug);
}

//=======================================================================================
//	End of File
//=======================================================================================