// 3D�I�u�W�F�N�g �N���X��`
#pragma once

#include "Graphics.h"
#include "ObjectBase.h"

// �`����@
enum ESynthetic {
	eNone = 0,		// �ʏ�`��
	eAdditive,		// ���Z����
	eAlphaBlend,	// ����������
	eSubtractive,	// ���Z����

	eMaxSynthetic
};

class CSceneBase;

class C3DObj : public CObjectBase
{
protected:

	ESynthetic		m_synthetic;	// �������`��t���O
	float			m_fDepth;		// �J��������̋���

public:
	C3DObj(CSceneBase* pScene);
	virtual ~C3DObj(void);

	virtual void Init();		// ������
	virtual void Update();		// �X�V
	virtual void PostUpdate();		// �X�V
	virtual void PreDraw();
	virtual void Draw();		// �\��
	virtual void DrawAlpha();	// �������\��
	virtual void Fin();			// �I������
	D3DXMATRIX& GetWorld() {return m_world;}
	void SetWorld(D3DXMATRIX& world) { m_world = world; }
	virtual float GetRadius();	// ���E�����a�擾
	void SetRadius(float fRadius) { m_fRadius = fRadius; }
	virtual D3DXVECTOR3& GetCenter();	// ���E�����S���W�擾
	void SetCenter(D3DXVECTOR3& vCenter) { m_center = vCenter; }
	virtual D3DXVECTOR3& GetBBox();	// ���E�{�b�N�X�擾
	void SetBBox(D3DXVECTOR3& vBBox) { m_bbox = vBBox; }
	D3DXVECTOR3 GetPos();		// ���W�擾
	void SetPos(D3DXVECTOR3& pos) {m_world._41 = pos.x; m_world._42 = pos.y; m_world._43 = pos.z;}
	D3DXVECTOR3 GetForward();	// �O���x�N�g���擾
	D3DXVECTOR3 GetRight();		// �E�x�N�g���擾
	D3DXVECTOR3 GetUp();		// ����x�N�g���擾
	CObjectBase* Find(UINT uID, CObjectBase* p = NULL);
	bool CollisionBSphere(C3DObj* pObj);
	bool CollisionAABB(C3DObj* pObj);
	bool CollisionOBB(C3DObj* pObj);
	CSceneBase* GetScene() {return m_pScene;}
	D3DXVECTOR3& GetSpeed() {return m_speed;}
	virtual void UpdateDamage() {if (m_dwDamage) --m_dwDamage;}
	void SetSpeed(D3DXVECTOR3& speed) {m_speed = speed;}
	virtual void SetSynthetic(ESynthetic synthetic) { m_synthetic = synthetic; }
	virtual ESynthetic GetSynthetic(void) { return (this) ? m_synthetic : eNone; }
	float GetDepth() { return m_fDepth; }
	void SetDepth(float fDepth) { m_fDepth = fDepth; }
	static int CmpDepth(const void* pLeft, const void* pRight);

};