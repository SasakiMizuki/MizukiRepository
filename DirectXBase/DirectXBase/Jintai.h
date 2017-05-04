// 階層型人体クラス定義
#pragma once
#include "C3DObj.h"
#include "HierarMesh.h"
//#include "Camera.h"
#include "Land.h"
#include "Enemy.h"

enum EParts {
	PARTS_BODY = 0,
	PARTS_BODY1,
	PARTS_HEAD,
	PARTS_SHOULDER_L,
	PARTS_ARM_L,
	PARTS_HAND_L,
	PARTS_SHOULDER_R,
	PARTS_ARM_R,
	PARTS_HAND_R,
	PARTS_THIGH_L,
	PARTS_LEG_L,
	PARTS_FOOT_L,
	PARTS_THIGH_R,
	PARTS_LEG_R,
	PARTS_FOOT_R,

	MAX_PARTS
};

enum EAnimPattern {
	ANIM_STUND = 0,
	ANIM_WORK,
	ANIM_ATTACK,
	ANIM_ROLLING,

	MAX_ANIM
};

struct TParts
{
	int				m_nParent;	// 親パーツNo.
	int				m_nType;	// メッシュ番号
	D3DXVECTOR3		m_vPos;		// オフセット
	D3DXVECTOR3		m_vAngle;	// 角度
	D3DXQUATERNION	m_q;		// クォータニオン
	D3DXMATRIX		m_matrix;	// ワールドマトリックス
	D3DXMATRIX		m_combine;	// 累積ワールドマトリックス
};

struct TAnimData
{
	int				m_nTime;
	D3DXVECTOR3		m_vPos[MAX_PARTS];
	D3DXVECTOR3		m_vAngle[MAX_PARTS];
	D3DXQUATERNION	m_q[MAX_PARTS];
};

class CJintai : public CMeshObj
{
protected:
	static CMesh*	m_pMesh;

	int				m_nTimer;
	int				m_nAnim;
	TParts			m_parts[MAX_PARTS];

	TAnimData*		m_pAnimData;
	int				m_nAnimData[MAX_ANIM];
	int				m_nMotion;	// 現在の動き

	int				m_nParts;
	DWORD			m_dwBlink;
	bool			m_bEdit;

	D3DXVECTOR3		m_angle;
	float			m_fSpeed;

	CLand*			m_pLand;
	//CCamera*		m_pCamera;

	bool			m_bLoop;
	CEnemy*			m_pEnemy;

	bool			m_bAttack;	// 攻撃中か否か
	bool			m_bRolling;	// 回避中か否か

	D3DXMATRIX		m_PassWorld;	// カメラに渡す用のワールド座標

public:
	CJintai(CSceneBase* pScene, D3DXVECTOR3 position = D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3 rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	virtual ~CJintai(void);

	static bool LoadMesh();
	static void ReleaseMesh();

	virtual void Init();
	virtual void Update();
	virtual void Draw(CShader* pShader = NULL);
	virtual void DrawAlpha();
	void AddDebugStr(LPTSTR pszMsg);

	TParts GetHandData() { return m_parts[PARTS_HAND_L]; }
	D3DXVECTOR3 GetAngle() { return m_angle; }
	D3DXMATRIX& GetPlayerWorld() { return m_PassWorld; }
	int GetMotion() { return m_nMotion; }
	void ChangeHP(float fHP) { m_fHP += fHP; }
private:
	void ChangeMotion(int nMotionNumber, bool bLoop = true);
	void UpdateAttack();
	void UpdateRolling();
protected:
	void UpdateEdit();
	void UpdateAnimation();
};