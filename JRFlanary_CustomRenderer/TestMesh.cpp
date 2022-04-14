#include "TestMesh.h"

TestMesh::~TestMesh() {
	vertices.clear();
	vertexBuffer->Release();
	indexBuffer->Release();
	constantBuffer->Release();
	vertexShader->Release();
	pixelShader->Release();
	inputLayout->Release();
}

HRESULT TestMesh::CreateVertexBuffer() {
	D3D11_BUFFER_DESC buffDesc;
	D3D11_SUBRESOURCE_DATA subData;
	ZeroMemory(&buffDesc, sizeof(D3D11_BUFFER_DESC));
	ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));

	buffDesc.ByteWidth = sizeof(TestVert)*vertices.size();
	buffDesc.StructureByteStride = 0;
	buffDesc.Usage = D3D11_USAGE_DEFAULT;
	buffDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buffDesc.CPUAccessFlags = 0;
	buffDesc.MiscFlags = 0;

	subData.pSysMem = vertices.data();

	return (*GetDevicePointer())->CreateBuffer(&buffDesc, &subData, &vertexBuffer);
}

HRESULT TestMesh::CreateIndexBuffer(){
	D3D11_BUFFER_DESC buffDesc;
	D3D11_SUBRESOURCE_DATA subData;
	ZeroMemory(&buffDesc, sizeof(D3D11_BUFFER_DESC));
	ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));

	buffDesc.ByteWidth = sizeof(int) * indices.size();
	buffDesc.StructureByteStride = 0;
	buffDesc.Usage = D3D11_USAGE_DEFAULT;
	buffDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	buffDesc.CPUAccessFlags = 0;
	buffDesc.MiscFlags = 0;

	subData.pSysMem = indices.data();

	return (*GetDevicePointer())->CreateBuffer(&buffDesc, &subData, &indexBuffer);
}

HRESULT TestMesh::CreateInputLayout() {
	D3D11_INPUT_ELEMENT_DESC testInputLayout[] = {
		{"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	return (*GetDevicePointer())->CreateInputLayout(testInputLayout, 2, TestVertexShader, sizeof(TestVertexShader), &inputLayout);
}

HRESULT TestMesh::CreateVertexShader() {

	return (*GetDevicePointer())->CreateVertexShader(TestVertexShader, sizeof(TestVertexShader), nullptr, &vertexShader);
}

HRESULT TestMesh::CreatePixelShader() {
	return (*GetDevicePointer())->CreatePixelShader(TestPixelShader, sizeof(TestPixelShader), nullptr, &pixelShader);
}

HRESULT TestMesh::CreateConstantBuffer() {
	D3D11_BUFFER_DESC buffDesc;
	D3D11_SUBRESOURCE_DATA subData;
	ZeroMemory(&buffDesc, sizeof(D3D11_BUFFER_DESC));
	ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));
	buffDesc.ByteWidth = sizeof(WVP);
	buffDesc.StructureByteStride = 0;
	buffDesc.Usage = D3D11_USAGE_DEFAULT;
	buffDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buffDesc.CPUAccessFlags = 0;
	buffDesc.MiscFlags = 0;

	XMMATRIX temp = XMMatrixIdentity();

	XMStoreFloat4x4(&wvp.wMatrix, temp);

	return (*GetDevicePointer())->CreateBuffer(&buffDesc, nullptr, &constantBuffer);
}

void TestMesh::Draw() {
	(*GetContextPointer())->IASetInputLayout(inputLayout);

	UINT strides[] = { sizeof(TestVert) };
	UINT offsets[] = { 0 };
	(*GetContextPointer())->IASetVertexBuffers(0, 1, &vertexBuffer, strides, offsets);
	(*GetContextPointer())->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	(*GetContextPointer())->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	(*GetContextPointer())->VSSetShader(vertexShader, nullptr, 0);
	(*GetContextPointer())->PSSetShader(pixelShader, nullptr, 0);

	Manipulate();

	(*GetContextPointer())->VSSetConstantBuffers(0, 1, &constantBuffer);

	(*GetContextPointer())->DrawIndexed(indices.size(), 0, 0);

}

void TestMesh::Init() {
	wvp.vMatrix = GetWVPPointer()->vMatrix;
	wvp.pMatrix = GetWVPPointer()->pMatrix;

	HRESULT hr;
	hr = CreateVertexShader();
	hr = CreateIndexBuffer();
	hr = CreatePixelShader();
	hr = CreateVertexBuffer();
	hr = CreateInputLayout();
	hr = CreateConstantBuffer();
}

