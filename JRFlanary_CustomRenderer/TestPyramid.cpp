#include "TestPyramid.h"

TestPyramid::TestPyramid() {
	translate = XMMatrixIdentity();
}

TestPyramid::TestPyramid(float x, float y, float z) {
	translate = XMMatrixTranslation(x, y, z);
}

TestPyramid::~TestPyramid() {
}

void TestPyramid::Manipulate() {
	yRot += .01f;
	XMMATRIX temp = translate;
	temp = XMMatrixMultiply(XMMatrixRotationY(yRot * (3.14f / 180.0f)), temp);

	XMStoreFloat4x4(&wvp.wMatrix, temp);

	(*GetContextPointer())->UpdateSubresource(constantBuffer, 0, nullptr, &wvp, 0, 0);
}

void TestPyramid::Init() {
	vertices.resize(5);

	vertices[0] = { {-.25f, -.25f, -.25f, 1}, {0,1,0,1} };
	vertices[1] = { {.25f, -.25f, -.25f, 1}, {1,0,0,1} };
	vertices[2] = { {-.25f, -.25f, .25f, 1}, {0,0,1,1} };
	vertices[3] = { {.25f, -.25f, .25f, 1}, {0,1,0,1} };
	vertices[4] = { {0.0f, .25f, 0.0f, 1}, {0,1,0,1} };

	indices.resize(18);
	indices = { 0,1,2,1,2,0,0,4,1,1,4,3,3,4,2,2,4,0 };

	TestMesh::Init();
}
