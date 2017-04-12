// 3D�I�u�W�F�N�g �N���X����
#include "C3DObj.h"
#include "SceneBase.h"

// ����
CObjectBase* C3DObj::Find(UINT uID, CObjectBase* p)
{
	int Number;
	if (p) {
		Number = p->GetNumber();
	} else {
		Number = 0;
	}
	if (m_pScene)
		return m_pScene->Find(uID, Number);
	return NULL;
}

// �R���X�g���N�^
C3DObj::C3DObj(CSceneBase* pScene){
	m_uID = ID_3DOBJ;
	m_dwDamage = 0;
	D3DXMatrixIdentity(&m_world);
	m_pScene = pScene;
	//m_world._41 = position.x;
	//m_world._42 = position.y;
	//m_world._43 = position.z;
}

// �f�X�g���N�^
C3DObj::~C3DObj(void)
{
}

// ������
void C3DObj::Init()
{
	//m_pScene->Add(this);
}

// �X�V
void C3DObj::Update() {
	m_speed += m_accel;
	m_world._41 += m_speed.x;
	m_world._42 += m_speed.y;
	m_world._43 += m_speed.z;
	UpdateDamage();
}

// �X�V
void C3DObj::PostUpdate() {

}

void C3DObj::PreDraw() {
}

// �\��
void C3DObj::Draw()
{
}

// �������\��
void C3DObj::DrawAlpha()
{
}

// �I������
void C3DObj::Fin()
{
	m_pScene->Del(GetNumber());
}

// ���W�擾
D3DXVECTOR3 C3DObj::GetPos()
{
	D3DXVECTOR3 pos(m_world._41, m_world._42, m_world._43);
	return pos;
}

// �O���x�N�g���擾
D3DXVECTOR3 C3DObj::GetForward()
{
	D3DXVECTOR3 fwd(m_world._31, m_world._32, m_world._33);
	return fwd;
}

// �E�x�N�g���擾
D3DXVECTOR3 C3DObj::GetRight()
{
	D3DXVECTOR3 right(m_world._11, m_world._12, m_world._13);
	return right;
}

// ����x�N�g���擾
D3DXVECTOR3 C3DObj::GetUp()
{
	D3DXVECTOR3 up(m_world._21, m_world._22, m_world._23);
	return up;
}

// ���E�����a�擾
float C3DObj::GetRadius()
{
	return m_fRadius;
}

// ���E�����S���W�擾
D3DXVECTOR3& C3DObj::GetCenter()
{
	return m_center;
}

// ���E�{�b�N�X�擾
D3DXVECTOR3& C3DObj::GetBBox()
{
	return m_bbox;
}

// ���E�����m�̓����蔻��
bool C3DObj::CollisionBSphere(C3DObj* pObj)
{
	// ���[���h��ԏ�̋��E�����S���W�����߂�
	D3DXVECTOR3 vPos1, vPos2;
	D3DXVec3TransformCoord(&vPos1,
		&GetCenter(), &GetWorld());
	D3DXVec3TransformCoord(&vPos2,
		&pObj->GetCenter(), &pObj->GetWorld());

	// ������2��Ɣ��a�̘a��2��Ɣ�r
	float fR = GetRadius() + pObj->GetRadius();
	return D3DXVec3LengthSq(&(vPos2 - vPos1))
		<= fR * fR;
}

