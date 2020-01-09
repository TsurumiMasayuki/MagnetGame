#pragma once
#include <string>
#include <unordered_map>
#include "SpriteRenderer.h"

class Timer;
class SpriteAnimation;

class AnimSpriteRenderer
	: public SpriteRenderer
{
public:
	AnimSpriteRenderer(GameObject* pUser);
	~AnimSpriteRenderer();

	virtual void onStart() override;
	virtual void onUpdate() override;
	virtual TypeID getType() const override;

	//アニメーションを設定します。
	void setAnimation(std::string key);
	//アニメーションを登録します。
	void addAnimation(std::string key, SpriteAnimation* pSpriteAnim);

private:
	std::string m_CurrentAnimation;									//現在のアニメーション名
	std::unordered_map<std::string, SpriteAnimation*> m_Animations;	//登録されているアニメーションのリスト
};