// 地面クラス定義
#pragma once
#include "MeshObj.h"

class CLand : public CMeshObj
{
protected:
	CMesh	m_mesh;
	bool	m_bLoad;

public:
	CLand(CSceneBase* pScene);
	virtual ~CLand(void);

	virtual void Init();	// 初期化
	virtual void Fin();		// 解放
};