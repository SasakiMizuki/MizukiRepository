//=======================================================================================
//
//	  定数定義、マクロ定義
//
//=======================================================================================

#ifndef _H_DEFINE
#define _H_DEFINE

//-------- マクロ
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x)			if(x){ x->Release(); x=NULL; }
#endif
#ifndef SAFE_DELETE
#define SAFE_DELETE(x)			if(x){ delete x; x=NULL; }
#endif
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x)	if(x){ delete[] x; x=NULL; }
#endif

#define power(x) (x * x)

#define SCREEN_WIDTH	800			// スクリーンの幅
#define SCREEN_HEIGHT	600			// スクリーンの高さ
#define FRAME_RATE		(1000/60)	// フレームレート

#endif

//=======================================================================================
//	End of File
//=======================================================================================