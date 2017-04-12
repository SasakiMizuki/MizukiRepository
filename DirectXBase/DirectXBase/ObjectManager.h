/*
#pragma once

#include <vector>
#include "ObjectBase.h"

class CObjectManager
{
private:
	std::vector<CObjectBase*> m_vObj;
	std::vector<CObjectBase*>::iterator itr;

	CObjectManager();
public:
	static CObjectManager* Instance();
	auto Add(CObjectBase*);
	void Del(std::vector<CObjectBase*>::iterator);
	void Init();
	void Update();
	void Fin();
	~CObjectManager();
};
*/