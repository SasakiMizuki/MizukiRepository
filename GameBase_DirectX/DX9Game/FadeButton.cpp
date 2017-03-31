#include "FadeButton.h"


bool CFadeButton::m_bLoad;

CFadeButton::CFadeButton(CSceneBase* pScene) :
C2DObj(pScene){
	m_uID = ID_BG;
	D3DXCreateTextureFromFile(CGraphics::GetDevice(), BUTTON_IMAGE_NAME, &m_pTexture);
	m_TexSize = D3DXVECTOR2(343, 56);
	m_Position.x = 400;
	m_Position.y = 450;
	m_fFedeVol = 5.0f;
	m_nAlpha = 255;
}


CFadeButton::~CFadeButton() {
}

void CFadeButton::Init() {

}

void CFadeButton::Update() {
	m_nAlpha += (int)m_fFedeVol;
	if (m_nAlpha > 255) {
		m_nAlpha = 255;
		m_fFedeVol *= -1;
	}
	if (m_nAlpha < 0) {
		m_nAlpha = 0;
		m_fFedeVol *= -1;
	}

	MakeVertexPolygon();
}

void CFadeButton::Fin() {
	if (m_pTexture) {
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

void CFadeButton::MakeVertexPolygon() {
	m_Vertex2D[0].pos = D3DXVECTOR3(m_Position.x - m_TexSize.x / 2, m_Position.y, 0.0f);
	m_Vertex2D[1].pos = D3DXVECTOR3(m_Position.x + m_TexSize.x / 2, m_Position.y, 0.0f);
	m_Vertex2D[2].pos = D3DXVECTOR3(m_Position.x - m_TexSize.x / 2, m_Position.y + m_TexSize.y, 0.0f);
	m_Vertex2D[3].pos = D3DXVECTOR3(m_Position.x + m_TexSize.x / 2, m_Position.y + m_TexSize.y, 0.0f);

	m_Vertex2D[0].rhw =
		m_Vertex2D[1].rhw =
		m_Vertex2D[2].rhw =
		m_Vertex2D[3].rhw = 1.0f;

	m_Vertex2D[0].col = D3DCOLOR_RGBA(255, 255, 255, m_nAlpha);
	m_Vertex2D[1].col = D3DCOLOR_RGBA(255, 255, 255, m_nAlpha);
	m_Vertex2D[2].col = D3DCOLOR_RGBA(255, 255, 255, m_nAlpha);
	m_Vertex2D[3].col = D3DCOLOR_RGBA(255, 255, 255, m_nAlpha);

	m_Vertex2D[0].tex = D3DXVECTOR2(m_PositionInTexLU.x, m_PositionInTexLU.y);
	m_Vertex2D[1].tex = D3DXVECTOR2(m_PositionInTexRD.x, m_PositionInTexLU.y);
	m_Vertex2D[2].tex = D3DXVECTOR2(m_PositionInTexLU.x, m_PositionInTexRD.y);
	m_Vertex2D[3].tex = D3DXVECTOR2(m_PositionInTexRD.x, m_PositionInTexRD.y);
}
