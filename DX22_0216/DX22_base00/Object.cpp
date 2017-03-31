#include "Object.h"
#include "Model.h"
#include "shadow.h"
#include "camera.h"

//----- マクロ定義 -----
#define OBJECT_TREE_NAME				"data/TEXTURE/tree.png"
#define OBJECT_TREE_SIZE_X				(90)
#define OBJECT_TREE_SIZE_Y				(100)

#define OBJECT_TREE_PATTAERN_DIVIDE_X	(1)
#define OBJECT_TREE_PATTAERN_DIVIDE_Y	(1)
#define OBJECT_NUM_TREE_ANIME_PATTERN	(OBJECT_TREE_PATTAERN_DIVIDE_X * OBJECT_TREE_PATTAERN_DIVIDE_Y)
#define OBJECT_TREE_PATTERN_SIZE_X		(1.0f / OBJECT_TREE_PATTAERN_DIVIDE_X)
#define OBJECT_TREE_PATTERN_SIZE_Y		(1.0f / OBJECT_TREE_PATTAERN_DIVIDE_Y)


#define MAX_OBJECT_NUM					(40)

//----- 構造体宣言 -----
LPDIRECT3DTEXTURE9		g_pTextureObject[OBJECT_NUM_MAX] ={ NULL };	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffObject = NULL;					// 頂点バッファインターフェースへのポインタ

//----- グローバル宣言 -----
//LPDIRECT3DTEXTURE9	g_pTextureObject[OBJECT_NUM_MAX] = {NULL};	//テクスチャへのポインタ
object g_tObject[MAX_OBJECT_NUM];
D3DXMATRIX				g_mtxWorldObject;			// ワールドマトリックス

//----- プロトタイプ宣言 -----
HRESULT MakeVertexObject(LPDIRECT3DDEVICE9 pDevice);

//===============================================================
//	初期化処理
//===============================================================
void InitObject(void) {
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, OBJECT_TREE_NAME, &g_pTextureObject[OBJECT_TREE]);


	for (int nCnt = 0; nCnt < MAX_OBJECT_NUM; nCnt ++) {
		g_tObject[nCnt].posBillboard				= D3DXVECTOR3( 0,0,0 );
		g_tObject[nCnt].sclBillboard				= D3DXVECTOR3( 1.0,1.0,1.0 );
		g_tObject[nCnt].vecBillboard				= D3DXVECTOR3( 0,0,0 );
		g_tObject[nCnt].nIdxShadowBillboard			= 0;
		g_tObject[nCnt].bEnableGravity				= false;
		g_tObject[nCnt].bLive						= false;
	}
	//頂点情報の作成
	MakeVertexObject(pDevice);

}

//===============================================================
//	終了処理
//===============================================================
void UninitObject() {
	for (int nCnt = 0; nCnt < OBJECT_NUM_MAX; nCnt ++) {
		if(g_pTextureObject[nCnt] != NULL){
			//テクスチャの開放
			g_pTextureObject[nCnt]->Release();
			g_pTextureObject[nCnt] = NULL;
		}
	}
}

//===============================================================
//	更新処理
//===============================================================
void UpdateObject() {

	for (int nCnt = 0; nCnt < MAX_OBJECT_NUM; nCnt ++) {
		if (!g_tObject[nCnt].bLive)
			continue;

		//g_tObject[nCnt].nCounterAnime ++;

		/*if (g_tObject[nCnt].fPosXTex - tPlayerData->nTexSizeX - tPlayerData->fMoveXTex < tPlayerData->fPosXTex &&
			g_tObject[nCnt].fPosXTex + g_tObject[nCnt].nTexSizeX - tPlayerData->fMoveXTex > tPlayerData->fPosXTex &&
			g_tObject[nCnt].fPosYTex - tPlayerData->nTexSizeY - tPlayerData->fMoveYTex < tPlayerData->fPosYTex &&
			g_tObject[nCnt].fPosYTex + g_tObject[nCnt].nTexSizeY - tPlayerData->fMoveYTex > tPlayerData->fPosYTex) {
			//左右に移動したとき
			if (tPlayerData->fMoveXTex) {
				tPlayerData->fMoveXTex = 0;
			}
			////左に移動したとき
			//else if(tPlayerData->fPosXTex < tPlayerData->fOldPosXTex){
			//	tPlayerData->fMoveXTex = 0;
			//}
			//上下に移動したとき
			if (tPlayerData->fMoveYTex) {
				tPlayerData->fMoveYTex = 0;
			}
			////上に移動したとき
			//else if(tPlayerData->fPosYTex < tPlayerData->fOldPosYTex){
			//	tPlayerData->fMoveYTex = 0;
			//}
		}*/

	}

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	MakeVertexObject(pDevice);
}

