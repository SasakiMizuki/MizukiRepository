#pragma once
#include "MeshObj.h"
#include "Jintai.h"
#include "Particle.h"
class CSword :
	public CMeshObj
{
private:
	static CMesh	m_mesh;
	static bool		m_bLoad;
	D3DXVECTOR3		m_angle;
	TParts			m_Parts;
	CJintai*		m_pPlayer;
	CEnemy*			m_pEnemy;
	CParticle*		m_pParticle;
public:
	CSword(CSceneBase* pScene);
	~CSword();

	void Init();
	void Fin();
	void Update();
	void PostUpdate();
	void DrawAlpha();
};
