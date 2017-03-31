#pragma once
#include "C3DObj.h"
#include "Camera.h"

enum EParticleCoord {
	eCartesian = 0,				// 直交座標系(x,y,z)
	eSpherical,					// 球座標系(r,φ,θ)
	eCylindrical,				// 円筒座標系(r,h,θ)

	eMaxParticleCoord
};

struct TParticleParam
{
	ESynthetic		synthetic;			// 描画方法
	EParticleCoord	coord;				// 座標系
	float			fDuration;			// 生成周期
	UINT			uMaxParticles;		// 最大パーティクル数
	bool			bLooping;			// 繰り返し
	float			fGravity;			// 重力加速度
	float			fStartSpeed;		// 初速
	float			fStartSpeed2;		// 初速2
	float			fStartSize;			// 初期サイズ
	float			fStartSize2;		// 初期サイズ2
	float			fStartRotation;		// 初期角度
	float			fStartRotation2;	// 初期角度2
	D3DCOLOR		cStartColor;		// 初期カラー
	D3DCOLOR		cStartColor2;		// 初期カラー2
	float			fStartLifetime;		// 寿命
	float			fStartLifetime2;	// 寿命2
	UINT			uRate;				// 1秒あたりのパーティクル生成数
	float			fCornAngle;			// コーン角度
	float			fRadius;			// 半径(180:半球、360:球)
	bool			bColorOverLifetime;	// 生存時間で色を変更(初期カラーが無効になる)
	D3DCOLOR		cOverLifetime[2];	// [0]:開始色、[1]:終了色
	bool			bSizeOverLifetime;	// 生存時間でサイズを変更(初期サイズが無効になる)
	float			fOverLifetime[2];	// [0]:開始サイズ、[1]:終了サイズ
	TCHAR			szTexFName[_MAX_PATH];	// テクスチャファイル名
};

class CParticle : public C3DObj
{
private:
	CCamera*			m_pCamera;
	LPDIRECT3DTEXTURE9	m_pTexture;
	TCHAR				m_szTexFName[_MAX_PATH];	// テクスチャファイル名

	TParticleParam		m_pp;
	float				m_fTime;			// パーティクル生成時間
	float				m_fRate;			// パーティクル生成数ワーク
	UINT				m_uParticles;		// 残りパーティクル数

	struct TGrain {
		TGrain*		m_pBack;
		TGrain*		m_pNext;
		D3DXVECTOR3	m_pos;
		D3DXVECTOR3	m_startPos;
		D3DXVECTOR3	m_velocity;
		D3DXVECTOR3	m_accel;
		float		m_size;
		float		m_startSize;
		float		m_angle;
		D3DCOLOR	m_color;
		D3DCOLOR	m_startColor;
		float		m_lifetime;
		float		m_startLifetime;
	};
	TGrain*		m_pGrain;
	TGrain*		m_pUse;
	TGrain*		m_pUnused;
	UINT		m_uUse;
	struct TVertex {
		D3DVECTOR	m_pos;
		D3DVECTOR	m_normal;
		D3DCOLOR	m_diffuse;
		float		m_u, m_v;
	};
	TVertex*	m_pVertex;
	WORD*		m_pIndex;

	bool		m_bPlay;	// 再生中フラグ
public:
	CParticle(CSceneBase* pScene);
	CParticle(CSceneBase* pScene, TParticleParam* ppp);
	virtual ~CParticle(void);

	virtual void PostInit(void);
	void Delete(TGrain* p);
	TGrain* New(void);
	virtual void Update(void);
	virtual void Draw(void);
	virtual void DrawAlpha(void);
	virtual void Fin(void);
	void DrawLast(void);
	void GetDebugString(LPTSTR pszText);
	void SetParam(TParticleParam& pp);
	void GetDefaultParam(TParticleParam& pp);
	void ChangeUse(bool bUse, D3DXMATRIX world);

private:
	void UpdateTexture(void);
};