// オブジェクトとプレイヤーの当たり判定
void HitChecktoObject() {
	static tPlayerData tPlayerDataBefore;
	tPlayerData * tPlayerData = GetPlayerData();

	for (int nCnt = 0; nCnt < MAX_OBJECT_NUM; nCnt ++) {
		if (!g_tObject[nCnt].bLive)
			continue;

		// プレイヤーとのあたり判定(未完成)
		if (tPlayerData->posModel.x < g_tObject[nCnt].posBillboard.x + (g_tObject[nCnt].sizeBillboard.x / 2.0f) &&
			tPlayerData->posModel.x > g_tObject[nCnt].posBillboard.x - (g_tObject[nCnt].sizeBillboard.x / 2.0f) &&
			tPlayerData->posModel.z < g_tObject[nCnt].posBillboard.z + (g_tObject[nCnt].sizeBillboard.x / 2.0f) &&
			tPlayerData->posModel.z > g_tObject[nCnt].posBillboard.z - (g_tObject[nCnt].sizeBillboard.x / 2.0f)) {
			if (tPlayerData->posModel.x < g_tObject[nCnt].posBillboard.x + (g_tObject[nCnt].sizeBillboard.x / 2.0f) &&
				tPlayerData->posModel.x > g_tObject[nCnt].posBillboard.x - (g_tObject[nCnt].sizeBillboard.x / 2.0f) &&
				(tPlayerDataBefore.posModel.x > g_tObject[nCnt].posBillboard.x + (g_tObject[nCnt].sizeBillboard.x / 2.0f) ||
					tPlayerDataBefore.posModel.x < g_tObject[nCnt].posBillboard.x - (g_tObject[nCnt].sizeBillboard.x / 2.0f)) && 
				tPlayerDataBefore.posModel.z < g_tObject[nCnt].posBillboard.z + (g_tObject[nCnt].sizeBillboard.x / 2.0f) &&
				tPlayerDataBefore.posModel.z > g_tObject[nCnt].posBillboard.z - (g_tObject[nCnt].sizeBillboard.x / 2.0f)) {
				tPlayerData->moveModel.x = 0;
				if (tPlayerData->posModel.x > g_tObject[nCnt].posBillboard.x)
					tPlayerData->posModel.x = g_tObject[nCnt].posBillboard.x + g_tObject[nCnt].sizeBillboard.x / 2.0f;
				if (tPlayerData->posModel.x < g_tObject[nCnt].posBillboard.x)
					tPlayerData->posModel.x = g_tObject[nCnt].posBillboard.x - g_tObject[nCnt].sizeBillboard.x / 2.0f;
			}
			if (tPlayerData->posModel.z < g_tObject[nCnt].posBillboard.z + (g_tObject[nCnt].sizeBillboard.x / 2.0f) &&
				tPlayerData->posModel.z > g_tObject[nCnt].posBillboard.z - (g_tObject[nCnt].sizeBillboard.x / 2.0f) &&
				(tPlayerDataBefore.posModel.z > g_tObject[nCnt].posBillboard.x + (g_tObject[nCnt].sizeBillboard.x / 2.0f) ||
				tPlayerDataBefore.posModel.z < g_tObject[nCnt].posBillboard.x - (g_tObject[nCnt].sizeBillboard.x / 2.0f)) &&
				tPlayerDataBefore.posModel.x < g_tObject[nCnt].posBillboard.z + (g_tObject[nCnt].sizeBillboard.x / 2.0f) &&
				tPlayerDataBefore.posModel.x > g_tObject[nCnt].posBillboard.z - (g_tObject[nCnt].sizeBillboard.x / 2.0f)) {
				tPlayerData->moveModel.z = 0;
				if (tPlayerData->posModel.z > g_tObject[nCnt].posBillboard.z)
					tPlayerData->posModel.z = g_tObject[nCnt].posBillboard.z + g_tObject[nCnt].sizeBillboard.x / 2.0f;
				if (tPlayerData->posModel.z < g_tObject[nCnt].posBillboard.z)
					tPlayerData->posModel.z = g_tObject[nCnt].posBillboard.z - g_tObject[nCnt].sizeBillboard.x / 2.0f;
			}
		}
		//g_tObject[nCnt].nCounterAnime ++;

		/*if (g_tObject[nCnt].fPosXTex - tPlayerData->nTexSizeX - tPlayerData->fMoveXTex < tPlayerData->fPosXTex &&
		g_tObject[nCnt].fPosXTex + g_tObject[nCnt].nTexSizeX - tPlayerData->fMoveXTex > tPlayerData->fPosXTex &&
		g_tObject[nCnt].fPosYTex - tPlayerData->nTexSizeY - tPlayerData->fMoveYTex < tPlayerData->fPosYTex &&
		g_tObject[nCnt].fPosYTex + g_tObject[nCnt].nTexSizeY - tPlayerData->fMoveYTex > tPlayerData->fPosYTex) {
		//左右に移動したとき
		if (tPlayerData->fMoveXTex) {
		tPlayerData->fMoveXTex = 0;
		}
		////左に移動したとき
		//else if(tPlayerData->fPosXTex < tPlayerData->fOldPosXTex){
		//	tPlayerData->fMoveXTex = 0;
		//}
		//上下に移動したとき
		if (tPlayerData->fMoveYTex) {
		tPlayerData->fMoveYTex = 0;
		}
		////上に移動したとき
		//else if(tPlayerData->fPosYTex < tPlayerData->fOldPosYTex){
		//	tPlayerData->fMoveYTex = 0;
		//}
		}*/

	}
	tPlayerDataBefore = *tPlayerData;
}
//===============================================================
//	描画処理
//===============================================================
void DrawObject() {
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxScale, mtxTranslate;
	//頂点フォーマット設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	
	/*pDevice->SetRenderState(
		D3DRS_BLENDOP,
		D3DBLENDOP_REVSUBTRACT
	);*/
	pDevice->SetRenderState(
		D3DRS_SRCBLEND,
		D3DBLEND_SRCALPHA
	);
	/*pDevice->SetRenderState(
		D3DRS_DESTBLEND,
		D3DBLEND_ONE
	);*/

	// Z比較なし
	/*pDevice->SetRenderState(
		D3DRS_ZFUNC,
		D3DCMP_ALWAYS
	);*/
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	//pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);			// αデスティネーションカラーの指定
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);			// Z比較なし

	for (int nCnt = 0; nCnt < MAX_OBJECT_NUM; nCnt ++) {
		if (!g_tObject[nCnt].bLive)
			continue;

		D3DXMatrixIdentity(&g_mtxWorldObject);
		mtxView = GetMtxView();
#if 0
		// 逆行列を求める
		D3DXMatrixInverse(
			&g_mtxWorldBillboard,
			NULL,
			&mtxView
		);
		g_mtxWorldBillboard._41 = 0.0f;
		g_mtxWorldBillboard._42 = 0.0f;
		g_mtxWorldBillboard._43 = 0.0f;	// 平行移動成分をなくす
#else
		// 転置行列を求める
		g_mtxWorldObject._11 = mtxView._11;
		g_mtxWorldObject._12 = mtxView._21;
		g_mtxWorldObject._13 = mtxView._31;
		g_mtxWorldObject._21 = mtxView._12;
		g_mtxWorldObject._22 = mtxView._22;
		g_mtxWorldObject._23 = mtxView._32;
		g_mtxWorldObject._31 = mtxView._13;
		g_mtxWorldObject._32 = mtxView._23;
		g_mtxWorldObject._33 = mtxView._33;	
		
#endif
		// スケールを反映
		D3DXMatrixScaling(&mtxScale, g_tObject[nCnt].sclBillboard.x,
										g_tObject[nCnt].sclBillboard.y,
										g_tObject[nCnt].sclBillboard.z);
		D3DXMatrixMultiply(&g_mtxWorldObject,
										&g_mtxWorldObject, &mtxScale);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, g_tObject[nCnt].posBillboard.x,
												g_tObject[nCnt].posBillboard.y,
												g_tObject[nCnt].posBillboard.z);
		D3DXMatrixMultiply(&g_mtxWorldObject,
										&g_mtxWorldObject, &mtxTranslate);

	

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldObject);

		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, g_pD3DVtxBuffObject, 0, sizeof(VERTEX_3D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_tObject[nCnt].pTextureObject);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCnt * 4), NUM_POLYGON);


		/*
		//テクスチャの設定
		pDevice->SetTexture(0, *g_tObject[nCnt].pTextureObject);
		//ポリゴン描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,
			NUM_POLYGON,
			&pVtx[0],
			sizeof(VERTEX_2D));
		*/
	}
	// ライティングを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(
		D3DRS_SRCBLEND,
		D3DBLEND_SRCALPHA
	);
	pDevice->SetRenderState(
		D3DRS_DESTBLEND,
		D3DBLEND_INVSRCALPHA
	);	

	// Z比較あり
	pDevice->SetRenderState(
		D3DRS_ZFUNC,
		D3DCMP_LESSEQUAL
	);

}

