#include "TitleBG.h"
#include "define.h"
bool CTitleBG::m_bLoad;

CTitleBG::CTitleBG(CSceneBase* pScene) :
	C2DObj(pScene){
	m_uID = ID_BG;
	D3DXCreateTextureFromFile(CGraphics::GetDevice(), TITLE_BG_NAME, &m_pTexture);
	m_TexSize = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
}


CTitleBG::~CTitleBG() {
}

void CTitleBG::Init() {

}

void CTitleBG::Update() {
	MakeVertexPolygon();
}

void CTitleBG::Fin() {
	if (m_pTexture) {
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

void CTitleBG::MakeVertexPolygon() {
	m_Vertex2D[0].pos = D3DXVECTOR3(m_Position.x, m_Position.y, 0.1f);
	m_Vertex2D[1].pos = D3DXVECTOR3(m_Position.x + m_TexSize.x, m_Position.y, 0.1f);
	m_Vertex2D[2].pos = D3DXVECTOR3(m_Position.x, m_Position.y + m_TexSize.y, 0.1f);
	m_Vertex2D[3].pos = D3DXVECTOR3(m_Position.x + m_TexSize.x, m_Position.y + m_TexSize.y, 0.1f);

	m_Vertex2D[0].rhw =
		m_Vertex2D[1].rhw =
		m_Vertex2D[2].rhw =
		m_Vertex2D[3].rhw = 1.0f;

	m_Vertex2D[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_Vertex2D[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_Vertex2D[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_Vertex2D[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	m_Vertex2D[0].tex = D3DXVECTOR2(m_PositionInTexLU.x, m_PositionInTexLU.y);
	m_Vertex2D[1].tex = D3DXVECTOR2(m_PositionInTexRD.x, m_PositionInTexLU.y);
	m_Vertex2D[2].tex = D3DXVECTOR2(m_PositionInTexLU.x, m_PositionInTexRD.y);
	m_Vertex2D[3].tex = D3DXVECTOR2(m_PositionInTexRD.x, m_PositionInTexRD.y);
}
