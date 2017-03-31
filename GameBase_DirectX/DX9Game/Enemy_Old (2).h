// ���@�N���X��`
#pragma once

#include "MeshObj.h"
#include "Land.h"

class CEnemy : public CMeshObj
{
private:
	static CHierarMesh	m_mesh;
	static bool		m_bLoad;
	CLand*			m_pLand;
	D3DXVECTOR3		m_angle;
	float			m_fSpeed;

	DWORD			m_dwPrev;
	double			m_dAnimTime;

public:
	CEnemy(CSceneBase* pScene);
	virtual ~CEnemy(void);

	virtual void Init();		// ������
	virtual void Fin();			// �I������
	virtual void Update();		// �X�V
	virtual void Draw();		// �`��
};