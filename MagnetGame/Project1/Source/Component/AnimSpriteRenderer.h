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

	//�A�j���[�V������ݒ肵�܂��B
	void setAnimation(std::string key);
	//�A�j���[�V������o�^���܂��B
	void addAnimation(std::string key, SpriteAnimation* pSpriteAnim);

private:
	std::string m_CurrentAnimation;									//���݂̃A�j���[�V������
	std::unordered_map<std::string, SpriteAnimation*> m_Animations;	//�o�^����Ă���A�j���[�V�����̃��X�g
};