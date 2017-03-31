// ���b�V�� �I�u�W�F�N�g �N���X��`

#pragma once
#include "C3DObj.h"
#include "HierarMesh.h"

class CMeshObj : public C3DObj
{
protected:
	CMesh*			m_pMesh;

public:
	CMeshObj(CSceneBase* pScene);
	virtual ~CMeshObj(void);

	virtual void Init();		// ������
	virtual void Update();		// �X�V
	virtual void Draw();		// �\��
	virtual void Fin();			// �I������
	virtual void SetMesh(CMesh* pMesh);
	CMesh* GetMesh() {return m_pMesh;}

	bool Intersect(D3DXVECTOR3& L0,
		D3DXVECTOR3& L1,
		bool bRay = false,
		D3DXVECTOR3* pCross = NULL,
		D3DXVECTOR3* pNormal = NULL);
	void SetBColor(float r, float g, float b, float a) { m_cvBColor.r = r; m_cvBColor.g = g; m_cvBColor.b = b; m_cvBColor.a = a; }
	DWORD GetPieceCount();
	void GetInitPiece(PIECE* pPiece);
};