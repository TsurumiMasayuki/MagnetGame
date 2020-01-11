#pragma once
#include <string>
#include "Math\RectF.h"
#include "Math\Vec2.h"

class Timer;

//2Dスプライト用アニメーションクラス
class SpriteAnimation
{
public:
	//コンストラクタ
	SpriteAnimation(std::string textureName, float textureWidth, float textureHeight, float animTime, int animCount, int yPos = 0);
	~SpriteAnimation();

	//リセット
	void reset();
	//更新
	void update();

	//テクスチャ名を返します。
	std::string getTextureName();
	//アニメーションの現在の切り取り位置を返します。
	RectF getAnimRect();
	//Pivotを返します。
	Vec2 getPivot();

private:
	std::string m_TextureName;	//画像の名前

	Timer* m_pTimer;		//画像切り替え間隔用タイマー

	int m_XPos;				//フレーム上の現在位置(横)
	int m_YPos;				//フレーム上の現在位置(縦)

	int m_AnimCount;		//フレーム数

	float m_PivotX;			//ピボット
	float m_PivotY;			//ピボット

	float m_CellWidth;		//切り取りサイズ(横)
	float m_CellHeight;		//切り取りサイズ(縦)
	float m_TextureWidth;	//画像サイズ(横)
	float m_TextureHeight;	//画像サイズ(縦)
};