#include "Fade.h"
#include "define.h"
#include "SceneBase.h"

bool CFade::m_bDoingFade;
int  CFade::m_nFadeMode;
int	 CFade::m_nAlpha;

const int FADE_INTERVAL(5);

// コンストラクタ
CFade::CFade(CSceneBase* pScene) :
C2DObj(pScene){
	m_pScene = pScene;
	m_uID = ID_FADE;
	D3DXCreateTextureFromFile(CGraphics::GetDevice(), FADE_TEXTURE_PATH, &m_pTexture);
	m_Position = D3DXVECTOR2(0.0f,0.0f);
	m_TexSize = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	//m_nAlpha = 255;
	m_pScene->Add(this);
}

// デストラクタ
CFade::~CFade() {
}

//　初期化
void CFade::Init() {

}

// 終了処理
void CFade::Fin() {
	if (m_pTexture) {
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}


// 更新
void CFade::Update() {
	if (m_bDoingFade) {
		switch (m_nFadeMode) {
		case FADEOUT:
			m_nAlpha += FADE_INTERVAL;	// テクスチャのアルファ値を変更
			if (m_nAlpha > 255) {		// フェード終了でフラグ変更
				m_nAlpha = 255;
				m_bDoingFade = false;
			}
			break;
		case FADEIN:
			m_nAlpha -= FADE_INTERVAL;
			if (m_nAlpha < 0) {
				m_nAlpha = 0;
				m_bDoingFade = false;
			}
			break;
		default:
			break;
		}
	}
	MakeVertexPolygon();
}

void CFade::Draw() {
	if (m_bDoingFade) {
		CGraphics::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		CGraphics::GetDevice()->SetFVF(FVF_VERTEX_2D);
		CGraphics::GetDevice()->SetTexture(0, m_pTexture);
		CGraphics::GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,
			NUM_POLYGON,
			&m_Vertex2D[0],
			sizeof(VERTEX_2D));
	}
}

// 頂点座標設定
void CFade::MakeVertexPolygon() {
	m_Vertex2D[0].pos = D3DXVECTOR3(m_Position.x, m_Position.y, 0.0f);
	m_Vertex2D[1].pos = D3DXVECTOR3(m_Position.x + m_TexSize.x, m_Position.y, 0.0f);
	m_Vertex2D[2].pos = D3DXVECTOR3(m_Position.x, m_Position.y + m_TexSize.y, 0.0f);
	m_Vertex2D[3].pos = D3DXVECTOR3(m_Position.x + m_TexSize.x, m_Position.y + m_TexSize.y, 0.0f);

	m_Vertex2D[0].rhw =
		m_Vertex2D[1].rhw =
		m_Vertex2D[2].rhw =
		m_Vertex2D[3].rhw = 1.0f;

	m_Vertex2D[0].col =
		m_Vertex2D[1].col =
		m_Vertex2D[2].col =
		m_Vertex2D[3].col = D3DCOLOR_RGBA(255, 255, 255, m_nAlpha);

	m_Vertex2D[0].tex = D3DXVECTOR2(m_PositionInTexLU.x, m_PositionInTexLU.y);
	m_Vertex2D[1].tex = D3DXVECTOR2(m_PositionInTexRD.x, m_PositionInTexLU.y);
	m_Vertex2D[2].tex = D3DXVECTOR2(m_PositionInTexLU.x, m_PositionInTexRD.y);
	m_Vertex2D[3].tex = D3DXVECTOR2(m_PositionInTexRD.x, m_PositionInTexRD.y);
}

// フェード開始
void CFade::Start(int nMode) {
	m_nFadeMode = nMode;
	m_nAlpha = 255 * m_nFadeMode;
	//m_nAlpha = 255;
	m_bDoingFade = true;
}