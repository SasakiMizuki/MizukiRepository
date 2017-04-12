#pragma once
#include "Graphics.h"
#include "ObjectBase.h"

#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
const int NUM_POLYGON(2);

typedef struct{
	D3DXVECTOR3 pos;	// 頂点座標
	float		rhw;	// テクスチャ用
	D3DCOLOR	col;	// 頂点カラー
	D3DXVECTOR2	tex;	// テクスチャ座標
}VERTEX_2D;

class CSceneBase;

class C2DObj : public CObjectBase
{
protected:
	//UINT		m_uID;
	VERTEX_2D	m_Vertex2D[4];
	D3DXVECTOR2 m_Position;		// ゲーム内座標
	D3DXVECTOR2 m_Speed;			// 移動量
	D3DXVECTOR2 m_TexSize;		// 大きさ
	D3DXVECTOR2 m_PatternDivide;	// 分割数
	D3DXVECTOR2 m_PositionInTexLU;// 画像内座標(0.0f～1.0f)	左上
	D3DXVECTOR2 m_PositionInTexRD;// 右下
	CSceneBase* m_pScene;
	char*		m_pszTexName;
	D3DXCOLOR	m_Color;
	int			m_nAlpha;

	LPDIRECT3DTEXTURE9 m_pTexture;	// テクスチャへのポインタ
public:
	virtual void MakeVertexPolygon();
	C2DObj(CSceneBase* pScene);
	virtual ~C2DObj();
	virtual void Init();
	virtual void Update();
	virtual void PostUpdate();
	virtual void PreDraw();
	virtual void Draw();
	virtual void DrawAlpha() {}
	virtual void Fin();
	virtual UINT GetID() { return m_uID; }
	virtual CSceneBase* GetScene() { return m_pScene; }
	CObjectBase* Find(UINT uID, CObjectBase* p = NULL);
};

