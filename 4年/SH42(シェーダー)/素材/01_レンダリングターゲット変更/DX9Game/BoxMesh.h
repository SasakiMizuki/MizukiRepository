#pragma once
#include "Mesh.h"
class CBoxMesh : public CMesh
{
private:
	LPDIRECT3DTEXTURE9	m_pTexture;

public:
	CBoxMesh(void);
	virtual ~CBoxMesh(void);
	void SetTexture(LPDIRECT3DTEXTURE9 pTex) {m_pTexture = pTex;}
	void Draw(D3DXMATRIX& world);
};
