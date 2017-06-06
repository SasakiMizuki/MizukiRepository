#pragma once
#include<d3d9.h>

class CRenderTarget
{
protected:
	// �����_�����O�^�[�Q�b�g
	LPDIRECT3DTEXTURE9 m_pTexture;	// �o�͐�e�N�X�`��
	LPDIRECT3DSURFACE9 m_pSurface;	// �o�͐�(�e�N�X�`���֘A�t��)
	LPDIRECT3DSURFACE9 m_pZBuffer;	// �o�͐�Z�o�b�t�@&�X�e���V���o�b�t�@

	// �o�b�N�o�b�t�@�ޔ�
	LPDIRECT3DSURFACE9 m_pSaveBB;
	LPDIRECT3DSURFACE9 m_pSaveZB;

public:
	CRenderTarget();
	virtual ~CRenderTarget();

	HRESULT Init();					// ����
	void Fin();						// ���
	LPDIRECT3DTEXTURE9 GetTexture() {	// �Q��
		return m_pTexture;
	}
	void Change();					// �؂�ւ�
	void Reset();					// ���ɖ߂�
};

