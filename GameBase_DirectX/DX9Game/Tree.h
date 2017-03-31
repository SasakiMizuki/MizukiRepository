#pragma once
#include "MeshObj.h"
class CTree :
	public CMeshObj
{
private:
	static CMesh	m_mesh;
	static bool		m_bLoad;


public:
	CTree(CSceneBase* pScene, D3DXVECTOR3 position);
	~CTree();
	void Init();
	void Fin();
};

