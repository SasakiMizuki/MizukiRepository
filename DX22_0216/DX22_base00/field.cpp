//=============================================================================
//
// 地面処理 [field.cpp]
//
//=============================================================================
#include "field.h"
#include "input.h"
#include "model.h"
#include "Fade.h"
#include "Object.h"
#include "Item.h"
#include "3DObject.h"
#include "Message.h"
#include "explosion.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_FIELD_GRASS	"data/TEXTURE/BGTEST.png"						// 読み込むテクスチャファイル名
#define	TEXTURE_FIELD_BEACH	"data/TEXTURE/beach.jpg"						// 読み込むテクスチャファイル名

#define	FIELD_SIZE_X	(5.0f)										// 1四角形あたりの地面のサイズ(X方向)
#define	FIELD_SIZE_Z	(5.0f)										// 1四角形あたりの地面のサイズ(Z方向)

const int FIELD_DIVIDE_X(4);
const int FIELD_DIVIDE_Z(4); 
const float FLOAT_FIELD_DIVIDE_Z(4);
const float FLOAT_FIELD_DIVIDE_X(4);

#define FILED_TYPE	(0)

const float LIMIT_FIELD = 250;
const int FIRST(13);

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexField(LPDIRECT3DDEVICE9 pDevice,
	int nNumBlockX, int nNumBlockZ,
	float fSizeBlockX, float fSizeBlockZ);
void SetVerTexField();

