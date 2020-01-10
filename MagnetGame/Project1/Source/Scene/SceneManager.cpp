#include "SceneManager.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	m_Scenes.at(m_CurrentScene)->shutdown();
	for (auto pScene : m_Scenes)
	{
		delete pScene.second;
	}
	m_Scenes.clear();
}

void SceneManager::update()
{
	m_Scenes.at(m_CurrentScene)->update();
}

void SceneManager::draw()
{
	m_Scenes.at(m_CurrentScene)->draw();
}

void SceneManager::addScene(std::string key, AbstractScene * pAbstractScene)
{
	m_Scenes.emplace(key, pAbstractScene);
}

void SceneManager::changeScene(std::string key)
{
	//古いシーンの終了処理
	if (!m_CurrentScene.empty())
		m_Scenes.at(m_CurrentScene)->shutdown();

	m_CurrentScene = key;

	//次の開始処理
	m_Scenes.at(m_CurrentScene)->init();
}
