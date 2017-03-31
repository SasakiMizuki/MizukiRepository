#ifndef __FADE_H__
#define __FADE_H__

#include "main.h"

typedef enum{
	FADE_NONE,
	FADE_IN,
	FADE_OUT,
	
	FADE_MAX
} eFade;
typedef struct{
	//polygon tPolygon;
	float fTexPosX;
	float fTexPosY;
	int   nTexSizeX;
	int   nTexSizeY;

	int nFadeAlpha;
	int nFadeVol;
} tFade;
#endif

void InitFade();
void UninitFade();
void UpdateFade();
void DrawFade();

void StartFadeOut();
void StartFadeIn();

eFade GetFade();