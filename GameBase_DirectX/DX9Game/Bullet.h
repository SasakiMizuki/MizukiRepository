// �e�N���X��`
#pragma once
#include "MeshObj.h"

class CBullet : public CMeshObj
{
protected:
	static CMesh	m_mesh;		// �e�\���p���b�V��
	static bool		m_bLoad;	// ���b�V���Ǎ��t���O
	CMeshObj*		m_pGunner;	// ���˂����@��
	DWORD			m_dwLife;	// ��������

public:
	CBullet(CScene* pScene);
	virtual ~CBullet(void);

	static bool LoadMesh();		// ���b�V���Ǎ�
	static void ReleaseMesh();	// ���b�V�����
	static void Fire(CMeshObj* pGunner);	// ����
	virtual void Update();		// �X�V
	virtual void DrawAlpha();	// �����������\��
};