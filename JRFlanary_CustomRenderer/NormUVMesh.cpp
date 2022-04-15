#include "NormUVMesh.h"

NormUVMesh::~NormUVMesh() {
	vertices.clear();
	vertexBuffer->Release();
	if (drawIndices) {
		indexBuffer->Release();
	}
	constantBuffer->Release();
	vertexShader->Release();
	pixelShader->Release();
	inputLayout->Release();
}

HRESULT NormUVMesh::CreateVertexBuffer() {
	D3D11_BUFFER_DESC buffDesc;
	D3D11_SUBRESOURCE_DATA subData;
	ZeroMemory(&buffDesc, sizeof(D3D11_BUFFER_DESC));
	ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));

	buffDesc.ByteWidth = sizeof(NormUVVert) * vertices.size();
	buffDesc.StructureByteStride = 0;
	buffDesc.Usage = D3D11_USAGE_DEFAULT;
	buffDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buffDesc.CPUAccessFlags = 0;
	buffDesc.MiscFlags = 0;

	subData.pSysMem = vertices.data();

	return (*GetDevicePointer())->CreateBuffer(&buffDesc, &subData, &vertexBuffer);
}

HRESULT NormUVMesh::CreateIndexBuffer() {
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

HRESULT NormUVMesh::CreateInputLayout() {
	D3D11_INPUT_ELEMENT_DESC testInputLayout[] = {
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	return (*GetDevicePointer())->CreateInputLayout(testInputLayout, 3, NormUVVertexShader, sizeof(NormUVVertexShader), &inputLayout);
}

HRESULT NormUVMesh::CreateVertexShader() {

	return (*GetDevicePointer())->CreateVertexShader(NormUVVertexShader, sizeof(NormUVVertexShader), nullptr, &vertexShader);
}

HRESULT NormUVMesh::CreatePixelShader() {
	return (*GetDevicePointer())->CreatePixelShader(NormUVPixelShader, sizeof(NormUVPixelShader), nullptr, &pixelShader);
}

HRESULT NormUVMesh::CreateConstantBuffer() {
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

void NormUVMesh::Draw() {
	(*GetContextPointer())->IASetInputLayout(inputLayout);

	UINT strides[] = { sizeof(NormUVVert) };
	UINT offsets[] = { 0 };
	(*GetContextPointer())->IASetVertexBuffers(0, 1, &vertexBuffer, strides, offsets);
	if (drawIndices) {
		(*GetContextPointer())->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	}
	(*GetContextPointer())->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	(*GetContextPointer())->VSSetShader(vertexShader, nullptr, 0);
	(*GetContextPointer())->PSSetShader(pixelShader, nullptr, 0);

	Manipulate();

	(*GetContextPointer())->VSSetConstantBuffers(0, 1, &constantBuffer);

	if (drawIndices) {
		(*GetContextPointer())->DrawIndexed(indices.size(), 0, 0);
	}
	else {
	
		(*GetContextPointer())->Draw(vertices.size(), 0);
	}

}

void NormUVMesh::Init() {
	wvp.vMatrix = GetWVPPointer()->vMatrix;
	wvp.pMatrix = GetWVPPointer()->pMatrix;

	HRESULT hr;
	hr = CreateVertexShader();
	if (drawIndices) {
		hr = CreateIndexBuffer();
	}
	hr = CreatePixelShader();
	hr = CreateVertexBuffer();
	hr = CreateInputLayout();
	hr = CreateConstantBuffer();
}
