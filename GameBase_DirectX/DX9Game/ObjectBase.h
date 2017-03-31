#pragma once
#include "Graphics.h"
// オブジェクト種別
enum GAMEOBJID {
	ID_3DOBJ = 0,
	ID_2DOBJ,
	ID_BILLBOARD,
	ID_MESHOBJ,
	ID_CAMERA,		// カメラ
	ID_PLAYER,		// 自機
	ID_LAND,		// 地面
	ID_SKY,			// スカイドーム
	ID_ENEMY,		// 敵機
	ID_BULLET,		// 弾
	ID_MISSILE,		// 追尾弾
	ID_EXPLOSION,	// 爆発
	ID_BG,			// 背景(2d)
	ID_JINTAI,		// プレイヤー
	ID_SWORD,		// 剣
	ID_PLAYERHP,	// プレイヤーHP表示
	ID_FADE,
	ID_TREE,
	ID_FIRE,
	ID_PARTICLE,	// パーティクル

	MAX_ID			// オブジェクト種別数
};

class CSceneBase;
class CObjectBase
{
protected:
	UINT			m_uID;		// オブジェクト種別
	DWORD			m_dwDamage;	// ダメージタイマ
	D3DXMATRIX		m_world;	// ワールド変換行列
	D3DXVECTOR3		m_speed;	// 速度
	D3DXVECTOR3		m_accel;	// 加速度
	float			m_fRadius;	// 境界球半径
	D3DXVECTOR3		m_center;	// 境界球中心座標
	D3DXVECTOR3		m_bbox;		// 境界ボックス(半分のサイズ)
	CSceneBase*		m_pScene;	// 所属するシーン
	float			m_fHP;
	D3DCOLORVALUE	m_cvBColor;	// 境界球/ボックス色
	int				m_nObjNumber;	// mapでの自身のキー
public:
	CObjectBase();
	virtual ~CObjectBase();
	virtual void Init();
	virtual void Update();
	virtual void PostUpdate();
	virtual void PreDraw();
	virtual void Draw();
	virtual void DrawAlpha();	// 半透明表示
	virtual void Fin();

	virtual UINT GetID() { return m_uID; }
	virtual DWORD GetDamage() { return m_dwDamage; }
	virtual void SetDamage(DWORD dwDamage) { m_dwDamage = dwDamage; }
	virtual float GetHP() { return m_fHP; }
	virtual void SetNumber(int nNumber) { m_nObjNumber = nNumber; }
	virtual int GetNumber() { return m_nObjNumber; }
};

