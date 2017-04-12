// 地面クラス実装
#include "Land.h"
#include "SceneBase.h"

// 定数
#define PATH_MESHLAND	_T("../data/model/land2.x")

// コンストラクタ
CLand::CLand(CSceneBase* pScene) :
	CMeshObj(pScene),
	m_bLoad(false)
{
	m_uID = ID_LAND;
	m_pScene->Add(this);
}

// デストラクタ
CLand::~CLand(void)
{
}

// 初期化
void CLand::Init()
{
	if (!m_bLoad) {
		m_bLoad = m_mesh.Initialize(PATH_MESHLAND);
	}
	if (m_bLoad) {
		SetMesh(&m_mesh);
	}
}

// 解放
void CLand::Fin()
{
	if (m_bLoad) {
		m_bLoad = false;
		SetMesh(NULL);
		m_mesh.Finalize();
	}
}