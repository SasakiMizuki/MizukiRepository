// 弾クラス実装
#include "Bullet.h"
#include "Scene.h"

// 定数
#define PATH_MESHBULLET	_T("../data/model/bullet.x")
#define BULLET_SPEED	20.0f
#define BULLET_DAMAGE	1
#define BULLET_LIFE		180

// 静的変数
CMesh CBullet::m_mesh;
bool CBullet::m_bLoad = false;

// コンストラクタ
CBullet::CBullet(CScene* pScene) :
	CMeshObj(pScene),
	m_pGunner(NULL),
	m_dwLife(BULLET_LIFE)
{
	m_uID = ID_BULLET;
}

// デストラクタ
CBullet::~CBullet(void)
{
}

// メッシュ読込
bool CBullet::LoadMesh()
{
	ReleaseMesh();
	m_bLoad = m_mesh.Initialize(PATH_MESHBULLET);
	return m_bLoad;
}

// メッシュ解放
void CBullet::ReleaseMesh()
{
	if (m_bLoad) {
		m_bLoad = false;
		m_mesh.Finalize();
	}
}

// 発射
void CBullet::Fire(CMeshObj* pGunner)
{
	if (!pGunner || !m_bLoad) return;
	CBullet* pBullet = new CBullet(pGunner->GetScene());
	pBullet->SetMesh(&m_mesh);
	pBullet->m_pGunner = pGunner;
	pBullet->SetPos(pGunner->GetPos());
	pBullet->SetWorld(pGunner->GetWorld());
	D3DXVECTOR3 vSpeed = pGunner->GetForward();
	pBullet->SetSpeed(vSpeed * BULLET_SPEED);
}

// 更新
void CBullet::Update()
{
	// 生存時間チェック、更新
	if (!m_dwLife) {
		delete this;
		return;
	}
	--m_dwLife;
	// 移動
	m_world._41 += m_speed.x;
	m_world._42 += m_speed.y;
	m_world._43 += m_speed.z;
	// 当たり判定
	CMeshObj* pObj = (CMeshObj*)Find(0);
	CMeshObj* pNext = NULL;
	for (; pObj; pObj = pNext) {
		pNext = (CMeshObj*)pObj->GetNext();
		switch (pObj->GetID()) {
		case ID_ENEMY:
		case ID_PLAYER:
			if (pObj == m_pGunner) {
				continue;
			}
			break;
		case ID_MISSILE:
			break;
		case ID_BULLET:
			if (pObj == this) {
				continue;
			}
			break;
		default:
			continue;
		}
		// 当たり判定
		if (CollisionBSphere(pObj)) {
			pObj->SetDamage(BULLET_DAMAGE);
			delete this;
			break;
		}
	}
}

// 半透明部分表示
void CBullet::DrawAlpha()
{
	CMeshObj::DrawAlpha();
	if (m_bLoad) {
		D3DCOLORVALUE cv = m_mesh.GetBColor();
		m_mesh.SetBColor(m_cvBColor);
		m_mesh.DrawBSphere(m_world);
		m_mesh.SetBColor(cv);
	}
}