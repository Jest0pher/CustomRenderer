#pragma once

#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

#include <vector>
#include "GlobalRendererComponents.h"
#include "WVP.h"

class RenderableObject {
public:
	virtual HRESULT CreateVertexBuffer() = 0;
	virtual HRESULT CreateIndexBuffer() = 0;
	virtual HRESULT CreateInputLayout() = 0;
	virtual HRESULT CreateVertexShader() = 0;
	virtual HRESULT CreatePixelShader() = 0;
	virtual void Draw() = 0;
	virtual void Init() = 0;
};