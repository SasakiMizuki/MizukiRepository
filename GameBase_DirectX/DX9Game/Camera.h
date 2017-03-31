// �J���� �N���X��`
#pragma once

#include "C3DObj.h"
#include "Player.h"
#include "jintai.h"
#include "Enemy.h"

enum ECamPos {
	CP_FIXED = 0,	// �Œ�
	CP_FPVIEW,		// 1�l��
	CP_TPVIEW,		// 3�l��

	MAX_VIEW
};

class CSky;
class CCamera : public C3DObj
{
private:
	D3DXMATRIX	m_proj;		// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX	m_view;		// �r���[�}�g���b�N�X
	CSky*		m_pSky;		// �X�J�C�h�[��
	//CPlayer*	m_pPlayer;	// ���@
	CJintai*	m_pPlayer;	// ���@
	CEnemy*		m_pEnemy;

	ECamPos		m_cp;		// �J�������
	D3DXVECTOR3	m_pos;		// ���_
	D3DXVECTOR3	m_at;		// �����_
	D3DXVECTOR3 m_up;		// ����x�N�g��
	D3DXVECTOR3	m_pos2;		// �ŏI���_
	D3DXVECTOR3	m_at2;		// �ŏI�����_
	D3DXVECTOR3 m_up2;		// �ŏI����x�N�g��
	float		m_fTime;	// �؂�ւ�����

	float		m_fFovy;	// ����p
	float		m_fAspect;	// �A�X�y�N�g��
	float		m_fZNear;	// �O���N���b�v����
	float		m_fZFar;	// ����N���b�v����

public:
	CCamera(CSceneBase* pScene);
	virtual ~CCamera(void);

	virtual void Init();
	virtual void Update();
	virtual void Draw();
	virtual void DrawAlpha();
	virtual void Fin();
	void PostUpdate();		// �X�V�㏈��
	void PreDraw();			// �`��O����
	D3DXMATRIX& GetView() { return m_view; }
	D3DXMATRIX& GetProj() { return m_proj; }
};