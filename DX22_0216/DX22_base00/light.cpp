//=============================================================================
//
// ���C�g���� [light.cpp]
//
//=============================================================================
#include "light.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
D3DLIGHT9 g_light;
D3DLIGHT9 g_light2;

float vol = 0.0f;
float Redvol = 0.003f;
float Greenvol = 0.002f;
float Bluevol = 0.005f;

//=============================================================================
// ���C�g�̏���������
//=============================================================================
HRESULT InitLight(LPDIRECT3DDEVICE9 pDevice)
{
	/*// ���C�g��L���ɂ���
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	// �A���r�G���g���C�g�i�����j��ݒ肷��
	g_pD3DDevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff);
	// �X�y�L�����i���ʔ��ˁj��L���ɂ���
	g_pD3DDevice->SetRenderState(D3DRS_SPECULARENABLE, TRUE);

	// ���C�g�����Ă�i���F�ŋ��ʔ��˂���ɐݒ�j
	D3DXVECTOR3 vecDirection(0, -1, -1);			// ���̌��������߂�
	D3DLIGHT9 light = {D3DLIGHT_DIRECTIONAL};	// ���C�g�I�u�W�F�N�g
	light.Diffuse.r  = 1.0f;
	light.Diffuse.g  = 1.0f;
	light.Diffuse.b  = 1.0f;
	light.Specular.r = 0.0f;
	light.Specular.g = 0.0f;
	light.Specular.b = 0.0f;
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDirection);
	g_pD3DDevice->SetLight(0, &light);
	g_pD3DDevice->LightEnable(0, TRUE);			// ���C�g�O��L��*/
	
	// ���C�g�̏��N���A
	ZeroMemory(&g_light, sizeof(D3DLIGHT9));
	// ���C�g�̃^�C�v�̐ݒ�
	g_light.Type = D3DLIGHT_DIRECTIONAL; // ���s����
	// ����
	D3DXVECTOR3 vecDir;
	vecDir = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&g_light.Direction, &vecDir);	// 3�����x�N�g���̐��K��
	// �f�B�t���[�Y(�g�U���ˌ�)
	g_light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	// �A���r�G���g(����)
	g_light.Ambient = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
		
	//g_light.Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	// ���C�g�̏��N���A
	ZeroMemory(&g_light2, sizeof(D3DLIGHT9));
	// ���C�g�̃^�C�v�̐ݒ�
	g_light2.Type = D3DLIGHT_DIRECTIONAL; // �^�C�v
	// ����
	D3DXVECTOR3 vecDir2;
	vecDir2 = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&g_light2.Direction, &vecDir2);	// 3�����x�N�g���̐��K��
	
	//g_light2.Direction.y = -1.0f;

	// �f�B�t���[�Y(�g�U���ˌ�)
	g_light2.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	// �A���r�G���g(����)
	//g_light2.Ambient = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

	g_light2.Specular = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

	//g_light2.Position = D3DXVECTOR3(-1.0f, 40.0f, -15.0f);

	//g_light2.Falloff = 1.0f;
	//g_light2.Theta = D3DXToRadian(100.0f);
	//g_light2.Phi = D3DXToRadian(300.0f);
	//g_light2.Range = 1200.0f;
	//
	//g_light2.Attenuation0 = 1.0f;
	

	// ���C�g�������_�����O�p�C�v���C���ɐݒ�
	pDevice->SetLight(0, &g_light);
	pDevice->SetLight(1, &g_light2);
	// ���C�g�̐ݒ�
	pDevice->LightEnable(0, TRUE);	//(���C�g�̔ԍ�, OnOff)
	pDevice->LightEnable(1, TRUE);	

	// �����_�[�X�e�[�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	return S_OK;
}

//=============================================================================
// ���C�g�̏I������
//=============================================================================
void UninitLight(void)
{
	
}

//=============================================================================
// ���C�g�̍X�V����
//=============================================================================
void UpdateLight(LPDIRECT3DDEVICE9 pDevice)
{

	D3DXVECTOR3 vecDir;
	static float LightX;
	
	static float Red = 0.0f;
	static float Green = 0.0f;
	static float Blue = 0.0f;
	static float Alpha = 1.0f;

	LightX += vol;
	Red		+= Redvol;
	Green	+= Greenvol;
	Blue	+= Bluevol;

	/*if(LightX > 1.0f){
		LightX = 1.0f;
		vol *= -1;
	}else if(LightX < -1.0){
		LightX = -1.0f;
		vol *= -1;
	}	
	if(Red > 1.0f){
		Red = 1.0f;
		Redvol *= -1;
	}else if(Red < -1.0){
		Red = -1.0f;
		Redvol *= -1;
	}	
	if(Green > 1.0f){
		Green = 1.0f;
		Greenvol *= -1;
	}else if(Green < -1.0){
		Green = -1.0f;
		Greenvol *= -1;
	}	
	if(Blue > 1.0f){
		Blue = 1.0f;
		Bluevol *= -1;
	}else if(Blue < -1.0){
		Blue = -1.0f;
		Bluevol *= -1;
	}

	vecDir = D3DXVECTOR3(LightX, -1.0f, 0.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&g_light.Direction, &vecDir);	// 3�����x�N�g���̐��K��
	
	g_light.Diffuse = D3DXCOLOR(Red, Blue, Green, Alpha);
	// ���C�g�������_�����O�p�C�v���C���ɐݒ�
	pDevice->SetLight(0, &g_light);
	// ���C�g�̐ݒ�
	//pDevice->LightEnable(0, TRUE);	//(���C�g�̔ԍ�, OnOff)
	// �����_�[�X�e�[�g�̐ݒ�
	//pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);*/
}

