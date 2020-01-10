#pragma once
#include "Math\Vec2.h"

class GameInput
{
public:
	//横方向の移動入力を返します。
	static float getHorizontal();
	//縦方向の移動入力を返します。
	static float getVertical();

	//S極パンチの入力がされたかどうか返します。
	static bool isMagChange();
	//S極パンチの方向を返します。
	static Vec2 getMagChangeDir();

	//ジャンプ入力がされたかどうか返します。
	static bool isJump();

private:
	GameInput();	//インスタンスの生成を禁止
};