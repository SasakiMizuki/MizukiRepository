// ���@�N���X��`
#pragma once

#include "MeshObj.h"
#include "Land.h"

class CPlayer : public CMeshObj
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
	CPlayer(CSceneBase* pScene);
	virtual ~CPlayer(void);

	virtual void Init();		// ������
	virtual void Fin();			// �I������
	virtual void Update();		// �X�V
	virtual void Draw();		// �`��
};