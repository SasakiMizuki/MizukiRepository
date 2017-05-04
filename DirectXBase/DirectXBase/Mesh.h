//=======================================================================================
//
//	  ���b�V�� �N���X��`
//
//=======================================================================================
#pragma once
#include <windows.h>		// Windows�v���O�����ɂ͂����t����
#include <tchar.h>			// �ėp�e�L�X�g �}�b�s���O
#include <d3d9.h>			// DirectX Graphics �֘A�̃w�b�_
#include <d3dx9.h>			// DirectX Graphics �֘A�̃w�b�_
#include "Shader.h"
// ���_�t�H�[�}�b�g
struct MVERTEX
{
	D3DVECTOR	pos;		// ���_���W
	D3DVECTOR	normal;		// �@���x�N�g��
	float		u, v;		// �e�N�X�`�����W
};
#define FVF_MVERTEX	(D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1)

// �j��
struct PIECE
{
	MVERTEX			v[3];	// �O�p�`�̍��W(�d�S�����_)
	D3DXMATRIX		world;	// ���[���h�ϊ�
	D3DXVECTOR3		speed;	// ���x
	D3DXVECTOR3		accel;	// �����x
	D3DCOLORVALUE	color;	// �F
	D3DXVECTOR3		axis;	// ��]��
	float			rspeed;	// ��]���x
};

class CMesh
{
private:
	LPD3DXMESH				m_pD3DMesh;		// D3DXMesh �I�u�W�F�N�g
	DWORD					m_dwNumMaterial;// �}�e���A����
	D3DMATERIAL9*			m_pMaterial;	// �}�e���A��
	LPDIRECT3DTEXTURE9*		m_ppTexture;	// �e�N�X�`��
	LPD3DXATTRIBUTERANGE	m_pAttr;		// �����e�[�u��
	DWORD					m_dwAttr;		// ������

	D3DXVECTOR3				m_vBBox;		// ���E�{�b�N�X(�����̃T�C�Y)
	D3DXVECTOR3				m_vCenter;		// ���E��/���E�{�b�N�X���S���W
	float					m_fRadius;		// ���E��(���a)

	LPD3DXMESH				m_pBBox;		// ���E�{�b�N�X ���b�V��
	LPD3DXMESH				m_pBSphere;		// ���E�����b�V��
	D3DCOLORVALUE			m_cvBColor;		// ���E��/�{�b�N�X�F

	PIECE*					m_pInitPiece;	// �j�Џ����l
	PIECE*					m_pPiece;		// �j��
	DWORD					m_dwPiece;		// �j�Ђ̐�
	DWORD					m_dwTime;		// �o�߃t���[����

public:
	CMesh();								// �R���X�g���N�^
	virtual ~CMesh();						// �f�X�g���N�^
	virtual bool Initialize(LPCTSTR pszFName, bool bReverse = false);	// ���b�V��������
	virtual void Finalize();						// ���b�V�����
	virtual void Draw(D3DXMATRIX& world, CShader* pShader);	// ���b�V���`��
	virtual void DrawNoAlpha(D3DXMATRIX& world);	// �s���������`��
	virtual void DrawAlpha(D3DXMATRIX& world);		// �����������`��
	virtual D3DXVECTOR3& GetBBox() {return m_vBBox;}
	virtual D3DXVECTOR3& GetCenter() {return m_vCenter;}
	virtual float GetRadius() {return m_fRadius;}
	virtual	void DrawOBB(D3DXMATRIX& world);
	virtual void DrawAABB(D3DXMATRIX& world);		// ���E�{�b�N�X�`��
	virtual void DrawBSphere(D3DXMATRIX& world);	// ���E���`��
	virtual void SetBColor(D3DCOLORVALUE& cvBColor) {m_cvBColor = cvBColor;}
	virtual void SetBColor(float r, float g, float b, float a) {m_cvBColor.r = r; m_cvBColor.g = g; m_cvBColor.b = b; m_cvBColor.a = a;}
	virtual D3DCOLORVALUE& GetBColor() {return m_cvBColor;}

	virtual bool Intersect(D3DXVECTOR3& L0,
		D3DXVECTOR3& L1,
		bool bRay = false,
		D3DXVECTOR3* pCross = NULL,
		D3DXVECTOR3* pNormal = NULL,
		D3DXMATRIX* pWorld = NULL);

	virtual void DrawPiece();					// �j�Е`��
	virtual void InitPiece(D3DXMATRIX& world);	// �j�Џ�����
	virtual void UpdatePiece();					// �j�ЍX�V
	virtual void FinPiece();					// �j�Ќ�Еt��
	virtual DWORD GetPieceCount() {return m_dwPiece;}
	virtual void GetInitPiece(PIECE* pPiece);
};

//=======================================================================================
//	End of File
//=======================================================================================