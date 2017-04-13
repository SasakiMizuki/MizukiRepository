// 弾クラス定義
#pragma once
#include "MeshObj.h"

class CBullet : public CMeshObj
{
protected:
	static CMesh	m_mesh;		// 弾表示用メッシュ
	static bool		m_bLoad;	// メッシュ読込フラグ
	CMeshObj*		m_pGunner;	// 発射した機体
	DWORD			m_dwLife;	// 生存時間

public:
	CBullet(CScene* pScene);
	virtual ~CBullet(void);

	static bool LoadMesh();		// メッシュ読込
	static void ReleaseMesh();	// メッシュ解放
	static void Fire(CMeshObj* pGunner);	// 発射
	virtual void Update();		// 更新
	virtual void DrawAlpha();	// 半透明部分表示
};