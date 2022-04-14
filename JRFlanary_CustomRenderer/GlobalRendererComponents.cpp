#include "GlobalRendererComponents.h"

ID3D11Device** device = nullptr;
IDXGISwapChain** swapChain = nullptr;
ID3D11DeviceContext** context = nullptr;
ID3D11RenderTargetView** renderTarget = nullptr;
D3D11_VIEWPORT* viewport = nullptr;
WVP* viewProjection = nullptr;

ID3D11Device** GetDevicePointer() {
	return device;
}
ID3D11DeviceContext** GetContextPointer() {
	return context;
}
IDXGISwapChain** GetSwapChainPointer() {
	return swapChain;
}
ID3D11RenderTargetView** GetRenderTargetPointer() {
	return renderTarget;
}
D3D11_VIEWPORT* GetViewportPointer() {
	return viewport;
}
WVP* GetWVPPointer() {
	return viewProjection;
}

void SetDevicePointer(ID3D11Device** _device) {
	device = _device;
}
void SetContextPointer(ID3D11DeviceContext** _context) {
	context = _context;
}
void SetSwapChainPointer(IDXGISwapChain** _swapChain) {
	swapChain = _swapChain;
}
void SetRenderTargetPointer(ID3D11RenderTargetView** _renderTarget) {
	renderTarget = _renderTarget;
}
void SetViewportPointer(D3D11_VIEWPORT* _viewport) {
	viewport = _viewport;
}
void SetWVPPointer(WVP* _wvp) {
	viewProjection = _wvp;
}
