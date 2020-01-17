#pragma once
#include "Math\Vec2.h"

//タイル画像のタイプ
enum TILE_IMAGE_TYPE
{
	TILE_IMAGE_TYPE_NONE,

	TILE_IMAGE_TYPE_UP,			//上
	TILE_IMAGE_TYPE_DOWN,		//下
	TILE_IMAGE_TYPE_RIGHT,		//右
	TILE_IMAGE_TYPE_LEFT,		//左

	TILE_IMAGE_TYPE_UPRIGHT,	//右上
	TILE_IMAGE_TYPE_UPLEFT,		//左上
	TILE_IMAGE_TYPE_DOWNRIGHT,	//右下
	TILE_IMAGE_TYPE_DOWNLEFT,	//左下

	TILE_IMAGE_TYPE_UPCORNER,	 //上向きコの字
	TILE_IMAGE_TYPE_DOWNCORNER,	 //下向きコの字
	TILE_IMAGE_TYPE_RIGHTCORNER, //右向きコの字
	TILE_IMAGE_TYPE_LEFTCORNER,	 //左向きコの字

	TILE_IMAGE_TYPE_UPCOLUMN,	 //上向きニの字
	TILE_IMAGE_TYPE_DOWNCOLUMN,	 //下向きニの字
	TILE_IMAGE_TYPE_RIGHTCOLUMN, //右向きニの字
	TILE_IMAGE_TYPE_LEFTCOLUMN,	 //左向きニの字

	TILE_IMAGE_TYPE_CENTER,		//中心
};

struct ImageInfo
{
	Vec2 imageCoord;
	float imageRotation;
};