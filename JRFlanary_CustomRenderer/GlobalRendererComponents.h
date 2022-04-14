#pragma once

#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#include "WVP.h"

ID3D11Device** GetDevicePointer();
ID3D11DeviceContext** GetContextPointer();
IDXGISwapChain** GetSwapChainPointer();
ID3D11RenderTargetView** GetRenderTargetPointer();
D3D11_VIEWPORT* GetViewportPointer();
WVP* GetWVPPointer();

void SetDevicePointer(ID3D11Device** _device);
void SetContextPointer(ID3D11DeviceContext** _context);
void SetSwapChainPointer(IDXGISwapChain** _swapChain);
void SetRenderTargetPointer(ID3D11RenderTargetView** _renderTarget);
void SetViewportPointer(D3D11_VIEWPORT* _viewport);
void SetWVPPointer(WVP* _wvp);
