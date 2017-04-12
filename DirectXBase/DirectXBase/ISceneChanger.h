#pragma once
typedef enum {
	Scene_Title,
	Scene_Game,
	Scene_End,

	MAX_SCENE
} eEntireScene;	// 全体のシーン	
				// 追加予定(？)

class ISceneChanger
{
public:
	virtual ~ISceneChanger();
	virtual void ChangeScene();
};

