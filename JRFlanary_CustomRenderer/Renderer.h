#pragma once

//#include <Windows.h>
//#include <d3d11.h>
//#pragma comment(lib, "d3d11.lib")
#include "RenderableObject.h"

class Renderer {	
public:
	ID3D11Device* device;
	IDXGISwapChain* swapChain;
	ID3D11DeviceContext* context;
	ID3D11RenderTargetView* renderTarget;
	D3D11_VIEWPORT viewport;
	WVP viewProjection;
	std::vector<RenderableObject*> objects;

	Renderer();
	~Renderer();
	void Draw();
	void InitRenderer(HWND windowHandle);

	
};
