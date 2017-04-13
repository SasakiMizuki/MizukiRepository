#pragma once
#include "C2DObj.h"

#define FADE_TEXTURE_PATH  _T("../data/image/fade.png")

enum eFADEMODE {
	FADEOUT,
	FADEIN
};

class CFade :
	public C2DObj
{
private:
	static bool m_bDoingFade;	// フェード中か否か
	static int	m_nFadeMode;	// フェードアウト:0　イン:1
	static int	m_nAlpha;
public:
	CFade(CSceneBase* pScene);
	virtual ~CFade();
	void Init();
	void Fin();
	void Update();
	void Draw();
	static void Start(int nMode);	// フェードアウト:0　イン:1
	void MakeVertexPolygon();
	static bool GetDoingFade() { return m_bDoingFade; }
};

