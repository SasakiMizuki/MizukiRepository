// 敵機クラス実装

#include "Enemy.h"
#include "Input.h"

#define PATH_MESHENEMY	_T("../data/model/J35/J35.x")
#define SPEED			4.0f

CMesh		CEnemy::m_mesh;
bool		CEnemy::m_bLoad = false;
CMeshObj*	CEnemy::m_pPlayer = NULL;

// コンストラクタ
CEnemy::CEnemy(CScene* pScene) :
	CMeshObj(pScene)
{
	m_uID = ID_ENEMY;
}

// デストラクタ
CEnemy::~CEnemy(void)
{
}

// 初期化
void CEnemy::Init()
{
	CMeshObj::Init();

	if (!m_bLoad) {
		m_bLoad = m_mesh.Initialize(PATH_MESHENEMY);
	}
	if (m_bLoad) {
		SetMesh(&m_mesh);
	}
	// 自機へのポインタを取得しておく
	if (!m_pPlayer) {
		m_pPlayer = (CMeshObj*)Find(ID_PLAYER);
	}
}

// 終了処理
void CEnemy::Fin()
{
	CMeshObj::Fin();

	SetMesh(NULL);
	if (m_bLoad) {
		m_bLoad = false;
		m_mesh.Finalize();
	}
}

// 更新

void CEnemy::Update()
{
	UpdateDamage();

	// ワールドマトリックスからローカル軸、座標抽出
	D3DXMATRIX world = GetWorld();
	D3DXVECTOR3 vX, vY, vZ, vP;
	vX = D3DXVECTOR3(world._11, world._12, world._13);
	vY = D3DXVECTOR3(world._21, world._22, world._23);
	vZ = D3DXVECTOR3(world._31, world._32, world._33);
	vP = D3DXVECTOR3(world._41 ,world._42, world._43);
	world._41 = world._42 = world._43 = 0.0f;// 一時的に原点へ

	// ターゲットの方向取得
	D3DXVECTOR3 vT;
	if (m_pPlayer) {
		vT = m_pPlayer->GetPos() - vP;
	} else {
		vT = vZ * 1000.0f;
	}
	D3DXVec3Normalize(&vT, &vT);

	// ターゲットは前にいる?
	float fForward = D3DXVec3Dot(&vT, &vZ);
	// ターゲットは上にいる?
	float fUp = D3DXVec3Dot(&vT, &vY);
	// ターゲットは右にいる?
	float fRight = D3DXVec3Dot(&vT, &vX);

	// 回転角更新
	D3DXVECTOR3 angle(0.0f, 0.0f, 0.0f);
	float fAdjust = cosf(D3DXToRadian(85));
	if (fRight > fAdjust) {			// 右?
		angle.z = -1.5f;			//  右旋回
	} else if (fRight < -fAdjust) {	// 左?
		angle.z = 1.5f;				//  左旋回
	} else {						// 前後上下
		if (fUp < 0.0f) {			// 下?
			angle.z = 1.5f;			//  左旋回
		}
	}
	if (fForward > 0.0f) {			// 前?
		if (fUp > fAdjust) {		// 上?
			angle.x = -1.0f;		//  上昇
		} else if (fUp < -fAdjust) {// 下?
			angle.x = 1.0f;			//  下降
		}
	} else {					// 上下左右か後ろ
		angle.x = -1.0f;			//  上昇
	}
	D3DXMATRIX rot_x, rot_z;
	D3DXMatrixRotationAxis(&rot_z, &vZ, D3DXToRadian(angle.z));
	D3DXMatrixRotationAxis(&rot_x, &vX, D3DXToRadian(angle.x));
	world *= (rot_z * rot_x);
	// 移動
	if (!CInput::GetKeyPress(DIK_RSHIFT)) {
		vP += (vZ * SPEED);
	}
	world._41 = vP.x;
	world._42 = vP.y;
	world._43 = vP.z;
	// ワールドマトリックスを更新
	SetWorld(world);
}

void CEnemy::DrawAlpha()
{
	CMeshObj::DrawAlpha();
	if (m_pMesh) {
		D3DCOLORVALUE cv = m_pMesh->GetBColor();
		m_pMesh->SetBColor(m_cvBColor);
		//m_pMesh->DrawAABB(m_world);
		m_pMesh->DrawBSphere(m_world);
		m_pMesh->SetBColor(cv);
	}
}