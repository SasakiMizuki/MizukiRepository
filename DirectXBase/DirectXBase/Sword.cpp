#include "Sword.h"
#include "SceneBase.h"

#define PATH_MESHSWORD	_T("../data/model/sword.x")

const float SWORD_POWER(10.0f);

CMesh	CSword::m_mesh;
bool	CSword::m_bLoad = false;

CSword::CSword(CSceneBase* pScene):
CMeshObj(pScene){
	m_uID = ID_SWORD;
	m_pParticle = NULL;
	m_pScene->Add(this);
}


CSword::~CSword() {
}

void CSword::Init() {
	CMeshObj::Init();

	if (!m_bLoad) {
		m_bLoad = m_mesh.Initialize(PATH_MESHSWORD, true);
	}
	if (m_bLoad) {
		SetMesh(&m_mesh);
	}
	m_pPlayer = (CJintai*)Find(ID_JINTAI);
	m_pEnemy = (CEnemy*)Find(ID_ENEMY);

	if (!m_pParticle) {
		m_pParticle = new CParticle(m_pScene);
		m_pParticle->PostInit();
	}
}

void CSword::Fin() {
	CMeshObj::Fin();

	if (m_bLoad) {
		SetMesh(NULL);
		m_bLoad = false;
		m_mesh.Finalize();
	}
	/*if (m_pParticle) {
		delete m_pParticle;
		m_pParticle = NULL;
	}*/

}

void CSword::Update() {
	m_Parts = m_pPlayer->GetHandData();
	D3DXVECTOR3 vec = m_pPlayer->GetAngle();

	D3DXVECTOR3 pos = D3DXVECTOR3(m_Parts.m_combine._41, m_Parts.m_combine._42, m_Parts.m_combine._43);
	//D3DXMatrixRotationX(&m_world, m_Parts.m_combine._14);
	//D3DXMatrixRotationZ(&m_world, (m_Parts.m_combine._34));
	D3DXMatrixRotationY(&m_world, D3DXToRadian(vec.y)); 
	D3DXQuaternionRotationYawPitchRoll(&m_Parts.m_q, D3DXToRadian(vec.x), D3DXToRadian(vec.y), D3DXToRadian(vec.z));
	D3DXMatrixRotationQuaternion(&m_Parts.m_matrix, &m_Parts.m_q);

	SetPos(pos);

	if (m_pPlayer->GetMotion() == ANIM_ATTACK) {
		if (CollisionOBB(m_pEnemy)) {
			if (!m_pEnemy->GetDamage()) {
				m_pEnemy->SetDamage(180);
				m_pEnemy->ChangeHP(-SWORD_POWER);
				m_pParticle->ChangeUse(true, m_pEnemy->GetWorld());
				//CExplosion* pExp = new CExplosion(GetScene());
				//pExp->Start(this);
			}
		}
	}
	m_pParticle->Update();
}

void CSword::PostUpdate() {
}

void CSword::DrawAlpha() {
	m_pParticle->DrawAlpha();
}