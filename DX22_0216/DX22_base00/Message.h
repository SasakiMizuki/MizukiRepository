#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include "main.h"

//----- �񋓑̐錾 -----

//----- �\���̐錾 -----

//----- �v���g�^�C�v�錾 -----
void InitMessage(void);
void UninitMessage(void);
void UpdateMessage(void);
void DrawMessage(void);

void SetMessageData(int,int,int,char*);				//Message�Z�b�g(X���W,Y���W,��������(frame),���b�Z�[�W���e)
void SetMessageData(int,int,int,char*,char*);
void SetMessageData(int,int,int,char*,char*,char*);
#endif