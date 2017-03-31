//=============================================================================
//
// �J�������� [camera.cpp]
//
//=============================================================================
#include "camera.h"
#include "input.h"
//#include "main.h"
#include "model.h"
#include <math.h>

//*****************************************************************************
// �}�N����`
//*****************************************************************************
const float CAMERA_MOVE_VOL (3.0f);

const float CAMRA_MOVE_RIMIT (1.0f);
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
D3DXVECTOR3		g_posCameraPoint;	// ���_
D3DXVECTOR3		g_posCameraTarget;	// �����_
D3DXVECTOR3		g_vecCameraUp;		// ��
D3DXVECTOR3		g_posCameraPointDest;//���_�̖ڕW�ʒu
D3DXVECTOR3		g_posCameraTargetDest;//�����_�̖ڕW�n�_
D3DXMATRIX		g_mtxView;			// �r���[�}�g���N�X
D3DXMATRIX		g_mtxProjection;	// �v���W�F�N�V�����}�g���N�X
D3DXVECTOR3		g_rotCamera;		// �p�x
float			RadTheta = 270.0f;
float			Radgamma = 30.0f;
float			Raddelta = 0.0f;
float			Radius = 200;

float			g_fLengthCamera;

//=============================================================================
// �J�����̏���������
//=============================================================================
HRESULT InitCamera(void)
{
	g_posCameraPoint = D3DXVECTOR3(0.0f, 100.0f, -200.0f);
	g_posCameraTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_vecCameraUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	g_rotCamera = D3DXVECTOR3(0, 0, 0);
	g_posCameraPointDest = g_posCameraPoint;
	g_posCameraTargetDest = g_posCameraTarget;

	D3DXVECTOR3 temp = g_posCameraTarget - g_posCameraPoint;
	g_fLengthCamera = D3DXVec3Length(&temp);

	return S_OK;
}

//=============================================================================
// �J�����̏I������
//=============================================================================
void UninitCamera(void)
{
}

//=============================================================================
// �J�����̍X�V����
//=============================================================================
void UpdateCamera(void)
{
	//�ړ�
	/*if(GetKeyboardPress(DIK_LEFT)){
		RadTheta -= CAMERA_MOVE_VOL;
	}
	if(GetKeyboardPress(DIK_RIGHT)){
		RadTheta += CAMERA_MOVE_VOL;
	}
	if(GetKeyboardPress(DIK_UP)){
		Radgamma -= CAMERA_MOVE_VOL;
		//RadTheta -= CAMERA_MOVE_VOL;
	}
	if(GetKeyboardPress(DIK_DOWN)){
		Radgamma += CAMERA_MOVE_VOL;
		//RadTheta += CAMERA_MOVE_VOL;
	}*/
	if(GetKeyboardPress(DIK_U)){
		Radgamma -= CAMERA_MOVE_VOL;
	}
	if(GetKeyboardPress(DIK_I)){
		Radgamma += CAMERA_MOVE_VOL;
	}
	if(GetKeyboardPress(DIK_9)){
		Radius += CAMERA_MOVE_VOL;
	}
	if(GetKeyboardPress(DIK_U)){
		g_rotCamera.y -= 0.1f;
	}
	if(GetKeyboardPress(DIK_J)){
		g_rotCamera.y += 0.1f;
	}
	if(GetKeyboardPress(DIK_C)){
		g_fLengthCamera -= 10.0f;
		if(g_fLengthCamera < 2)
			g_fLengthCamera = 2;
	}
	if(GetKeyboardPress(DIK_V)){
		g_fLengthCamera += 10.0f;
		if(g_fLengthCamera > 1000)
			g_fLengthCamera = 1000;
	}


	//if(sin(D3DXToRadian(Radgamma)) < 0){
	//	g_vecCameraUp = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	//}else{
	//	g_vecCameraUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//}

	/*g_posCameraPoint = D3DXVECTOR3(cos(D3DXToRadian(RadTheta)) * cos(D3DXToRadian(Radgamma)) * Radius,
									sin(D3DXToRadian(Radgamma)) * Radius, 
									cos(D3DXToRadian(Radgamma)) * sin(D3DXToRadian(RadTheta)) * Radius);*/

	// ���f�������苗���ɒu��
	D3DXVECTOR3 modelPos = GetModelPos();
	D3DXVECTOR3 modelRot = GetModelRot();

	// �p�^�[��3:�ڕW�ʒu��ݒ�
	g_posCameraPointDest = modelPos + D3DXVECTOR3(sin(modelRot.y) * g_fLengthCamera, 0.4f * g_fLengthCamera, cos(modelRot.y) * g_fLengthCamera);
	g_posCameraTargetDest = modelPos;
	
	g_posCameraPoint += (g_posCameraPointDest - g_posCameraPoint) * 0.20f;
	g_posCameraTarget += (g_posCameraTargetDest - g_posCameraTarget) * 0.20f;

	//D3DXVec3Normalize(&g_posCameraPoint, &g_posCameraPoint);
	
}

//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void SetCamera(LPDIRECT3DDEVICE9 pDevice)
{
	// �`��O�ɃJ���������Z�b�g����
	// �r���[�}�g���N�X�̏�����
	D3DXMatrixIdentity(&g_mtxView);
	
	// �r���[�}�g���N�X�̍쐬
	/**************�����̃��C��**************/
	D3DXMatrixLookAtLH(
		&g_mtxView,			// �i�[�p
		&g_posCameraPoint,
		&g_posCameraTarget,
		&g_vecCameraUp);
	/****************************************/
	
	// �r���[�}�g���N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_mtxView);
	
	// �v���W�F�N�V�����}�g���N�X�̏�����
	D3DXMatrixIdentity(&g_mtxProjection);
	
	// �v���W�F�N�V�����}�g���N�X�̍쐬
	/**************�����̃��C��**************/
	D3DXMatrixPerspectiveFovLH(
		&g_mtxProjection,	// �i�[��
		D3DXToRadian(60.0f),// �f�O���[���烉�W�A���l�ɕύX
		(float)SCREEN_WIDTH / SCREEN_HEIGHT,// �A�X�y�N�g��
		1.0f,
		2000.0f);
	/****************************************/
	
	// �v���W�F�N�V�����}�g���N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_mtxProjection);


}

//=============================================================================
// �J�����̌������擾
//=============================================================================
D3DXVECTOR3 GetRotCamera(void)
{
	return g_rotCamera;
}

// �r���[�̎擾
D3DXMATRIX GetMtxView(){
	return g_mtxView;
}
