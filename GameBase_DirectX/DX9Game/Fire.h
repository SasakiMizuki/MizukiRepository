#pragma once
#include "MeshObj.h"

class CJintai;
class CFire :
	public CMeshObj
{
private:
	static CMesh	m_mesh;
	static bool		m_bLoad;
	float			m_fSpeed;
	CJintai*		m_pPlayer;
	int				m_nLifeTimer;
	bool			m_bLive;
public:
	CFire(CSceneBase* pScene, D3DXMATRIX world);
	virtual ~CFire();

	virtual void Init();		// ‰Šú‰»
	virtual void Fin();			// I—¹ˆ—
	virtual void Update();		// XV
	//virtual void Draw();
	virtual void DrawAlpha();
	bool GetLive() { return m_bLive; }
};

