// ���@�N���X��`

#pragma once

#include "MeshObj.h"
#include "Land.h"
#include "Fire.h"

enum eENEMY_MOTION {
	ENEMY_STUND,
	ENEMY_ATTACK,
	ENEMY_FIRE,

	MAX_ENEMY_MOVE
};
class CJintai;
class CEnemy : public CMeshObj
{
private:
	static CMesh	m_mesh;
	static bool		m_bLoad;
	CLand*			m_pLand;
	D3DXVECTOR3		m_angle;
	float			m_fSpeed;
	int				m_nMotion;

	CJintai*		m_pPlayer;
	CFire*			m_pFire;

	bool			m_bAttack;
	bool			m_bFire;

	int				m_nMotionCounter;	// �U�����̃^�C���J�E���^�[
public:
	CEnemy(CSceneBase* pScene);
	virtual ~CEnemy(void);

	virtual void Init();		// ������
	virtual void Fin();			// �I������
	virtual void Update();		// �X�V
	virtual void DrawAlpha();
	void ChangeHP(float fHP) { m_fHP += fHP; }
private:
	void UpdateAttack();
	void UpdateFire();
};