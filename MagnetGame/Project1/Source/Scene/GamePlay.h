#pragma once
#include "AbstractScene.h"
#include "Actor\IGameMediator.h"
#include "Math\Vec2.h"

class GameObjectManager;
class Player;
class Stage;
class PauseObject;
class TitleBackGround;
class EventText;
class TitleFade;
class FadeOut;
class ButtonTex;
class ExText;
class Hint;
class NameTexture;
class BackGround;

class GamePlay :
	public AbstractScene, IGameMediator {
public:
	GamePlay();
	~GamePlay();
	virtual void init() override;
	virtual void update() override;
	virtual void draw() override;
	virtual void shutdown() override;
	virtual std::string nextScene() override;
	virtual bool isEnd() override;

	virtual void addGameObject(GameObject * pAddObject) override;
	virtual void removeGameObject(GameObject * pRemoveObject) override;
	virtual PhysicsWorld * getPhysicsWorld() override;
	virtual Tilemap * getTilemap() override;
	virtual ForceMap * getNMapRead() override;
	virtual ForceMap * getSMapRead() override;
	virtual ForceMap * getNMapWrite() override;
	virtual ForceMap * getSMapWrite() override;
	virtual ObstacleMap * getObstacleMap() override;
	virtual void gameEnd() override;

private:
	GameObjectManager* m_pGameObjectManager;
	PhysicsWorld* m_pPhysicsWorld;

	Player* m_pPlayer;
	TitleBackGround*m_pBackGround;
	PauseObject*m_pPause;
	EventText*m_pText;
	FadeOut*m_pFadeOut;
	TitleFade*m_pFadeIn;
	ExText*m_pExText;
	ButtonTex*m_pButton;
	Hint *m_pHint;
	NameTexture*m_pNameTex;
	BackGround*m_bg;

	bool m_canPause;
	bool m_GameEndFlag;
	Vec2 m_CurrentStage;

	Stage* m_pCurrentStage;

	std::string nScene;

	int NowStageNum;

private:
	void TextUpdate();
	void Pause();
	void ReadRespawnData();
	void Fade();
	void HintUpdate();
};