#include "Renderer.h"



Renderer::Renderer() {
	SetDevicePointer(&device);
	SetContextPointer(&context);
	SetSwapChainPointer(&swapChain);
	SetRenderTargetPointer(&renderTarget);
	SetViewportPointer(&viewport);
	SetWVPPointer(&viewProjection);

}

Renderer::~Renderer() {
	device->Release();
	swapChain->Release();
	context->Release();
	renderTarget->Release();
}

void Renderer::Draw() {
	float color[4] = { 0.5f,0.5f,0.5f,1.0f };

	context->ClearRenderTargetView(renderTarget, color);

	context->OMSetRenderTargets(1, &renderTarget, nullptr);
	context->RSSetViewports(1, &viewport);

	for (int i = 0; i < objects.size(); i++) {
		objects[i]->Draw();
	}

	swapChain->Present(0, 0);
}

void Renderer::InitRenderer(HWND windowHandle) {
	D3D_FEATURE_LEVEL dx11 = D3D_FEATURE_LEVEL_11_0;

	RECT windowRect;
	GetClientRect(windowHandle, &windowRect);

	//swapchain description
	DXGI_SWAP_CHAIN_DESC swap;
	ZeroMemory(&swap, sizeof(DXGI_SWAP_CHAIN_DESC));
	swap.BufferCount = 1;
	swap.OutputWindow = windowHandle;
	swap.Windowed = true;
	swap.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swap.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swap.BufferDesc.Width = windowRect.right - windowRect.left;
	swap.BufferDesc.Height = windowRect.bottom - windowRect.top;
	swap.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swap.SampleDesc.Count = 1;
	swap.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	

	//create device and swapchain
	//remove the debug flag
	HRESULT hr;

	UINT createDeviceFlags = 0;

#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, &dx11, 1, D3D11_SDK_VERSION, &swap, &swapChain, &device, 0, &context);

	//Render Target
	ID3D11Resource* backBuffer;
	hr = swapChain->GetBuffer(0, __uuidof(backBuffer), (void**)&backBuffer);
	hr = device->CreateRenderTargetView(backBuffer, nullptr, &renderTarget);
	backBuffer->Release();

	//Viewport
	viewport.Width = swap.BufferDesc.Width;
	viewport.Height = swap.BufferDesc.Height;
	viewport.TopLeftX = viewport.TopLeftY = 0;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;

	ZeroMemory(&viewProjection, sizeof(WVP));
	XMMATRIX temp = XMMatrixIdentity();
	XMStoreFloat4x4(&viewProjection.wMatrix, temp);
	temp = XMMatrixLookAtLH({ 0, .5f, -1 }, { 0,0,1 }, { 0,1,0 });
	XMStoreFloat4x4(&viewProjection.vMatrix, temp);
	temp = XMMatrixPerspectiveFovLH(90 * (3.14f / 180.0f), viewport.Width / viewport.Height, .1f, 100.0f);
	XMStoreFloat4x4(&viewProjection.pMatrix, temp);
	
}