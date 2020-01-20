#pragma once
#include "AbstractScene.h"
#include "Actor\IGameMediator.h"

class GameObjectManager;
class Deliveryman;
class TitlePlayer;
class ObjN;
class TitleBackGround;
class TitleFade;
class EventText;
class TitleLogo;
class TitleHane;
class Title_Sprite;
class Title_Cloud;
class Timer;
class SmokeEffect;
class Letter;
class ButtonTex;

class Title :
	public AbstractScene, IGameMediator {
public:
	Title();
	~Title();
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
	GameObjectManager*m_pGameObjectManager;
	Deliveryman*m_pDeliveryman;
	TitlePlayer*m_pTitlePlayer;
	PhysicsWorld* m_pPhysicsWorld;
	ObjN *m_pObjN;
	TitleBackGround*m_pBackGround;
	TitleLogo*m_pTitleLogo;
	TitleFade*m_pFade;
	EventText*m_pText;
	TitleHane*hane;
	Title_Sprite*title_sprite;
	Title_Cloud*title_cloud;
	Timer * timer;
	Timer * smoketimer;
	SmokeEffect*smokeEffect;
	Letter*m_pLetter;
	ButtonTex*m_pButton;

	enum SceneState
	{
		Idle,
		Delivery,
		Player,
		Fade,
	};
	SceneState sState;

	bool m_pTitleEndFlag;
	int Cnt;
	float Alpha;
};