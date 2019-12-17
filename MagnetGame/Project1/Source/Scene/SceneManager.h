#pragma once
#include <string>
#include <unordered_map>
#include "Scene\AbstractScene.h"

class RenderManager;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void update(float deltaTime);
	void draw(RenderManager* pRenderManager);

	void addScene(std::string key, AbstractScene* pAbstractScene);
	void changeScene(std::string key);

private:
	std::string m_CurrentScene;
	std::unordered_map<std::string, AbstractScene*> m_Scenes;
};

