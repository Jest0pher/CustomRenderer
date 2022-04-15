#include "NormUVCube.h"
NormUVCube::NormUVCube() {
	drawIndices = true;
	translate = XMMatrixIdentity();
}

NormUVCube::NormUVCube(float x, float y, float z) {
	drawIndices = true;
	translate = XMMatrixTranslation(x, y, z);
}

NormUVCube::~NormUVCube() {

}

void NormUVCube::Manipulate() {
	yRot += .01f;
	XMMATRIX temp = translate;
	temp = XMMatrixMultiply(XMMatrixScaling(1, 2, 1), temp);
	temp = XMMatrixMultiply(XMMatrixRotationY(yRot * (3.14f / 180.0f)), temp);

	XMStoreFloat4x4(&wvp.wMatrix, temp);

	(*GetContextPointer())->UpdateSubresource(constantBuffer, 0, nullptr, &wvp, 0, 0);
}

void NormUVCube::Init() {
	vertices.resize(8);

	vertices[0] = { {-.25f, -.25f, -.25f}};
	vertices[1] = { {.25f, -.25f, -.25f}};
	vertices[2] = { {-.25f, -.25f, .25f}};
	vertices[3] = { {.25f, -.25f, .25f}};
	vertices[4] = { {-.25f, .25f, -.25f}};
	vertices[5] = { {.25f, .25f, -.25f}};
	vertices[6] = { {-.25f, .25f, .25f}};
	vertices[7] = { {.25f, .25f, .25f}};

	indices.resize(36);
	indices = { 0,1,2, 2,1,3, 0,4,5, 0,5,1, 1,5,7, 1,7,3, 4,6,7, 4,7,5, 2,6,4, 2,4,0, 3,7,6, 3,6,2 };

	NormUVMesh::Init();
}
