//=======================================================================================
//
//	  �Q�[���V�[�� �N���X��`
//
//=======================================================================================
#pragma once

#include <map>
#include "Graphics.h"
#include "C3DObj.h"
#include "C2DObj.h"
#include "RenderTarget.h"
#include "Mesh.h"
class CSceneBase
{
protected:
	CGraphics*	 m_pGraph;			// �O���t�B�b�N�f�o�C�X
	//CObjectBase* m_pObj;				// �I�u�W�F�N�g�擪
	TCHAR		m_szDebug[1024];	// �f�o�b�O�p������
	int			m_FPS;				// �t���[�����J�E���g�p

	DWORD		m_dwTick;			// �o�ߎ���(�t���[����)
	std::map<int, CObjectBase*> m_mObj;
	CRenderTarget m_target;
	CShader	m_shader;

	bool		m_bSceneChange;		// �t�F�[�h���ҋ@�pflag
	unsigned int m_nNumberOfObj;	// ���ݐ����Ă���(�}�b�v�ɓ����Ă���)�I�u�W�F�N�g�̑���

public:
	CSceneBase();
	virtual ~CSceneBase();

	virtual CSceneBase* Create(CGraphics* pGraph);
	virtual void Release();
	virtual void Render();
	virtual void Update();
	virtual void SetFPS(int nFPS) {m_FPS = nFPS;}
	virtual void AddDebugStr(LPCTSTR psz) {lstrcat(m_szDebug, psz);}
	
	virtual void Add(CObjectBase* pObj);
	virtual void Del(int nNumber);
	virtual CObjectBase* Find(UINT uID, int nNumber);
	virtual void InitObj();
	virtual void FinObj();
	virtual void UpdateObj();
	virtual void DrawObj();
	//virtual DWORD GetTick();

	virtual bool Initialize(CGraphics* pGraph);
	virtual void Finalize();
	virtual void Draw();
};

//=======================================================================================
//	End of File
//=======================================================================================