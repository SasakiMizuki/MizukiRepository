#include "EndBG.h"
#include "define.h"


CEndBG::CEndBG(CSceneBase* pScene) :
	C2DObj(pScene) {
	m_uID = ID_BG;
	D3DXCreateTextureFromFile(CGraphics::GetDevice(), END_BG_NAME, &m_pTexture);
	m_TexSize = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
}


CEndBG::~CEndBG() {
}


void CEndBG::Init() {

}

void CEndBG::Update() {
	MakeVertexPolygon();
}

void CEndBG::Draw() {
	CGraphics::GetDevice()->SetFVF(FVF_VERTEX_2D);
	CGraphics::GetDevice()->SetTexture(0, m_pTexture);
	CGraphics::GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,
		NUM_POLYGON,
		&m_Vertex2D,
		sizeof(VERTEX_2D));
}

void CEndBG::Fin() {
	if (m_pTexture) {
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
