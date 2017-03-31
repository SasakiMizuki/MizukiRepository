//=============================================================================
//
// �r���{�[�h���� [bullet.cpp]
//
//=============================================================================
#include "bullet.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "model.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_BULLET		"data/TEXTURE/bullet000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	BULLET_SIZE_X		(6.0f)							// �r���{�[�h�̕�
#define	BULLET_SIZE_Y		(6.0f)							// �r���{�[�h�̍���
#define	VALUE_MOVE_BULLET	(0.30f)							// �ړ����x
#define	VALUE_JUMP				(10.0f)							// �W�����v��
#define	VALUE_GRAVITY			(0.45f)							// �d��
#define	RATE_REGIST				(0.075f)						// ��R�W��
#define	RATE_REFRECT			(-0.90f)						// ���ˌW��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//=============================================================================
// ����������
//=============================================================================
HRESULT CBullet::InitBullet(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_���̍쐬
	MakeVertexBullet(pDevice,D3DXVECTOR3(0.0f,0.0f,0.0f));

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
								TEXTURE_BULLET,			// �t�@�C���̖��O
								&m_pD3DTextureBullet);	// �ǂݍ��ރ������[

	m_posBullet = D3DXVECTOR3(0.0f, 18.0f, 0.0f);
	m_sclBullet = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_vecBullet = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �e�̐ݒ�
	m_nIdxShadowBullet = CreateShadow(m_posBullet, BULLET_SIZE_X, BULLET_SIZE_Y);

	SetColorShadow(m_nIdxShadowBullet, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBullet::UninitBullet(void)
{
	if(m_pD3DTextureBullet != NULL)
	{// �e�N�X�`���̊J��
		m_pD3DTextureBullet->Release();
		m_pD3DTextureBullet = NULL;
	}

	if(m_pD3DVtxBuffBullet != NULL)
	{// ���_�o�b�t�@�̊J��
		m_pD3DVtxBuffBullet->Release();
		m_pD3DVtxBuffBullet = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CBullet::UpdateBullet(void)
{
	D3DXVECTOR3 rotCamera;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	// �J�����̉�]���擾
	rotCamera = GetRotCamera();

	if(GetKeyboardPress(DIK_LEFT))
	{
		if(GetKeyboardPress(DIK_UP))
		{// ���O�ړ�
			
			
		}
		else if(GetKeyboardPress(DIK_DOWN))
		{// ����ړ�
			
			
		}
		else
		{// ���ړ�
			
			
		}
	}
	else if(GetKeyboardPress(DIK_RIGHT))
	{
		if(GetKeyboardPress(DIK_UP))
		{// �E�O�ړ�
			
			
		}
		else if(GetKeyboardPress(DIK_DOWN))
		{// �E��ړ�
			
			
		}
		else
		{// �E�ړ�
			
			
		}
	}
	else if(GetKeyboardPress(DIK_UP))
	{// �O�ړ�
		
		
	}
	else if(GetKeyboardPress(DIK_DOWN))
	{// ��ړ�
		
		
	}

	if(GetKeyboardTrigger(DIK_SPACE))
	{// �W�����v
		if(m_bEnableGravity == true)
		{	// ������֑��x��ǉ�
			m_vecBullet.y += 10.0f;
		}
	}

	if(GetKeyboardTrigger(DIK_LSHIFT)){
		MakeVertexBullet(pDevice, GetModelPos());
	}

	// �r���{�[�h�̈ړ�
	m_posBullet.x += m_vecBullet.x;
	m_posBullet.y += m_vecBullet.y;
	m_posBullet.z += m_vecBullet.z;

	// ����
	m_vecBullet.x += (0.0f - m_vecBullet.x) * RATE_REGIST;
	m_vecBullet.y += (0.0f - m_vecBullet.y) * RATE_REGIST;
	m_vecBullet.z += (0.0f - m_vecBullet.z) * RATE_REGIST;

	// �͈͊O�`�F�b�N
	

	{// �e�̐ݒ�
		// �ʒu
		SetPositionShadow(
			m_nIdxShadowBullet,
			m_posBullet
		);

		// �T�C�Y
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

		// ���l
		float colA = (400.0f - (m_posBullet.y - 9.0f)) / 800.0f;
		if(colA < 0.0f)
		{
			colA = 0.0f;
		}
		SetColorShadow(m_nIdxShadowBullet, D3DXCOLOR(1.0f, 1.0f, 1.0f, colA));
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void CBullet::DrawBullet(LPDIRECT3DDEVICE9 pDevice)
{
	D3DXMATRIX mtxView, mtxScale, mtxTranslate;

	// ���C�e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �r���[�}�g���b�N�X���擾
	mtxView = GetMtxView();

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorldBullet);

	// �|���S���𐳖ʂɌ�����
#if 0
	// �t�s������߂�
	D3DXMatrixInverse(
		&m_mtxWorldBullet,
		NULL,
		&mtxView
	);
	m_mtxWorldBullet._41 = 0.0f;
	m_mtxWorldBullet._42 = 0.0f;
	m_mtxWorldBullet._43 = 0.0f;	// ���s�ړ��������Ȃ���
#else
	// �]�u�s������߂�
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

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScale, m_sclBullet.x,
									m_sclBullet.y,
									m_sclBullet.z);
	D3DXMatrixMultiply(&m_mtxWorldBullet,
									&m_mtxWorldBullet, &mtxScale);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, m_posBullet.x,
											m_posBullet.y,
											m_posBullet.z);
	D3DXMatrixMultiply(&m_mtxWorldBullet,
									&m_mtxWorldBullet, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorldBullet);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_pD3DVtxBuffBullet, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pD3DTextureBullet);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	// ���C���e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
HRESULT CBullet::MakeVertexBullet(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 BulletPos)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
												FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&m_pD3DVtxBuffBullet,	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))						// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pD3DVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(BulletPos.x - BULLET_SIZE_X / 2, BulletPos.y - BULLET_SIZE_Y / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-BULLET_SIZE_X / 2, BULLET_SIZE_Y / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(BULLET_SIZE_X / 2, -BULLET_SIZE_Y / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(BULLET_SIZE_X / 2, BULLET_SIZE_Y / 2, 0.0f);

		// �@���̐ݒ�
		pVtx[0].normal = 
		pVtx[1].normal = 
		pVtx[2].normal = 
		pVtx[3].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
				   
		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// ���_�f�[�^���A�����b�N����
		m_pD3DVtxBuffBullet->Unlock();
	}

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void CBullet::SetVertexBullet(float fSizeX, float fSizeY)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pD3DVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-fSizeX / 2, fSizeY / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(fSizeX / 2, fSizeY / 2, 0.0f);

		// ���_�f�[�^���A�����b�N����
		m_pD3DVtxBuffBullet->Unlock();
	}
}