//*****************************************************************************
// グローバル変数
//*****************************************************************************
FIELD g_tField;
static SOUND_LABEL g_eMusic;
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitField( LPDIRECT3DDEVICE9 pDevice,
	int nNumBlockX, int nNumBlockZ,
	float fSizeBlockX, float fSizeBlockZ)
{

	// テクスチャの読み込み
	if (&g_tField.pD3DTextureField[FIELD_GRASS] != NULL) {
		D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
			TEXTURE_FIELD_GRASS,			// ファイルの名前
			&g_tField.pD3DTextureField[FIELD_GRASS]);	// 読み込むメモリー	
	}
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
		TEXTURE_FIELD_BEACH,			// ファイルの名前
		&g_tField.pD3DTextureField[FIELD_BEACH]);	// 読み込むメモリー
	g_tField.FieldType = FIELD_GRASS;
	g_tField.nFieldNumber = FIRST;

	SetObjectinField();
	// 頂点情報の作成
	MakeVertexField(pDevice, nNumBlockX, nNumBlockZ, fSizeBlockX, fSizeBlockZ);

	g_eMusic = SOUND_LABEL_BGM_WAVE;

	StartFadeIn();
	ItemSetting(g_tField.nFieldNumber);
	SetObjectinField();
	Setting3DObject(g_tField.nFieldNumber);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitField(void)
{
	for (int a = 0; a < MAX_FIELD_TYPE; a ++) {
		if (g_tField.pD3DTextureField != NULL)
		{// テクスチャの開放
			g_tField.pD3DTextureField[a]->Release();
			g_tField.pD3DTextureField[a] = NULL;
		}
	}

	if(g_tField.pD3DVtxBuffField != NULL){
		//頂点バッファの解放
		g_tField.pD3DVtxBuffField->Release();
		g_tField.pD3DVtxBuffField = NULL;
	}
	
	if(g_tField.pD3DIdxBuffField){
		// インデックスバッファの解放
		g_tField.pD3DIdxBuffField->Release();
		g_tField.pD3DIdxBuffField = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateField(void)
{
	static bool bFade = false;
	static bool bMove = false;
	tPlayerData * PlayerData = GetPlayerData();
	D3DXVECTOR3 exPOS = D3DXVECTOR3(PlayerData->posModel.x,PlayerData->posModel.y + 30,PlayerData->posModel.z);


	// 東へ移動
	if (PlayerData->posModel.x > LIMIT_FIELD && ((g_tField.nFieldNumber % 4) != 3)) {
		PlayerData->posModel.x = LIMIT_FIELD;
		StartFadeOut();
		DeleteObject();
		Delete3DObject();
		DeleteItem();
		bFade = true;
	} else if(PlayerData->posModel.x > LIMIT_FIELD && ((g_tField.nFieldNumber % 4) == 3)){
		PlayerData->posModel.x = LIMIT_FIELD;
	}
	if (bFade && PlayerData->bPlayerMove && PlayerData->posModel.x == LIMIT_FIELD) {
		PlayerData->posModel.x = -LIMIT_FIELD;
		bFade = false;
		g_tField.nFieldNumber ++;
		ItemSetting(g_tField.nFieldNumber);
		SetVerTexField();
		SetObjectinField(); 
		Setting3DObject(g_tField.nFieldNumber);
		StartFadeIn();
		if (g_tField.nFieldNumber <= 11 && g_eMusic == SOUND_LABEL_BGM_WAVE) {
			StopSound();
			g_eMusic = SOUND_LABEL_BGM_BIRD;
			PlaySound(SOUND_LABEL_BGM_BIRD);
		}
		if (g_tField.nFieldNumber > 11 && g_eMusic == SOUND_LABEL_BGM_BIRD) {
			StopSound();
			g_eMusic = SOUND_LABEL_BGM_WAVE;
			PlaySound(SOUND_LABEL_BGM_WAVE);
		}
	}
	// 西へ移動
	if (PlayerData->posModel.x < -LIMIT_FIELD && (g_tField.nFieldNumber % 4)) {
		PlayerData->posModel.x = -LIMIT_FIELD;
		StartFadeOut();
		DeleteObject();
		Delete3DObject();
		DeleteItem();
		bFade = true;
	} else if (PlayerData->posModel.x < -LIMIT_FIELD && !(g_tField.nFieldNumber % 4)) {
		PlayerData->posModel.x = -LIMIT_FIELD;
	}
	if (bFade && PlayerData->bPlayerMove && PlayerData->posModel.x == -LIMIT_FIELD) {
		PlayerData->posModel.x = LIMIT_FIELD;
		bFade = false;
		g_tField.nFieldNumber --;
		ItemSetting(g_tField.nFieldNumber);
		SetVerTexField();
		SetObjectinField();
		Setting3DObject(g_tField.nFieldNumber);
		StartFadeIn();
		if (g_tField.nFieldNumber <= 11 && g_eMusic == SOUND_LABEL_BGM_WAVE) {
			StopSound();
			g_eMusic = SOUND_LABEL_BGM_BIRD;
			PlaySound(SOUND_LABEL_BGM_BIRD);
		}
		if (g_tField.nFieldNumber > 11 && g_eMusic == SOUND_LABEL_BGM_BIRD) {
			StopSound();
			g_eMusic = SOUND_LABEL_BGM_WAVE;
			PlaySound(SOUND_LABEL_BGM_WAVE);
		}
	}	
	// 北へ移動
	if (PlayerData->posModel.z > LIMIT_FIELD && (g_tField.nFieldNumber >= 4)) {
		PlayerData->posModel.z = LIMIT_FIELD;
		StartFadeOut();
		DeleteObject();
		Delete3DObject();
		DeleteItem();
		bFade = true;
	} else if (PlayerData->posModel.z > LIMIT_FIELD && (g_tField.nFieldNumber < 4)) {
 		PlayerData->posModel.z = LIMIT_FIELD;
	}
	if (bFade && PlayerData->bPlayerMove && PlayerData->posModel.z == LIMIT_FIELD) {
		PlayerData->posModel.z = -LIMIT_FIELD;
		bFade = false;
		g_tField.nFieldNumber -= 4;
		ItemSetting(g_tField.nFieldNumber);
		SetVerTexField();
		SetObjectinField();
		Setting3DObject(g_tField.nFieldNumber);
		StartFadeIn();
		if (g_tField.nFieldNumber <= 11 && g_eMusic == SOUND_LABEL_BGM_WAVE) {
			StopSound();
			g_eMusic = SOUND_LABEL_BGM_BIRD;
			PlaySound(SOUND_LABEL_BGM_BIRD);
		}
		if (g_tField.nFieldNumber > 11 && g_eMusic == SOUND_LABEL_BGM_BIRD) {
			StopSound();
			g_eMusic = SOUND_LABEL_BGM_WAVE;
			PlaySound(SOUND_LABEL_BGM_WAVE);
		}
	}
	// 南へ移動
	if (PlayerData->posModel.z < -LIMIT_FIELD && (g_tField.nFieldNumber < 12)) {
		PlayerData->posModel.z = -LIMIT_FIELD;
		SetPlayerCanMove(false);
		StartFadeOut();
		DeleteObject();
		Delete3DObject();
		DeleteItem();
		bFade = true;
	}else if(PlayerData->posModel.z < -LIMIT_FIELD && (g_tField.nFieldNumber >= 12)){
		PlayerData->posModel.z = -LIMIT_FIELD;
	}
	if (bFade && PlayerData->bPlayerMove && PlayerData->posModel.z == -LIMIT_FIELD) {
		PlayerData->posModel.z = LIMIT_FIELD;
		bFade = false;
		g_tField.nFieldNumber += 4;
		ItemSetting(g_tField.nFieldNumber);
		SetVerTexField();
		SetObjectinField();
		Setting3DObject(g_tField.nFieldNumber);
		StartFadeIn();
		if (g_tField.nFieldNumber <= 11 && g_eMusic == SOUND_LABEL_BGM_WAVE) {
			StopSound();
			g_eMusic = SOUND_LABEL_BGM_BIRD;
			PlaySound(SOUND_LABEL_BGM_BIRD);
		}
		if (g_tField.nFieldNumber > 11 && g_eMusic == SOUND_LABEL_BGM_BIRD) {
			StopSound();
			g_eMusic = SOUND_LABEL_BGM_WAVE;
			PlaySound(SOUND_LABEL_BGM_WAVE);
		}
	}

	// 移動制限、アイテム獲得
	switch (g_tField.nFieldNumber) {
	case 0:

		break;
	case 1:

		break;
	case 2:
		if (GetKeyboardTrigger(DIK_RETURN) &&
			PlayerData->posModel.x > -190.0 &&
			PlayerData->posModel.x < -100.0 &&
			PlayerData->posModel.z < 140.0 &&
			PlayerData->posModel.z > 70.0 ) {
			StartFadeOut();
			SetMessageData(50, 420, 90, "ぼろぼろの家がある", "何かあるかもしれない");
			bFade = true;
		}
		   if (bFade && PlayerData->bPlayerMove) {
			   if (GetItemFlag(ITEM_CLOTH)) {
				   if (GetItemFlag(ITEM_FLIPPERS)) {
				   } else {
					   AcquisitionItem((eItem)ITEM_FLIPPERS);
				   }
			   } else {
				   AcquisitionItem((eItem)ITEM_CLOTH);
			   }
			   bFade = false;
			   StartFadeIn();
		   }

		break;
	case 3:
		if (PlayerData->posModel.z > -85.0f)
			PlayerData->posModel.z = -85.0f;
		break;
	case 4:

		break;
	case 5:

		break;
	case 6:

		break;
	case 7:

		break;
	case 8:

		break;
	case 9:

		break;
	case 10:

		break;
	case 11:

		break;
	case 12:
		if (PlayerData->posModel.z < -10.0f) {
			PlayerData->posModel.z = -10.0f;
			SetMessageData(50, 420, 150, "ここから先は行けそうにない");

		}

		break;
	case 13:
		if (PlayerData->posModel.x <= 0.0f &&
			PlayerData->posModel.z <= -10.0f) {
			PlayerData->posModel.z = -10.0f;
			SetMessageData(50, 420, 150, "ここから先は行けそうにない");
		}
		else if (PlayerData->posModel.x > 0.0f &&
			PlayerData->posModel.z < 125.0f) {
			PlayerData->posModel.z = 125.0f;
			SetMessageData(50, 420, 150, "ここから先は行けそうにない");
		}

		break;
	case 14:
		if (PlayerData->posModel.z >= -40.0f &&
			PlayerData->posModel.z <= 125.0f) {
			if(PlayerData->posModel.z < 125.0f)
				SetExplosion(exPOS, 10, 10);
			PlayerData->posModel.z = 125.0f;
			if (!GetItemFlag(ITEM_FLIPPERS))
				SetMessageData(50, 420, 150, "ここから先は行けそうにない", "向こうにわたる手段があるかもしれない");
			else {
				SetMessageData(50, 420, 150, "ここから先は行けそうにない", "足ひれを付ければ泳げそうだ");
				if (GetKeyboardTrigger(DIK_RETURN)) {
					PlayerData->posModel.x = 120.0f;
					PlayerData->posModel.z = -70.0f;
					SetMessageData(50, 420, 150, "向こう岸へ渡った");
				}
			}
		}
		if (PlayerData->posModel.z >= -50.0f &&
			PlayerData->posModel.z <= 115.0f) {
			if(PlayerData->posModel.z > -50.0f)
				SetExplosion(exPOS, 10, 10);
			PlayerData->posModel.z = -50.0f;
			if (!GetItemFlag(ITEM_FLIPPERS))
				SetMessageData(50, 420, 150, "ここから先は行けそうにない", "向こうにわたる手段があるかもしれない");
			else{
				SetMessageData(50, 420, 150, "ここから先は行けそうにない", "足ひれを付ければ泳げそうだ");
				if (GetKeyboardTrigger(DIK_RETURN)) {
					PlayerData->posModel.x = 120.0f;
					PlayerData->posModel.z = 140.0f;
					SetMessageData(50, 420, 150, "向こう岸へ渡った");
				}
			}
		}
		if (PlayerData->posModel.z <= -50.0f &&
			PlayerData->posModel.x <= -30.0f) {
			if(PlayerData->posModel.x < -30.0f)
				SetExplosion(exPOS, 10, 10);
			PlayerData->posModel.x = -30.0f;
			if (!GetItemFlag(ITEM_FLIPPERS))
				SetMessageData(50, 420, 150, "ここから先は行けそうにない", "向こうにわたる手段があるかもしれない");
			else {
				SetMessageData(50, 420, 150, "ここから先は行けそうにない", "足ひれを付ければ泳げそうだ");
				if (GetKeyboardTrigger(DIK_RETURN)) {
					PlayerData->posModel.x = 120.0f;
					PlayerData->posModel.z = -70.0f;
					SetMessageData(50, 420, 150, "向こう岸へ渡った");
				}
			}
		}if (PlayerData->posModel.x <= 80.0f &&
			PlayerData->posModel.x >= 50.0f &&
			PlayerData->posModel.y >= 40.0f &&
			PlayerData->posModel.z <= -140.0f &&
			PlayerData->posModel.z >= -180.0f) {
			AcquisitionItem(ITEM_FOOD);
		}
		break;
	case 15:
		if (PlayerData->posModel.z >= -40.0f &&
			PlayerData->posModel.z <= 125.0f) {
			if(PlayerData->posModel.z < 125.0f)
				SetExplosion(exPOS, 10, 10);
			PlayerData->posModel.z = 125.0f;
			if (!GetItemFlag(ITEM_FLIPPERS))
				SetMessageData(50, 420, 150, "ここから先は行けそうにない", "向こうにわたる手段があるかもしれない");
			else {
				SetMessageData(50, 420, 150, "ここから先は行けそうにない", "足ひれを付ければ泳げそうだ");
				if (GetKeyboardTrigger(DIK_RETURN)) {
					PlayerData->posModel.x = -100.0f;
					PlayerData->posModel.z = -70.0f;
					SetMessageData(50, 420, 150, "向こう岸へ渡った");
				}
			}
		}
		if (PlayerData->posModel.z >= -50.0f &&
			PlayerData->posModel.z <= 115.0f) {
			if(PlayerData->posModel.z > -50.0f)
				SetExplosion(exPOS, 10, 10);
			PlayerData->posModel.z = -50.0f;
			if (!GetItemFlag(ITEM_FLIPPERS))
				SetMessageData(50, 420, 150, "ここから先は行けそうにない", "向こうにわたる手段があるかもしれない");
			else {
				SetMessageData(50, 420, 150, "ここから先は行けそうにない", "足ひれを付ければ泳げそうだ");
				if (GetKeyboardTrigger(DIK_RETURN)) {
					PlayerData->posModel.x = -100.0f;
					PlayerData->posModel.z = 140.0f;
					SetMessageData(50, 420, 150, "向こう岸へ渡った");
				}
			}
		}
		if (PlayerData->posModel.z <= -50.0f &&
			PlayerData->posModel.x >= 90.0f) {
			if(PlayerData->posModel.x > 90.0f)
				SetExplosion(exPOS, 10, 10);
			PlayerData->posModel.x = 90.0f;
			if (!GetItemFlag(ITEM_FLIPPERS))
				SetMessageData(50, 420, 150, "ここから先は行けそうにない", "向こうにわたる手段があるかもしれない");
			else {
				SetMessageData(50, 420, 150, "ここから先は行けそうにない", "足ひれを付ければ泳げそうだ");
				PlayerData->posModel.x = -100.0f;
				PlayerData->posModel.z = 140.0f;
				SetMessageData(50, 420, 150, "向こう岸へ渡った");
			}
		}
		break;

	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawField( LPDIRECT3DDEVICE9 pDevice )
{
	D3DXMatrixIdentity(&g_tField.mtxField);	// Identity:単位○○
		
	//ワールドマトリクスの設定
	pDevice->SetTransform(D3DTS_WORLD,&g_tField.mtxField);

	//頂点バッファデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, 
		g_tField.pD3DVtxBuffField, 
		0, 
		sizeof(VERTEX_3D));

	// インデックスバッファをレンダリングパイプラインに設定
	pDevice->SetIndices(g_tField.pD3DIdxBuffField);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);
	
	static bool a;

	if(a/*砂浜と草原切り替え*/) 
		//テクスチャの設定
		pDevice->SetTexture(0, g_tField.pD3DTextureField[FIELD_BEACH]);
	//テクスチャの設定
	else
		pDevice->SetTexture(0, g_tField.pD3DTextureField[FIELD_GRASS]);
	//テクスチャの削除(ポリゴンの色を出したいときなど)
	//pDevice->SetTexture(0, NULL);

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLESTRIP,	// 
		0,						// 頂点バッファのベース位置
		0,						// 頂点バッファの使用開始位置
		g_tField.nNumVertexField,
		0,						// インデックスバッファの開始位置
		g_tField.nNumPolygonField
	);
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexField(LPDIRECT3DDEVICE9 pDevice, int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ)
{
	// 頂点数(縮退ポリゴン用を考慮する)
	//g_tField.nNumVertexField = (nNumBlockX + 1) * nNumBlockZ * 2 + (nNumBlockZ - 1) * 2;
	g_tField.nNumVertexField = nNumBlockZ * 2 * ((nNumBlockX + 1) + 1) - 2;
	// ポリゴン数(縮退ポリゴン用を考慮する)
	//g_tField.nNumPolygonField = nNumBlockX * nNumBlockZ * 2 + (nNumBlockZ - 1) * 4;
	g_tField.nNumPolygonField = nNumBlockZ * 2 * (nNumBlockX + 2) - 4;
	
	// 頂点数の設定
	g_tField.nNumVertexField = (nNumBlockX + 1) * (nNumBlockZ + 1);	// インデックス数の設定(縮退ポリゴンを考慮する)
	g_tField.nNumVertexIndex = nNumBlockZ * 2 * ((nNumBlockX + 1) + 1) - 2;

	// オブジェクトの頂点バッファを生成
	if( FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * g_tField.nNumVertexField,	//頂点データ用に確保するバッファサイズ
		D3DUSAGE_WRITEONLY,				//頂点バッファの使用法
		FVF_VERTEX_3D,					//使用する頂点フォーマット
		D3DPOOL_MANAGED,				//リソースのバッファを保持するメモリクラスを指定
		&g_tField.pD3DVtxBuffField,			//頂点バッファインタフェースへのポインタ
		NULL))){
			return E_FAIL;
	}
	if(FAILED(pDevice->CreateIndexBuffer(
		sizeof(WORD) * g_tField.nNumVertexIndex,	// インデックスデータ用に確保するバッファサイズ(バイト)
		D3DUSAGE_WRITEONLY,					// 使用法
		D3DFMT_INDEX16,						// フォーマット
		D3DPOOL_MANAGED,					// リソースのバッファを保持するメモリクラスを指定
		&g_tField.pD3DIdxBuffField,
		NULL))){
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D * pVtx;

#if FILED_TYPE == 1	//1枚の四角形ポリゴンに張り付けるテクスチャのサイズ
		const float fSizeTexX = 1.0f / nNumBlockX;
		const float fSizeTexZ = 1.0f / nNumBlockZ;
#elif FILED_TYPE == 2
		const float fSizeTexX = 1.0f;
		const float fSizeTexZ = 1.0f;
#else
		const float fSizeTexX = ((1.0f / nNumBlockX) / nNumBlockX);
		const float fSizeTexZ = ((1.0f / nNumBlockZ) / nNumBlockZ);
#endif


		//頂点データの範囲をロックし頂点バッファへのポインタを取得
		g_tField.pD3DVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

		/*for(int nCntZ = 0; nCntZ < nNumBlockZ; nCntZ ++){
			if(nCntZ > 0){
				// 縮退ポリゴンのためのダブりを設定
				// 頂点座標
				pVtx[0].vtx = D3DXVECTOR3(-(nNumBlockX / 2.0f) * fSizeBlockX, 0.0f, nNumBlockZ / 2.0f * fSizeBlockZ - (nCntZ + 1) * fSizeBlockZ);

				// 法線ベクトルの設定
				pVtx[0].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

				// 反射光の設定
				pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				// テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, fSizeTexZ * (nCntZ + 1));
	
				pVtx ++;	// 次へ
	
			}
			for(int nCntX = 0; nCntX <= nNumBlockX; nCntX ++, pVtx += 2){
				float posX;
				float posZ;

				posX = (nCntX - nNumBlockX / 2) * fSizeBlockX;
				posZ = (-(nCntZ + 1) + nNumBlockZ / 2) * fSizeBlockZ;
				// 頂点座標の設定
				pVtx[0].vtx = D3DXVECTOR3(posX, 0.0f, posZ);
				pVtx[1].vtx = D3DXVECTOR3(posX, 0.0f, posZ + fSizeBlockZ);

				// 法線ベクトルの設定
				pVtx[0].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				pVtx[1].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

				// 反射光の設定
				pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				// テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(fSizeTexX * nCntX, fSizeTexZ * (nCntZ + 1));
				pVtx[1].tex = D3DXVECTOR2(fSizeTexX * nCntX, fSizeTexZ * nCntZ);
			}
			if(nCntZ < nNumBlockZ - 1){
				// 縮退ポリゴンのためのダブりを設定
				// 頂点情報のコピー
				*pVtx = *(pVtx - 1);
				pVtx ++;	// 次へ
			}

		}*/
		float posX;
		float posZ;

		for(int nCntZ = 0; nCntZ < nNumBlockZ + 1; nCntZ ++){
			for(int nCntX = 0; nCntX < nNumBlockX + 1; nCntX ++){
			posX = (nCntX - nNumBlockX / 2) * fSizeBlockX;
			posZ = (-(nCntZ + 1) + nNumBlockZ / 2) * fSizeBlockZ + fSizeBlockZ;
			pVtx[nCntZ * (nNumBlockX + 1) + nCntX].vtx = D3DXVECTOR3(posX, 0.0f, posZ);
			// 法線
			pVtx[nCntZ * (nNumBlockX + 1) + nCntX].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			// 反射光
			pVtx[nCntZ * (nNumBlockX + 1) + nCntX].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			// テクスチャ座標
			pVtx[nCntZ * (nNumBlockX + 1) + nCntX].tex = D3DXVECTOR2(fSizeTexX * (nCntX + g_tField.nFieldNumber % FIELD_DIVIDE_X * FIELD_DIVIDE_X),
																	 fSizeTexZ * ((nCntZ) + g_tField.nFieldNumber / FIELD_DIVIDE_Z * FIELD_DIVIDE_Z));
			}
		}

		//頂点データをアンロックする
		g_tField.pD3DVtxBuffField->Unlock();

	}
	// インデックスバッファの中身を埋める
	WORD* pIdx;
	
	// インデックスデータの範囲をロックし頂点バッファへのポインタを取得
	g_tField.pD3DIdxBuffField->Lock(0, 0, (void**)&pIdx, 0);
	int nCntIdx = 0;
	for(int nCntZ = 0; nCntZ < nNumBlockZ; nCntZ ++){
		if(nCntZ > 0){
			// 縮退ポリゴンのためのダブりを設定
			pIdx[nCntIdx] = (nCntZ + 1) * (nNumBlockX + 1);
			nCntIdx ++;
		}
		for(int nCntX = 0; nCntX < nNumBlockX + 1; nCntX ++){
			pIdx[nCntIdx] = (nCntZ + 1) * (nNumBlockX + 1) + nCntX;
			nCntIdx ++;
			pIdx[nCntIdx] = nCntZ * (nNumBlockX + 1) + nCntX;
			nCntIdx ++;
		}
		if(nCntZ < nNumBlockZ - 1){
			// 縮退ポリゴンのためのダブりを設定
			pIdx[nCntIdx] = nCntZ * (nNumBlockX + 1) + nNumBlockX;
			nCntIdx ++;
		}
	}

	g_tField.pD3DIdxBuffField->Unlock();

	return S_OK;
}

