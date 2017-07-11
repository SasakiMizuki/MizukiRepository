// 自機クラス実装

#include "Enemy.h"
#include "Input.h"
#include "Jintai.h"
#include "SceneBase.h"

#define PATH_MESHENEMY	_T("../data/model/dragon.x")
#define SPEED			5.0f

const int MOVE_INTERVAL(60);
const int ATTACK_TIME(20);
const float ENEMY_POWER(10.0f);

CMesh	CEnemy::m_mesh;
bool	CEnemy::m_bLoad = false;

// コンストラクタ
CEnemy::CEnemy(CSceneBase* pScene) :
	CMeshObj(pScene),
	m_pLand(NULL),
	m_angle(0.0f, 0.0f, 0.0f),
	m_fSpeed(0.0f)
{
	m_uID = ID_ENEMY;
	m_pFire = NULL;
	m_pScene->Add(this);
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
		m_bLoad = m_mesh.Initialize(PATH_MESHENEMY, true);
	}
	if (m_bLoad) {
		SetMesh(&m_mesh);
	}
	m_pPlayer = (CJintai*)Find(ID_JINTAI);
	m_pLand = (CLand*)Find(ID_LAND);
	m_fHP = 100.0f;

	m_world._41 = m_world._43 = 200.0f;
	m_nMotion = ENEMY_STUND;
}

// 終了処理
void CEnemy::Fin()
{
	CMeshObj::Fin();

	if (m_bLoad) {
		SetMesh(NULL);
		m_bLoad = false;
		m_mesh.Finalize();
	}
	SAFE_DELETE(m_pFire);
}

// 更新

void CEnemy::Update()
{
	static int nMoveCount = MOVE_INTERVAL;
	C3DObj::Update();

	if (!(&m_pMesh)) {
		int a = 0;
	}
	//SetMesh(&m_mesh);
	if (m_pPlayer && m_nMotion == ENEMY_STUND) {
		m_fSpeed = 0.0f;
		m_angle.y = (float)D3DXToDegree(atan2((m_pPlayer->GetWorld()._41 - m_world._41), (m_pPlayer->GetWorld()._43 - m_world._43)));
		//nMoveCount--;
	}


	switch (m_nMotion) {
	case ENEMY_STUND:
		if (nMoveCount < 0.0f) {
			if (rand() % 2) {
				m_nMotion = ENEMY_ATTACK;
				nMoveCount = 70;
				m_nMotionCounter = ATTACK_TIME;
				m_bAttack = true;
			} else {
				if (!m_pFire) {
					m_nMotion = ENEMY_FIRE;
					nMoveCount = 240;
					m_bFire = true;
				} else {
					nMoveCount = 20;
				}
			}
		}
		break;
	case ENEMY_ATTACK:
		UpdateAttack();
		break;
	case ENEMY_FIRE:
		UpdateFire();
		break;
	default:
		break;
	}

	D3DXVECTOR3 pos = GetPos();
	D3DXMatrixRotationY(&m_world, D3DXToRadian(m_angle.y));
	D3DXVECTOR3 vZ;
	D3DXVec3TransformNormal(&vZ,
&D3DXVECTOR3(0.0f, 0.0f, 1.0f), &m_world);
	pos += vZ * m_fSpeed;
	if (pos.x < -2000.0f)
		pos.x = -2000.0f;
	else if (pos.x > 2000.0f)
		pos.x = 2000.0f;
	if (pos.z < -2000.0f)
		pos.z = -2000.0f;
	else if (pos.z > 2000.0f)
		pos.z = 2000.0f;

	SetPos(pos);

	D3DXVECTOR3 vCross;
	if (m_pLand && m_pLand->Intersect(D3DXVECTOR3(pos.x, pos.y + 5000.0f, pos.z),
		D3DXVECTOR3(0.0f, -1.0f, 0.0f), true, &vCross)) {
		pos.y = vCross.y;
	} else {
		pos.y = 0.0f;
	}
	if (pos.x < -2000.0f)
		pos.x = -2000.0f;
	else if (pos.x > 2000.0f)
		pos.x = 2000.0f;
	if (pos.z < -2000.0f)
		pos.z = -2000.0f;
	else if (pos.z > 2000.0f)
		pos.z = 2000.0f;

	SetPos(pos);

	if (m_pFire) {
		if (!(m_pFire->GetLive())) {
			delete m_pFire;
			m_pFire = NULL;
		}
	}
}

void CEnemy::DrawAlpha() {

}

void CEnemy::UpdateAttack() {
	m_fSpeed = 5.0f;
	if (!(--m_nMotionCounter)) {
		m_nMotion = ENEMY_STUND;
	}
	if (CollisionOBB(m_pPlayer) && m_pPlayer->GetMotion() != ANIM_ROLLING) {
		if (!m_pPlayer->GetDamage()) {
			m_pPlayer->SetDamage(180);
			m_pPlayer->ChangeHP(-ENEMY_POWER);
			//CExplosion* pExp = new CExplosion(GetScene());
			//pExp->Start(this);
		}
			
	}
}

void CEnemy::UpdateFire() {
	m_pFire = new CFire(m_pScene,m_world);
	m_nMotion = ENEMY_STUND;
}