#pragma once
#include <DirectXMath.h>
using namespace DirectX;
struct WVP {
	XMFLOAT4X4 wMatrix;
	XMFLOAT4X4 vMatrix;
	XMFLOAT4X4 pMatrix;
};

