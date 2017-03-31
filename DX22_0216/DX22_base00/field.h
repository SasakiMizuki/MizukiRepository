//=============================================================================
//
// �n�ʏ��� [field.h]
//
//=============================================================================
#ifndef _FIELD_H_
#define _FIELD_H_

#include "main.h"

typedef enum{
	FIELD_GRASS,
	FIELD_BEACH,

	MAX_FIELD_TYPE
}eFieldType;
typedef struct {
	LPDIRECT3DTEXTURE9		pD3DTextureField[MAX_FIELD_TYPE];	// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 pD3DVtxBuffField;	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
	D3DXMATRIX				mtxField;

	int						nNumVertexField;	//�����_��
	int						nNumPolygonField;	//���|���S����
	LPDIRECT3DINDEXBUFFER9	pD3DIdxBuffField;	// �C���f�b�N�X�o�b�t�@�C���^�t�F�[�X�ւ̃|�C���^
	int						nNumVertexIndex;	// ���C���f�b�N�X��

	int						nFieldNumber;
	eFieldType				FieldType;
} FIELD;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitField(LPDIRECT3DDEVICE9, int, int, float, float);
void UninitField(void);
void UpdateField(void);
void DrawField(LPDIRECT3DDEVICE9);
int  GetFieldNumber();
void SetObjectinField();

#endif
