#include "Billboard.h"


//�R���X�g���N�^
CBillboard::CBillboard(CSceneBase* pScene):
C2DObj(pScene){
	m_uID = ID_BILLBOARD;
}

// �f�X�g���N�^
CBillboard::~CBillboard() {
}

// ������
void CBillboard::Init() {
	// �e�N�X�`���̎擾
	D3DXCreateTextureFromFile(CGraphics::GetDevice(), (LPCSTR)m_pszTexName, &m_pTexture);

	// �J�����̌���
	m_pCamera = (CCamera*)Find(ID_CAMERA);

	// �T�C�Y������
	m_Size = D3DXVECTOR2(0.0f,0.0f);

	MakeVertex();
	//MakeVertex();
}

// �I������
void CBillboard::Fin() {
	if (m_pTexture) {
		m_pTexture->Release();
		m_pTexture = NULL;
	}
	if (m_pVtxBuffer != NULL) {// ���_�o�b�t�@�̊J��
		m_pVtxBuffer->Release();
		m_pVtxBuffer = NULL;
	}
}

// �X�V����
void CBillboard::Update() {
	D3DXMATRIX mtxScale;

	D3DXMatrixIdentity(&m_world);

	// �]�u�s������߂�
	m_world._11 = m_pCamera->GetView()._11;
	m_world._12 = m_pCamera->GetView()._21;
	m_world._13 = m_pCamera->GetView()._31;
	m_world._21 = m_pCamera->GetView()._12;
	m_world._22 = m_pCamera->GetView()._22;
	m_world._23 = m_pCamera->GetView()._32;
	m_world._31 = m_pCamera->GetView()._13;
	m_world._32 = m_pCamera->GetView()._23;
	m_world._33 = m_pCamera->GetView()._33;

	// �X�P�[���𔽉f
	/*D3DXMatrixScaling(&mtxScale, m_Scale.x,
		m_Scale.y,
		m_Scale.z);
	D3DXMatrixMultiply(&m_world,
		&m_world, &mtxScale);*/
}

// �`��
void CBillboard::Draw() {
	D3DXMATRIX mtxTranslate;
	// ���C�g����
	CGraphics::GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);


	// �ړ��𔽉f
	//D3DXMatrixTranslation(&mtxTranslate, m_world._41, m_world._42, m_world._43);
	//D3DXMatrixMultiply(&m_world,
	//	&m_world, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	CGraphics::GetDevice()->SetTransform(D3DTS_WORLD, &m_world);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	CGraphics::GetDevice()->SetStreamSource(0, m_pVtxBuffer, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	CGraphics::GetDevice()->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	CGraphics::GetDevice()->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	CGraphics::GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	// ���C�e�B���O��L���ɂ���
	CGraphics::GetDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);

}
//=============================================================================
// ���_���̍쐬
//=============================================================================
void CBillboard::MakeVertex() {
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	CGraphics::GetDevice()->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&m_pVtxBuffer,			// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL);						// NULL�ɐݒ�

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-m_Size.x / 2, -m_Size.y / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-m_Size.x / 2, m_Size.y / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(m_Size.x / 2, -m_Size.y / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(m_Size.x / 2, m_Size.y / 2, 0.0f);

		// �@���̐ݒ�
		pVtx[0].normal =
			pVtx[1].normal =
			pVtx[2].normal =
			pVtx[3].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// ���_�f�[�^���A�����b�N����
		m_pVtxBuffer->Unlock();
	}
}
