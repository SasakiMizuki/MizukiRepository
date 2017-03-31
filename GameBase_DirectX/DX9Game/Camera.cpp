// �J���� �N���X����
#include "Camera.h"
#include "Sky.h"
#include "GameWnd.h"
#include "Input.h"
#include "define.h"
#include "SceneBase.h"

// �Œ�J�����ʒu
#define CAMERA_POSX		0.0f
#define CAMERA_POSY		60.0f
#define CAMERA_POSZ		250.0f
// �Œ�J���������_
#define LOOK_POSX		0.0f
#define LOOK_POSY		60.0f
#define LOOK_POSZ		0.0f
// �Œ�J����������x�N�g��
#define UP_DIRX			0.0f
#define UP_DIRY			1.0f
#define UP_DIRZ			0.0f

// �R���X�g���N�^
CCamera::CCamera(CSceneBase* pScene) :
	C3DObj(pScene),
	m_pSky(NULL),
	m_pPlayer(NULL),
	m_fFovy(FOVY),
	m_fAspect((float)SCREEN_WIDTH / SCREEN_HEIGHT),
	m_fZNear(NEAR_CLIP),
	m_fZFar(FAR_CLIP),
	m_cp(CP_TPVIEW),
	m_fTime(0.0f)
{
	m_uID = ID_CAMERA;

	m_pos = D3DXVECTOR3(CAMERA_POSX, CAMERA_POSY, CAMERA_POSZ);
	m_pos2 = m_pos;
	m_at = D3DXVECTOR3(LOOK_POSX, LOOK_POSY, LOOK_POSZ);
	m_at2 = m_at;
	m_up = D3DXVECTOR3(UP_DIRX, UP_DIRY, UP_DIRZ);
	m_up2 = m_up;
	m_pScene->Add(this);
}

// �f�X�g���N�^
CCamera::~CCamera(void)
{
}

// ������
void CCamera::Init()
{
	D3DXMATRIX world;
	D3DXMatrixTranslation(&world, CAMERA_POSX, CAMERA_POSY, CAMERA_POSZ);
	SetWorld(world);
	m_pSky = (CSky*)Find(ID_SKY);
	m_pPlayer = (CJintai*)Find(ID_JINTAI);
	m_pEnemy = (CEnemy*)Find(ID_ENEMY);
}

// �X�V
void CCamera::Update()
{
	// �������Ȃ�
}

// �X�V�㏈��
void CCamera::PostUpdate()
{
	D3DXVECTOR3 vX, vY, vZ, vP; 


	m_fTime -= 1.0f/60.0f;
	if (m_fTime < 0.0f) {
		m_fTime = 0.0f;
	}
	if (CInput::GetKeyTrigger(DIK_2) || CInput::GetKeyTrigger(DIK_NUMPAD2)) {
		m_cp = CP_FIXED;
		m_fTime = 1.0f;
	}
	if (CInput::GetKeyTrigger(DIK_1) || CInput::GetKeyTrigger(DIK_NUMPAD1)) {
		m_cp = CP_FPVIEW;
		m_fTime = 1.0f;
	}
	if (CInput::GetKeyTrigger(DIK_3) || CInput::GetKeyTrigger(DIK_NUMPAD3)) {
		m_cp = CP_TPVIEW;
		m_fTime = 1.0f;
	}
	if (m_pPlayer) {
		float Distance = sqrtf(power(m_pEnemy->GetWorld()._43 - m_pPlayer->GetWorld()._43) + power(m_pEnemy->GetWorld()._41 - m_pPlayer->GetWorld()._41));
		switch (m_cp) {
		case CP_FPVIEW:
			D3DXVec3TransformCoord(&m_pos2,
				&D3DXVECTOR3(0.0f, 160.0f, 55.0f),
				&m_pPlayer->GetPlayerWorld());
			D3DXVec3TransformCoord(&m_at2,
				&D3DXVECTOR3(0.0f, 160.0f, 100.0f),
				&m_pPlayer->GetWorld());
			D3DXVec3TransformNormal(&m_up2,
				&D3DXVECTOR3(0.0f, 1.0f, 0.0f),
				&m_pPlayer->GetWorld());
			break;
		case CP_TPVIEW:
			D3DXVec3TransformCoord(&m_pos2,
				&D3DXVECTOR3(0.0f, 360.0f, -380.0f),
				&m_pPlayer->GetPlayerWorld());
		//	m_pos2.x = (100.0f*m_pEnemy->GetWorld()._41 + (Distance + (-100.0f))*m_pPlayer->GetWorld()._41) / Distance;
		//	m_pos2.z = (100.0f*m_pEnemy->GetWorld()._43 + (Distance + (-100.0f))*m_pPlayer->GetWorld()._43) / Distance;
		//	m_pos2.y = 200.0f;
			D3DXVec3TransformCoord(&m_at2,
				&D3DXVECTOR3(0.0f, 200.0f, 0.0f),
				//&m_pPlayer->GetWorld());
				&m_pEnemy->GetWorld());
			D3DXVec3TransformNormal(&m_up2,
				&D3DXVECTOR3(0.0f, 1.0f, 0.0f),
				&m_pPlayer->GetWorld());
			break;
		case CP_FIXED:
		default:
			m_at2 = m_pPlayer->GetPos();
			m_up2 = D3DXVECTOR3(UP_DIRX, UP_DIRY, UP_DIRZ);
			break;
		}
		float fNew;
		fNew = 1.0f - m_fTime;
		m_pos = m_pos * m_fTime + m_pos2 * fNew;
		m_at = m_at * m_fTime + m_at2 * fNew;
		m_up = m_up * m_fTime + m_up2 * fNew;
		D3DXMatrixLookAtLH(&m_view,
			&m_pos, &m_at, &m_up);
		SetPos(m_pos);
	}

	D3DXMatrixPerspectiveFovLH(&m_proj, m_fFovy, m_fAspect, m_fZNear, m_fZFar);
	if (m_pSky) {
		m_pSky->PostUpdate();
	}
}

// �`��O����
void CCamera::PreDraw()
{
	LPDIRECT3DDEVICE9 pD = CGraphics::GetDevice();
	pD->SetTransform(D3DTS_PROJECTION, &m_proj);
	pD->SetTransform(D3DTS_VIEW, &m_view);
	if (m_pSky) {
		m_pSky->PreDraw();
	}
}

// �`��
void CCamera::Draw()
{
	// �������Ȃ�
}

// �������`��
void CCamera::DrawAlpha()
{
	// �������Ȃ�
}

// �I������
void CCamera::Fin()
{
	// �Ȃ�
}