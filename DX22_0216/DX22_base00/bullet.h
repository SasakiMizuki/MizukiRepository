//=============================================================================
//
// �r���{�[�h���� [billboard.h]
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

class CBullet{
public:
	HRESULT MakeVertexBullet(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 BulletPos);
	void SetVertexBullet(float fSizeX, float fSizeY);

	HRESULT InitBullet(LPDIRECT3DDEVICE9 pDevice);
	void UninitBullet(void);
	void UpdateBullet(void);
	void DrawBullet(LPDIRECT3DDEVICE9 pDevice);

private:
	LPDIRECT3DTEXTURE9		m_pD3DTextureBullet = NULL;	// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pD3DVtxBuffBullet = NULL;	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
							
	D3DXMATRIX				m_mtxWorldBullet;			// ���[���h�}�g���b�N�X
	D3DXVECTOR3				m_posBullet;					// �ʒu
	D3DXVECTOR3				m_sclBullet;					// �X�P�[��
	D3DXVECTOR3				m_vecBullet;					// �ړ���
	int						m_nIdxShadowBullet;			// �eID
	bool					m_bEnableGravity = true;		// �d�͎g�p�t���O

};

#endif
