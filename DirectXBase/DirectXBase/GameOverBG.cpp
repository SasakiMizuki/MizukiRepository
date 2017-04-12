#include "GameOverBG.h"
#include "define.h"


CGameOverBG::CGameOverBG(CSceneBase* pScene) :
	C2DObj(pScene) {
	m_uID = ID_BG;
	D3DXCreateTextureFromFile(CGraphics::GetDevice(), GAMEOVER_BG_NAME, &m_pTexture);
	m_TexSize = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
}


CGameOverBG::~CGameOverBG() {
}

void CGameOverBG::Init() {

}

void CGameOverBG::Update() {
	MakeVertexPolygon();
}

void CGameOverBG::Draw() {
	CGraphics::GetDevice()->SetFVF(FVF_VERTEX_2D);
	CGraphics::GetDevice()->SetTexture(0, m_pTexture);
	CGraphics::GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,
		NUM_POLYGON,
		&m_Vertex2D,
		sizeof(VERTEX_2D));
}

void CGameOverBG::Fin() {
	if (m_pTexture) {
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

