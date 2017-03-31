#pragma once
#include "C2DObj.h"
#include "Camera.h"

#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE| D3DFVF_TEX1)

// ��L�R�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct {
	D3DXVECTOR3 vtx;		//���_���W
	D3DXVECTOR3 normal;		//�@���x�N�g��
	D3DCOLOR	diffuse;	//���ˌ�
	D3DXVECTOR2 tex;		//�e�N�X�`�����W
} VERTEX_3D;

class CBillboard :
	public C2DObj
{
protected:
	CCamera* m_pCamera;	// �J�����ւ̃|�C���^
	D3DXVECTOR2 m_Size;	// �傫��
	VERTEX_3D   m_Vertex3D;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffer;
	D3DXVECTOR3 m_Scale;
public:
	CBillboard(CSceneBase* pScene);
	virtual ~CBillboard();
	virtual void Init();
	virtual void Fin();
	virtual void Update();
	virtual void Draw();
	virtual void MakeVertex();
};

