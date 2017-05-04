//=======================================================================================
//
//	  メッシュ クラス定義
//
//=======================================================================================
#pragma once
#include <windows.h>		// Windowsプログラムにはこれを付ける
#include <tchar.h>			// 汎用テキスト マッピング
#include <d3d9.h>			// DirectX Graphics 関連のヘッダ
#include <d3dx9.h>			// DirectX Graphics 関連のヘッダ

#include "MyHierarchy.h"
#include "Mesh.h"

class CHierarMesh:public CMesh
{
private:
	LPD3DXFRAME					m_pFrameRoot;	// ルート フレーム オブジェクト
	LPD3DXANIMATIONCONTROLLER	m_pAnimCtrl;	// アニメーション コントローラ オブジェクト
	UINT						m_uNumAnimSet;	// アニメーション セット数
	LPD3DXANIMATIONSET*			m_ppAnimSet;	// アニメーション セット
	CMyHierarchy				m_Hierarchy;	// 階層メモリ確保/解放クラス
	DWORD						m_dwPrev;		// 直前の時刻

public:
	CHierarMesh();								// コンストラクタ
	virtual ~CHierarMesh();						// デストラクタ
	bool Initialize(LPCTSTR pszFName);		// メッシュ初期化
	void Finalize();						// メッシュ解放
	void Draw(D3DXMATRIX& world, CShader* pShader = NULL);			// メッシュ描画
	void SwitchAnimSet(UINT uAnimSet);		// アニメーション切替
	void SetTime(double dTime);				// アニメーション開始時間設定

	bool Intersect(D3DXVECTOR3& L0,
		D3DXVECTOR3& L1,
		bool bRay = false,
		D3DXVECTOR3* pCross = NULL,
		D3DXVECTOR3* pNormal = NULL,
		D3DXMATRIX* pWorld = NULL);

private:
	void RenderHierarMeshContainer(LPD3DXMESHCONTAINER pHierarMeshContainerBase, LPD3DXFRAME pFrameBase);
	void UpdateFrameMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix);
	void DrawFrame(LPD3DXFRAME pFrame);
	HRESULT AllocBoneMatrix(LPD3DXMESHCONTAINER pHierarMeshContainerBase);
	HRESULT AllocAllBoneMatrix(LPD3DXFRAME pFrameBase);

	bool IntersectFrame(LPD3DXFRAME pFrameBase,
		D3DXVECTOR3& L0, D3DXVECTOR3& W, bool bRay,
		D3DXVECTOR3* pCross, D3DXVECTOR3* pNormal);
	bool IntersectHierarMeshContainer(
		LPD3DXMESHCONTAINER pHierarMeshContainer,
		D3DXVECTOR3& L0, D3DXVECTOR3& W, bool bRay,
		D3DXVECTOR3* pCross, D3DXVECTOR3* pNormal);
};

//=======================================================================================
//	End of File
//=======================================================================================