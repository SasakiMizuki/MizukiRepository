#pragma once
typedef enum {
	Scene_Title,
	Scene_Game,
	Scene_End,

	MAX_SCENE
} eEntireScene;	// �S�̂̃V�[��	
				// �ǉ��\��(�H)

class ISceneChanger
{
public:
	virtual ~ISceneChanger();
	virtual void ChangeScene();
};

