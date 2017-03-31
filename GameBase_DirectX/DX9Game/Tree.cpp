#include "Tree.h"
#include "SceneBase.h"

// íËêî
#define PATH_MESHTREE	_T("../data/model/tree.x")

CMesh	CTree::m_mesh;
bool	CTree::m_bLoad;

CTree::CTree(CSceneBase* pScene, D3DXVECTOR3 position) :
CMeshObj(pScene){
	m_world._11 = m_world._22 = m_world._33 = 60.0f;
	m_world._41 = position.x;
	m_world._42 = position.y;
	m_world._43 = position.z;
	m_uID = ID_TREE;
}


CTree::~CTree() {
}

void CTree::Init() {
	if (!m_bLoad) {
		m_bLoad = m_mesh.Initialize(PATH_MESHTREE);
	}
	if (m_bLoad) {
		SetMesh(&m_mesh);
	}
}

void CTree::Fin() {
	if (m_bLoad) {
		m_bLoad = false;
		SetMesh(NULL);
		m_mesh.Finalize();
	}
}