//===============================================================
//	オブジェト生成
//===============================================================
void SetInfoObject(enum_object eObject, float fPosTexX, float fPosTexY, float fPosTexZ) {
	for (int nCnt = 0; nCnt < MAX_OBJECT_NUM; nCnt ++) {
		if (g_tObject[nCnt].bLive)
			continue;

		g_tObject[nCnt].pTextureObject = g_pTextureObject[eObject];

		// オブジェクト切り替え(家とフェンスはモデルを使用するかも)
		switch (eObject) {
		case OBJECT_TREE:
			g_tObject[nCnt].sizeBillboard		= D3DXVECTOR2(OBJECT_TREE_SIZE_X, OBJECT_TREE_SIZE_Y);

			break;
		/*case OBJECT_FENCE:
			g_tObject[nCnt].nTexSizeX			= OBJECT_FENCE_SIZE_X;
			g_tObject[nCnt].nTexSizeY			= OBJECT_FENCE_SIZE_Y;
			g_tObject[nCnt].nPatternDivideX	= OBJECT_FENCE_PATTAERN_DIVIDE_X;
			g_tObject[nCnt].nPatternDivideY	= OBJECT_FENCE_PATTAERN_DIVIDE_Y;

			break;
		case OBJECT_HOUSE:
			g_tObject[nCnt].nTexSizeX			= OBJECT_HOUSE_SIZE_X;
			g_tObject[nCnt].nTexSizeY			= OBJECT_HOUSE_SIZE_Y;
			g_tObject[nCnt].nPatternDivideX	= OBJECT_HOUSE_PATTAERN_DIVIDE_X;
			g_tObject[nCnt].nPatternDivideY	= OBJECT_HOUSE_PATTAERN_DIVIDE_Y;

			break;*/
		default:
			break;

		}
		g_tObject[nCnt].posBillboard		= D3DXVECTOR3(fPosTexX, fPosTexY, fPosTexZ);
		//g_tObject[nCnt].nIdxShadowBillboard = CreateShadow(g_tObject[nCnt].posBillboard, g_tObject[nCnt].sizeBillboard.x, g_tObject[nCnt].sizeBillboard.y);
		//SetColorShadow(g_tObject[nCnt].nIdxShadowBillboard, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		g_tObject[nCnt].bLive = true;

		break;
	}
}