int GetFieldNumber() {
	return g_tField.nFieldNumber;
}

void SetVerTexField() {
	{//頂点バッファの中身を埋める
		VERTEX_3D * pVtx;

#if FILED_TYPE == 1	//1枚の四角形ポリゴンに張り付けるテクスチャのサイズ
		const float fSizeTexX = 1.0f / nNumBlockX;
		const float fSizeTexZ = 1.0f / nNumBlockZ;
#elif FILED_TYPE == 2
		const float fSizeTexX = 1.0f;
		const float fSizeTexZ = 1.0f;
#else
		const float fSizeTexX = ((1.0f / FLOAT_FIELD_DIVIDE_X) / FLOAT_FIELD_DIVIDE_X);
		const float fSizeTexZ = ((1.0f / FLOAT_FIELD_DIVIDE_Z) / FLOAT_FIELD_DIVIDE_Z);
#endif


		//頂点データの範囲をロックし頂点バッファへのポインタを取得
		g_tField.pD3DVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntZ = 0; nCntZ < FIELD_DIVIDE_Z + 1; nCntZ ++) {
			for (int nCntX = 0; nCntX < FIELD_DIVIDE_X + 1; nCntX ++) {
				pVtx[nCntZ * (FIELD_DIVIDE_X + 1) + nCntX].tex = D3DXVECTOR2(fSizeTexX * (nCntX + g_tField.nFieldNumber % FIELD_DIVIDE_X * FIELD_DIVIDE_X),
																		fSizeTexZ * ((nCntZ)+ g_tField.nFieldNumber / FIELD_DIVIDE_Z * FIELD_DIVIDE_Z));
			}
		}
		g_tField.pD3DVtxBuffField->Unlock();
	}
}

