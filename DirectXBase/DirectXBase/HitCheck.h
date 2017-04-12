#pragma once

#include "Enemy.h"
#include "Jintai.h"
class CHitCheck
{
public:
	~CHitCheck();
private:
	CHitCheck();
	CJintai* m_pJintai;
	CEnemy*  m_pEnemy;
	void HitCheck();

};

