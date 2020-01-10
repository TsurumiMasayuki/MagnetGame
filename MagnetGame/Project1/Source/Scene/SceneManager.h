#pragma once
#include <string>
#include <unordered_map>
#include "Scene\AbstractScene.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void update();
	void draw();

	void addScene(std::string key, AbstractScene* pAbstractScene);
	void changeScene(std::string key);

private:
	std::string m_CurrentScene;
	std::unordered_map<std::string, AbstractScene*> m_Scenes;
};

