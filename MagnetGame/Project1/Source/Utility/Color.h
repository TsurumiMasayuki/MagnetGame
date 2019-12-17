#pragma once
#include <DirectXMath.h>

struct Color
{
public:
	Color();
	Color(float r, float g, float b, float a);
	//DirectX::Colors�p
	Color(DirectX::XMVECTOR color);
	~Color();

	DirectX::XMVECTOR toXMFLOAT4() const;

public:
	float r;
	float g;
	float b;
	float a;
};