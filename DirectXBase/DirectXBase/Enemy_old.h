// �G�@�N���X��`

#pragma once

#include "MeshObj.h"

class CEnemy : public CMeshObj
{
private:
	static CMesh		m_mesh;
	static bool			m_bLoad;
	static CMeshObj*	m_pPlayer;

public:
	CEnemy(CScene* pScene);
	virtual ~CEnemy(void);

	virtual void Init();		// ������
	virtual void Fin();			// �I������
	virtual void Update();		// �X�V
	virtual void DrawAlpha();	// �����������`��
};