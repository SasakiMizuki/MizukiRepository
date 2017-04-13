#include "Fire.h"
#include "Jintai.h"

#define PATH_MESHFIRE	_T("../data/model/fire_collision.x")
#define SPEED			5.0f

CMesh	CFire::m_mesh;
bool	CFire::m_bLoad = false;

CFire::CFire(CSceneBase* pScene, D3DXMATRIX world) :
CMeshObj(pScene){

	if (!m_bLoad) {
		m_bLoad = m_mesh.Initialize(PATH_MESHFIRE);
	}
	if (m_bLoad) {
		SetMesh(&m_mesh);
	}
	m_uID = ID_FIRE;
	m_world = world;
	m_world._42 += 70.0f;
	m_bLive = true;
	m_nLifeTimer = 180;
	m_fSpeed = 5.0f;
	m_pPlayer = (CJintai*)Find(ID_JINTAI);
}


CFire::~CFire() {
}

void CFire::Init() {
	CMeshObj::Init();
	m_fHP = 100.0f;

}
void CFire::Fin() {
	CMeshObj::Fin();

	if (m_bLoad) {
		SetMesh(NULL);
		m_bLoad = false;
		m_mesh.Finalize();
	}
}
void CFire::Update() {
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 vZ;
	D3DXVec3TransformNormal(&vZ,
		&D3DXVECTOR3(0.0f, 0.0f, 1.0f), &m_world);
	pos += vZ * m_fSpeed;
	SetPos(pos);
	m_nLifeTimer --;
	if (m_nLifeTimer < 0.0f)
		m_bLive = false;
	if (CollisionOBB(m_pPlayer) && m_pPlayer->GetMotion() != ANIM_ROLLING) {
		if (!m_pPlayer->GetDamage()) {
			m_pPlayer->SetDamage(180);
			m_pPlayer->ChangeHP(-25);
		}

	}
}

void CFire::DrawAlpha() {
	//m_pMesh->DrawOBB(m_world);
}