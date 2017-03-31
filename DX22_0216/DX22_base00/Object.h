#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "main.h"

//----- �񋓌^ -----
typedef enum {
	OBJECT_TREE,
	OBJECT_FENCE,
	OBJECT_HOUSE,

	OBJECT_NUM_MAX
} enum_object;


//----- �\���� -----
typedef struct {
	LPDIRECT3DTEXTURE9		pD3DTextureBillboard;	// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 pD3DVtxBuffBillboard;	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

	D3DXMATRIX				mtxWorldBillboard;			// ���[���h�}�g���b�N�X
	D3DXVECTOR2				sizeBillboard;				// �傫��
	D3DXVECTOR3				posBillboard;				// �ʒu
	D3DXVECTOR3				sclBillboard;				// �g�嗦
	D3DXVECTOR3				vecBillboard;				// �ړ���
	int						nIdxShadowBillboard;		// �eID
	bool					bEnableGravity;				// �d�͎g�p�t���O
	bool					bLive;						//�����t���O

	enum_object eObject;
	LPDIRECT3DTEXTURE9  pTextureObject;	//�e�N�X�`���ւ̃|�C���^
	VERTEX_3D *pVertex;		//���_�i�[��
} object;

//----- �v���g�^�C�v -----
void InitObject();
void UninitObject();
void UpdateObject();
void DrawObject();

void DeleteObject();
void DeleteObject(int);

void HitChecktoObject();
void SetInfoObject(enum_object, float, float, float);

//void PlayerPos();



#endif