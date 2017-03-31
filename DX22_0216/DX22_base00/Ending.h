#pragma once
#include "main.h"

typedef struct {
	float fTexPosX;
	float fTexPosY;
	int   nTexSizeX;
	int   nTexSizeY;
	float fPosXLeft;
	float fPosXRight;
	float fPosYUp;
	float fPosYDown;

	int nFadeAlpha;
	int nFadeVol;
} tEnding;

void InitEnding();
void UninitEnding();
void UpdateEnding();
void DrawEnding();