#include "PlayerHP.h"
#include "SceneBase.h"


CPlayerHP::CPlayerHP(CSceneBase* pScene) :
CBillboard(pScene){
	m_uID = ID_PLAYERHP;
	m_pScene->Add(this);
}


CPlayerHP::~CPlayerHP() {
}

void CPlayerHP::Init() {
	//MakeVertexPolygon();
	D3DXCreateTextureFromFile(CGraphics::GetDevice(), PLAYER_HP_TEXTRUE, &m_pTexture);

	m_pCamera = (CCamera*)Find(ID_CAMERA);
	m_pPlayer = (CJintai*)Find(ID_JINTAI);

	m_Size = D3DXVECTOR2(80.0f, 10.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_fMaxPlayerHP = m_pPlayer->GetHP();
	MakeVertex();
}

void CPlayerHP::Fin() {
	if (m_pTexture) {
		m_pTexture->Release();
		m_pTexture = NULL;
	}

}

void CPlayerHP::Update() {
	m_fPlayerHP = m_pPlayer->GetHP();

	MakeVertex();

	D3DXMatrixIdentity(&m_world);

	// 転置行列を求める
	m_world._11 = m_pCamera->GetView()._11;
	m_world._12 = m_pCamera->GetView()._21;
	m_world._13 = m_pCamera->GetView()._31;
	m_world._21 = m_pCamera->GetView()._12;
	m_world._22 = m_pCamera->GetView()._22;
	m_world._23 = m_pCamera->GetView()._32;
	m_world._31 = m_pCamera->GetView()._13;
	m_world._32 = m_pCamera->GetView()._23;
	m_world._33 = m_pCamera->GetView()._33;

	m_world._41 = m_pPlayer->GetWorld()._41;
	m_world._42 = m_pPlayer->GetWorld()._42 + 170.0f;
	m_world._43 = m_pPlayer->GetWorld()._43;
}

void CPlayerHP::Draw() {
	D3DXMATRIX mtxTranslate;
	// ライト無効
	CGraphics::GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);


	// 移動を反映
	//D3DXMatrixTranslation(&mtxTranslate, m_world._41, m_world._42, m_world._43);
	//D3DXMatrixMultiply(&m_world,
	//	&m_world, &mtxTranslate);

	// ワールドマトリックスの設定
	CGraphics::GetDevice()->SetTransform(D3DTS_WORLD, &m_world);

	// 頂点バッファをデバイスのデータストリームにバインド
	CGraphics::GetDevice()->SetStreamSource(0, m_pVtxBuffer, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	CGraphics::GetDevice()->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	CGraphics::GetDevice()->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	CGraphics::GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	// ライティングを有効にする
	CGraphics::GetDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);

}

void CPlayerHP::DrawAlpha() {

}

void CPlayerHP::MakeVertex() {
	float fHPPercent = m_fPlayerHP / m_fMaxPlayerHP;

	// オブジェクトの頂点バッファを生成
	CGraphics::GetDevice()->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_3D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&m_pVtxBuffer,			// 頂点バッファインターフェースへのポインタ
		NULL);						// NULLに設定

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-m_Size.x / 2, -m_Size.y / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-m_Size.x / 2, m_Size.y / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3((-m_Size.x/2)+(m_Size.x*fHPPercent) , -m_Size.y / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3((-m_Size.x/2)+(m_Size.x*fHPPercent) , m_Size.y / 2, 0.0f);

		// 法線の設定
		pVtx[0].normal =
			pVtx[1].normal =
			pVtx[2].normal =
			pVtx[3].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// 反射光の設定
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(fHPPercent, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(fHPPercent, 0.0f);

		// 頂点データをアンロックする
		m_pVtxBuffer->Unlock();
	}
}