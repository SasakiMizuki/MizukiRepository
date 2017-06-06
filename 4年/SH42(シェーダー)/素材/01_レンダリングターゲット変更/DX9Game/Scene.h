//=======================================================================================
//
//	  �Q�[���V�[�� �N���X��`
//
//=======================================================================================
#pragma once

#include "Graphics.h"
#include "Mesh.h"	// CMesh�N���X��`
#include "RenderTarget.h"
#include "BoxMesh.h"

class CScene
{
private:
	CGraphics*	m_pGraph;			// �O���t�B�b�N�f�o�C�X

	TCHAR		m_szDebug[1024];	// �f�o�b�O�p������
	int			m_FPS;				// �t���[�����J�E���g�p

	//-------- �Q�[���p�I�u�W�F�N�g
	D3DXMATRIX	m_world;// ���b�V���\���p
	CMesh		m_mesh;	// ���b�V�� �I�u�W�F�N�g
	D3DXVECTOR3	m_angle;// ���b�V���\���p

	CRenderTarget	m_target;	// �����_�����O�^�[�Q�b�g�ؑ�
	CBoxMesh		m_box;		// �e�N�X�`����\�郂�f��
	D3DXMATRIX		m_boxWorld;	// �e�N�X�`����\�郂�f���p
	D3DXVECTOR3		m_boxAngle;	// �e�N�X�`����\�郂�f���p

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