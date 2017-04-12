// 敵機クラス定義

#pragma once

#include "MeshObj.h"

class CEnemy : public CMeshObj
{
private:
	static CMesh		m_mesh;
	static bool			m_bLoad;
	static CMeshObj*	m_pPlayer;

public:
	CEnemy(CScene* pScene);
	virtual ~CEnemy(void);

	virtual void Init();		// 初期化
	virtual void Fin();			// 終了処理
	virtual void Update();		// 更新
	virtual void DrawAlpha();	// 半透明部分描画
};