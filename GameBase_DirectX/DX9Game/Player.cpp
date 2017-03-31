// 自機クラス実装
#include "Player.h"
#include "Input.h"
#include "Debug.h"

//#define PATH_MESHPLAYER	_T("../data/model/player.x")
#define PATH_MESHPLAYER	_T("../data/model/tiny_4anim.x")
#define SPEED			10.0f
#define ACCEL			0.1f
#define BRAKE			0.2f

#define START_WALK		0.5
#define END_WALK		1.5
#define START_RUN		2.0
#define END_RUN			3.0

CHierarMesh	CPlayer::m_mesh;
bool	CPlayer::m_bLoad = false;

// コンストラクタ
CPlayer::CPlayer(CSceneBase* pScene) :
	CMeshObj(pScene),
	m_pLand(NULL),
	m_angle(0.0f, 0.0f, 0.0f),
	m_fSpeed(0.0f),
	m_dAnimTime(0.0)
{
	m_uID = ID_PLAYER;
}

// デストラクタ
CPlayer::~CPlayer(void)
{
}

// 初期化
void CPlayer::Init()
{
	CMeshObj::Init();

	if (!m_bLoad) {
		m_bLoad = m_mesh.Initialize(PATH_MESHPLAYER);
		if (m_bLoad) {
			SetMesh(&m_mesh);
			m_mesh.SwitchAnimSet(3);
		}
	}
	m_pLand = (CLand*)Find(ID_LAND);
}

// 終了処理
void CPlayer::Fin()
{
	CMeshObj::Fin();

	if (m_bLoad) {
		SetMesh(NULL);
		m_bLoad = false;
		m_mesh.Finalize();
	}
}

// 更新
void CPlayer::Update()
{
	bool bRot = false;
	if (CInput::GetKeyPress(DIK_LEFT) || CInput::GetKeyPress(DIK_A)) {
		m_angle.y -= 5.0f;
		if (m_angle.y < -180.0f) {
			m_angle.y += 360.0f;
		}
		bRot = true;
	}
	if (CInput::GetKeyPress(DIK_RIGHT) || CInput::GetKeyPress(DIK_D)) {
		m_angle.y += 5.0f;
		if (m_angle.y >= 180.0f) {
			m_angle.y -= 360.0f;
		}
		bRot = true;
	}
	if (CInput::GetKeyPress(DIK_UP) || CInput::GetKeyPress(DIK_W)) {
		m_fSpeed += ACCEL;
		if (m_fSpeed > SPEED) {
			m_fSpeed = SPEED;
		}
	}
	if (CInput::GetKeyPress(DIK_DOWN) || CInput::GetKeyPress(DIK_S)) {
		m_fSpeed -= BRAKE;
		if (m_fSpeed < 0.0f) {
			m_fSpeed = 0.0f;
		}
	}
	D3DXVECTOR3 pos = GetPos();
	D3DXMatrixRotationY(&m_world, D3DXToRadian(m_angle.y));
	D3DXVECTOR3 vZ;
	D3DXVec3TransformNormal(&vZ, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &m_world);
	pos += vZ * m_fSpeed;
	D3DXVECTOR3 vCross;
	if (m_pLand && m_pLand->Intersect(D3DXVECTOR3(pos.x, pos.y + 5000.0f, pos.z),
		D3DXVECTOR3(0.0f, -1.0f, 0.0f), true, &vCross)) {
		pos.y = vCross.y;
	} else {
		pos.y = 0.0f;
	}
	SetPos(pos);
	if (m_fSpeed > SPEED / 2) {
		m_mesh.SwitchAnimSet(1);
	} else if (m_fSpeed > 0.0f || bRot) {
		m_mesh.SwitchAnimSet(2);
	} else {
		m_mesh.SwitchAnimSet(3);
	}
	/*
	DWORD dwNow = ::timeGetTime();
	double dSlice = (dwNow - m_dwPrev) / 1000.0;
	m_dwPrev = dwNow;
	if (m_fSpeed > SPEED / 2) {
		if (m_dAnimTime < START_RUN || m_dAnimTime >= END_RUN)
			m_dAnimTime = START_RUN;
		else {
			m_dAnimTime += dSlice;
			if (m_dAnimTime >= END_RUN)
				m_dAnimTime = START_RUN + 2/60.0;
		}
	} else if (m_fSpeed > 0.0f || bRot) {
		if (m_dAnimTime < START_WALK || m_dAnimTime >= END_WALK)
			m_dAnimTime = START_WALK;
		else {
			m_dAnimTime += dSlice;
			if (m_dAnimTime >= END_WALK)
				m_dAnimTime = START_WALK + 2/60.0;
		}
	} else {
		m_dAnimTime = 0.0f;
	}*/
}

// 描画
void CPlayer::Draw()
{
	//m_mesh.SetTime(m_dAnimTime);
	CGraphics::GetDevice()->SetRenderState(D3DRS_SPECULARENABLE, FALSE);	// 鏡面反射を無効
	D3DXMATRIX mRotX;
	D3DXMatrixRotationX(&mRotX, D3DXToRadian(-90));
	D3DXMATRIX mWorld = mRotX * m_world;
	m_mesh.Draw(mWorld);
	CGraphics::GetDevice()->SetRenderState(D3DRS_SPECULARENABLE, TRUE);	// 鏡面反射を有効
}