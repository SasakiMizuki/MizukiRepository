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
	m_target.Init();
	if (!m_mesh.Initialize(_T("../data/model/fig01/fig01.x"))) {
		::MessageBox(NULL, _T("X�t�@�C�����ǂ߂܂���."), _T("error"), MB_OK);
		return false;
	}
	D3DXMatrixIdentity(&m_world);
	m_angle = D3DXVECTOR3(0, 0, 0);

	m_focus = 0.5f;

	m_shader.Load(_T("../data/shader/Focus.fx"));

	return true;
}

//---------------------------------------------------------------------------------------
// �f�o�C�X�A���\�[�X���
//---------------------------------------------------------------------------------------
void CScene::Finalize()
{
	//-------- �Q�[���p�I�u�W�F�N�g�̌�n��
	m_shader.Release();
	m_mesh.Finalize();
	m_target.Fin();
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
	m_angle.y -= 1.0f;
	if (m_angle.y < -180.0f)
		m_angle.y += 360.0f;
	D3DXMatrixRotationYawPitchRoll(&m_world,
		D3DXToRadian(m_angle.y), D3DXToRadian(m_angle.x),
		D3DXToRadian(m_angle.z));

	if (CInput::GetKeyPress(DIK_UP)) {
		m_focus += 0.001f;
		if (m_focus > 1.0f)
			m_focus = 1.0f;
	}
	if (CInput::GetKeyPress(DIK_DOWN)) {
		m_focus -= 0.001f;
		if (m_focus < 0.0f) {
			m_focus = 0.0f;
		}
	}
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
	m_target.Save();
	m_target.Change(0);
	m_shader.SetTechnique();
	m_shader.SetCamera(&m_pGraph->GetCameraPos());
	m_shader.SetViewMatrix(&m_pGraph->GetViewMatrix());
	m_shader.SetProjMatrix(&m_pGraph->GetProjMatrix());
	m_shader.SetLight(&m_pGraph->GetLight());
	m_mesh.Draw(m_world, &m_shader);

	m_target.Change(1);
	m_shader.SetTechnique(1);
	m_shader.Begin();
	m_shader.BeginPass(0);
	m_shader.SetTexture(m_target.GetTexture(0));
	m_shader.Commit();

	LPDIRECT3DDEVICE9 pDevice = m_pGraph->GetDevice();
	struct VERTEX {
		float x, y, z, rhw;
		float u, v;
	} vtxH[4] ={
		{ 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f },
		{ 400.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f },
		{ 0.0f, 300.0f, 0.0f, 1.0f, 0.0f, 1.0f },
		{ 400.0f, 300.0f, 0.0f, 1.0f, 1.0f, 1.0f },
	};
	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vtxH, sizeof(vtxH[0]));
	m_shader.EndPass();
	m_shader.End();
	// ��ʊE�[�x
	m_target.Reset();
	m_shader.SetTechnique(2);
	m_shader.Begin();
	m_shader.BeginPass(0);
	m_shader.SetTexture(m_target.GetTexture(0));
	m_shader.SetDepthTexture(m_target.GetTexture(1));
	m_shader.SetBlurTexture(m_target.GetTexture(2));
	m_shader.SetFocus(m_focus);
	m_shader.Commit();
	VERTEX vtx[4] ={
		{ 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f },
		{ 800.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f },
		{ 0.0f, 600.0f, 0.0f, 1.0f, 0.0f, 1.0f },
		{ 800.0f, 600.0f, 0.0f, 1.0f, 1.0f, 1.0f },
	};
	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vtx, sizeof(vtx[0]));
	m_shader.EndPass();
	m_shader.End();

	_stprintf(str, _T("focus = %f\n"), m_focus);
	lstrcat(m_szDebug, str);

	// �f�o�b�O������`��
	m_pGraph->DrawText(0, 0, m_szDebug);
}

//=======================================================================================
//	End of File
//=======================================================================================