// ビルボードオブジェクト設置(現在は木のみ)
void SetObjectinField() {
	// マップ番号ごとに
	switch (g_tField.nFieldNumber) {
	case 0:

		break;
	case 1:

		break;
	case 2:

		break;
	case 3:

		break;
	case 4:
		SetInfoObject(OBJECT_TREE, 80.0f, 45.0f, 30.0f);
		SetInfoObject(OBJECT_TREE, 160.0f, 45.0f, 30.0f);
		SetInfoObject(OBJECT_TREE, 240.0f, 45.0f, 30.0f);
		SetInfoObject(OBJECT_TREE, 0.0f, 45.0f, 30.0f);
		SetInfoObject(OBJECT_TREE, 0.0f, 45.0f, -50.0f);
		SetInfoObject(OBJECT_TREE, 0.0f, 45.0f, -130.0f);
		SetInfoObject(OBJECT_TREE, 0.0f, 45.0f, -210.0f);

		break;
	case 5:
		SetInfoObject(OBJECT_TREE, 0.0f, 45.0f, -210.0f);
		SetInfoObject(OBJECT_TREE, 0.0f, 45.0f, -130.0f);
		SetInfoObject(OBJECT_TREE, 0.0f, 45.0f, -50.0f);

		break;
	case 6:

		break;
	case 7:

		break;
	case 8:
		SetInfoObject(OBJECT_TREE, 0.0f, 45.0f, 210.0f);
		SetInfoObject(OBJECT_TREE, 0.0f, 45.0f, 130.0f);

		break;
	case 9:

		break;
	case 10:

		break;
	case 11:

		break;
	case 12:

		break;
	case 13:

		break;
	case 14:

		break;
	case 15:
		SetInfoObject(OBJECT_TREE, 250.0f, 45.0f, 100.0f);
		SetInfoObject(OBJECT_TREE, 250.0f, 45.0f, 200.0f);

		break;

	}
}