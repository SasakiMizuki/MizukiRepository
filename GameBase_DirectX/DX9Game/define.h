//=======================================================================================
//
//	  �萔��`�A�}�N����`
//
//=======================================================================================

#ifndef _H_DEFINE
#define _H_DEFINE

//-------- �}�N��
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

#define SCREEN_WIDTH	800			// �X�N���[���̕�
#define SCREEN_HEIGHT	600			// �X�N���[���̍���
#define FRAME_RATE		(1000/60)	// �t���[�����[�g

#endif

//=======================================================================================
//	End of File
//=======================================================================================