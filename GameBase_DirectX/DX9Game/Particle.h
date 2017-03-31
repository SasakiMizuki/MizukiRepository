#pragma once
#include "C3DObj.h"
#include "Camera.h"

enum EParticleCoord {
	eCartesian = 0,				// �������W�n(x,y,z)
	eSpherical,					// �����W�n(r,��,��)
	eCylindrical,				// �~�����W�n(r,h,��)

	eMaxParticleCoord
};

struct TParticleParam
{
	ESynthetic		synthetic;			// �`����@
	EParticleCoord	coord;				// ���W�n
	float			fDuration;			// ��������
	UINT			uMaxParticles;		// �ő�p�[�e�B�N����
	bool			bLooping;			// �J��Ԃ�
	float			fGravity;			// �d�͉����x
	float			fStartSpeed;		// ����
	float			fStartSpeed2;		// ����2
	float			fStartSize;			// �����T�C�Y
	float			fStartSize2;		// �����T�C�Y2
	float			fStartRotation;		// �����p�x
	float			fStartRotation2;	// �����p�x2
	D3DCOLOR		cStartColor;		// �����J���[
	D3DCOLOR		cStartColor2;		// �����J���[2
	float			fStartLifetime;		// ����
	float			fStartLifetime2;	// ����2
	UINT			uRate;				// 1�b������̃p�[�e�B�N��������
	float			fCornAngle;			// �R�[���p�x
	float			fRadius;			// ���a(180:�����A360:��)
	bool			bColorOverLifetime;	// �������ԂŐF��ύX(�����J���[�������ɂȂ�)
	D3DCOLOR		cOverLifetime[2];	// [0]:�J�n�F�A[1]:�I���F
	bool			bSizeOverLifetime;	// �������ԂŃT�C�Y��ύX(�����T�C�Y�������ɂȂ�)
	float			fOverLifetime[2];	// [0]:�J�n�T�C�Y�A[1]:�I���T�C�Y
	TCHAR			szTexFName[_MAX_PATH];	// �e�N�X�`���t�@�C����
};

class CParticle : public C3DObj
{
private:
	CCamera*			m_pCamera;
	LPDIRECT3DTEXTURE9	m_pTexture;
	TCHAR				m_szTexFName[_MAX_PATH];	// �e�N�X�`���t�@�C����

	TParticleParam		m_pp;
	float				m_fTime;			// �p�[�e�B�N����������
	float				m_fRate;			// �p�[�e�B�N�����������[�N
	UINT				m_uParticles;		// �c��p�[�e�B�N����

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

	bool		m_bPlay;	// �Đ����t���O
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