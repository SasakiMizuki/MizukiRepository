// �G�@�N���X����

#include "Enemy.h"
#include "Input.h"

#define PATH_MESHENEMY	_T("../data/model/J35/J35.x")
#define SPEED			4.0f

CMesh		CEnemy::m_mesh;
bool		CEnemy::m_bLoad = false;
CMeshObj*	CEnemy::m_pPlayer = NULL;

// �R���X�g���N�^
CEnemy::CEnemy(CScene* pScene) :
	CMeshObj(pScene)
{
	m_uID = ID_ENEMY;
}

// �f�X�g���N�^
CEnemy::~CEnemy(void)
{
}

// ������
void CEnemy::Init()
{
	CMeshObj::Init();

	if (!m_bLoad) {
		m_bLoad = m_mesh.Initialize(PATH_MESHENEMY);
	}
	if (m_bLoad) {
		SetMesh(&m_mesh);
	}
	// ���@�ւ̃|�C���^���擾���Ă���
	if (!m_pPlayer) {
		m_pPlayer = (CMeshObj*)Find(ID_PLAYER);
	}
}

// �I������
void CEnemy::Fin()
{
	CMeshObj::Fin();

	SetMesh(NULL);
	if (m_bLoad) {
		m_bLoad = false;
		m_mesh.Finalize();
	}
}

// �X�V

void CEnemy::Update()
{
	UpdateDamage();

	// ���[���h�}�g���b�N�X���烍�[�J�����A���W���o
	D3DXMATRIX world = GetWorld();
	D3DXVECTOR3 vX, vY, vZ, vP;
	vX = D3DXVECTOR3(world._11, world._12, world._13);
	vY = D3DXVECTOR3(world._21, world._22, world._23);
	vZ = D3DXVECTOR3(world._31, world._32, world._33);
	vP = D3DXVECTOR3(world._41 ,world._42, world._43);
	world._41 = world._42 = world._43 = 0.0f;// �ꎞ�I�Ɍ��_��

	// �^�[�Q�b�g�̕����擾
	D3DXVECTOR3 vT;
	if (m_pPlayer) {
		vT = m_pPlayer->GetPos() - vP;
	} else {
		vT = vZ * 1000.0f;
	}
	D3DXVec3Normalize(&vT, &vT);

	// �^�[�Q�b�g�͑O�ɂ���?
	float fForward = D3DXVec3Dot(&vT, &vZ);
	// �^�[�Q�b�g�͏�ɂ���?
	float fUp = D3DXVec3Dot(&vT, &vY);
	// �^�[�Q�b�g�͉E�ɂ���?
	float fRight = D3DXVec3Dot(&vT, &vX);

	// ��]�p�X�V
	D3DXVECTOR3 angle(0.0f, 0.0f, 0.0f);
	float fAdjust = cosf(D3DXToRadian(85));
	if (fRight > fAdjust) {			// �E?
		angle.z = -1.5f;			//  �E����
	} else if (fRight < -fAdjust) {	// ��?
		angle.z = 1.5f;				//  ������
	} else {						// �O��㉺
		if (fUp < 0.0f) {			// ��?
			angle.z = 1.5f;			//  ������
		}
	}
	if (fForward > 0.0f) {			// �O?
		if (fUp > fAdjust) {		// ��?
			angle.x = -1.0f;		//  �㏸
		} else if (fUp < -fAdjust) {// ��?
			angle.x = 1.0f;			//  ���~
		}
	} else {					// �㉺���E�����
		angle.x = -1.0f;			//  �㏸
	}
	D3DXMATRIX rot_x, rot_z;
	D3DXMatrixRotationAxis(&rot_z, &vZ, D3DXToRadian(angle.z));
	D3DXMatrixRotationAxis(&rot_x, &vX, D3DXToRadian(angle.x));
	world *= (rot_z * rot_x);
	// �ړ�
	if (!CInput::GetKeyPress(DIK_RSHIFT)) {
		vP += (vZ * SPEED);
	}
	world._41 = vP.x;
	world._42 = vP.y;
	world._43 = vP.z;
	// ���[���h�}�g���b�N�X���X�V
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