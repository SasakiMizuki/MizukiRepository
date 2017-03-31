//=============================================================================
//
// ビルボード処理 [bullet.cpp]
//
//=============================================================================
#include "bullet.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "model.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_BULLET		"data/TEXTURE/bullet000.png"	// 読み込むテクスチャファイル名
#define	BULLET_SIZE_X		(6.0f)							// ビルボードの幅
#define	BULLET_SIZE_Y		(6.0f)							// ビルボードの高さ
#define	VALUE_MOVE_BULLET	(0.30f)							// 移動速度
#define	VALUE_JUMP				(10.0f)							// ジャンプ力
#define	VALUE_GRAVITY			(0.45f)							// 重力
#define	RATE_REGIST				(0.075f)						// 抵抗係数
#define	RATE_REFRECT			(-0.90f)						// 反射係数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBullet::InitBullet(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点情報の作成
	MakeVertexBullet(pDevice,D3DXVECTOR3(0.0f,0.0f,0.0f));

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
								TEXTURE_BULLET,			// ファイルの名前
								&m_pD3DTextureBullet);	// 読み込むメモリー

	m_posBullet = D3DXVECTOR3(0.0f, 18.0f, 0.0f);
	m_sclBullet = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_vecBullet = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 影の設定
	m_nIdxShadowBullet = CreateShadow(m_posBullet, BULLET_SIZE_X, BULLET_SIZE_Y);

	SetColorShadow(m_nIdxShadowBullet, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CBullet::UninitBullet(void)
{
	if(m_pD3DTextureBullet != NULL)
	{// テクスチャの開放
		m_pD3DTextureBullet->Release();
		m_pD3DTextureBullet = NULL;
	}

	if(m_pD3DVtxBuffBullet != NULL)
	{// 頂点バッファの開放
		m_pD3DVtxBuffBullet->Release();
		m_pD3DVtxBuffBullet = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CBullet::UpdateBullet(void)
{
	D3DXVECTOR3 rotCamera;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	// カメラの回転を取得
	rotCamera = GetRotCamera();

	if(GetKeyboardPress(DIK_LEFT))
	{
		if(GetKeyboardPress(DIK_UP))
		{// 左前移動
			
			
		}
		else if(GetKeyboardPress(DIK_DOWN))
		{// 左後移動
			
			
		}
		else
		{// 左移動
			
			
		}
	}
	else if(GetKeyboardPress(DIK_RIGHT))
	{
		if(GetKeyboardPress(DIK_UP))
		{// 右前移動
			
			
		}
		else if(GetKeyboardPress(DIK_DOWN))
		{// 右後移動
			
			
		}
		else
		{// 右移動
			
			
		}
	}
	else if(GetKeyboardPress(DIK_UP))
	{// 前移動
		
		
	}
	else if(GetKeyboardPress(DIK_DOWN))
	{// 後移動
		
		
	}

	if(GetKeyboardTrigger(DIK_SPACE))
	{// ジャンプ
		if(m_bEnableGravity == true)
		{	// 上方向へ速度を追加
			m_vecBullet.y += 10.0f;
		}
	}

	if(GetKeyboardTrigger(DIK_LSHIFT)){
		MakeVertexBullet(pDevice, GetModelPos());
	}

	// ビルボードの移動
	m_posBullet.x += m_vecBullet.x;
	m_posBullet.y += m_vecBullet.y;
	m_posBullet.z += m_vecBullet.z;

	// 減速
	m_vecBullet.x += (0.0f - m_vecBullet.x) * RATE_REGIST;
	m_vecBullet.y += (0.0f - m_vecBullet.y) * RATE_REGIST;
	m_vecBullet.z += (0.0f - m_vecBullet.z) * RATE_REGIST;

	// 範囲外チェック
	

	{// 影の設定
		// 位置
		SetPositionShadow(
			m_nIdxShadowBullet,
			m_posBullet
		);

		// サイズ
		float fSizeX = BULLET_SIZE_X + (m_posBullet.y - 9.0f) * 0.025f;
		if(fSizeX < BULLET_SIZE_X)
		{
			fSizeX = BULLET_SIZE_X;
		}
		float fSizeY = BULLET_SIZE_Y + (m_posBullet.y - 9.0f) * 0.025f;
		if(fSizeY < BULLET_SIZE_Y)
		{
			fSizeY = BULLET_SIZE_Y;
		}
		SetVertexShadow(m_nIdxShadowBullet, fSizeX, fSizeY);

		// α値
		float colA = (400.0f - (m_posBullet.y - 9.0f)) / 800.0f;
		if(colA < 0.0f)
		{
			colA = 0.0f;
		}
		SetColorShadow(m_nIdxShadowBullet, D3DXCOLOR(1.0f, 1.0f, 1.0f, colA));
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void CBullet::DrawBullet(LPDIRECT3DDEVICE9 pDevice)
{
	D3DXMATRIX mtxView, mtxScale, mtxTranslate;

	// ライティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ビューマトリックスを取得
	mtxView = GetMtxView();

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorldBullet);

	// ポリゴンを正面に向ける
#if 0
	// 逆行列を求める
	D3DXMatrixInverse(
		&m_mtxWorldBullet,
		NULL,
		&mtxView
	);
	m_mtxWorldBullet._41 = 0.0f;
	m_mtxWorldBullet._42 = 0.0f;
	m_mtxWorldBullet._43 = 0.0f;	// 平行移動成分をなくす
#else
	// 転置行列を求める
	m_mtxWorldBullet._11 = mtxView._11;
	m_mtxWorldBullet._12 = mtxView._21;
	m_mtxWorldBullet._13 = mtxView._31;
	m_mtxWorldBullet._21 = mtxView._12;
	m_mtxWorldBullet._22 = mtxView._22;
	m_mtxWorldBullet._23 = mtxView._32;
	m_mtxWorldBullet._31 = mtxView._13;
	m_mtxWorldBullet._32 = mtxView._23;
	m_mtxWorldBullet._33 = mtxView._33;	
#endif

	// スケールを反映
	D3DXMatrixScaling(&mtxScale, m_sclBullet.x,
									m_sclBullet.y,
									m_sclBullet.z);
	D3DXMatrixMultiply(&m_mtxWorldBullet,
									&m_mtxWorldBullet, &mtxScale);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, m_posBullet.x,
											m_posBullet.y,
											m_posBullet.z);
	D3DXMatrixMultiply(&m_mtxWorldBullet,
									&m_mtxWorldBullet, &mtxTranslate);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorldBullet);

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, m_pD3DVtxBuffBullet, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pD3DTextureBullet);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	// ラインティングを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
HRESULT CBullet::MakeVertexBullet(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 BulletPos)
{
	// オブジェクトの頂点バッファを生成
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
												FVF_VERTEX_3D,				// 使用する頂点フォーマット
												D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
												&m_pD3DVtxBuffBullet,	// 頂点バッファインターフェースへのポインタ
												NULL)))						// NULLに設定
	{
        return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		m_pD3DVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(BulletPos.x - BULLET_SIZE_X / 2, BulletPos.y - BULLET_SIZE_Y / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-BULLET_SIZE_X / 2, BULLET_SIZE_Y / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(BULLET_SIZE_X / 2, -BULLET_SIZE_Y / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(BULLET_SIZE_X / 2, BULLET_SIZE_Y / 2, 0.0f);

		// 法線の設定
		pVtx[0].normal = 
		pVtx[1].normal = 
		pVtx[2].normal = 
		pVtx[3].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
				   
		// 反射光の設定
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// 頂点データをアンロックする
		m_pD3DVtxBuffBullet->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void CBullet::SetVertexBullet(float fSizeX, float fSizeY)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		m_pD3DVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-fSizeX / 2, fSizeY / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(fSizeX / 2, fSizeY / 2, 0.0f);

		// 頂点データをアンロックする
		m_pD3DVtxBuffBullet->Unlock();
	}
}
