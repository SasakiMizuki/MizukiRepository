// スカイドーム クラス定義

#pragma once

#include "MeshObj.h"
#include "Camera.h"

class CSky : public CMeshObj
{
private:
	static CHierarMesh	m_mesh;
	CCamera*		m_pCamera;

public:
	CSky(CSceneBase* pScene);
	virtual ~CSky(void);

	virtual void Init();		// 初期化
	virtual void Update();		// 更新
	virtual void Draw(CShader* pShader = NULL);		// 描画
	virtual void DrawAlpha();	// 半透明描画
	virtual void Fin();			// 解放
	void PostUpdate();			// 更新後処理
	void PreDraw();				// 描画前処理
};