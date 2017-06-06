//=======================================================================================
//
//	  �Q�[���V�[�� �N���X��`
//
//=======================================================================================
#pragma once

#include "Graphics.h"
#include "RenderTarget.h"

#include "Mesh.h"	// CMesh�N���X��`

class CScene
{
private:
	CGraphics*	m_pGraph;			// �O���t�B�b�N�f�o�C�X

	TCHAR		m_szDebug[1024];	// �f�o�b�O�p������
	int			m_FPS;				// �t���[�����J�E���g�p

	//-------- �Q�[���p�I�u�W�F�N�g
	D3DXMATRIX	m_world;	// ���b�V���\���p
	CMesh		m_mesh;		// ���b�V�� �I�u�W�F�N�g
	CShader		m_shader;	// �V�F�[�_
	D3DXVECTOR3	m_angle;
	CRenderTarget m_target;
	float m_focus;
public:
	CScene();
	virtual ~CScene();

	static CScene* Create(CGraphics* pGraph);
	void Release();
	void Render();
	void Update();
	void SetFPS(int nFPS) {m_FPS = nFPS;}
	void AddDebugStr(LPCTSTR psz) {lstrcat(m_szDebug, psz);}

private:
	bool Initialize(CGraphics* pGraph);
	void Finalize();
	void Draw();
};

//=======================================================================================
//	End of File
//=======================================================================================