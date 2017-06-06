// �����_�����O �^�[�Q�b�g�ύX
#pragma once
#include <d3d9.h>

#define MAX_TEXTURE	3
#define MAX_TARGET 2

class CRenderTarget
{
protected:
	// �����_�����O �^�[�Q�b�g
	LPDIRECT3DTEXTURE9	m_pTexture[MAX_TEXTURE];	// �o�͐�e�N�X�`��
	LPDIRECT3DSURFACE9	m_pSurface[MAX_TEXTURE];	// �o�͐�(�e�N�X�`�����֘A�t)
	LPDIRECT3DSURFACE9	m_pZBuffer[MAX_TARGET];	// �o�͐�Z�o�b�t�@&�X�e���V���o�b�t�@

	// �o�b�N�o�b�t�@�ޔ�
	LPDIRECT3DSURFACE9	m_pSaveBB[MAX_TARGET];
	LPDIRECT3DSURFACE9	m_pSaveZB;
	D3DVIEWPORT9		m_vpSave;
public:
	CRenderTarget(void);
	virtual ~CRenderTarget(void);

	HRESULT Init();						// ����
	void Fin();							// ���
	LPDIRECT3DTEXTURE9 GetTexture(UINT uIdx = 0)		// �Q��
	{
		return m_pTexture[uIdx];
	}
	void Save();
	void Change(UINT uTarget);						// �؂�ւ�
	void Reset();						// ���ɖ߂�
};
