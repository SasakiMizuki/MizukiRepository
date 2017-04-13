// 3Dオブジェクト クラス定義
#pragma once

#include "Graphics.h"
#include "ObjectBase.h"

// 描画方法
enum ESynthetic {
	eNone = 0,		// 通常描画
	eAdditive,		// 加算合成
	eAlphaBlend,	// 半透明合成
	eSubtractive,	// 減算合成

	eMaxSynthetic
};

class CSceneBase;

class C3DObj : public CObjectBase
{
protected:

	ESynthetic		m_synthetic;	// 半透明描画フラグ
	float			m_fDepth;		// カメラからの距離

public:
	C3DObj(CSceneBase* pScene);
	virtual ~C3DObj(void);

	virtual void Init();		// 初期化
	virtual void Update();		// 更新
	virtual void PostUpdate();		// 更新
	virtual void PreDraw();
	virtual void Draw();		// 表示
	virtual void DrawAlpha();	// 半透明表示
	virtual void Fin();			// 終了処理
	D3DXMATRIX& GetWorld() {return m_world;}
	void SetWorld(D3DXMATRIX& world) { m_world = world; }
	virtual float GetRadius();	// 境界球半径取得
	void SetRadius(float fRadius) { m_fRadius = fRadius; }
	virtual D3DXVECTOR3& GetCenter();	// 境界球中心座標取得
	void SetCenter(D3DXVECTOR3& vCenter) { m_center = vCenter; }
	virtual D3DXVECTOR3& GetBBox();	// 境界ボックス取得
	void SetBBox(D3DXVECTOR3& vBBox) { m_bbox = vBBox; }
	D3DXVECTOR3 GetPos();		// 座標取得
	void SetPos(D3DXVECTOR3& pos) {m_world._41 = pos.x; m_world._42 = pos.y; m_world._43 = pos.z;}
	D3DXVECTOR3 GetForward();	// 前方ベクトル取得
	D3DXVECTOR3 GetRight();		// 右ベクトル取得
	D3DXVECTOR3 GetUp();		// 上方ベクトル取得
	CObjectBase* Find(UINT uID, CObjectBase* p = NULL);
	bool CollisionBSphere(C3DObj* pObj);
	bool CollisionAABB(C3DObj* pObj);
	bool CollisionOBB(C3DObj* pObj);
	CSceneBase* GetScene() {return m_pScene;}
	D3DXVECTOR3& GetSpeed() {return m_speed;}
	virtual void UpdateDamage() {if (m_dwDamage) --m_dwDamage;}
	void SetSpeed(D3DXVECTOR3& speed) {m_speed = speed;}
	virtual void SetSynthetic(ESynthetic synthetic) { m_synthetic = synthetic; }
	virtual ESynthetic GetSynthetic(void) { return (this) ? m_synthetic : eNone; }
	float GetDepth() { return m_fDepth; }
	void SetDepth(float fDepth) { m_fDepth = fDepth; }
	static int CmpDepth(const void* pLeft, const void* pRight);

};