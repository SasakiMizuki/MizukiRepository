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
#include "Scene.h"
#include "Input.h"

//---------------------------------------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------------------------------------
CScene::CScene()
{
	m_FPS = 0;
}

//---------------------------------------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------------------------------------
CScene::~CScene()
{
}

//---------------------------------------------------------------------------------------
// �V�[������
//---------------------------------------------------------------------------------------
CScene* CScene::Create(CGraphics* pGraph)
{
	CScene* pScene = new CScene();
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
bool CScene::Initialize(CGraphics* pGraph)
{
	m_pGraph = pGraph;

	//-------- �Q�[���p�I�u�W�F�N�g�̏�����
	m_target.Init();	// �����_�����O�^�[�Q�b�g�ؑ� ������
	if (!m_mesh.Initialize(_T("../data/model/gtank.X"))) {
		::MessageBox(NULL, _T("gtank.X���ǂ߂܂���."), _T("error"), MB_OK);
		return false;
	}
	if (!m_box.Initialize(_T("../data/model/box.x"))) {
		::MessageBox(NULL, _T("box.x���ǂ߂܂���."), _T("error"), MB_OK);
		return false;
	}
	D3DXMatrixIdentity(&m_world);
	D3DXMatrixIdentity(&m_boxWorld);
	m_angle = D3DXVECTOR3(0, 0, 0);
	m_boxAngle = D3DXVECTOR3(0, 0, 0);

	return true;
}

//---------------------------------------------------------------------------------------
// �f�o�C�X�A���\�[�X���
//---------------------------------------------------------------------------------------
void CScene::Finalize()
{
	//-------- �Q�[���p�I�u�W�F�N�g�̌�n��
	m_box.Finalize();
	m_mesh.Finalize();
	m_target.Fin();		// �����_�����O�^�[�Q�b�g�ؑ� ���
}

//---------------------------------------------------------------------------------------
// �V�[�����
//---------------------------------------------------------------------------------------
void CScene::Release()
{
	Finalize();
	delete this;
}

//---------------------------------------------------------------------------------------
// �Q�[���`�揈���i���C�����[�v����R�[�������j
//---------------------------------------------------------------------------------------
void CScene::Render()
{
	if (m_pGraph->Begin()) {	// �`��J�n

		Draw();					// �`�揈��

		m_pGraph->End();		// �`��I��
	}
	m_pGraph->SwapBuffer();		// �o�b�N�o�b�t�@����
}

//---------------------------------------------------------------------------------------
// �Q�[�����C�������i���C�����[�v����R�[�������j
//---------------------------------------------------------------------------------------
void CScene::Update()
{
	// ���͍X�V
	CInput::Update();

	//----- �����ɃQ�[���{�̏���
	if (::GetAsyncKeyState(VK_SHIFT) & 0x8000) {
		if (::GetAsyncKeyState(VK_LEFT) & 0x8000) {
			m_angle.y += 1.0f;
			if (m_angle.y >= 180.0f) m_angle.y -= 360.0f;
		}
		if (::GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			m_angle.y -= 1.0f;
			if (m_angle.y < -180.0f) m_angle.y += 360.0f;
		}
	} else {
		if (::GetAsyncKeyState(VK_LEFT) & 0x8000) {
			m_boxAngle.y += 1.0f;
			if (m_boxAngle.y >= 180.0f) m_boxAngle.y -= 360.0f;
		}
		if (::GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			m_boxAngle.y -= 1.0f;
			if (m_boxAngle.y < -180.0f) m_boxAngle.y += 360.0f;
		}
	}
	D3DXMatrixRotationYawPitchRoll(&m_world,
		D3DXToRadian(m_angle.y),
		D3DXToRadian(m_angle.x),
		D3DXToRadian(m_angle.z));
	D3DXMatrixRotationYawPitchRoll(&m_boxWorld,
		D3DXToRadian(m_boxAngle.y),
		D3DXToRadian(m_boxAngle.x),
		D3DXToRadian(m_boxAngle.z));
}

//---------------------------------------------------------------------------------------
// �`�揈���iCGraphics::Render() ����R�[�������j
//---------------------------------------------------------------------------------------
void CScene::Draw()
{
	m_szDebug[0] = _T('\0');	// �f�o�b�O�����񏉊���

	// FPS ����ʂɕ`�悷�邽�߂̕�������쐬
	TCHAR	str[256];
	_stprintf(str, _T("FPS = %d\n"), m_FPS);
	lstrcat(m_szDebug, str);

	//----- �����ɕ`�揈��
	m_target.Change();	// �����_�����O�^�[�Q�b�g�ۑ��A�ؑ�
	m_mesh.Draw(m_world);
	m_target.Reset();	// �����_�����O�^�[�Q�b�g���A

	m_box.SetTexture(m_target.GetTexture());
	m_box.Draw(m_boxWorld);
/*
	float width = 800.0f;
	float height = 600.0f;
	float x1 = width * 0.25f;
	float y1 = height * 0.25f;
	float x2 = x1 + width * 0.5f;
	float y2 = y1 + height * 0.5f;
	struct {
		float		x, y, z, rhw;
		D3DCOLOR	diffuse;
		float		u, v;
	} vtx[] = {
		{x1, y2, 0.0f, 1.0f, (DWORD)-1, 0.0f, 1.0f},
		{x1, y1, 0.0f, 1.0f, (DWORD)-1, 0.0f, 0.0f},
		{x2, y2, 0.0f, 1.0f, (DWORD)-1, 1.0f, 1.0f},
		{x2, y1, 0.0f, 1.0f, (DWORD)-1, 1.0f, 0.0f},
	};
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();
	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE |
		D3DFVF_TEX1);
	pDevice->SetTexture(0, m_target.GetTexture());
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2,
		vtx, sizeof(vtx[0]));
*/
	// �f�o�b�O������`��
	m_pGraph->DrawText(0, 0, m_szDebug);
}

//=======================================================================================
//	End of File
//=======================================================================================