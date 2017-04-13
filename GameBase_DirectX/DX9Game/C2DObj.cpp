#include "C2DObj.h"
#include "SceneBase.h"


C2DObj::C2DObj(CSceneBase* pScene) {
	m_pScene = pScene;

	m_Position = D3DXVECTOR2(0.0f, 0.0f);
	m_Speed = D3DXVECTOR2(0.0f, 0.0f);
	m_TexSize = D3DXVECTOR2(100.0f, 100.0f);
	m_PatternDivide = D3DXVECTOR2(1.0f, 1.0f);
	m_PositionInTexLU = D3DXVECTOR2(0.0f, 0.0f);
	m_PositionInTexRD = D3DXVECTOR2(1.0f, 1.0f);
	m_uID = ID_2DOBJ;
	m_dwDamage = 0;
	m_Color = D3DXCOLOR(255, 255, 255, 255);
	m_nAlpha = 255;
}


C2DObj::~C2DObj() {
}

CObjectBase* C2DObj::Find(UINT uID, CObjectBase* p) {
	int Number;
	if (p) {
		Number = p->GetNumber();
	} else {
		Number = 0;
	}
	if (m_pScene)
		return m_pScene->Find(uID, Number);
	return NULL;
}

void C2DObj::Init() {
	MakeVertexPolygon();
	D3DXCreateTextureFromFile(CGraphics::GetDevice(), (LPCWSTR)m_pszTexName, &m_pTexture);

}

void C2DObj::Update() {
	// ”h¶æ‚Å‰½‚©‚µ‚Ä‚­‚¾‚³‚¢
	MakeVertexPolygon();
}

void C2DObj::PostUpdate() {
}

void C2DObj::PreDraw() {
}

void C2DObj::Draw() {
	CGraphics::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	CGraphics::GetDevice()->SetFVF(FVF_VERTEX_2D);
	CGraphics::GetDevice()->SetTexture(0, m_pTexture);
	CGraphics::GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,
											NUM_POLYGON,
											&m_Vertex2D[0],
											sizeof(VERTEX_2D));
}

void C2DObj::Fin() {
	if (m_pTexture) {
		m_pTexture->Release();
		m_pTexture = NULL;
	}
	if (m_pScene)
		m_pScene->Del(GetNumber());
}

void C2DObj::MakeVertexPolygon() {
	m_Vertex2D[0].pos = D3DXVECTOR3(m_Position.x, m_Position.y, 0.0f);
	m_Vertex2D[1].pos = D3DXVECTOR3(m_Position.x + m_TexSize.x, m_Position.y, 0.0f);
	m_Vertex2D[2].pos = D3DXVECTOR3(m_Position.x, m_Position.y + m_TexSize.y, 0.0f);
	m_Vertex2D[3].pos = D3DXVECTOR3(m_Position.x + m_TexSize.x, m_Position.y + m_TexSize.y, 0.0f);

	m_Vertex2D[0].rhw =
	m_Vertex2D[1].rhw =
	m_Vertex2D[2].rhw =
	m_Vertex2D[3].rhw = 1.0f;
	
	m_Vertex2D[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	m_Vertex2D[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	m_Vertex2D[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	m_Vertex2D[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	
	m_Vertex2D[0].tex = D3DXVECTOR2(m_PositionInTexLU.x, m_PositionInTexLU.y);
	m_Vertex2D[1].tex = D3DXVECTOR2(m_PositionInTexRD.x, m_PositionInTexLU.y);
	m_Vertex2D[2].tex = D3DXVECTOR2(m_PositionInTexLU.x, m_PositionInTexRD.y);
	m_Vertex2D[3].tex = D3DXVECTOR2(m_PositionInTexRD.x, m_PositionInTexRD.y);
}