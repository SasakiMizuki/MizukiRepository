// 自機クラス定義

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

	int				m_nMotionCounter;	// 攻撃時のタイムカウンター
public:
	CEnemy(CSceneBase* pScene);
	virtual ~CEnemy(void);

	virtual void Init();		// 初期化
	virtual void Fin();			// 終了処理
	virtual void Update();		// 更新
	virtual void DrawAlpha();
	void ChangeHP(float fHP) { m_fHP += fHP; }
private:
	void UpdateAttack();
	void UpdateFire();
};