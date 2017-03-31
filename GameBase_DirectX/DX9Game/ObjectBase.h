#pragma once
#include "Graphics.h"
// �I�u�W�F�N�g���
enum GAMEOBJID {
	ID_3DOBJ = 0,
	ID_2DOBJ,
	ID_BILLBOARD,
	ID_MESHOBJ,
	ID_CAMERA,		// �J����
	ID_PLAYER,		// ���@
	ID_LAND,		// �n��
	ID_SKY,			// �X�J�C�h�[��
	ID_ENEMY,		// �G�@
	ID_BULLET,		// �e
	ID_MISSILE,		// �ǔ��e
	ID_EXPLOSION,	// ����
	ID_BG,			// �w�i(2d)
	ID_JINTAI,		// �v���C���[
	ID_SWORD,		// ��
	ID_PLAYERHP,	// �v���C���[HP�\��
	ID_FADE,
	ID_TREE,
	ID_FIRE,
	ID_PARTICLE,	// �p�[�e�B�N��

	MAX_ID			// �I�u�W�F�N�g��ʐ�
};

class CSceneBase;
class CObjectBase
{
protected:
	UINT			m_uID;		// �I�u�W�F�N�g���
	DWORD			m_dwDamage;	// �_���[�W�^�C�}
	D3DXMATRIX		m_world;	// ���[���h�ϊ��s��
	D3DXVECTOR3		m_speed;	// ���x
	D3DXVECTOR3		m_accel;	// �����x
	float			m_fRadius;	// ���E�����a
	D3DXVECTOR3		m_center;	// ���E�����S���W
	D3DXVECTOR3		m_bbox;		// ���E�{�b�N�X(�����̃T�C�Y)
	CSceneBase*		m_pScene;	// ��������V�[��
	float			m_fHP;
	D3DCOLORVALUE	m_cvBColor;	// ���E��/�{�b�N�X�F
	int				m_nObjNumber;	// map�ł̎��g�̃L�[
public:
	CObjectBase();
	virtual ~CObjectBase();
	virtual void Init();
	virtual void Update();
	virtual void PostUpdate();
	virtual void PreDraw();
	virtual void Draw();
	virtual void DrawAlpha();	// �������\��
	virtual void Fin();

	virtual UINT GetID() { return m_uID; }
	virtual DWORD GetDamage() { return m_dwDamage; }
	virtual void SetDamage(DWORD dwDamage) { m_dwDamage = dwDamage; }
	virtual float GetHP() { return m_fHP; }
	virtual void SetNumber(int nNumber) { m_nObjNumber = nNumber; }
	virtual int GetNumber() { return m_nObjNumber; }
};

