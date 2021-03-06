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
#include "Shader.h"
// 頂点フォーマット
struct MVERTEX
{
	D3DVECTOR	pos;		// 頂点座標
	D3DVECTOR	normal;		// 法線ベクトル
	float		u, v;		// テクスチャ座標
};
#define FVF_MVERTEX	(D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1)

// 破片
struct PIECE
{
	MVERTEX			v[3];	// 三角形の座標(重心が原点)
	D3DXMATRIX		world;	// ワールド変換
	D3DXVECTOR3		speed;	// 速度
	D3DXVECTOR3		accel;	// 加速度
	D3DCOLORVALUE	color;	// 色
	D3DXVECTOR3		axis;	// 回転軸
	float			rspeed;	// 回転速度
};

class CMesh
{
private:
	LPD3DXMESH				m_pD3DMesh;		// D3DXMesh オブジェクト
	DWORD					m_dwNumMaterial;// マテリアル数
	D3DMATERIAL9*			m_pMaterial;	// マテリアル
	LPDIRECT3DTEXTURE9*		m_ppTexture;	// テクスチャ
	LPD3DXATTRIBUTERANGE	m_pAttr;		// 属性テーブル
	DWORD					m_dwAttr;		// 属性数

	D3DXVECTOR3				m_vBBox;		// 境界ボックス(半分のサイズ)
	D3DXVECTOR3				m_vCenter;		// 境界球/境界ボックス中心座標
	float					m_fRadius;		// 境界球(半径)

	LPD3DXMESH				m_pBBox;		// 境界ボックス メッシュ
	LPD3DXMESH				m_pBSphere;		// 境界球メッシュ
	D3DCOLORVALUE			m_cvBColor;		// 境界球/ボックス色

	PIECE*					m_pInitPiece;	// 破片初期値
	PIECE*					m_pPiece;		// 破片
	DWORD					m_dwPiece;		// 破片の数
	DWORD					m_dwTime;		// 経過フレーム数

public:
	CMesh();								// コンストラクタ
	virtual ~CMesh();						// デストラクタ
	virtual bool Initialize(LPCTSTR pszFName, bool bReverse = false);	// メッシュ初期化
	virtual void Finalize();						// メッシュ解放
	virtual void Draw(D3DXMATRIX& world, CShader* pShader);	// メッシュ描画
	virtual void DrawNoAlpha(D3DXMATRIX& world);	// 不透明部分描画
	virtual void DrawAlpha(D3DXMATRIX& world);		// 半透明部分描画
	virtual D3DXVECTOR3& GetBBox() {return m_vBBox;}
	virtual D3DXVECTOR3& GetCenter() {return m_vCenter;}
	virtual float GetRadius() {return m_fRadius;}
	virtual	void DrawOBB(D3DXMATRIX& world);
	virtual void DrawAABB(D3DXMATRIX& world);		// 境界ボックス描画
	virtual void DrawBSphere(D3DXMATRIX& world);	// 境界球描画
	virtual void SetBColor(D3DCOLORVALUE& cvBColor) {m_cvBColor = cvBColor;}
	virtual void SetBColor(float r, float g, float b, float a) {m_cvBColor.r = r; m_cvBColor.g = g; m_cvBColor.b = b; m_cvBColor.a = a;}
	virtual D3DCOLORVALUE& GetBColor() {return m_cvBColor;}

	virtual bool Intersect(D3DXVECTOR3& L0,
		D3DXVECTOR3& L1,
		bool bRay = false,
		D3DXVECTOR3* pCross = NULL,
		D3DXVECTOR3* pNormal = NULL,
		D3DXMATRIX* pWorld = NULL);

	virtual void DrawPiece();					// 破片描画
	virtual void InitPiece(D3DXMATRIX& world);	// 破片初期化
	virtual void UpdatePiece();					// 破片更新
	virtual void FinPiece();					// 破片後片付け
	virtual DWORD GetPieceCount() {return m_dwPiece;}
	virtual void GetInitPiece(PIECE* pPiece);
};

//=======================================================================================
//	End of File
//=======================================================================================