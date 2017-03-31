#pragma once
#include "main.h"

//----- �񋓑̐錾 -----
typedef enum{
	TITLE_BG,
	TITLE_ROGO,
	TITLE_PRESSSTART,

	TITLE_NUM_MAX
} eTitle;

typedef struct{
	float fTexPosX;
	float fTexPosY;
	int   nTexSizeX;
	int   nTexSizeY;
	float fPosXLeft;
	float fPosXRight;
	float fPosYUp;
	float fPosYDown;

	int nFadeAlpha;
} tTitle;

void InitTitle();
void UninitTitle();
void UpdateTitle();
void DrawTitle();