//===========================================================
//	頂点の設定
//===========================================================
HRESULT MakeVertexObject(LPDIRECT3DDEVICE9 pDevice) {


	// オブジェクトの頂点バッファを生成
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_OBJECT_NUM,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
												FVF_VERTEX_3D,				// 使用する頂点フォーマット
												D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
												&g_pD3DVtxBuffObject,		// 頂点バッファインターフェースへのポインタ
												NULL)))						// NULLに設定
	{
        return E_FAIL;
	}

	{
		VERTEX_3D * pVtx;
		g_pD3DVtxBuffObject->Lock(0, 0, (void**)&pVtx, 0);
		for (int nCnt = 0; nCnt < MAX_OBJECT_NUM; nCnt ++, pVtx += 4) {
			if (!g_tObject[nCnt].bLive)
				continue;


			pVtx[0].vtx = D3DXVECTOR3(-g_tObject[nCnt].sizeBillboard.x / 2, - g_tObject[nCnt].sizeBillboard.y / 2, 0.0f);	//(X, Y, Z)
			pVtx[1].vtx = D3DXVECTOR3(-g_tObject[nCnt].sizeBillboard.x / 2, g_tObject[nCnt].sizeBillboard.y / 2, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(g_tObject[nCnt].sizeBillboard.x / 2, -g_tObject[nCnt].sizeBillboard.y / 2, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(g_tObject[nCnt].sizeBillboard.x / 2, g_tObject[nCnt].sizeBillboard.y / 2, 0.0f);

			pVtx[0].normal =
				pVtx[1].normal =
				pVtx[2].normal =
				pVtx[3].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);	//

			pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			pVtx[0].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.0f, 0.0f);

		}

		g_pD3DVtxBuffObject->Unlock();
	}
	return S_OK;
}

//オブジェクト削除
void DeleteObject() {
	for (int nCnt = 0; nCnt < MAX_OBJECT_NUM; nCnt ++) {
		if (!g_tObject[nCnt].bLive)
			continue;

		g_tObject[nCnt].pTextureObject	= NULL;
		g_tObject[nCnt].posBillboard	= D3DXVECTOR3(0,0,0);
		g_tObject[nCnt].sizeBillboard	= D3DXVECTOR2(0,0);
		g_tObject[nCnt].bLive			= false;
	}
}

void DeleteObject(int nDeleteNum) {
	g_tObject[nDeleteNum].pTextureObject	= NULL;
	g_tObject[nDeleteNum].posBillboard		= D3DXVECTOR3(0,0,0);
	g_tObject[nDeleteNum].sizeBillboard		= D3DXVECTOR2(0,0);
	g_tObject[nDeleteNum].bLive				= false;
}