#pragma once

#include <vector>
#include "C3DObj.h"
#include "Tree.h"

class CTreeManager:public C3DObj
{
private:
	std::vector<CTree> vecTree;

public:
	CTreeManager(CSceneBase* pScene);
	virtual ~CTreeManager();
	void Init();
	void Fin();
	void Draw(CShader* pShader = NULL);
};

