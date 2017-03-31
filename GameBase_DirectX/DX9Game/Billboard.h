#pragma once
#include "C2DObj.h"
#include "Camera.h"

#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE| D3DFVF_TEX1)

// 上記３Ｄポリゴン頂点フォーマットに合わせた構造体を定義
typedef struct {
	D3DXVECTOR3 vtx;		//頂点座標
	D3DXVECTOR3 normal;		//法線ベクトル
	D3DCOLOR	diffuse;	//反射光
	D3DXVECTOR2 tex;		//テクスチャ座標
} VERTEX_3D;

class CBillboard :
	public C2DObj
{
protected:
	CCamera* m_pCamera;	// カメラへのポインタ
	D3DXVECTOR2 m_Size;	// 大きさ
	VERTEX_3D   m_Vertex3D;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffer;
	D3DXVECTOR3 m_Scale;
public:
	CBillboard(CSceneBase* pScene);
	virtual ~CBillboard();
	virtual void Init();
	virtual void Fin();
	virtual void Update();
	virtual void Draw();
	virtual void MakeVertex();
};