// AABB���m�̓����蔻��
bool C3DObj::CollisionAABB(C3DObj* pObj)
{
	// ���[���h��ԏ�̋��E�{�b�N�X���S���W�����߂�
	D3DXVECTOR3 vPos1, vPos2;
	D3DXVec3TransformCoord(&vPos1,
		&GetCenter(), &GetWorld());
	D3DXVec3TransformCoord(&vPos2,
		&pObj->GetCenter(), &pObj->GetWorld());
	// AABB���m�̓����蔻��
	D3DXVECTOR3& vR1 = GetBBox();
	D3DXVECTOR3& vR2 = pObj->GetBBox();
	return (vPos1.x - vR1.x <= vPos2.x + vR2.x) &&
		(vPos2.x - vR2.x <= vPos1.x + vR1.x) &&
		(vPos1.y - vR1.y <= vPos2.y + vR2.y) &&
		(vPos2.y - vR2.y <= vPos1.y + vR1.y) &&
		(vPos1.z - vR1.z <= vPos2.z + vR2.z) &&
		(vPos2.z - vR2.z <= vPos1.z + vR1.z);
}
// OBB���m�̓����蔻��
bool C3DObj::CollisionOBB(C3DObj* pObj) {
	// ���[���h�}�g���b�N�X�擾
	D3DXMATRIX& mW1 = GetWorld();
	D3DXMATRIX& mW2 = pObj->GetWorld();
	// ���[���h��ԏ�̋��E�{�b�N�X���S���W�����߂�
	D3DXVECTOR3 vPos1, vPos2;
	D3DXVec3TransformCoord(&vPos1, &GetCenter(), &mW1);
	D3DXVec3TransformCoord(&vPos2, &pObj->GetCenter(), &mW2);
	// ���S���W�Ԃ̃x�N�g�������߂�
	D3DXVECTOR3 vD = vPos2 - vPos1;

	// ���f�����W�������߂�
	D3DXVECTOR3 vN[6];
	vN[0] = D3DXVECTOR3(mW1._11, mW1._12, mW1._13);
	vN[1] = D3DXVECTOR3(mW1._21, mW1._22, mW1._23);
	vN[2] = D3DXVECTOR3(mW1._31, mW1._32, mW1._33);
	vN[3] = D3DXVECTOR3(mW2._11, mW2._12, mW2._13);
	vN[4] = D3DXVECTOR3(mW2._21, mW2._22, mW2._23);
	vN[5] = D3DXVECTOR3(mW2._31, mW2._32, mW2._33);
	// OBB�̑傫��(����)�̒������|�����x�N�g�������߂�
	D3DXVECTOR3& vBBox1 = GetBBox();
	D3DXVECTOR3& vBBox2 = pObj->GetBBox();
	D3DXVECTOR3 vL[6];
	vL[0] = vN[0] * vBBox1.x;
	vL[1] = vN[1] * vBBox1.y;
	vL[2] = vN[2] * vBBox1.z;
	vL[3] = vN[3] * vBBox2.x;
	vL[4] = vN[4] * vBBox2.y;
	vL[5] = vN[5] * vBBox2.z;

	// ���������̓��f�����W��
	float fL, fD;
	for (int i = 0; i < 6; ++i) {
		D3DXVECTOR3& vS = vN[i];// ���������
								// OBB�̉e(����)�̍��v
		fL = 0.0f;
		for (int j = 0; j < 6; ++j) {
			fL += fabsf(D3DXVec3Dot(&vS, &vL[j]));
		}
		// �e�ƒ��S�Ԃ̋����̔�r
		fD = fabsf(D3DXVec3Dot(&vS, &vD));
		if (fL < fD) {
			return false;	// �������Ă��Ȃ�
		}
	}
	// ����������2�ӂ��琶��
	D3DXVECTOR3 vS;	// ���������
	for (int i = 0; i < 3; ++i) {
		for (int j = 3; j < 6; ++j) {
			// �����������v�Z
			D3DXVec3Cross(&vS, &vN[i], &vN[j]);
			D3DXVec3Normalize(&vS, &vS);
			// OBB�̉e(����)�̍��v
			fL = 0.0f;
			for (int k = 0; k < 6; ++k) {
				fL += fabsf(D3DXVec3Dot(&vS, &vL[k]));
			}
			// �e�ƒ��S�Ԃ̋����̔�r
			fD = fabsf(D3DXVec3Dot(&vS, &vD));
			if (fL < fD) {
				return false;	// �������Ă��Ȃ�
			}
		}
	}
	return true;	// �������Ă���
}

// �J��������̋������r
int C3DObj::CmpDepth(const void* pLeft, const void* pRight) {
	C3DObj** ppLeft = (C3DObj**)pLeft;
	C3DObj** ppRight = (C3DObj**)pRight;
	// �J��������̋����̍~���Ń\�[�g
	float fDiff = (*ppLeft)->m_fDepth - (*ppRight)->m_fDepth;
	if (fabsf(fDiff) <= FLT_EPSILON) {
		return (*ppRight)->m_synthetic - (*ppLeft)->m_synthetic;
	}
	if ((*ppLeft)->m_fDepth < (*ppRight)->m_fDepth) {
		return 1;
	}
	if ((*ppLeft)->m_fDepth >(*ppRight)->m_fDepth) {
		return -1;
	}
	return 0;
}