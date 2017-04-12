// 自機クラス定義
#pragma once

#include "MeshObj.h"
#include "Land.h"

class CPlayer : public CMeshObj
{
private:
	static CHierarMesh	m_mesh;
	static bool		m_bLoad;
	CLand*			m_pLand;
	D3DXVECTOR3		m_angle;
	float			m_fSpeed;

	DWORD			m_dwPrev;
	double			m_dAnimTime;

public:
	CPlayer(CSceneBase* pScene);
	virtual ~CPlayer(void);

	virtual void Init();		// 初期化
	virtual void Fin();			// 終了処理
	virtual void Update();		// 更新
	virtual void Draw();		// 描画
};