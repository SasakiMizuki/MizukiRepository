// メッシュ オブジェクト クラス実装
#include "MeshObj.h"
#include "SceneBase.h"

// コンストラクタ
CMeshObj::CMeshObj(CSceneBase* pScene) :
	C3DObj(pScene),
	m_pMesh(NULL)
{
	m_uID = ID_MESHOBJ;
}

// デストラクタ
CMeshObj::~CMeshObj(void)
{
}

// 初期化
void CMeshObj::Init()
{
}

// 更新
void CMeshObj::Update()
{
	C3DObj::Update();
}

// 表示
void CMeshObj::Draw()
{
	if (m_pMesh) {
		m_pMesh->Draw(m_world);
	}
}

// 終了処理
void CMeshObj::Fin()
{
}

// レイとの当たり判定
bool CMeshObj::Intersect(D3DXVECTOR3& L0, D3DXVECTOR3& L1, bool bRay,
	D3DXVECTOR3* pCross, D3DXVECTOR3* pNormal)
{
	if (m_pMesh)
		return m_pMesh->Intersect(L0, L1, bRay, pCross, pNormal);
	return false;
}

void CMeshObj::SetMesh(CMesh* pMesh) {
	m_pMesh = pMesh;
	if (m_pMesh) {
		SetRadius(m_pMesh->GetRadius());
		SetCenter(m_pMesh->GetCenter());
		SetBBox(m_pMesh->GetBBox());
	}
}

DWORD CMeshObj::GetPieceCount() {
	if (m_pMesh) {
		return m_pMesh->GetPieceCount();
	}
	return 0;
}

void CMeshObj::GetInitPiece(PIECE* pPiece) {
	if (m_pMesh) {
		m_pMesh->GetInitPiece(pPiece);
	}
}